/*
 * Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
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

#ifndef _MACH_TIMER_H
#define _MACH_TIMER_H

#include <stdint.h>

#define POLLUX_TIMER_BASE 0xC0001800
#define POLLUX_TIMER_OFFSET 0x80
#define POLLUX_TIMER_COUNT 5

struct pollux_timer_regs_t {
	uint32_t count;
	uint32_t match;
	uint32_t control;
	uint32_t _reserved[13];
	uint32_t clkenb;
	uint32_t clkgen;
};

#define pollux_timer(n) ((volatile struct pollux_timer_regs_t *) \
	(POLLUX_TIMER_BASE + (POLLUX_TIMER_OFFSET * (n))))

/* control */
#define TIMER_LDCNT			6
#define TIMER_INTPEND			5
#define TIMER_INTENB			4
#define TIMER_RUN			3
#define TIMER_WDENB			2
#define TIMER_SELTCLK			0

/* clkenb */
#define TIMER_TCLKMODE			3
#define TIMER_CLKGENENB			2

/* clkgen */
#define TIMER_CLKDIV			4
#define TIMER_CLKSRCSEL			1

#endif /* _MACH_TIMER_H */

