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

#ifndef _MACH_CSC_H
#define _MACH_CSC_H

#include <stdint.h>

#define POLLUX_CSC_BASE 0xC0009000

struct pollux_csc_regs_t {
	uint32_t control;
	uint32_t size;
	uint32_t addry;
	uint32_t addrcb;
	uint32_t addrcr;
	uint32_t addrtex;
	uint32_t tpctrl;
	uint32_t tpy;
	uint32_t tpcb;
	uint32_t tpcr;
	uint32_t _reserved[102];
	uint32_t clkenb;
};

#define pollux_csc ((volatile struct pollux_csc_regs_t *) \
	(POLLUX_CSC_BASE))

/* control */
#define CSC_DITHER			5
#define CSC_QMODE			4
#define CSC_INTPEND			2
#define CSC_INTENB			1
#define CSC_RUN				0

/* size */
#define CSC_HEIGHT			16
#define CSC_WIDTH			0

/* addry */
#define CSC_SEGY			21
#define CSC_OFFY_Y			11
#define CSC_OFFX_Y			0

/* addrcb */
#define CSC_SEG_CB			21
#define CSC_OFFY_CB			11
#define CSC_OFFX_CB			0

/* addrcr */
#define CSC_SEG_CR			21
#define CSC_OFFY_CR			11
#define CSC_OFFX_CR			0

/* addrtex */
#define CSC_SEG_TEX			21
#define CSC_OFFY_TEX			11
#define CSC_OFFX_TEX			0

/* tpctrl */
#define CSC_TPENB			19
#define CSC_TPINVCR			18
#define CSC_TPINVCB			17
#define CSC_TPINVY			16
#define CSC_TPCOLOR			0

/* tpy */
#define CSC_TPMAXY			8
#define CSC_TPMINY			0

/* tpcb */
#define CSC_TPMAXCB			8
#define CSC_TPMINCB			0

/* tpcr */
#define CSC_TPMAXCR			8
#define CSC_TPMINCR			0

/* clkenb */
#define CSC_PCLKMODE			3
#define CSC_BCLKMODE			0

#endif /* _MACH_CSC_H */

