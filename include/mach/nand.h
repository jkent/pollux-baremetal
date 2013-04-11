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

#ifndef _MACH_NAND_H
#define _MACH_NAND_H

#define NAND_BASE (0xAC000000)

#define NAND_REG(x) (x)

#define NAND_DATA			NAND_REG(0x00)
#define NAND_CMD			NAND_REG(0x10)
#define NAND_ADDR			NAND_REG(0x18)

#define NAND_CMD_READ0			(0x00)
#define NAND_CMD_READ1			(0x01)
#define NAND_CMD_RNDOUT			(0x05)
#define NAND_CMD_PAGEPROG		(0x10)
#define NAND_CMD_READOOB		(0x50)
#define NAND_CMD_ERASE1			(0x60)
#define NAND_CMD_STATUS			(0x70)
#define NAND_CMD_STATUS_MULTI		(0x71)
#define NAND_CMD_SEQIN			(0x80)
#define NAND_CMD_RNDIN			(0x85)
#define NAND_CMD_READID			(0x90)
#define NAND_CMD_ERASE2			(0xd0)
#define NAND_CMD_PARAM			(0xec)
#define NAND_CMD_GET_FEATURES		(0xee)
#define NAND_CMD_SET_FEATURES		(0xef)
#define NAND_CMD_RESET			(0xff)
#define NAND_CMD_LOCK			(0x2a)
#define NAND_CMD_UNLOCK1		(0x23)
#define NAND_CMD_UNLOCK2		(0x24)
#define NAND_CMD_READSTART		(0x30)
#define NAND_CMD_RNDOUTSTART		(0xe0)
#define NAND_CMD_CACHEDPROG		(0x15)

#define NAND_STATUS_FAIL		(0x01)
#define NAND_STATUS_FAIL_N1		(0x02)
#define NAND_STATUS_TRUE_READY		(0x20)
#define NAND_STATUS_READY		(0x40)
#define NAND_STATUS_WP			(0x80)

#endif /* _MACH_NAND_H */

