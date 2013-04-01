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

#ifndef _MACH_MLC_H
#define _MACH_MLC_H

#include <stdint.h>

#define POLLUX_MLC_BASE 0xC0004000
#define POLLUX_MLC_OFFSET 0x400
#define POLLUX_MLC_COUNT 2

struct pollux_mlc_regs_t {
	uint32_t controlt;
	uint32_t screensize;
	uint32_t bgcolor;
	uint32_t leftright0;
	uint32_t topbottom0;
	uint32_t leftright0_0;
	uint32_t topbottom0_0;
	uint32_t leftright0_1;
	uint32_t topbottom0_1;
	uint32_t control0;
	uint32_t hstride0;
	uint32_t vstride0;
	uint32_t tpcolor0;
	uint32_t invcolor0;
	uint32_t address0;
	uint32_t palette0;
	uint32_t leftright1;
	uint32_t topbottom1;
	uint32_t leftright1_0;
	uint32_t topbottom1_0;
	uint32_t leftright1_1;
	uint32_t topbottom1_1;
	uint32_t control1;
	uint32_t hstride1;
	uint32_t vstride1;
	uint32_t tpcolor1;
	uint32_t invcolor1;
	uint32_t address1;
	uint32_t palette1;
	uint32_t leftright2;
	uint32_t topbottom2;
	uint32_t control2;
	uint32_t vstride2;
	uint32_t tpcolor2;
	uint32_t _reserved;
	uint32_t address2;
	uint32_t addresscb;
	uint32_t addresscr;
	uint32_t vstridecb;
	uint32_t vstridecr;
	uint32_t hscale;
	uint32_t vscale;
	uint32_t luenh;
	uint32_t chenh0;
	uint32_t chenh1;
	uint32_t chenh2;
	uint32_t chenh3;
	uint32_t _reserved2[193];
	uint32_t clkenb;
};

#define pollux_mlc(n) ((volatile struct pollux_mlc_regs_t *) \
	(POLLUX_MLC_BASE + (POLLUX_MLC_OFFSET * (n))))

/* controlt */
#define MLC_PIXELBUFFER_PWD		11
#define MLC_PIXELBUFFER_SLD		10
#define MLC_PRIORITY			8
#define MLC_TDIRTYFLAG			3
#define MLC_MLCENB			1
#define MLC_FIELDENB			0

/* screensize */
#define MLC_SCREENHEIGHT		16
#define MLC_SCREENWIDTH			0

/* leftright* */
#define MLC_INVALIDENB			28
#define MLC_LEFT			16
#define MLC_RIGHT			0

/* topbottom* */
#define MLC_TOP				16
#define MLC_BOTTOM			0

/* control0/1/2 */
#define MLC_FORMAT			16
#define MLC_PALETTEPWD			15
#define MLC_LINEBUFFER_PWD		15
#define MLC_PALETTESLD			14
#define MLC_LINEBUFFER_SLMD		14
#define MLC_LOCKSIZE			12
#define MLC_LAYERENB			5
#define MLC_DIRTYFLAG			4
#define MLC_BLENDENB			2
#define MLC_INVENB			1
#define MLC_TPENB			0

/* tpcolor0/1/2 */
#define MLC_ALPHA			28
#define MLC_TPCOLOR			0

/* palette0/1 */
#define MLC_PALETTEADDR			24
#define MLC_PALETTEDATA			0

/* hscale */
#define MLC_HFILTERENB			28
#define MLC_HSCALE			0

/* vscale */
#define MLC_VILTERENB			28
#define MLC_VSCALE			0

/* luenh */
#define MLC_BRIGHTNESS			8
#define MLC_CONTRAST			0

/* chenh0/1/2/3 */
#define MLC_HUECRB			24
#define MLC_HUECRA			16
#define MLC_HUECBB			8
#define MLC_HUECBA			0

/* clkenb */
#define MLC_PCLKMODE			3
#define MLC_BCLKMODE			0

#endif /* _MACH_MLC_H */

