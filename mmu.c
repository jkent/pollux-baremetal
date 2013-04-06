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

#include "asm/types.h"
#include "baremetal/mmu.h"

#define CR_M  (1 <<  0)
#define CR_C  (1 <<  2)
#define CR_I  (1 << 12)


static void create_page_tables(void)
{
	int i;

	/* zero tlb */
	for (i = 0; i < 0x1000; i++)
		main_page_table[i] = 0;

	/* DDR linear array */
	for (i = 0; i < 0x100; i++) {
		main_page_table[i]  = (2 <<  0); /* section entry */
		main_page_table[i] |= (3 <<  2); /* cache and buffer */
		main_page_table[i] |= (0 <<  5); /* domain 0 */
		main_page_table[i] |= (3 << 10); /* unrestricted access */
		main_page_table[i] |= (i << 20); /* section address */
	}

	/* DDR display array */
	for (i = 0x200; i < 0x300; i++) {
		main_page_table[i]  = (2 <<  0); /* section entry */
		main_page_table[i] |= (3 <<  2); /* cache and buffer */
		main_page_table[i] |= (0 <<  5); /* domain 0 */
		main_page_table[i] |= (3 << 10); /* unrestricted access */
		main_page_table[i] |= (i << 20); /* section address */
	}

	/* static bus */
	for (i = 0x800; i < 0xA80; i++) {
		main_page_table[i]  = (2 <<  0); /* section entry */
		main_page_table[i] |= (3 <<  2); /* cache and buffer */
		main_page_table[i] |= (0 <<  5); /* domain 0 */
		main_page_table[i] |= (3 << 10); /* unrestricted access */
		main_page_table[i] |= (i << 20); /* section address */
	}

	/* NAND registers */
	for (i = 0xAC0; i < 0xB00; i++) {
		main_page_table[i]  = (2 <<  0); /* section entry */
		main_page_table[i] |= (0 <<  2); /* no cache or buffer */
		main_page_table[i] |= (0 <<  5); /* domain 0 */
		main_page_table[i] |= (3 << 10); /* unrestricted access */
		main_page_table[i] |= (i << 20); /* section address */
	}

	/* I/O */
	for (i = 0xC00; i < 0xE00; i++) {
		main_page_table[i]  = (2 <<  0); /* section entry */
		main_page_table[i] |= (0 <<  2); /* no cache or buffer */
		main_page_table[i] |= (0 <<  5); /* domain 0 */
		main_page_table[i] |= (3 << 10); /* unrestricted access */
		main_page_table[i] |= (i << 20); /* section address */
	}
}

void enable_mmu(void)
{
	u32 n;
	
	asm("mrc p15, 0, %0, c1, c0, 0\n\t":"=r"(n));
	n &= ~(CR_M | CR_C | CR_I); /* disable mmu, dcache, icache */
	asm("mcr p15, 0, %0, c1, c0, 0\n\t"::"r"(n));

	/* invalidate icache */
	asm("mcr p15, 0, %0, c7, c5, 0\n\t"::"r"(0));
	/* invalidate dcache */
	asm("mcr p15, 0, %0, c7, c6, 0\n\t"::"r"(0));

	create_page_tables();

	/* domain 0 unchecked access (manager) */
	asm("mcr p15, 0, %0, c3, c0, 0\n\t"::"r"(3));

	/* point ttbr at tlb */
	asm("mcr p15, 0, %0, c2, c0, 0\n\t"::"r"(main_page_table));

	asm("mrc p15, 0, %0, c1, c0, 0\n\t":"=r"(n));
	n |= CR_M | CR_C | CR_I; /* enable mmu, dcache, icache */
	asm("mcr p15, 0, %0, c1, c0, 0\n\t"::"r"(n));
}

