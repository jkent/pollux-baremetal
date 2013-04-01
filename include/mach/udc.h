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

#ifndef _MACH_UDC_H
#define _MACH_UDC_H

#define UDC_BASE (0xC0018000)

#define UDC_REG(x) (x)

/* Non-Indexed Registers */
#define UDC_IR				UDC_REG(0x00) /* Index Register */
#define UDC_EIR				UDC_REG(0x02) /* EP Intr Status */
#define UDC_EIER			UDC_REG(0x04) /* EP Intr Enable */
#define UDC_EP0				(1 << 0)
#define UDC_FAR				UDC_REG(0x06) /* Gadget Address */
#define UDC_FNR				UDC_REG(0x08) /* Frame Number */
#define UDC_EDR				UDC_REG(0x0a) /* EP Direction */
#define UDC_TR				UDC_REG(0x0c) /* Test Register */
#define UDC_SSR				UDC_REG(0x0e) /* System Status */
#define UDC_SSR_FLAGS			(0xff8f)
#define UDC_SSR_ERR			(0xfc80)
#define UDC_SSR_VBUSOFF			(1 << 9)
#define UDC_SSR_VBUSON			(1 << 8)
#define UDC_SSR_HSP			(1 << 4)
#define UDC_SSR_SDE			(1 << 3)
#define UDC_SSR_RESUME			(1 << 2)
#define UDC_SSR_SUSPEND			(1 << 1)
#define UDC_SSR_RESET			(1 << 0)
#define UDC_SCR				UDC_REG(0x10) /* System Control */
#define UDC_SCR_DTZIEN_EN		(1 << 14)
#define UDC_SCR_RRD_EN			(1 << 5)
#define UDC_SCR_SUS_EN			(1 << 1)
#define UDC_SCR_RST_EN			(1 << 0)
#define UDC_EP0SR			UDC_REG(0x12) /* EP0 Status */
#define UDC_EP0SR_EP0_LWO		(1 << 6)
#define UDC_EP0SR_STALL			(1 << 4)
#define UDC_EP0SR_TX_SUCCESS		(1 << 1)
#define UDC_EP0SR_RX_SUCCESS		(1 << 0)
#define UDC_EP0CR			UDC_REG(0x14) /* EP0 Control */
#define UDC_BR(_x)			UDC_REG(0x30 + (_x * 2))

/* Indexed Registers */
#define UDC_ESR				UDC_REG(0x16) /* EPn Status */
#define UDC_ESR_DTCZ			(1 << 9)
#define UDC_ESR_SPT			(1 << 8)
#define UDC_ESR_FLUSH			(1 << 6)
#define UDC_ESR_STALL			(1 << 5)
#define UDC_ESR_LWO			(1 << 4)
#define UDC_ESR_PSIF_ONE		(1 << 2)
#define UDC_ESR_PSIF_TWO		(2 << 2)
#define UDC_ESR_TX_SUCCESS		(1 << 1)
#define UDC_ESR_RX_SUCCESS		(1 << 0)
#define UDC_ECR				UDC_REG(0x18) /* EPn Control */
#define UDC_ECR_DUEN			(1 << 7)
#define UDC_ECR_FLUSH			(1 << 6)
#define UDC_ECR_CDP			(1 << 2)
#define UDC_ECR_STALL			(1 << 1)
#define UDC_ECR_IEMS			(1 << 0)
#define UDC_BRCR			UDC_REG(0x1a) /* Read Count */
#define UDC_BWCR			UDC_REG(0x1c) /* Write Count */
#define UDC_MPR				UDC_REG(0x1e) /* Max Pkt Size */
#define UDC_DCR				UDC_REG(0x20) /* DMA Control */
#define UDC_DCR_ARDRD			(1 << 5)
#define UDC_DCR_FMDE			(1 << 4)
#define UDC_DCR_DMDE			(1 << 3)
#define UDC_DCR_TDR			(1 << 2)
#define UDC_DCR_RDR			(1 << 1)
#define UDC_DCR_DEN			(1 << 0)
#define UDC_DTCR			UDC_REG(0x22) /* DMA Transfer Count */
#define UDC_DFCR			UDC_REG(0x24) /* DMA FIFO Count */
#define UDC_DTTCRL			UDC_REG(0x26) /* DMA Total Low */
#define UDC_DTTCRH			UDC_REG(0x28) /* DMA Total High */

/* PHY Registers */
#define UDC_PLICR			UDC_REG(0x50)
#define UDC_PCR				UDC_REG(0x52)
#define UDC_PCR_URSTC			(1 << 7)
#define UDC_PCR_PCE			(1 << 0)

/* Others */
#define UDC_USER0			UDC_REG(0x84a)
#define UDC_USER0_XOBLOCK		(1 << 0)
#define UDC_USER1			UDC_REG(0x84c)
#define UDC_USER1_VBUSENB		(1 << 15)

/* Clock Registers - 32-bit */
#define UDC_CLKENB			UDC_REG(0x8c0)
#define UDC_CLKENB_PCLK_ACCESS		(0 << 3)
#define UDC_CLKENB_PCLK_ALWAYS		(1 << 3)
#define UDC_CLKENB_CLKGENENB		(1 << 2)
#define UDC_CLKENB_USBD_DISABLED	(0 << 0)
#define UDC_CLKENB_USBD_DYNAMIC		(2 << 0)
#define UDC_CLKENB_USBD_ALWAYS		(3 << 0)
#define UDC_CLKGEN			UDC_REG(0x8c4)
#define UDC_CLKGEN_CLKDIV(_x)		(_x << 4)
#define UDC_CLKGEN_CLKSRC_EXT		(3 << 1)

#endif /* _MACH_UDC_H */

