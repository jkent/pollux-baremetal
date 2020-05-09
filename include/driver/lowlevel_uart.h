/*
 * Copyright (C) 2011-2020 Jeff Kent <jeff@jkent.net>
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

#include <asm/types.h>

void lowlevel_uart_init(u32 baudinfo);
u8 lowlevel_read_u8(void);
void lowlevel_write_u8(u8 c);
u16 lowlevel_read_u16(void);
void lowlevel_write_u16(u16 n);
u32 lowlevel_read_u32(void);
void lowlevel_write_u32(u32 n);
