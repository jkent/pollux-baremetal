/* vim: set ts=4 sw=4 noexpandtab
 *
 * Copyright (C) 2011-2020 Jeff Kent <jakent@gmail.com>
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
 
#ifndef __UART_H__
#define __UART_H__

#include <asm/types.h>

typedef struct lowlevel_uart_baudinfo_t lowlevel_uart_baudinfo_t;

void lowlevel_uart_init(const lowlevel_uart_baudinfo_t *baudinfo);
const lowlevel_uart_baudinfo_t *lowlevel_uart_find_baudinfo(u32 baudrate);
u8 lowlevel_uart_getc(void);
void lowlevel_uart_putc(u8 c);
u16 lowlevel_uart_get_u16(void);
void lowlevel_uart_put_u16(u16 n);
u32 lowlevel_uart_get_u32(void);
void lowlevel_uart_put_u32(u32 n);

#endif /* __UART_H__ */
