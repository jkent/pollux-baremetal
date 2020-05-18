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
#include <baremetal/clocking.h>
#include <baremetal/exception.h>
#include <baremetal/mmu.h>
#include <stdlib.h>

extern void __libc_init_array(void);
extern void __libc_fini_array(void);
extern int main(void);

void startup(void)
{
#if defined(CONFIG_BAREMETAL_EXCEPTION)
	init_exceptions();
#endif

#if defined(CONFIG_BAREMETAL_MMU)
 	mmu_init();
    mmu_enable();
#endif

#if defined(CONFIG_BAREMETAL_DCACHE)
    dcache_enable();
#endif

#if defined(CONFIG_BAREMETAL_ICACHE)
	icache_enable();
#endif

#if defined(CONFIG_BAREMETAL_PLL0_INIT_533)
    pll0_init();
#endif

#if defined(CONFIG_BAREMETAL_PLL1_INIT_120)
	pll1_init();
#endif

#if defined(CONFIG_BAREMETAL_DDR_INIT)
    ddr_init();
#endif

#if defined(CONFIG_BAREMETAL_NEWLIB)
	__libc_init_array();
	atexit(__libc_fini_array);

	int result = main();
	exit(result);
#else
	main();
	while(1)
		;
#endif
}
