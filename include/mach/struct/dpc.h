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

#ifndef _MACH_DPC_H
#define _MACH_DPC_H

#include <stdint.h>

#define POLLUX_DPC_BASE 0xc0003000
#define POLLUX_DPC_OFFSET 0x400
#define POLLUX_DPC_COUNT 2

struct pollux_dpc_regs_t {
	uint16_t _reserved;
	uint16_t vencctrla;
	uint16_t vencctrlb;
	uint16_t _reserved2;
	uint16_t vencsch;
	uint16_t venchue;
	uint16_t vencsat;
	uint16_t venccrt;
	uint16_t vencbrt;
	uint16_t vencfscadjh;
	uint16_t vencfscadjl;
	uint16_t _reserved3[5];
	uint16_t vencdacsel;
	uint16_t _reserved4[15];
	uint16_t vencicntl;
	uint16_t _reserved5[3];
	uint16_t venchsvso;
	uint16_t venchsos;
	uint16_t venchsoe;
	uint16_t vencvsos;
	uint16_t vencvsoe;
	uint16_t _reserved6[21];
	uint16_t htotal;
	uint16_t hswidth;
	uint16_t hastart;
	uint16_t haend;
	uint16_t vtotal;
	uint16_t vswidth;
	uint16_t vastart;
	uint16_t vaend;
	uint16_t ctrl0;
	uint16_t ctrl1;
	uint16_t evtotal;
	uint16_t evswidth;
	uint16_t evastart;
	uint16_t evaend;
	uint16_t ctrl2;
	uint16_t vseoffset;
	uint16_t vssoffset;
	uint16_t evseoffset;
	uint16_t evssoffset;
	uint16_t delay0;
	uint16_t upscalecon0;
	uint16_t upscalecon1;
	uint16_t upscalecon2;
	uint16_t rnumgencon0;
	uint16_t rnumgencon1;
	uint16_t rnumgencon2;
	uint16_t fdtaddr;
	uint16_t frdithervalue;
	uint16_t fgdithervalue;
	uint16_t fbdithervalue;
	uint16_t _reserved7[132];
	uint32_t clkenb;
	uint32_t clkgen0;
	uint32_t clkgen1;
};

#define pollux_dpc(n) ((volatile struct pollux_dpc_regs_t *) \
	(POLLUX_DPC_BASE + (POLLUX_DPC_OFFSET * (n))))

/* vencctrla */
#define DPC_PWDENC			7
#define DPC_FDRST			6
#define DPC_FDSEL			4
#define DPC_PED				3
#define DPC_IFMT			1
#define DPC_PHALT			0

/* venctrlb */
#define DPC_CBW				2
#define DPC_YBW				0

/* venchsvso */
#define DPC_VSOB8			6
#define DPC_HSOB10_8			3
#define DPC_HSOE10_8			0

/* ctrl0 */
#define DPC_DPCENB			15
#define DPC_ENCMODE			14
#define DPC_ENCRST			13
#define DPC_RGBMODE			12
#define DPC_INTENB			11
#define DPC_INTPEND			10
#define DPC_SCANMODE			9
#define DPC_SEAVENB			8
#define DPC_DELAYRGB			4
#define DPC_POLFIELD			2
#define DPC_POLVSYNC			1
#define DPC_POLHSYNC			0

/* ctrl1 */
#define DPC_SWAPRB			15
#define DPC_YCRANGE			13
#define DPC_FORMAT			8
#define DPC_YCORDER			6
#define DPC_BDITHER			4
#define DPC_GDITHER			2
#define DPC_RDITHER			0

/* ctrl2 */
#define DPC_CL2CYC			12
#define DPC_STNLCDBITWIDTH		9
#define DPC_LCDTYPE			8
#define DPC_PADCLKSEL			0

/* delay0 */
#define DPC_DELAYDE			8
#define DPC_DELAYVS			4
#define DPC_DELAYHS			0

/* upscalecon0 */
#define DPC_UPSCALEL			8
#define DPC_UPSCALERENB			0

/* rnumgencon2 */
#define DPC_RNUMGENENB			12
#define DPC_RNCONVALUE1			0

/* clkenb */
#define DPC_PCLKMODE			3
#define DPC_CLKGENENB			2

/* clkgen0/1 */
#define DPC_OUTCLKENB			15
#define DPC_OUTCLKDELAY			12
#define DPC_CLKDIV			4
#define DPC_CLKSRCSEL			1
#define DPC_OUTCLKINV			0

#endif /* _MACH_DPC_H */

