/*
 * Copyright (C) 2011-2020 Jeff Kent <jeff@jkent.net>
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
#include <mach/gpio.h>
#include <mach/uart.h>
#include <stddef.h>

/*
 * This is a minimal UART initialization.  We assume that PLL1 is set to the
 * default 147.461538 MHz and most of the UART registers are sane.  Tested
 * on the POLLUX VR3520F.
 */
EARLY_CODE void lowlevel_uart_init(u32 baudinfo)
{
	if (baudinfo == 0) {
		baudinfo = (11 << 16) | (1 << 1) | (39 << 4);
	}
	u16 clkgen = baudinfo & 0xFFFF;
	u16 brd = (baudinfo >> 16) & 0xFFFF;

	/* Wait until the transmitter is done */
	while (!(readw(UART0_BASE + UART_TRSTATUS) & UART_TRSTATUS_TXDONE))
		;

	/* Configure clock */
	writew(clkgen, UART0_BASE + UART_CLKGEN);
	/* Set baudrate divisor */
	writew(brd, UART0_BASE + UART_BRD);
	/* Set GPIO as TX */
	writel(GPIO_ALTFN_ALTFN1 << (8 * 2), GPIOA_BASE + GPIO_ALTFNL);
	/* Enable TX and RX */
	writel(UART_UCON_TRANSMODE_INTPOLL | UART_UCON_RECVMODE_INTPOLL, UART0_BASE + UART_UCON);
}

EARLY_CODE u8 lowlevel_read_u8(void)
{
	while (!(readw(UART0_BASE + UART_TRSTATUS) & UART_TRSTATUS_RXREADY))
		;
	return readb(UART0_BASE + UART_RHB);
}

EARLY_CODE void lowlevel_write_u8(u8 c)
{
	while (!(readw(UART0_BASE + UART_TRSTATUS) & UART_TRSTATUS_TXEMPTY))
		;
	writeb(c, UART0_BASE + UART_THB);
}

EARLY_CODE u16 lowlevel_read_u16(void)
{
	u16 n;
	n = lowlevel_read_u8();
	n |= lowlevel_read_u8() << 8;
	return n;
}

EARLY_CODE void lowlevel_write_u16(u16 n)
{
	lowlevel_write_u8(n);
	lowlevel_write_u8(n >> 8);
}

EARLY_CODE u32 lowlevel_read_u32(void)
{
	u32 n;
	n = lowlevel_read_u16();
	n |= lowlevel_read_u16() << 16;
	return n;
}

EARLY_CODE void lowlevel_write_u32(u32 n)
{
	lowlevel_write_u16(n);
	lowlevel_write_u16(n >> 16);
}
