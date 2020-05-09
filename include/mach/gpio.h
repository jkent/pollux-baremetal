/*
 * Copyright (C) 2013-2020 Jeff Kent <jeff@jkent.net>
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

#define GPIOA_BASE (0xC000A000)
#define GPIOB_BASE (0xC000A040)
#define GPIOC_BASE (0xC000A080)

#define GPIO_REG(x) (x)

#define GPIO_OUT				GPIO_REG(0x00)
#define GPIO_OUTENB				GPIO_REG(0x04)
#define GPIO_DETMODEL				GPIO_REG(0x08)
#define GPIO_DETMODEH				GPIO_REG(0x0C)
#define GPIO_INTENB				GPIO_REG(0x10)
#define GPIO_DET				GPIO_REG(0x14)
#define GPIO_PAD				GPIO_REG(0x18)
#define GPIO_PUENB				GPIO_REG(0x1C)
#define GPIO_ALTFNL				GPIO_REG(0x20)
#define GPIO_ALTFNH				GPIO_REG(0x24)
#define GPIO_ALTFN_GPIO				(0)
#define GPIO_ALTFN_ALTFN1			(1)
#define GPIO_ALTFN_ALTFN2			(2)
