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

#ifndef _MACH_SSPSPI_H
#define _MACH_SSPSPI_H

#include <stdint.h>

#define POLLUX_SSPSPI_BASE 0xC0007800
#define POLLUX_SSPSPI_OFFSET 0x800
#define POLLUX_SSPSPI_COUNT 3

struct pollux_sspspi_regs_t {
	uint16_t cont0;
	uint16_t cont1;
	uint16_t data;
	uint16_t stat;
	uint16_t rx_breceive_sz;
	uint16_t _reserved[28];
	uint32_t clkenb;
	uint32_t clkgen;
};

#define pollux_sspspi(n) ((volatile struct pollux_sspspi_regs_t *) \
	(POLLUX_SSPSPI_BASE + (POLLUX_SSPSPI_OFFSET * (n))))

/* cont0 */
#define SSPSPI_ST_RXBRECEIVE		15
#define SSPSPI_BRECEIVE			13
#define SSPSPI_DMAENB			12
#define SSPSPI_ENB			11
#define SSPSPI_FFCLR			10
#define SSPSPI_EXTCLKSEL		9
#define SSPSPI_NUMBIT			5
#define SSPSPI_DIVCNT			0

/* cont1 */
#define SSPSPI_BYTE_SWAP		5
#define SSPSPI_SLAVE_SEL		4
#define SSPSPI_SCLKPOL			3
#define SSPSPI_SCLKSH			2
#define SSPSPI_TYPE			0

/* stat */
#define SSPSPI_IRQEENB			15
#define SSPSPI_IRQWENB			14
#define SSPSPI_IRQRENB			13
#define SSPSPI_TXSHIFTEREMPTY		8
#define SSPSPI_IRQE			6
#define SSPSPI_IRQW			5
#define SSPSPI_IRQR			4
#define SSPSPI_WFFFULL			3
#define SSPSPI_WFFEMPTY			2
#define SSPSPI_RFFFULL			1
#define SSPSPI_RFFEMPTY			0

/* clkenb */
#define SSPSPI_PCLKMODE			3
#define SSPSPI_CLKGENENB		2

/* clkgen */
#define SSPSPI_CLKDIV			4
#define SSPSPI_CLKSRCSEL		1

#endif /* _MACH_SSPSPI_H */

