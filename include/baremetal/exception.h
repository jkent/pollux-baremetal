/*
 * Copyright (C) 2013-2020 Jeff Kent <jeff@jkent.net>
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

#pragma once

#include <asm/types.h>

#define EXC_RESET (0)
#define EXC_UNDEFINED (1)
#define EXC_SWI (2)
#define EXC_PREFETCH_ABORT (3)
#define EXC_DATA_ABORT (4)
#define EXC_RESERVED (5)
#define EXC_IRQ (6)
#define EXC_FIQ (7)

typedef void (*irq_handler_t)(void);

void init_interrupts(void);
void interrupt_handler(u64 pending);
void enable_interrupts(void);
void disable_interrupts(void);

void install_exc(u8 num, irq_handler_t handler);
void install_irq(u8 num, irq_handler_t handler);
void install_swi(u8 num, irq_handler_t handler);
