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

#pragma once

#define TIMER0_BASE (0xC0001800)
#define TIMER1_BASE (0xC0001880)
#define TIMER2_BASE (0xC0001900)
#define TIMER3_BASE (0xC0001980)
#define TIMER4_BASE (0xC0001A00)

#define TIMER_REG(x) (x)

#define TIMER_TMRCOUNT      TIMER_REG(0x00)
#define TIMER_TMRMATCH      TIMER_REG(0x04)
#define TIMER_TMRCONTROL    TIMER_REG(0x08)
#define TIMER_LDCNT         (1 << 6)
#define TIMER_INTPEND       (1 << 5)
#define TIMER_INTENB        (1 << 4)
#define TIMER_RUN           (1 << 3)
#define TIMER_WDENB         (1 << 2)
#define TIMER_SELTCLK(_x)   (_x << 0)
#define TIMER_TMRCLKENB     TIMER_REG(0x40)
#define TIMER_TCLKMODE      (1 << 3)
#define TIMER_CLKGENENB     (1 << 2)
#define TIMER_TMRCLKGEN     TIMER_REG(0x44)
#define TIMER_CLKDIV(_x)    (_x << 4)
#define TIMER_CLKSRCSEL(_x) (_x << 1)
