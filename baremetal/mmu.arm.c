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

#include <asm/types.h>
#include <baremetal/linker.h>
#include <baremetal/mmu.h>
#include <malloc.h>
#include <string.h>

void mmu_load(void *main_tlb)
{
	/* set domain 0 for unchecked access (manager) */
    asm("mov r1, #3\n\t"
        "mcr p15, 0, r1, c3, c0, 0" ::: "r1");

	/* load tlb */
	asm("mcr p15, 0, %0, c2, c0, 0" :: "r" (main_tlb) : "memory");
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

void mmu_init(void)
{
	u32 *main_tlb = (u32 *)&_main_tlb;

	/* linear DDR */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0x000; i < 0x080; i++) {
#else
	for (int i = 0x800; i < 0x880; i++) {
#endif
		main_tlb[i]  = (i << 20); /* section address */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 <<  2); /* cache and buffer */
		main_tlb[i] |= (2 <<  0); /* section entry */
	}

	/* display DDR */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0x200; i < 0x280; i++) {
#else
	for (int i = 0xA00; i < 0xA80; i++) {
#endif
		main_tlb[i]  = (i << 20); /* section address */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 <<  2); /* cache and buffer */
		main_tlb[i] |= (2 <<  0); /* section entry */
	}

	/* static bus */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0x800; i < 0xA80; i++) {
#else
	for (int i = 0x000; i < 0x280; i++) {
#endif
		main_tlb[i]  = (i << 20); /* section address */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 <<  2); /* cache and buffer */
		main_tlb[i] |= (2 <<  0); /* section entry */
	}

	/* NAND registers */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0xAC0; i < 0xB00; i++) {
#else
	for (int i = 0x2C0; i < 0x300; i++) {
#endif
		main_tlb[i]  = (i << 20); /* section address */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (0 <<  2); /* no cache or buffer */
		main_tlb[i] |= (2 <<  0); /* section entry */
	}

	/* I/O */
	for (int i = 0xC00; i < 0xE00; i++) {
		main_tlb[i]  = (i << 20); /* section address */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (0 <<  2); /* no cache or buffer */
		main_tlb[i] |= (2 <<  0); /* section entry */
	}

#if defined(CONFIG_BAREMETAL_INTERRUPTS)
	u32 *ivt_tlb = (u32 *)&_ivt_tlb;

	/* 0xFFF00000 - 0xFFFFFFFF  */
	main_tlb[0xFFF]  = (u32)ivt_tlb & 0xFFFFFC00;
	main_tlb[0xFFF] |= (0 << 5); /* domain 0 */
	main_tlb[0xFFF] |= (1 << 4); /* cache and buffer */
	main_tlb[0xFFF] |= (1 << 0); /* coarse page table */

	u32 *ivt_phys = (u32 *)&_ivt_phys;

	/* 0xFFFF0000 - 0xFFFFFFFF */
	for (int i = 0xF0; i < 0x100; i++) {
		ivt_tlb[i]  = (u32)ivt_phys & 0xFFFF0000;
		ivt_tlb[i] |= (3 << 4); /* unrestricted access */
		ivt_tlb[i] |= (0 << 2); /* no cache and buffer */
		ivt_tlb[i] |= (2 << 0); /* small page descriptor */
	}
#endif

	mmu_load(main_tlb);
}