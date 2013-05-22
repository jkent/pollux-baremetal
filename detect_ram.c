/*
 * Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
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

#include "asm/io.h"
#include "mach/mcuy.h"

int ramsize;

static void detect_ram(void)
{
	u32 memcfg;
	volatile u32 *low, *high;

	memcfg = readl((void __iomem *) MCUY_BASE + MCUY_CFG);
	ramsize = 8 << (memcfg & 0x3);

	low = (u32 *)((ramsize << 20) - 4);
	high = (u32 *)(((ramsize + 64) << 20) - 4);

	*low = 0x55AA55AA;
	*high = 0xAA55AA55;

	if (*low == 0xAA55AA55)
		return;

	ramsize <<= 1;
}