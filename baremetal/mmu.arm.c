/*
 * Copyright (C) 2020 Jeff Kent <jeff@jkent.net>
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

#include <asm/types.h>

#define CR_M (1 << 0) /* enable MMU */

void mmu_assign_tlb(u32 *tlb)
{
	/* set domain 0 for unchecked access (manager) */
    asm("mov r1, #3\n\t"
        "mcr p15, 0, r1, c3, c0, 0" ::: "r1");

    asm("mcr p15, 0, %0, c2, c0, 0" : "=r" (tlb));
}

void mmu_enable(void)
{
	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr) :: "cc");
	cr |= CR_M;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));
}

void mmu_disable(void)
{
	u32 cr;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r" (cr) :: "cc");
	cr &= ~CR_M;
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r" (cr));
}