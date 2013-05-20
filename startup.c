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

#include "config.h"
#include "baremetal/cache.h"
#include "baremetal/uart.h"
#include "baremetal/util.h"

extern void ddr_init(void);
extern void pll0_init(void);
extern int main(void);

__attribute__((noreturn))
__attribute__((naked))
void startup(void)
{
#if defined(CONFIG_BAREMETAL_ENABLE_DCACHE)
	init_tlb(main_tlb);
	assign_tlb(main_tlb);
	enable_cache();
#elif defined(CONFIG_BAREMETAL_ENABLE_ICACHE)
	enable_cache();
#endif

#if defined(CONFIG_BAREMETAL_DDR_INIT)
	ddr_init();
#endif

#if defined(CONFIG_BAREMETAL_PLL0_INIT)
	pll0_init();
#endif

#if defined(CONFIG_BAREMETAL_UART_BASIC)
	uart_basic_init();
#endif

	main();
	halt();
}

