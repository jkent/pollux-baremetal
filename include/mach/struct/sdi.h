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

#ifndef _MACH_SDI_H
#define _MACH_SDI_H

#include <stdint.h>

#define POLLUX_SDI_BASE 0xC0009800
#define POLLUX_MLC_OFFSET 0x3000
#define POLLUX_MLC_COUNT 2

struct pollux_sdi_regs_t {
	uint32_t ctrl;
	uint32_t _reserved;
	uint32_t clkdiv;
	uint32_t _reserved2;
	uint32_t clkena;
	uint32_t tmout;
	uint32_t ctype;
	uint32_t blksiz;
	uint32_t bytcnt;
	uint32_t intmask;
	uint32_t cmdarg;
	uint32_t cmd;
	uint32_t resp0;
	uint32_t resp1;
	uint32_t resp2;
	uint32_t resp3;
	uint32_t mintsts;
	uint32_t rintsts;
	uint32_t status;
	uint32_t fifoth;
	uint32_t _reserved3[3];
	uint32_t tcbcnt;
	uint32_t tbbcnt;
	uint32_t _reserved4[39];
	uint32_t data;
	uint32_t _reserved5[431];
	uint32_t clkenb;
	uint32_t clkgen;
};

#define pollux_sdi(n) ((volatile struct pollux_sdi_regs_t *) \
	(POLLUX_SDI_BASE + (POLLUX_SDI_SIZE * (n))))

#define SDI_ABORT_RDATA			8
#define SDI_SEND_IRQ_RESP		7
#define SDI_READ_WAIT			6
#define SDI_DMA_ENA			5
#define SDI_INT_ENA			4
#define SDI_DMARST			2
#define SDI_FIFORST			1
#define SDI_CTRLRST			0

#define SDI_LOWPWR			16
#define SDI_CLKENA			0

#define SDI_DTMOUT			8
#define SDI_RSPTMOUT			0

#define SDI_EIGHTBIT			16
#define SDI_WIDTH			0

#define SDI_MSKSDIO			16
#define SDI_MSKEBE			15
#define SDI_MSKACD			14
#define SDI_MSKSBE			13
#define SDI_MSKHLE			12
#define SDI_MSKFRUN			11
#define SDI_MSKHTO			10
#define SDI_MSKDRTO			9
#define SDI_MSKRTO			8
#define SDI_MSKDCRC			7
#define SDI_MSKRCRC			6
#define SDI_MSKRXDR			5
#define SDI_MSKTXDR			4
#define SDI_MSKDTO			3
#define SDI_MSKCD			2
#define SDI_MSKRE			1

#define SDI_STARTCMD			31
#define SDI_UPDATECLKONLY		21
#define SDI_CARDNUM			16
#define SDI_SENDINIT			15
#define SDI_STOPABORT			14
#define SDI_WAITPRVDAT			13
#define SDI_SENDAUTOSTOP		12
#define SDI_TRMODE			11
#define SDI_RW				10
#define SDI_DATEXP			9
#define SDI_CHKRSPCRC			8
#define SDI_RSPLEN			7
#define SDI_RSPEXP			6
#define SDI_CMDINDEX			0

#define SDI_SDIOINT			16
#define SDI_EBEINT			15
#define SDI_ACDINT			14
#define SDI_SBEINT			13
#define SDI_HLEINT			12
#define SDI_FRUNINT			11
#define SDI_HTOINT			10
#define SDI_DRTOINT			9
#define SDI_RTOINT			8
#define SDI_DCRCINT			7
#define SDI_RCRCINT			6
#define SDI_RXDRINT			5
#define SDI_TXDRINT			4
#define SDI_DTOINT			3
#define SDI_CDINT			2
#define SDI_REINT			1

#define SDI_SDIO			16
#define SDI_EBE				15
#define SDI_ACD				14
#define SDI_SBE				13
#define SDI_HLE				12
#define SDI_FRUN			11
#define SDI_HTO				10
#define SDI_DRTO			9
#define SDI_RTO				8
#define SDI_DCRC			7
#define SDI_RCRC			6
#define SDI_RXDR			5
#define SDI_TXDR			4
#define SDI_DTO				3
#define SDI_CD				2
#define SDI_RE				1

#define SDI_DMAREQ			31
#define SDI_DMAACK			30
#define SDI_FIFOCOUNT			17
#define SDI_RSPINDEX			11
#define SDI_FSMBUSY			10
#define SDI_DATABUSY			9
#define SDI_CPRESENT			8
#define SDI_CMDFSM			4
#define SDI_FIFOFULL			3
#define SDI_FIFOEMPTY			2
#define SDI_TXWMARK			1
#define SDI_RXWMARK			0

#define SDI_RXTH			16
#define SDI_TXTH			0

#define SDI_TCLKMODE			3
#define SDI_CLKGENENB			2

#define SDI_CLKDIV0			4
#define SDI_CLKSRCSEL0			1

#endif /* _MACH_SDI_H */

