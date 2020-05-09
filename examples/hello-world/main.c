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

#include <asm/types.h>
#include <driver/early-uart.h>
#include <stdio.h> 

int putchar(int c)
{
    if (c == '\n') {
        early_write_u8((u8)'\r');
    }
    early_write_u8((u8)c);
    return c;
}

int puts(const char *s)
{
    while (*s) {
        if (!putchar(*s++)) {
            return EOF;
        }
    }
    return putchar('\n');
}

int main(void)
{
    puts("Hello world!");

    while(1)
        ;
    return 0;
}
