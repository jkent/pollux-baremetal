/*
 * Copyright (C) 2020 Jeff Kent <jeff@jkent.net>
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

#include <asm/io.h>
#include <asm/types.h>
#include <mach/mcuy.h>

__attribute__((weak,noreturn))
void halt(void)
{
    while(1)
        ;
}

u32 get_ram_size(void)
{
	u32 memcfg = readl(MCUY_BASE + MCUY_CFG);
	u32 ramsize = 8 << (memcfg & 0x3);

	volatile u32 *low = (void *)((ramsize << 20) - 4);
	volatile u32 *high = (void *)(((ramsize + 64) << 20) - 4);

#if !defined(CONFIG_BAREMETAL_SHADOW)
	(void *)low += 0x80000000;
	(void *)high += 0x80000000;
#endif

	u32 old_low = *low;
	u32 old_high = *high;
	
	*(u32 *)low = 0x55AA55AA;
	*(u32 *)high = 0xAA55AA55;

	if (*(u32 *)low != 0xAA55AA55)
		ramsize <<= 1;

	*low = old_low;
	*high = old_high;

    return ramsize << 20;
}
