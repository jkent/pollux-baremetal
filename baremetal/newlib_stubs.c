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
#include <baremetal/linker.h>
#include <driver/early_uart.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>

extern u32 __heap_start__;

int _close(int fd)
{
    return -1;
}

void _fini(void)
{
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

void _init(void)
{
}

int _isatty(int file)
{
    return  1;
}

int _lseek(int file, int offset, int whence)
{
    return  0;
}

int _read(int fd, char *buf, int count)
{
    return -1;
}

caddr_t _sbrk(ptrdiff_t incr)
{
    static caddr_t heap = NULL;

    if (heap == NULL) {
        heap = (caddr_t)&__heap_start__;
    }

    caddr_t prev_heap = heap;
    register caddr_t sp __asm__("sp");
    if (heap + incr > sp) {
        errno = ENOMEM;
        return (caddr_t) -1;
    }

    heap += incr;

    return prev_heap;
}

int _write(int fd, char *buf, int count)
{
    int written = 0;

    if (fd != 1 && fd != 2) {
        errno = EBADF;
        return -1;
    }

    for (; count != 0; --count) {
        early_write_u8(*buf++);
        ++written;
    }
    return written;
}

void _exit(int status)
{
    while (1)
        ;
}
