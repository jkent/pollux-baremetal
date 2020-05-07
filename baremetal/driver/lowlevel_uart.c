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
#include <mach/gpio.h>
#include <mach/uart.h>
#include <stddef.h>

#define BAUDINFO(baud, clksrc, div, brd) \
	{baud, UART_CLKGEN_CLKDIV(div) | UART_CLKGEN_CLKSRCSEL(clksrc), brd}
#define END_BAUDINFO {0, 0, 0}

struct lowlevel_uart_baudinfo_t {
	u32 baudrate;
	u16 clkgen;
	u16 brd;
};

EARLY_RODATA const static struct lowlevel_uart_baudinfo_t baudinfo_table[] = {
	BAUDINFO(  19200, 1, 39, 11),
	BAUDINFO( 115200, 1, 39,  1),
	BAUDINFO( 230400, 1,  4,  7),
	BAUDINFO( 460800, 1,  4,  3),
	BAUDINFO( 921600, 1,  4,  1),
	BAUDINFO(1500000, 0, 15,  0),
	END_BAUDINFO,
};

/*
 * This is a minimal UART initialization.  We assume that PLL1 is set to the
 * default 147.461538 MHz and most of the UART registers are sane.  Tested
 * on the POLLUX VR3520F.
 */
EARLY_CODE void lowlevel_uart_init(const lowlevel_uart_baudinfo_t *baudinfo)
{
	if (baudinfo == NULL) {
		baudinfo = &baudinfo_table[0];
	}

	/* Wait until the transmitter is done */
	while (!(readw(UART0_BASE + UART_TRSTATUS) & UART_TRSTATUS_TXDONE))
		;

	/* Configure clock */
	writew(baudinfo->clkgen, UART0_BASE + UART_CLKGEN);
	/* Set baudrate divisor */
	writew(baudinfo->brd, UART0_BASE + UART_BRD);
	/* Set GPIO as TX */
	writel(GPIO_ALTFN_ALTFN1 << (8 * 2), GPIOA_BASE + GPIO_ALTFNL);
	/* Enable TX and RX */
	writel(UART_UCON_TRANSMODE_INTPOLL | UART_UCON_RECVMODE_INTPOLL, UART0_BASE + UART_UCON);
}

EARLY_CODE const lowlevel_uart_baudinfo_t *lowlevel_uart_find_baudinfo(u32 baudrate)
{
	const lowlevel_uart_baudinfo_t *p = &baudinfo_table[0];

	while (p->baudrate) {
		if (p->baudrate == baudrate) {
			return p;
		}
		p++;
	}
	return NULL;
}

EARLY_CODE u8 lowlevel_uart_getc(void)
{
	while (!(readw(UART0_BASE + UART_TRSTATUS) & UART_TRSTATUS_RXREADY))
		;
	return readb(UART0_BASE + UART_RHB);
}

EARLY_CODE void lowlevel_uart_putc(u8 c)
{
	while (!(readw(UART0_BASE + UART_TRSTATUS) & UART_TRSTATUS_TXEMPTY))
		;
	writeb(c, UART0_BASE + UART_THB);
}

EARLY_CODE u16 lowlevel_uart_get_u16(void)
{
	u16 n;
	n = lowlevel_uart_getc();
	n |= lowlevel_uart_getc() << 8;
	return n;
}

EARLY_CODE void lowlevel_uart_put_u16(u16 n)
{
	lowlevel_uart_putc(n);
	lowlevel_uart_putc(n >> 8);
}

EARLY_CODE u32 lowlevel_uart_get_u32(void)
{
	u32 n;
	n = lowlevel_uart_get_u16();
	n |= lowlevel_uart_get_u16() << 16;
	return n;
}

EARLY_CODE void lowlevel_uart_put_u32(u32 n)
{
	lowlevel_uart_put_u16(n);
	lowlevel_uart_put_u16(n >> 16);
}
