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

#ifndef _MACH_CLKPWR_H
#define _MACH_CLKPWR_H

#define CLKPWR_BASE (0xC000F000)

#define CLKPWR_REG(x) (x)

#define CLKPWR_CLKMODE				CLKPWR_REG(0x00)
#define CLKPWR_CLKMODE_PLL1PWDN			(1 << 30)
#define CLKPWR_CLKMODE_BCLKSEL_MASK		(0x3 << 24)
#define CLKPWR_CLKMODE_BCLKSEL_PLL0		(0 << 24)
#define CLKPWR_CLKMODE_BCLKSEL_PLL1		(1 << 24)
#define CLKPWR_CLKMODE_BCLKDIV_MASK		(0xF << 20)
#define CLKPWR_CLKMODE_BCLKDIV(_x)		(_x << 20)
#define CLKPWR_CLKMODE_AHBDIV_MASK		(0xF << 6)
#define CLKPWR_CLKMODE_AHBDIV(_x)		(_x << 6)
#define CLKPWR_CLKMODE_CPUSEL_MASK		(0x3 << 4)
#define CLKPWR_CLKMODE_CPUSEL_PLL0		(0 << 24)
#define CLKPWR_CLKMODE_CPUSEL_PLL1		(1 << 24)
#define CLKPWR_CLKMODE_CPUDIV_MASK		(0xF << 0)
#define CLKPWR_CLKMODE_CPUDIV(_x)		(_x << 0)
#define CLKPWR_PLL0				CLKPWR_REG(0x04)
#define CLKPWR_PLL1				CLKPWR_REG(0x08)
#define CLKPWR_GPIOWAKE				CLKPWR_REG(0x40)
#define CLKPWR_RTCWAKE				CLKPWR_REG(0x44)
#define CLKPWR_WAKERISE				CLKPWR_REG(0x48)
#define CLKPWR_WAKEFALL				CLKPWR_REG(0x4C)
#define CLKPWR_WAKEPEND				CLKPWR_REG(0x50)
#define CLKPWR_INTPENDSPAD			CLKPWR_REG(0x58)
#define CLKPWR_RSTSTATUS			CLKPWR_REG(0x5C)
#define CLKPWR_INTENB				CLKPWR_REG(0x60)
#define CLKPWR_PWRMODE				CLKPWR_REG(0x7C)
#define CLKPWR_PWRMODE_CHGPLL			(1 << 15)
#define CLKPWR_PWRMODE_GPIOSWRSTENB		(1 << 13)
#define CLKPWR_PWRMODE_SWRST			(1 << 12)
#define CLKPWR_PWRMODE_LASTPWRMODE_MASK		(0x7 << 4)
#define CLKPWR_PWRMODE_LASTWRMODE_NORMAL	(0 << 4)
#define CLKPWR_PWRMODE_LASTPWRMODE_IDLE		(1 << 4)
#define CLKPWR_PWRMODE_LASTPWRMODE_STOP		(2 << 4)
#define CLKPWR_PWRMODE_CURPWRMODE_MASK		(0x3 << 0)
#define CLKPWR_PWRMODE_CURPWRMODE_NORMAL	(0 << 0)
#define CLKPWR_PWRMODE_CURPWRMODE_IDLE		(1 << 0)
#define CLKPWR_PWRMODE_CURPWRMODE_STOP		(2 << 0)
#define CLKPWR_GPIOADRVL			CLKPWR_REG(0x100)
#define CLKPWR_GPIOADRVH			CLKPWR_REG(0x104)
#define CLKPWR_GPIOBDRVL			CLKPWR_REG(0x108)
#define CLKPWR_GPIOBDRVH			CLKPWR_REG(0x10C)
#define CLKPWR_GPIOCDRVL			CLKPWR_REG(0x110)
#define CLKPWR_GPIOCDRVH			CLKPWR_REG(0x114)
#define CLKPWR_BUSDRV				CLKPWR_REG(0x118)

#define CLKPWR_PLL(pdiv, mdiv, sdiv) \
	((pdiv << 18) | (mdiv << 8) | (sdiv << 0))

#endif /* _MACH_CLKPWR_H */

