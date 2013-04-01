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

#ifndef _MACH_MCUD_H
#define _MACH_MCUD_H

#include <stdint.h>

#define POLLUX_MCUD_BASE 0xC0014800

struct pollux_mcud_regs_t {
	uint16_t cfg;
	uint16_t time0;
	uint16_t time1;
	uint16_t _reserved;
	uint16_t refresh;
	uint16_t control;
	uint16_t clkdelay;
	uint16_t dqsoutdelay;
	uint16_t dqsindelay;
};

#define pollux_mcud ((volatile struct pollux_mcud_regs_t *) \
	(POLLUX_MCUD_BASE))

/* cfg */
#define MCUD_DS				9
#define MCUD_DISDLL			8
#define MCUD_SDRTYPE			6
#define MCUD_SDRBUSBW			4
#define MCUD_SDRBW			2
#define MCUD_SDRCAP			0

/* time0 */
#define MCUD_TMRD			12
#define MCUD_TRP			8
#define MCUD_TRCD			0

/* time1 */
#define MCUD_MODESET			15
#define MCUD_LAT			12
#define MCUD_TRC			8
#define MCUD_TRAS			4
#define MCUD_TWR			0

/* control */
#define MCUD_UPLAT			8
#define MCUD_RDLAT			6
#define MCUD_BLOCKDISP			0

/* dqsoutdelay */
#define MCUD_DLYOUTDQS1			4
#define MCUD_DLYOUTDQS0			0

/* dqsindelay */
#define MCUD_DLYINDQS1			4
#define MCUD_DLYINDQS0			0

#endif /* _MACH_MCUD_H */

