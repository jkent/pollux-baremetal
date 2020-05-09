/*
 * Copyright (C) 2020 Jeff Kent <jeff@jkent.net>
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

#pragma once

#define ALIVE_BASE (0xC0019000)

#define ALIVE_REG(x) (x)

#define ALIVE_PWRGATEREG			ALIVE_REG(0x00)
#define ALIVE_PWRGATEREG_NPOWERGATING 	(1 << 0)
#define ALIVE_GPIORSTREG			ALIVE_REG(0x04)
#define ALIVE_GPIOSETREG			ALIVE_REG(0x08)
#define ALIVE_GPIOREADREG		ALIVE_REG(0x0C)
#define ALIVE_GPIO_VDDPWRTOGGLE		(1 << 8)
#define ALIVE_GPIO_VDDPWRONRST		(1 << 7)
#define ALIVE_GPIO(_x) 			(1 << _x)
#define ALIVE_GPIOSCRATCHRST		ALIVE_REG(0x10)
#define ALIVE_GPIOSCRATCHSET		ALIVE_REG(0x14)
#define ALIVE_GPIOSCRATCREAD		ALIVE_REG(0x18)
