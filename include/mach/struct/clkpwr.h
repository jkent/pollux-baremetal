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

#ifndef _MACH_CLKPWR_H
#define _MACH_CLKPWR_H

#include <stdint.h>

#define POLLUX_CLKPWR_BASE 0xC000F000

struct pollux_clkpwr_regs_t {
	uint32_t clkmode;
	uint32_t pllset0;
	uint32_t pllset1;
	uint32_t _reserved[13];
	uint32_t gpiowakeupenb;
	uint32_t rtcwakeupenb;
	uint32_t gpiowakeupriseenb;
	uint32_t gpiowakeupfallenb;
	uint32_t gpiopend;
	uint32_t _reserved2;
	uint32_t intpendspad;
	uint32_t pwrrststatus;
	uint32_t intenb;
	uint32_t _reserved3[6];
	uint32_t pwrmode;
	uint32_t _reserved4[32];
	uint32_t padstrengthgpioal;
	uint32_t padstrengthgpioah;
	uint32_t padstrengthgpiobl;
	uint32_t padstrengthgpiobh;
	uint32_t padstrengthgpiocl;
	uint32_t padstrengthgpioch;
	uint32_t padstrengthbus;
};

#define pollux_clkpwr ((volatile struct pollux_clkpwr_regs_t *) \
	(POLLUX_CLKPWR_BASE))

/* clkmode */
#define CLKPWR_PLLPWDN1			30
#define CLKPWR_CLKSELBCLK		24
#define CLKPWR_CLKDIV1BCLK		20
#define CLKPWR_CLKDIV2CPU0		6
#define CLKPWR_CLKSELCPU0		4
#define CLKPWR_DIVCPU0			0

/* pllset0/1 */
#define CLKPWR_PDIV			18
#define CLKPWR_MDIV			8
#define CLKPWR_SDIV			0

/* gpiowakeupenb */
#define CLKPWR_WKUPEN31			31
#define CLKPWR_WKUPEN30			30
#define CLKPWR_WKUPEN29			29
#define CLKPWR_WKUPEN28			28
#define CLKPWR_WKUPEN27			27
#define CLKPWR_WKUPEN26			26
#define CLKPWR_WKUPEN25			25
#define CLKPWR_WKUPEN24			24
#define CLKPWR_WKUPEN23			23
#define CLKPWR_WKUPEN22			22
#define CLKPWR_WKUPEN21			21
#define CLKPWR_WKUPEN20			20
#define CLKPWR_WKUPEN19			19
#define CLKPWR_WKUPEN18			18
#define CLKPWR_WKUPEN17			17
#define CLKPWR_WKUPEN16			16
#define CLKPWR_WKUPEN15			15
#define CLKPWR_WKUPEN14			14
#define CLKPWR_WKUPEN13			13
#define CLKPWR_WKUPEN12			12
#define CLKPWR_WKUPEN11			11
#define CLKPWR_WKUPEN10			10
#define CLKPWR_WKUPEN9			9
#define CLKPWR_WKUPEN8			8
#define CLKPWR_WKUPEN7			7
#define CLKPWR_WKUPEN6			6
#define CLKPWR_WKUPEN5			5
#define CLKPWR_WKUPEN4			4
#define CLKPWR_WKUPEN3			3
#define CLKPWR_WKUPEN2			2
#define CLKPWR_WKUPEN1			1
#define CLKPWR_WKUPEN0			0

/* rtcwakeupenb */
#define CLKPWR_WKRTC			0

/* gpiowakeupriseenb */
#define CLKPWR_RISEWKSRC31		31
#define CLKPWR_RISEWKSRC30		30 /* reserved */
#define CLKPWR_RISEWKSRC29		29 /* reserved */
#define CLKPWR_RISEWKSRC28		28 /* reserved */
#define CLKPWR_RISEWKSRC27		27
#define CLKPWR_RISEWKSRC26		26
#define CLKPWR_RISEWKSRC25		25
#define CLKPWR_RISEWKSRC24		24
#define CLKPWR_RISEWKSRC23		23
#define CLKPWR_RISEWKSRC22		22
#define CLKPWR_RISEWKSRC21		21
#define CLKPWR_RISEWKSRC20		20
#define CLKPWR_RISEWKSRC19		19
#define CLKPWR_RISEWKSRC18		18
#define CLKPWR_RISEWKSRC17		17
#define CLKPWR_RISEWKSRC16		16
#define CLKPWR_RISEWKSRC15		15
#define CLKPWR_RISEWKSRC14		14
#define CLKPWR_RISEWKSRC13		13
#define CLKPWR_RISEWKSRC12		12
#define CLKPWR_RISEWKSRC11		11
#define CLKPWR_RISEWKSRC10		10
#define CLKPWR_RISEWKSRC9		9
#define CLKPWR_RISEWKSRC8		8
#define CLKPWR_RISEWKSRC7		7
#define CLKPWR_RISEWKSRC6		6
#define CLKPWR_RISEWKSRC5		5
#define CLKPWR_RISEWKSRC4		4
#define CLKPWR_RISEWKSRC3		3
#define CLKPWR_RISEWKSRC2		2
#define CLKPWR_RISEWKSRC1		1
#define CLKPWR_RISEWKSRC0		0

