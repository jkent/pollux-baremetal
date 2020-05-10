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

#pragma once

#include <asm/types.h>

typedef void (*irq_handler_t)(void);

extern u32 *ivt_tlb[0x400];
extern u32 *ivt_phys[0x400];

extern irq_handler_t *swi_handlers;
extern irq_handler_t *irq_handlers;

void init_interrupts(void);
void interrupt_handler(u64 pending);
void enable_interrupts(void);
void disable_interrupts(void);

void reset_handler(void);
void undef_handler(void);
void swi_handler(void);
void pabort_handler(void);
void dabort_handler(void);
void reserved_handler(void);
void irq_handler(void);
void fiq_handler(void);
