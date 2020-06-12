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

#include <asm/io.h>
#include <driver/uart.h>
#include <mach/gpio.h>
#include <mach/uart.h>
#include <stddef.h>

/*
 * This is a minimal UART initialization.  We assume that PLL1 is set to the
 * default 147.461538 MHz and most of the UART registers are sane.  Tested
 * on the POLLUX VR3520F.
 */
void uart0_init_baudinfo(u32 baudinfo)
{
	void __iomem *uart = (void __iomem *)UART0_BASE;
	void __iomem *gpio = (void __iomem *)GPIOA_BASE;

	if (baudinfo == 0) {
		baudinfo = (11 << 16) | (39 << 4) | (1 << 1);
	}
	u16 clkgen = baudinfo & 0xFFFF;
	u16 brd = (baudinfo >> 16) & 0xFFFF;

	/* Wait until the transmitter is done */
	while (!(readw(uart + UART_TRSTATUS) & UART_TRSTATUS_TXDONE))
		;

	/* Configure clock */
	writew(clkgen, uart + UART_CLKGEN);
	/* Set baudrate divisor */
	writew(brd, uart + UART_BRD);
	/* Set GPIO as TX */
	writel(GPIO_ALTFN_ALTFN1 << (8 * 2), gpio + GPIO_ALTFNL);
	/* Enable TX and RX */
	writel(UART_UCON_TRANSMODE_INTPOLL | UART_UCON_RECVMODE_INTPOLL, uart + UART_UCON);
}

#if !defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
u8 uart0_readb(void)
{
	void __iomem *uart = (void __iomem *)UART0_BASE;
	while (!(readw(uart + UART_TRSTATUS) & UART_TRSTATUS_RXREADY))
		;
	return readb(uart + UART_RHB);
}

u32 uart0_readl(void)
{
	u32 n;
	n = uart0_readw();
	n |= uart0_readw() << 16;
	return n;
}
#endif

u16 uart0_readw(void)
{
	u16 n;
	n = uart0_readb();
	n |= uart0_readb() << 8;
	return n;
}

#if !defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
void uart0_writeb(u8 c)
{
	void __iomem *uart = (void __iomem *)UART0_BASE;
	while (!(readw(uart + UART_TRSTATUS) & UART_TRSTATUS_TXEMPTY))
		;
	writeb(c, uart + UART_THB);
}

void uart0_writel(u32 n)
{
	uart0_writew(n);
	uart0_writew(n >> 16);
}
#endif

void uart0_writew(u16 n)
{
	uart0_writeb(n);
	uart0_writeb(n >> 8);
}