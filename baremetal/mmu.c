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

#include <baremetal/interrupt.h>
#include <baremetal/mmu.h>

void mmu_init(void)
{
	/* linear DDR */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0x000; i < 0x080; i++) {
#else
	for (int i = 0x800; i < 0x880; i++) {
#endif
		main_tlb[i]  = (2 <<  0); /* section entry */
		main_tlb[i] |= (3 <<  2); /* cache and buffer */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (i << 20); /* section address */
	}

	/* display DDR */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0x200; i < 0x280; i++) {
#else
	for (int i = 0xA00; i < 0xA80; i++) {
#endif
		main_tlb[i]  = (2 <<  0); /* section entry */
		main_tlb[i] |= (3 <<  2); /* cache and buffer */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (i << 20); /* section address */
	}

	/* static bus */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0x800; i < 0xA80; i++) {
#else
	for (int i = 0x000; i < 0x280; i++) {
#endif
		main_tlb[i]  = (2 <<  0); /* section entry */
		main_tlb[i] |= (3 <<  2); /* cache and buffer */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (i << 20); /* section address */
	}

	/* NAND registers */
#if defined(CONFIG_BAREMETAL_SHADOW)
	for (int i = 0xAC0; i < 0xB00; i++) {
#else
	for (int i = 0x2C0; i < 0x300; i++) {
#endif
		main_tlb[i]  = (2 <<  0); /* section entry */
		main_tlb[i] |= (0 <<  2); /* no cache or buffer */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (i << 20); /* section address */
	}

	/* I/O */
	for (int i = 0xC00; i < 0xE00; i++) {
		main_tlb[i]  = (2 <<  0); /* section entry */
		main_tlb[i] |= (0 <<  2); /* no cache or buffer */
		main_tlb[i] |= (0 <<  5); /* domain 0 */
		main_tlb[i] |= (3 << 10); /* unrestricted access */
		main_tlb[i] |= (i << 20); /* section address */
	}

#if defined(CONFIG_BAREMTAL_INTERRUPTS)
	/* IVT */
	main_tlb[0xFFF] = (3 << 0); /* fine page table */
	main_tlb[0xFFF] |= (1 << 4); /* cache and buffer */
	main_tlb[0xFFF] |= (0 << 5); /* domain 0 */
	main_tlb[0xFFF] |= (u32)ivt_tlb & 0xFFFFF000;

	/* 2nd level IVT */
	for (int i = 0x3FB; i < 0x400; i++) {
		ivt_tlb[i] = (2 << 0); /* small page descriptor */
		ivt_tlb[i] |= (0 <<  2); /* no cache and buffer */
		ivt_tlb[i] |= (255 << 4); /* unrestricted access */
		ivt_tlb[i] |= (u32)ivt_phys & 0xFFFFF000;
	}
#endif

	mmu_load();
}