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

#ifndef _MACH_GPIO_H
#define _MACH_GPIO_H

#include <stdint.h>

#define POLLUX_GPIO_BASE 0xC000A000
#define POLLUX_GPIO_OFFSET 0x40
#define POLLUX_GPIO_COUNT 3

struct pollux_gpio_regs_t {
	uint32_t out;
	uint32_t outenb;
	uint32_t detmode0;
	uint32_t detmode1;
	uint32_t intenb;
	uint32_t det;
	uint32_t pad;
	uint32_t puenb;
	uint32_t altfn0;
	uint32_t altfn1;
};

#define pollux_gpio(n) ((volatile struct pollux_gpio_regs_t *) \
	(POLLUX_GPIO_BASE + (POLLUX_GPIO_OFFSET * (n))))

/* detmode0 */
#define GPIO_DETMODE0_15		30
#define GPIO_DETMODE0_14		28
#define GPIO_DETMODE0_13		26
#define GPIO_DETMODE0_12		24
#define GPIO_DETMODE0_11		22
#define GPIO_DETMODE0_10		20
#define GPIO_DETMODE0_9			18
#define GPIO_DETMODE0_8			16
#define GPIO_DETMODE0_7			14
#define GPIO_DETMODE0_6			12
#define GPIO_DETMODE0_5			10
#define GPIO_DETMODE0_4			8
#define GPIO_DETMODE0_3			6
#define GPIO_DETMODE0_2			4
#define GPIO_DETMODE0_1			2
#define GPIO_DETMODE0_0			0

/* detmode1 */
#define GPIO_DETMODE1_31		30
#define GPIO_DETMODE1_30		28
#define GPIO_DETMODE1_29		26
#define GPIO_DETMODE1_28		24
#define GPIO_DETMODE1_27		22
#define GPIO_DETMODE1_26		20
#define GPIO_DETMODE1_25		18
#define GPIO_DETMODE1_24		16
#define GPIO_DETMODE1_23		14
#define GPIO_DETMODE1_22		12
#define GPIO_DETMODE1_21		10
#define GPIO_DETMODE1_20		8
#define GPIO_DETMODE1_19		6
#define GPIO_DETMODE1_18		4
#define GPIO_DETMODE1_17		2
#define GPIO_DETMODE1_16		0

/* altfn0 */
#define GPIO_ALTFN0_15			30
#define GPIO_ALTFN0_14			28
#define GPIO_ALTFN0_13			26
#define GPIO_ALTFN0_12			24
#define GPIO_ALTFN0_11			22
#define GPIO_ALTFN0_10			20
#define GPIO_ALTFN0_9			18
#define GPIO_ALTFN0_8			16
#define GPIO_ALTFN0_7			14
#define GPIO_ALTFN0_6			12
#define GPIO_ALTFN0_5			10
#define GPIO_ALTFN0_4			8
#define GPIO_ALTFN0_3			6
#define GPIO_ALTFN0_2			4
#define GPIO_ALTFN0_1			2
#define GPIO_ALTFN0_0			0

/* altfn1 */
#define GPIO_ALTFN1_31			30
#define GPIO_ALTFN1_30			28
#define GPIO_ALTFN1_29			26
#define GPIO_ALTFN1_28			24
#define GPIO_ALTFN1_27			22
#define GPIO_ALTFN1_26			20
#define GPIO_ALTFN1_25			18
#define GPIO_ALTFN1_24			16
#define GPIO_ALTFN1_23			14
#define GPIO_ALTFN1_22			12
#define GPIO_ALTFN1_21			10
#define GPIO_ALTFN1_20			8
#define GPIO_ALTFN1_19			6
#define GPIO_ALTFN1_18			4
#define GPIO_ALTFN1_17			2
#define GPIO_ALTFN1_16			0

#endif /* _MACH_GPIO_H */

