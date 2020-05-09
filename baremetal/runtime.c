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

#include <baremetal/cache.h>
#include <baremetal/mmu.h>
#include <baremetal/util.h>
#include <baremetal/clocking.h>

void runtime(void)
{
#if defined(CONFIG_BAREMETAL_ENABLE_ICACHE)
    icache_enable();
#endif
#if defined(CONIFG_BAREMETAL_ENABLE_MMU)
    init_tlb(main_tlb);
    assign_tlb(main_tlb);
    mmu_enable()
#endif
#if defined(CONFIG_BAREMETAL_ENABLE_DCACHE)
    dcache_enable();
#endif
#if defined(CONFIG_BAREMETAL_PLL0_INIT_533)
    pll0_init();
#endif
#if defined(CONFIG_BAREMETAL_DDR_INIT)
    ddr_init();
#endif

    main();
    halt();
}