/* gpiowakefalleenb */
#define CLKPWR_FALLWKSRC31		31
#define CLKPWR_FALLWKSRC30		30 /* reserved */
#define CLKPWR_FALLWKSRC29		29 /* reserved */
#define CLKPWR_FALLWKSRC28		28 /* reserved */
#define CLKPWR_FALLWKSRC27		27
#define CLKPWR_FALLWKSRC26		26
#define CLKPWR_FALLWKSRC25		25
#define CLKPWR_FALLWKSRC24		24
#define CLKPWR_FALLWKSRC23		23
#define CLKPWR_FALLWKSRC22		22
#define CLKPWR_FALLWKSRC21		21
#define CLKPWR_FALEWKSRC20		20
#define CLKPWR_FALLWKSRC19		19
#define CLKPWR_FALLWKSRC18		18
#define CLKPWR_FALLWKSRC17		17
#define CLKPWR_FALLWKSRC16		16
#define CLKPWR_FALLWKSRC15		15
#define CLKPWR_FALLWKSRC14		14
#define CLKPWR_FALLWKSRC13		13
#define CLKPWR_FALLWKSRC12		12
#define CLKPWR_FALLWKSRC11		11
#define CLKPWR_FALLWKSRC10		10
#define CLKPWR_FALLWKSRC9		9
#define CLKPWR_FALLWKSRC8		8
#define CLKPWR_FALLWKSRC7		7
#define CLKPWR_FALLWKSRC6		6
#define CLKPWR_FALLWKSRC5		5
#define CLKPWR_FALLWKSRC4		4
#define CLKPWR_FALLWKSRC3		3
#define CLKPWR_FALLWKSRC2		2
#define CLKPWR_FALLWKSRC1		1
#define CLKPWR_FALLWKSRC0		0

/* gpiopend */
#define CLKPWR_WKDET31			31
#define CLKPWR_WKDET30			30 /* reserved */
#define CLKPWR_WKDET29			29 /* reserved */
#define CLKPWR_WKDET28			28 /* reserved */
#define CLKPWR_WKDET27			27
#define CLKPWR_WKDET26			26
#define CLKPWR_WKDET25			25
#define CLKPWR_WKDET24			24
#define CLKPWR_WKDET23			23
#define CLKPWR_WKDET22			22
#define CLKPWR_WKDET21			21
#define CLKPWR_WKDET20			20
#define CLKPWR_WKDET19			19
#define CLKPWR_WKDET18			18
#define CLKPWR_WKDET17			17
#define CLKPWR_WKDET16			16
#define CLKPWR_WKDET15			15
#define CLKPWR_WKDET14			14
#define CLKPWR_WKDET13			13
#define CLKPWR_WKDET12			12
#define CLKPWR_WKDET11			11
#define CLKPWR_WKDET10			10
#define CLKPWR_WKDET9			9
#define CLKPWR_WKDET8			8
#define CLKPWR_WKDET7			7
#define CLKPWR_WKDET6			6
#define CLKPWR_WKDET5			5
#define CLKPWR_WKDET4			4
#define CLKPWR_WKDET3			3
#define CLKPWR_WKDET2			2
#define CLKPWR_WKDET1			1
#define CLKPWR_WKDET0			0

/* intpendspad */
#define CLKPWR_BATFW			14
#define CLKPWR_GPIORESETW		13
#define CLKPWR_WATCHDOGRSTW		12
#define CLKPWR_POWERONRSTW		11
#define CLKPWR_SCRPAD			0

/* pwrrststatus */
#define CLKPWR_BATF			3
#define CLKPWR_GPIORESETR		2
#define CLKPWR_WATCHDOGRSTR		1
#define CLKPWR_POWERONRSTR		0

/* intenb */
#define CLKPWR_BATFINTENB		2
#define CLKPWR_GPIOINTENB		0

/* pwrmode */
#define CLKPWR_CHGPLL			15
#define CLKPWR_GPIOSWRSTENB		13
#define CLKPWR_SWRST			12
#define CLKPWR_LASTPWRMODE		4
#define CLKPWR_CURPWRMODE		0

