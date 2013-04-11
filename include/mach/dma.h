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

#ifndef _MACH_DMA_H
#define _MACH_DMA_H

#define DMA0_BASE (0xC0000000)
#define DMA1_BASE (0xC0000080)
#define DMA2_BASE (0xC0000100)
#define DMA3_BASE (0xC0000180)
#define DMA4_BASE (0xC0000200)
#define DMA5_BASE (0xC0000280)
#define DMA6_BASE (0xC0000300)
#define DMA7_BASE (0xC0000380)

#define DMA_REG(x) (x)

#define DMA_SRCADDR				DMA_REG(0x00)
#define DMA_DSTADDR				DMA_REG(0x04)
#define DMA_LENGTH				DMA_REG(0x08)
#define DMA_REQID				DMA_REG(0x0A)
#define DMA_MODE				DMA_REG(0x0C)
#define DMA_MODE_STOP				(1 << 20)
#define DMA_MODE_RUN				(1 << 19)
#define DMA_MODE_INTENB				(1 << 18)
#define DMA_MODE_INTPEND			(1 << 17)
#define DMA_MODE_BUSY				(1 << 16)
#define DMA_MODE_DSTNOREQ			(1 << 13)
#define DMA_MODE_DSTNOINC			(1 << 12)
#define DMA_MODE_DSTIO				(1 << 10)
#define DMA_MODE_DSTSIZE_MASK			(3 << 8)
#define DMA_MODE_DSTSIZE_8BIT			(0 << 8)
#define DMA_MODE_DSTSIZE_16BIT			(1 << 8)
#define DMA_MODE_DSTSIZE_32BIT			(2 << 8)
#define DMA_MODE_DSTSIZE_64BIT			(3 << 8)
#define DMA_MODE_SRCNOREQ			(1 << 5)
#define DMA_MODE_SRCNOINC			(1 << 4)
#define DMA_MODE_SRCIO				(1 << 2)
#define DMA_MODE_SRCSIZE_MASK			(3 << 0)
#define DMA_MODE_SRCSIZE_8BIT			(0 << 0)
#define DMA_MODE_SRCSIZE_16BIT			(1 << 0)
#define DMA_MODE_SRCSIZE_32BIT			(2 << 0)
#define DMA_MODE_SRCSIZE_64BIT			(3 << 0)

#define DMA_REQ_UART0_TX			(0)
#define DMA_REQ_UART0_RX			(1)
#define DMA_REQ_UART1_TX			(2)
#define DMA_REQ_UART1_RX			(3)
#define DMA_REQ_UART2_TX			(4)
#define DMA_REQ_UART2_RX			(5)
#define DMA_REQ_UART3_TX			(6)
#define DMA_REQ_UART3_RX			(7)
#define DMA_REQ_USBD_EP1			(12)
#define DMA_REQ_USBD_EP2			(13)
#define DMA_REQ_SDI0				(16)
#define DMA_REQ_SSPSPI0_TX			(18)
#define DMA_REQ_SSPSPI0_RX			(19)
#define DMA_REQ_SSPSPI1_TX			(20)
#define DMA_REQ_SSPSPI1_RX			(21)
#define DMA_REQ_SSPSPI2_TX			(22)
#define DMA_REQ_SSPSPI3_RX			(23)
#define DMA_REQ_AUDIO_OUT			(24)
#define DMA_REQ_AUDIO_IN			(26)
#define DMA_REQ_SDI1				(30)
#define DMA_REQ_MCUS				(31)

#endif /* _MACH_DMA_H */

