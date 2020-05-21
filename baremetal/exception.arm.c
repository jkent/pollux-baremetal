/*
 * Copyright (C) 2020 Jeff Kent <jeff@jkent.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <asm/io.h>
#include <baremetal/exception.h>
#include <baremetal/linker.h>
#include <driver/uart.h>
#include <mach/irq.h>
#include <stdlib.h>

#define STR(x) #x
#define XSTR(s) STR(s)

static irq_handler_t *exc_table = NULL;
static irq_handler_t *irq_table = (irq_handler_t *)&_irq_table;
static irq_handler_t *swi_table = (irq_handler_t *)&_swi_table;

static const uint8_t magic_lut[64] asm ("magic_lut") = {
	 0,  1,  2, 53,  3,  7, 54, 27,  4, 38, 41,  8, 34, 55, 48, 28,
	62,  5, 39, 46, 44, 42, 22,  9, 24, 35, 59, 56, 49, 18, 29, 11,
	63, 52,  6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
	51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
};

__attribute__((interrupt("SWI"), naked))
void swi_handler(void)
{
	asm("push {r0-r1, lr}\n\t"
		"mrs r0, spsr\n\t"
		"tst r0, #(1<<5)\n\t"
		"ldrneh r0, [lr, #-2]\n\t"
		"ldreq r0, [lr, #-4]\n\t"
		"bic r0, r0, #0xFFFFFF00\n\t"
		"ldr r1, =_swi_table\n\t"
		"ldr r1, [r1, r0, LSL#2]\n\t"
		"cmp r1, #0\n\t"
		"strne r1, [sp, #8]\n\t"
		"pop {r0-r1, pc}\n"
	".ltorg");
}

__attribute__((interrupt("ABORT")))
void pabort_handler(void)
{
	uart0_writeb('p');
	uart0_writeb('!');
}

__attribute__((interrupt("ABORT")))
void dabort_handler(void)
{
	uart0_writeb('d');
	uart0_writeb('!');
}

__attribute__((interrupt("IRQ")))
void irq_handler(void)
{
	void __iomem *irq = (void __iomem *)IRQ_BASE;
	u64 pending = readq(irq + IRQ_PENDL) & 0xFFFFFFFFFFFULL;
	u8 n = magic_lut[(u64)(pending * 0x022FDD63CC95386DULL) >> 58];
	if (irq_table[n] != NULL) {
		irq_table[n]();
	}
	writeq(pending, irq + IRQ_PENDL);
}

void init_exceptions(void)
{
	asm("ldr r0, =_stack_top\n\t"
		"msr cpsr_c, #0xD1\n\t" /* fiq */
		"mov sp, r0\n\t"
		"sub r0, r0, #" XSTR(CONFIG_BAREMETAL_FIQ_STACK_SIZE) "\n\t"
		"msr cpsr_c, #0xD2\n\t" /* irq */
		"mov sp, r0\n\t"
		"sub r0, r0, #" XSTR(CONFIG_BAREMETAL_IRQ_STACK_SIZE) "\n\t"
		"msr cpsr_c, #0xD7\n\t" /* abt */
		"mov sp, r0\n\t"
		"sub r0, r0, #" XSTR(CONFIG_BAREMETAL_ABT_STACK_SIZE) "\n\t"
		"msr cpsr_c, #0xDB\n\t" /* und */
		"mov sp, r0\n\t"
		"sub r0, r0, #" XSTR(CONFIG_BAREMETAL_UND_STACK_SIZE) "\n\t"
		"msr cpsr_c, #0xD3\n\t" ::: "r0"); /* svc */

	void *exc_base;
#if !defined(CONFIG_BAREMETAL_MMU)
	exc_base = (void *)0x00000000;
#else

#define CR_V (1 << 13)
	/* set high exceptions */
	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr));
	cr |= CR_V;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));

	exc_base = (void *)&_exc_phys;
#endif
	exc_table = (irq_handler_t *)(exc_base + 0x20);
	for (int i = 0; i < 8; i++) {
		u32 *vect = (u32 *)exc_base + i;
		*vect = 0xE59FF018; /* ldr pc, [pc, #24] */
		*((u32 *)(exc_table) + i) = (u32)vect;
	}

	install_exc(EXC_SWI, swi_handler);
	install_exc(EXC_PREFETCH_ABORT, pabort_handler);
	install_exc(EXC_DATA_ABORT, dabort_handler);
	install_exc(EXC_IRQ, irq_handler);
}

void install_exc(u8 num, irq_handler_t handler)
{
	if (num >= 8) {
		return;
	}
	exc_table[num] = handler;
}

void install_irq(u8 num, irq_handler_t handler)
{
	if (num >= 64) {
		return;
	}
	irq_table[num] = handler;
}

void install_swi(u8 num, irq_handler_t handler)
{
	swi_table[num] = handler;
}