/* padstrengthgpioal */
#define CLKPWR_GPIOA15_DRV		30
#define CLKPWR_GPIOA14_DRV		28
#define CLKPWR_GPIOA13_DRV		26
#define CLKPWR_GPIOA12_DRV		24
#define CLKPWR_GPIOA11_DRV		22
#define CLKPWR_GPIOA10_DRV		20
#define CLKPWR_GPIOA9_DRV		18
#define CLKPWR_GPIOA8_DRV		16
#define CLKPWR_GPIOA7_DRV		14
#define CLKPWR_GPIOA6_DRV		12
#define CLKPWR_GPIOA5_DRV		10
#define CLKPWR_GPIOA4_DRV		8
#define CLKPWR_GPIOA3_DRV		6
#define CLKPWR_GPIOA2_DRV		4
#define CLKPWR_GPIOA1_DRV		2
#define CLKPWR_GPIOA0_DRV		0

/* padstrengthgpioah */
#define CLKPWR_GPIOA31_DRV		30
#define CLKPWR_GPIOA30_DRV		28
#define CLKPWR_GPIOA25_DRV		18
#define CLKPWR_GPIOA24_DRV		16
#define CLKPWR_GPIOA23_DRV		14
#define CLKPWR_GPIOA22_DRV		12
#define CLKPWR_GPIOA21_DRV		10
#define CLKPWR_GPIOA20_DRV		8
#define CLKPWR_GPIOA19_DRV		6
#define CLKPWR_GPIOA18_DRV		4
#define CLKPWR_GPIOA17_DRV		2
#define CLKPWR_GPIOA16_DRV		0

/* padstrengthgpiobl */
#define CLKPWR_GPIOB15_DRV		30
#define CLKPWR_GPIOB14_DRV		28
#define CLKPWR_GPIOB13_DRV		26
#define CLKPWR_GPIOB12_DRV		24
#define CLKPWR_GPIOB11_DRV		22
#define CLKPWR_GPIOB10_DRV		20
#define CLKPWR_GPIOB9_DRV		18
#define CLKPWR_GPIOB8_DRV		16
#define CLKPWR_GPIOB7_DRV		14
#define CLKPWR_GPIOB6_DRV		12
#define CLKPWR_GPIOB5_DRV		10
#define CLKPWR_GPIOB4_DRV		8
#define CLKPWR_GPIOB3_DRV		6
#define CLKPWR_GPIOB2_DRV		4
#define CLKPWR_GPIOB1_DRV		2
#define CLKPWR_GPIOB0_DRV		0

/* padstrengthgpiobh */
#define CLKPWR_GPIOB31_DRV		30
#define CLKPWR_GPIOB30_DRV		28
#define CLKPWR_GPIOB29_DRV		26
#define CLKPWR_GPIOB28_DRV		24
#define CLKPWR_GPIOB27_DRV		22
#define CLKPWR_GPIOB26_DRV		20
#define CLKPWR_GPIOB25_DRV		18
#define CLKPWR_GPIOB24_DRV		16
#define CLKPWR_GPIOB23_DRV		14
#define CLKPWR_GPIOB22_DRV		12
#define CLKPWR_GPIOB21_DRV		10
#define CLKPWR_GPIOB20_DRV		8
#define CLKPWR_GPIOB19_DRV		6
#define CLKPWR_GPIOB18_DRV		4
#define CLKPWR_GPIOB17_DRV		2
#define CLKPWR_GPIOB16_DRV		0

/* padstrengthgpiocl */
#define CLKPWR_GPIOC15_DRV		30
#define CLKPWR_GPIOC14_DRV		28
#define CLKPWR_GPIOC13_DRV		26
#define CLKPWR_GPIOC12_DRV		24
#define CLKPWR_GPIOC11_DRV		22
#define CLKPWR_GPIOC10_DRV		20
#define CLKPWR_GPIOC9_DRV		18
#define CLKPWR_GPIOC8_DRV		16
#define CLKPWR_GPIOC7_DRV		14
#define CLKPWR_GPIOC6_DRV		12
#define CLKPWR_GPIOC5_DRV		10
#define CLKPWR_GPIOC4_DRV		8
#define CLKPWR_GPIOC3_DRV		6
#define CLKPWR_GPIOC2_DRV		4
#define CLKPWR_GPIOC1_DRV		2
#define CLKPWR_GPIOC0_DRV		0

/* padstrengthgpioch */
#define CLKPWR_GPIOC19_DRV		6
#define CLKPWR_GPIOC18_DRV		4
#define CLKPWR_GPIOC17_DRV		2
#define CLKPWR_GPIOC16_DRV		0

/* padstrengthbus */
#define CLKPWR_DDR_CNTL_DRV		30
#define CLKPWR_DDR_ADDR_DRV		28
#define CLKPWR_DDR_DATA_DRV		26
#define CLKPWR_DDR_CLK_DRV		24
#define CLKPWR_STATIC_CNTL_DRV		22
#define CLKPWR_STATIC_ADDR_DRV		20
#define CLKPWR_STATIC_DATA_DRV		18
#define CLKPWR_VSYNC_DRV		6
#define CLKPWR_HSYNC_DRV		4
#define CLKPWR_DE_DRV			2
#define CLKPWR_PVCLK_DRV		0

#endif /* _MACH_CLKPWR_H */

