/* vim: set ts=4 sw=4 noexpandtab
 *
 * Copyright (C) 2011-2020 Jeff Kent <jakent@gmail.com>
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

#include <asm/attributes.h>
#include <asm/io.h>
#include <driver/lowlevel_uart.h>
#include <mach/alive.h>
#include <stddef.h>

#define STARTUP_SIGNATURE 0x54524155

#if defined (CONFIG_BAREMETAL_LATCH_POWER)
static void startup_latch_power(void);
#endif
static void startup_set_baudrate(void);
static void startup_load_rest(void);
void main(void);

EARLY_CODE NAKED void startup(void)
{
	lowlevel_uart_init(0);
#if defined(CONFIG_BAREMETAL_LATCH_POWER)
	startup_latch_power();
#endif
	lowlevel_write_u32(STARTUP_SIGNATURE);
	startup_set_baudrate();
	startup_load_rest();
	main();

	/* Never return */
	while(1);	
}

#if defined(CONFIG_BAREMETAL_LATCH_POWER)
EARLY_CODE static void startup_latch_power(void)
{
	writel(ALIVE_PWRGATEREG_NPOWERGATING, ALIVE_BASE + ALIVE_PWRGATEREG);
	writel(0, ALIVE_BASE + ALIVE_GPIORSTREG);
	writel(ALIVE_GPIO_VDDPWRONRST, ALIVE_BASE + ALIVE_GPIOSETREG);
	writel(0, ALIVE_BASE + ALIVE_GPIOSETREG);
	writel(0, ALIVE_BASE + ALIVE_PWRGATEREG);
}
#endif

EARLY_CODE static void startup_set_baudrate(void)
{
	u32 baudinfo = lowlevel_read_u32();
	lowlevel_write_u8(1);
	lowlevel_uart_init(baudinfo);
	while (1) {
		if (lowlevel_read_u8() != '\x55') {
			continue;
		}
		if (lowlevel_read_u8() == '\xAA') {
			break;
		}
	}
	lowlevel_write_u8(1);
}

EARLY_CODE static void startup_load_rest(void)
{
	void *start = (void *)(readw(0xA4000000) & 0x400 ? 16384 : 512);
	u32 size = lowlevel_read_u32();

#if CONFIG_BAREMETAL_RELOCATE
	start += CONFIG_BAREMETAL_RELOCATE_ADDRESS;
#endif

	for (void *p = start; p < start + size; p += 4) {
		*(u32 *)p = lowlevel_read_u32();
	}
}
