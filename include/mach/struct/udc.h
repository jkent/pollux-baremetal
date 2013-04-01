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

#include <stdint.h>

#define POLLUX_UDC_BASE 0xC0018000

struct pollux_udc_regs_t {
	uint16_t ir;       // * index register
	uint16_t eir;      // * endpoint interrupt register
	uint16_t eier;     // * endpoint interrupt enable register
	uint16_t far;      // * function address register
	uint16_t fnr;      // frame number register
	uint16_t edr;      // * endpoint direction register
	uint16_t tr;       // * test register
	uint16_t ssr;      // * system status register
	uint16_t scr;      // * system control register
	uint16_t ep0sr;    // * ep0 status register
	uint16_t ep0cr;    // * ep0 control register
	uint16_t esr;      // * [ir] endpoint status register
	uint16_t ecr;      // * [ir] endpoint control register
	uint16_t brcr;     // * [ir] byte read count register
	uint16_t bwcr;     // * [ir] byte write count register
	uint16_t mpr;      // * [ir] max packet register
	uint16_t dcr;      // * [ir] dma control register
	uint16_t dtcr;     // * [ir] dma transfer control register
	uint16_t dfcr;     // * [ir] dma fifo counter register
	uint16_t dttcr[2]; // * [ir] dma total transfer counter register
	uint16_t esr2;     // endpoint status register 2 (mirror of esr?)
	uint16_t scr2;     // system control register 2
	uint16_t _reserved;
	uint16_t epbr[16]; // endpoint buffer registers
	uint16_t plicr;    // phy link interface control register
	uint16_t pcr;      // phy control register
	uint16_t _reserved2[1019];
	uint16_t user0;
	uint16_t user1;
	uint16_t _reserved3[56];
	uint32_t clkenb;
	uint32_t clkgen;
};

#define pollux_udc ((volatile struct pollux_udc_regs_t *) \
	POLLUX_UDC_BASE)

/* eir */
#define UDC_EP15I			15
#define UDC_EP14I			14
#define UDC_EP13I			13
#define UDC_EP12I			12
#define UDC_EP11I			11
#define UDC_EP10I			10
#define UDC_EP9I			9
#define UDC_EP8I			8
#define UDC_EP7I			7
#define UDC_EP6I			6
#define UDC_EP5I			5
#define UDC_EP4I			4
#define UDC_EP3I			3
#define UDC_EP2I			2
#define UDC_EP1I			1
#define UDC_EP0I			0

/* eier */
#define UDC_EP15IE			15
#define UDC_EP14IE			14
#define UDC_EP13IE			13
#define UDC_EP12IE			12
#define UDC_EP11IE			11
#define UDC_EP10IE			10
#define UDC_EP9IE			9
#define UDC_EP8IE			8
#define UDC_EP7IE			7
#define UDC_EP6IE			6
#define UDC_EP5IE			5
#define UDC_EP4IE			4
#define UDC_EP3IE			3
#define UDC_EP2IE			2
#define UDC_EP1IE			1
#define UDC_EP0IE			0

/* fnr */
#define UDC_FTL				14
#define UDC_SM				13
#define UDC_FN				0

/* edr */
#define UDC_EP15DS			15
#define UDC_EP14DS			14
#define UDC_EP13DS			13
#define UDC_EP12DS			12
#define UDC_EP11DS			11
#define UDC_EP10DS			10
#define UDC_EP9DS			9
#define UDC_EP8DS			8
#define UDC_EP7DS			7
#define UDC_EP6DS			6
#define UDC_EP5DS			5
#define UDC_EP4DS			4
#define UDC_EP3DS			3
#define UDC_EP2DS			2
#define UDC_EP1DS			1

/* tr */
#define UDC_VBUS			15
#define UDC_EUERR			13
#define UDC_PERR			12
#define UDC_FDWR			11
#define UDC_SPDSEL			6
#define UDC_XTMD			4
#define UDC_XTPS			3
#define UDC_XTKS			2
#define UDC_XTJS			1
#define UDC_XTSNS			0

/* ssr */
#define UDC_BAERR			15
#define UDC_TMERR			14
#define UDC_BSERR			13
#define UDC_TCERR			12
#define UDC_DCERR			11
#define UDC_EOERR			10
#define UDC_VBUSOFF			9
#define UDC_VBUSON			8
#define UDC_TBM				7
#define UDC_DP				6
#define UDC_DM				5
#define UDC_HSP				4
#define UDC_SDE				3
#define UDC_HFRM			2
#define UDC_HFSUSP			1
#define UDC_HFRES			0

/* scr */
#define UDC_DTZIEN			14
#define UDC_DIEN			12
#define UDC_VBUSOFFEN			11
#define UDC_VBUSONEN			10
#define UDC_RWDE			9
#define UDC_EIE				8
#define UDC_BIS				7
#define UDC_SPDEN			6
#define UDC_RRDE			5
#define UDC_IPS				4
#define UDC_SPDC			3
#define UDC_MFRM			2
#define UDC_HSUSPE			1
#define UDC_HRESE			0

/* ep0sr */
#define UDC_EP0LWO			6
#define UDC_EP0SHT			4
#define UDC_EP0TST			1
#define UDC_EP0RSR			0

/* ep0cr */
#define UDC_EP0TTE			3
#define UDC_EP0TTS			2
#define UDC_EP0ESS			1
#define UDC_EP0TZLS			0

/* esr */
#define UDC_FUDR			15
#define UDC_FOVF			14
#define UDC_FPID			11
#define UDC_OSD				10
#define UDC_DTCZ			9
#define UDC_SPT				8
#define UDC_DOM				7
#define UDC_FFS				6
#define UDC_FSC				5
#define UDC_LWO				4
#define UDC_PSIF			2
#define UDC_TPS				1
#define UDC_RPS				0

/* ecr */
#define UDC_SRE				15 // reserved on s3c2443
#define UDC_INPKTHLD		12
#define UDC_OUTPKTHLD		11
#define UDC_TNPMF			9
#define UDC_IME				8
#define UDC_DUEN			7
#define UDC_FLUSH			6
#define UDC_TTE				5
#define UDC_TTS				3
#define UDC_CDP				2
#define UDC_ESS				1
#define UDC_IEMS			0 // TZLS on s3c2443

/* dcr */
#define UDC_ARDRD			5
#define UDC_FMDE			4
#define UDC_DMDE			3
#define UDC_TDR				2
#define UDC_RDR				1
#define UDC_DEN				0

/* scr2 */
#define UDC_EP2RST			2
#define UDC_EP1RST			1
#define UDC_EP0RST			0

/* plicr */
#define UDC_PLC				8
#define UDC_LPC				4

/* pcr */
#define UDC_URSTC			7
#define UDC_SIDC			6
#define UDC_OPMC			4
#define UDC_TMSC			3
#define UDC_XCRC			2
#define UDC_SUSPC			1
#define UDC_PCE				0

/* user0 */
#define UDC_XOBLOCK_ON		0

/* user1 */
#define UDC_VBUSENB			15

/* clkenb */
#define UDC_PCLKMODE		3
#define UDC_CLKGENENB		2
#define UDC_CLKENB			0

/* clkgen */
#define UDC_CLKDIV			4
#define UDC_CLKSRCSEL		1

#endif /* _MACH_UDC_H */

