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

#include <stdio.h>

#include "baremetal/clocking.h"
#include "baremetal/mmu.h"
#include "baremetal/uart.h"
#include "baremetal/util.h"

extern void uart_basic_init(void);
extern int main(void);

void __attribute__((naked, noreturn)) _start(void)
{
	int i;

	uart_basic_init();

	fputs("\nstartup:", stdout);
	fflush(stdout);

	fputs(" ddr", stdout);
	fflush(stdout);
	init_ddr();

	fputs(" pll", stdout);
	fflush(stdout);
	init_pll();

	fputs(" mmu", stdout);
	fflush(stdout);
	enable_mmu();

	fputs("\nOK!\n", stdout);

	i = main();
	printf("main exited with %d\n", i);
	halt();
}
