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

#ifndef _MACH_ALIVE_H
#define _MACH_ALIVE_H

#include <stdint.h>

#define POLLUX_ALIVE_BASE 0xC0019000

struct pollux_alive_regs_t {
	uint32_t pwrgate;
	uint32_t gpiorst;
	uint32_t gpioset;
	uint32_t gpioread;
	uint32_t scratchrst;
	uint32_t scratchset;
	uint32_t scratchread;
};

#define pollux_alive ((volatile struct pollux_alive_regs_t *) \
	(POLLUX_ALIVE_BASE))

/* pwrgate */
#define ALIVE_NPOWERGATING		0

/* gpiorst/set/read */
#define ALIVE_VDDPWRTOGGLE		8
#define ALIVE_VDDPWRON			7
#define ALIVE_GPIO6			6
#define ALIVE_GPIO5			5
#define ALIVE_GPIO4			4
#define ALIVE_GPIO3			3
#define ALIVE_GPIO2			2
#define ALIVE_GPIO1			1
#define ALIVE_GPIO0			0

#endif /* _MACH_ALIVE_H */

