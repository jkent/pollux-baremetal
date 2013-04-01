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

#include <stdint.h>

#define POLLUX_UART_BASE 0xC0016000
#define POLLUX_UART_OFFSET1 0x80
#define POLLUX_UART_OFFSET2 0x800
#define POLLUX_UART_COUNT 4

struct pollux_uart_regs_t {
	uint16_t lcon;
	uint16_t ucon;
	uint16_t fcon;
	uint16_t mcon;
	uint16_t trstatus;
	uint16_t estatus;
	uint16_t fstatus;
	uint16_t mstatus;
	uint16_t thb;
	uint16_t rhb;
	uint16_t brd;
	uint16_t timeout;
	uint16_t intstatus;
	uint16_t _reserved[19];
	uint32_t clkenb;
	uint32_t clkgen;
};

#define pollux_uart(n) ((volatile struct pollux_uart_regs_t *) \
	(POLLUX_UART_BASE + (POLLUX_UART_OFFSET1 * (n)) + \
	((POLLUX_UART_OFFSET2 - (POLLUX_UART_OFFSET1 * 2)) * (n >> 1))))

/* lcon */
#define UART_SYNC_PENDCLR		7
#define UART_SIR_MODE			6
#define UART_PARITY_MODE		3
#define UART_STOPBIT			2
#define UART_WORD_LEN			0

/* ucon */
#define UART_TX_INT			9
#define UART_RX_INT			8
#define UART_RX_TIMEOUT			7
#define UART_RX_ERRSTATUS		6
#define UART_LOOPBACK_MODE		5
#define UART_SEND_BREAK			4
#define UART_TRANS_MODE			2
#define UART_RECEIVE_MODE		0

/* fcon */
#define UART_TX_FIFO_TRIGGER		6
#define UART_RX_FIFO_TRIGGER		4
#define UART_TX_FIFO_RESET		2
#define UART_RX_FIFO_RESET		1
#define UART_FIFO_EN			0

/* mcon */
#define UART_HALF_CH_ENB		7
#define UART_SCRXENB			6
#define UART_SCTXENB			5
#define UART_AFC			4
#define UART_DTR_ACTIVE			1
#define UART_RTS_ACTIVE			0

/* trstatus */
#define UART_TRANSMITTER_EMPTY		2
#define UART_TRANSMIT_BUFFER_EMPTY	1
#define UART_RECEIVE_BUFFER_DATA_READY	0

/* estatus */
#define UART_BREAK_DETECT		3
#define UART_FRAME_ERROR		2
#define UART_PARITY_ERROR		1
#define UART_OVERRUN_ERROR		0

/* fstatus */
#define UART_RX_FIFO_ERROR		10
#define UART_TX_FIFO_FULL		9
#define UART_RX_FIFO_FULL		8
#define UART_TX_FIFO_COUNT		4
#define UART_RX_FIFO_COUNT		0

/* mstatus */
#define UART_DELTA_DCD			7
#define UART_DELTA_RI			6
#define UART_DELTA_DSR			5
#define UART_DELTA_CTS			4
#define UART_DCD			3
#define UART_RI				2
#define UART_DSR			1
#define UART_CTS			0

/* intstatus */
#define UART_MENB			7
#define UART_ERRENB			6
#define UART_IRQRXENB			5
#define UART_IRQTXENB			4
#define UART_MPEND			3
#define UART_ERRPEND			2
#define UART_RXPEND			1
#define UART_TXPEND			0

/* clkenb */
#define UART_PCLKMODE			3
#define UART_CLKGENENB			2

/* clkgen */
#define UART_CLKDIV			4
#define UART_CLKSRCSEL			1

#endif /* _MACH_UART_H */

