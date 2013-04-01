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

#ifndef _MACH_DMA_H
#define _MACH_DMA_H

#include <stdint.h>

#define POLLUX_DMA_BASE 0xC0000000
#define POLLUX_DMA_OFFSET 0x80
#define POLLUX_DMA_COUNT 8

struct pollux_dma_regs_t {
	uint32_t srcaddr;
	uint32_t dstaddr;
	uint16_t length;
	uint16_t reqid;
	uint32_t mode;
	uint32_t srcaddr_buf;
	uint32_t dstaddr_buf;
	uint16_t length_buf;
	uint16_t reqid_buf;
	uint32_t mode_buf;
	uint32_t cmdwait;
	uint32_t cmdstop;
	uint32_t cmdbusy;
	uint32_t cmdspace;
};

#define pollux_dma(n) ((volatile struct pollux_dma_regs_t *) \
	(POLLUX_DMA_BASE + (POLLUX_DMA_OFFSET * (n))))

/* mode/mode_buf */
#define DMA_STOP			20
#define DMA_RUN				19
#define DMA_INTENB			18
#define DMA_INTPEND			17
#define DMA_BUSY			16
#define DMA_DSTNOTREQCHK		13
#define DMA_DSTNOTINC			12
#define DMA_DSTIOMODE			10
#define DMA_DSTIOSIZE			8
#define DMA_SRCNOTREQCHK		5
#define DMA_SRCNOTINC			4
#define DMA_PACKMODE			3
#define DMA_SRCIOMODE			2
#define DMA_SRCIOSIZE			0

#define DMA_UART0_TX			0
#define DMA_UART0_RX			1
#define DMA_UART1_TX			2
#define DMA_UART1_RX			3
#define DMA_UART2_TX			4
#define DMA_UART2_RX			5
#define DMA_UART3_TX			6
#define DMA_UART3_RX			7
#define DMA_USBD_EP1			12
#define DMA_USBD_EP2			13
#define DMA_SDI0			16
#define DMA_SSPSPI0_TX			18
#define DMA_SSPSPI0_RX			19
#define DMA_SSPSPI1_TX			20
#define DMA_SSPSPI1_RX			21
#define DMA_SSPSPI2_TX			22
#define DMA_SSPSPI3_RX			23
#define DMA_AUDIO_OUT			24
#define DMA_AUDIO_IN			26
#define DMA_SDI1			30
#define DMA_MCUS			31

#endif /* _MACH_DMA_H */

