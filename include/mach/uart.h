/*
 * Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
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

#ifndef _MACH_UART_H
#define _MACH_UART_H

#define UART0_BASE (0xC0016000)
#define UART1_BASE (0xC0016080)
#define UART2_BASE (0xC0016800)
#define UART3_BASE (0xC0016080)

#define UART_REG(x) (x)

#define UART_LCON				UART_REG(0x00)
#define UART_UCON				UART_REG(0x02)
#define UART_UCON_TRANSMODE_MASK		(3 << 2)			
#define UART_UCON_TRANSMODE_DISABLE		(0 << 2)			
#define UART_UCON_TRANSMODE_INTPOLL		(1 << 2)			
#define UART_UCON_TRANSMODE_DMA			(2 << 2)			
#define UART_UCON_RECVMODE_MASK			(3 << 0)
#define UART_UCON_RECVMODE_DISABLE		(0 << 0)
#define UART_UCON_RECVMODE_INTPOLL		(1 << 0)
#define UART_UCON_RECVMODE_DMA			(2 << 0)
#define UART_FCON				UART_REG(0x04)
#define UART_MCON				UART_REG(0x06)
#define UART_TRSTATUS				UART_REG(0x08)
#define UART_TRSTATUS_TXDONE			(1 << 2)
#define UART_TRSTATUS_TXEMPTY			(1 << 1)
#define UART_TRSTATUS_RXREADY			(1 << 0)
#define UART_ESTATUS				UART_REG(0x0a)
#define UART_FSTATUS				UART_REG(0x0c)
#define UART_MSTATUS				UART_REG(0x0e)
#define UART_THB				UART_REG(0x10)
#define UART_RHB				UART_REG(0x12)
#define UART_BRD				UART_REG(0x14)
#define UART_TIMEOUT				UART_REG(0x16)
#define UART_INTSTATUS				UART_REG(0x18)
#define UART_CLKENB				UART_REG(0x40)
#define UART_CLKENB_PCLKMODE			(1 << 3)
#define UART_CLKENB_CLKGENENB			(1 << 2)
#define UART_CLKGEN				UART_REG(0x44)
#define UART_CLKGEN_CLKDIV_MASK			(0x3F << 4)
#define UART_CLKGEN_CLKDIV(_x)			(_x << 4)
#define UART_CLKGEN_CLKSRCSEL_PLL0		(0 << 1)
#define UART_CLKGEN_CLKSRCSEL_PLL1		(1 << 1)

#endif /* _MACH_UART_H */

