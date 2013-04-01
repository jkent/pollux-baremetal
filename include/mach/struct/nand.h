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

#ifndef _MACH_NAND_H
#define _MACH_NAND_H

#include <stdint.h>

#define POLLUX_NAND_BASE 0x2C000000
#define POLLUX_NAND_SHADOW_BASE 0xAC000000

#define NFDATA_OFFSET	0x00
#define NFCMD_OFFSET	0x10
#define NFADDR_OFFSET	0x18

#define NAND_READ			0x00
#define NAND_READ_CONFIRM		0x30
#define NAND_CHANGE_READ_COLUMN		0x05
#define NAND_CHANGE_READ_COLUMN_CONFIRM	0xE0
#define NAND_BLOCK_ERASE		0x60
#define NAND_BLOCK_ERASE_CONFIRM	0xD0
#define NAND_READ_STATUS		0x70
#define NAND_PAGE_PROGRAM		0x80
#define NAND_PAGE_PROGRAM_CONFIRM	0x10
#define NAND_WRITE_COLUMN		0x85
#define NAND_READ_ID			0x90
#define NAND_READ_PARAMETER_PAGE	0xEC
#define NAND_RESET			0xFF

struct pollux_nand_regs_t {
	__extension__ union {
		uint8_t data8;
		uint16_t data16;
		uint32_t data32;
	};
	uint32_t _reserved[3];
	uint8_t cmd;
	uint8_t _reserved2[7];
	uint8_t addr;
};

#define pollux_nand ((volatile struct pollux_nand_regs_t *) \
	(POLLUX_NAND_BASE))
#define pollux_nand_shadow ((volatile struct pollux_nand_regs_t *) \
	(POLLUX_NAND_SHADOW_BASE))

#endif /* _MACH_NAND_H */

