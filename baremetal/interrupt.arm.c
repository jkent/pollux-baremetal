/*
 * Copyright (C) 2013-2020 Jeff Kent <jeff@jkent.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

#define CR_V (1 << 13)

#include <asm/io.h>
#include <mach/interrupt.h>
#include <baremetal/interrupt.h>
#include <stddef.h>

irq_handler_t *swi_handlers;
irq_handler_t *irq_handlers;
u32 *ivt;

static const uint8_t magic_lut[64] = {
	 0,  1,  2, 53,  3,  7, 54, 27,  4, 38, 41,  8, 34, 55, 48, 28,
	62,  5, 39, 46, 44, 42, 22,  9, 24, 35, 59, 56, 49, 18, 29, 11,
	63, 52,  6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
	51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
};

__attribute__((interrupt, weak))
void reset_handler(void)
{
}

__attribute__((interrupt("UNDEF"), weak))
void undef_handler(void)
{
}

__attribute__((interrupt("SWI"), weak))
void swi_handler(void)
{
	u32 swi;
	asm("ldr %0, [lr, #-4]" : "=r" (swi));
	swi &= ~0x000003FF;
	irq_handler_t handler = swi_handlers[swi];
	if (handler != NULL) {
		handler();
	}
}

__attribute__((interrupt("ABORT"), weak))
void pabort_handler(void)
{
}

__attribute__((interrupt("ABORT"), weak))
void dabort_handler(void)
{
}

__attribute__((interrupt, weak))
void reserved_handler(void)
{
}

__attribute__((interrupt("IRQ"), weak))
void irq_handler(void)
{
	u32 pendh = readl(IRQ_BASE + IRQ_PENDH) & 0x00000FFF;
	u32 pendl = readl(IRQ_BASE + IRQ_PENDL);
	u64 pending = (u64)pendh << 32 | pendl;
	uint8_t irq = magic_lut[(uint64_t)(pending * 0x022FDD63CC95386DULL) >> 58];

	writel(0, IRQ_BASE + irq < 32 ? IRQ_PENDL : IRQ_PENDH);

	irq_handler_t handler = irq_handlers[irq];
	if (handler != NULL) {
		handler();
	}
}

__attribute__((interrupt("FIQ"), weak))
void fiq_handler(void)
{
}

void init_interrupts(void)
{
	ivt = (u32 *)0xFFFF0000;

	for (int i = 0; i < 8; i++) {
		ivt[i] = 0xE59FF018; /* ldr pc, [pc, #24] */
	}

	ivt[8] = (u32)reset_handler;
	ivt[9] = (u32)undef_handler;
	ivt[10] = (u32)swi_handler;
	ivt[11] = (u32)pabort_handler;
	ivt[12] = (u32)dabort_handler;
	ivt[13] = (u32)reserved_handler;
	ivt[14] = (u32)irq_handler;
	ivt[15] = (u32)fiq_handler;

	swi_handlers = (irq_handler_t *)(ivt + 1024);
	irq_handlers = (irq_handler_t *)(ivt + 2048);

	/* set high vectors */
	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr) :: "cc");
	cr |= CR_V;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));
}

void enable_interrupts(void)
{
	u32 cpsr;
	asm("mrs %0, cpsr" : "=r" (cpsr));
	cpsr &= ~(0x80);
	asm("msr cpsr, %0" :: "r" (cpsr));
}

void disable_interrupts(void)
{
	u32 cpsr;
	asm("mrs %0, cpsr" : "=r" (cpsr));
	cpsr |= 0x80;
	asm("msr cpsr, %0" :: "r" (cpsr));
}
