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
#include <baremetal/cache.h>
#include <baremetal/clocking.h>
#include <baremetal/exception.h>
#include <baremetal/mmu.h>
#include <baremetal/util.h>
#include <driver/uart.h>
#include <mach/alive.h>
#include <stdlib.h>

extern void __libc_init_array(void);
extern void __libc_fini_array(void);
extern int main(void);

void startup(void)
{
	/* clear .bss */
	asm ("ldr r0, =_bss\n\t"
		"ldr r1, =_ebss\n\t"
		"mov r2, #0\n"
	"1:	cmp r0, r1\n\t"
		"bhs 2f\n\t"
		"str r2, [r0]\n\t"
		"add r0, r0, #4\n\t"
		"b 1b\n"
	"2:" ::: "r0", "r1", "r2", "cc", "memory");

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
	uart0_writeb(0x5A);
	while(uart0_readb() != 0xA5)
		;
#endif

#if defined(CONFIG_BAREMETAL_STARTUP_DEBUG)
	halt();
#endif

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
