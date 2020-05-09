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

#include <baremetal/interrupt.h>
#include <stddef.h>

interrupt_handler_t irq_handlers[64] = {0};

static const uint8_t magic_lut[64] = {
	 0,  1,  2, 53,  3,  7, 54, 27,  4, 38, 41,  8, 34, 55, 48, 28,
	62,  5, 39, 46, 44, 42, 22,  9, 24, 35, 59, 56, 49, 18, 29, 11,
	63, 52,  6, 26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
	51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12
};

typedef struct {
	u32 reset;
	u32 undef;
	u32 swi;
	u32 pabort;
	u32 dabort;
	u32 reserved;
	u32 irq;
	u32 fiq;
} vector_table_t;

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
}

__attribute__((interrupt("FIQ"), weak))
void fiq_handler(void)
{
}

void setup_vector_table(void)
{
	u32 *branches = (u32 *)0x00000000;
	for (int i = 0; i < 8; i++) {
		branches[i] = 0xE59FF018; /* ldr pc, [pc, #24] */
	}

	u32 *vectors = (void *)0x00000020;
	vectors[0] = (u32)reset_handler;
	vectors[1] = (u32)undef_handler;
	vectors[2] = (u32)swi_handler;
	vectors[3] = (u32)pabort_handler;
	vectors[4] = (u32)dabort_handler;
	vectors[5] = (u32)reserved_handler;
	vectors[6] = (u32)irq_handler;
	vectors[7] = (u32)fiq_handler;
}

/* pending is guaranteed to have only one bit set at a time */
void interrupt_handler(u64 pending)
{
	interrupt_handler_t handler;
	uint8_t interrupt;

	pending &= 0x00000FFFFFFFFFFFull;
	interrupt = magic_lut[(uint64_t)(pending * 0x022fdd63cc95386dull) >> 58];
	handler = interrupt_handlers[interrupt];
	if (handler != NULL) {
		handler();
	}
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
