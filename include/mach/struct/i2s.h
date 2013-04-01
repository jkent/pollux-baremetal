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

#ifndef _MACH_I2S_H
#define _MACH_I2S_H

#include <stdint.h>

#define POLLUX_I2S_BASE 0xC000D800

struct pollux_i2s_regs_t {
	uint16_t _reserved[2];
	uint16_t ctrl;
	uint16_t config;
	uint16_t bufctrl;
	uint16_t bufconfig;
	uint16_t intenb;
	uint16_t intpend;
	uint16_t _reserved2[2];
	uint16_t status0;
	uint16_t status1;
	uint16_t _reserved3[467];
	uint32_t clkenb;
	uint32_t clkgen0;
	uint32_t clkgen1;
};

#define pollux_i2s ((volatile struct pollux_i2s_regs_t *) \
	(POLLUX_I2S_BASE))

/* ctrl */
#define I2S_LINK_RUN			1
#define I2S_EN				0

/* config */
#define I2S_IF_MODE			6
#define I2S_SYNC_PERIOD			4
#define I2S_LOOP_BACK			3
#define I2S_IN_EN			2
#define I2S_OUT_EN			1
#define I2S_MST_SLV			0

/* bufctrl */
#define I2S_BUF_IN_EN			1
#define I2S_BUF_OUT_EN			0

/* bufconfig */
#define I2S_IN_WIDTH			4
#define I2S_OUT_WIDTH			0

/* intenb */
#define I2S_IN_OVERINT			1
#define I2S_OUT_UNDERINT		0

/* intpend */
#define I2S_IN_OVERPEND			1
#define I2S_OUT_UNDERPEND		0

/* status0 */
#define I2S_STATE_RUN			2
#define I2S_STATE_READY			1
#define I2S_STATE_IDLE			0

/* status1 */
#define I2S_IN_BUF_RDY			1
#define I2S_OUT_BUF_RDY			0

/* clkenb */
#define I2S_PCLKMODE			3
#define I2S_CLKGENENB			2

/* clkgen0 */
#define I2S_CLKDIV0			4
#define I2S_CLKSRCSEL0			1
#define I2S_OUTCLKINV0			0

/* clkgen1 */
#define I2S_OUTCLKENB1			15
#define I2S_CLKDIV1			4
#define I2S_CLKSRCSEL1			1
#define I2S_OUTCLKINV1			0

#endif /* _MACH_I2S_H */

