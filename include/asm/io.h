/*
 * Copyright (C) 2020 Jeff Kent <jeff@jkent.net>
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

#pragma once

#include "asm/types.h"

#define readb(a) (*(volatile u8 *)(a))
#define readw(a) (*(volatile u16 *)(a))
#define readl(a) (*(volatile u32 *)(a))
#define readq(a) (*(volatile u64 *)(a))

#define writeb(v, a) ((void)(*(volatile u8 *)(a) = (v)))
#define writew(v, a) ((void)(*(volatile u16 *)(a) = (v)))
#define writel(v, a) ((void)(*(volatile u32 *)(a) = (v)))
#define writeq(v, a) ((void)(*(volatile u64 *)(a) = (v)))
