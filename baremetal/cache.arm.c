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

#include "asm/types.h"

#define CR_C  (1 <<  2) /* DCache enable */
#define CR_I  (1 << 12) /* ICache enable */

void icache_invalidate(void)
{
	u32 sbz = 0;
	asm("mcr p15, 0, %0, c7, c5, 0" :: "r" (sbz));
}

void icache_enable(void)
{
	icache_invalidate();

	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr) :: "cc");
	cr |= CR_I;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));
}

void icache_disable(void)
{
	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr) :: "cc");
	cr &= ~CR_I;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));

	icache_invalidate();
}

void dcache_invalidate(void)
{
	asm("1:	mrc p15, 0, r15, c7, c14, 3\n\t"
		"bne 1b" ::: "cc", "r15");
}

void dcache_enable(void)
{
	dcache_invalidate();

	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr) :: "cc");
	cr |= CR_C;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));
}

void dcache_disable(void)
{
	dcache_invalidate();

	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr) :: "cc");
	cr &= ~CR_C;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));
}
