/*
 * Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
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

#ifndef _MACH_TIMER_H
#define _MACH_TIMER_H

#define TIMER0_BASE (0xC0001800)
#define TIMER1_BASE (0xC0001880)
#define TIMER2_BASE (0xC0001900)
#define TIMER3_BASE (0xC0001980)
#define TIMER4_BASE (0xC0001A00)

#define TIMER_REG(x) (x)

#define TIMER_COUNT				TIMER_REG(0x00)
#define TIMER_MATCH				TIMER_REG(0x04)
#define TIMER_CONTROL				TIMER_REG(0x08)
#define TIMER_CONTROL_LDCNT			(1 << 6)
#define TIMER_CONTROL_INTPEND			(1 << 5)
#define TIMER_CONTROL_INTENB			(1 << 4)
#define TIMER_CONTROL_RUN			(1 << 3)
#define TIMER_CONTROL_WDENB			(1 << 2)
#define TIMER_CONTROL_SELTCLK_MASK		(3 << 0)
#define TIMER_CONTROL_SELTCLK_1			(3 << 0)
#define TIMER_CONTROL_SELTCLK_2			(0 << 0)
#define TIMER_CONTROL_SELTCLK_4			(1 << 0)
#define TIMER_CONTROL_SELTCLK_8			(2 << 0)
#define TIMER_CLKENB				TIMER_REG(0x40)
#define TIMER_CLKENB_TCLKMODE			(1 << 3)
#define TIMER_CLKENB_CLKGENENB			(1 << 2)
#define TIMER_CLKGEN				TIMER_REG(0x44)
#define TIMER_CLKGEN_CLKDIV_MASK		(0xFF << 4)
#define TIMER_CLKGEN_CLKDIV(_x)			(_x << 4)
#define TIMER_CLKGEN_CLKSRCSEL_MASK		(7 << 1)
#define TIMER_CLKGEN_CLKSRCSEL_PLL0		(0 << 1)
#define TIMER_CLKGEN_CLKSRCSEL_PLL1		(1 << 1)

#endif /* _MACH_TIMER_H */
