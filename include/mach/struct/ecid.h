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

#ifndef _MACH_ECID_H
#define _MACH_ECID_H

#include <stdint.h>

#define POLLUX_ECID_BASE 0xC001F800

struct pollux_ecid_regs_t {
	uint32_t ecid[4];
	uint32_t chipname[12];
	uint32_t _reserved;
	uint32_t guid[4];
	uint32_t ec;
};

#define pollux_ecid ((volatile struct pollux_ecid_regs_t *) \
	(POLLUX_ECID_BASE))

/* ec */
#define ECID_FENB			6
#define ECID_SET			5
#define ECID_SEN			4
#define ECID_BONDINGID			0

#endif /* _MACH_ECID_H */

