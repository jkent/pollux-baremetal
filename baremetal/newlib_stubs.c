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
#include <driver/uart.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#if defined(CONFIG_BAREMETAL_FREERTOS)
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#endif

int _close_r(struct _reent *ptr, int fd)
{
    return -1;
}

void _exit(int status)
{
    while (1)
        ;
}

void _fini(void)
{
}

int _fstat_r(struct _reent *ptr, int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _getpid_r(struct _reent *ptr)
{
    return  1;
}

void _init(void)
{
}

int _isatty_r(struct _reent *ptr, int file)
{
    return  1;
}

int _kill_r(struct _reent *ptr, int pid, int sig)
{
    ptr->_errno = EINVAL;
    return -1;
}

_off_t _lseek_r(struct _reent *ptr, int file, _off_t offset, int whence)
{
    return  0;
}

_ssize_t _read(struct _reent *ptr, int fd, void *buf, size_t count)
{
    return -1;
}

#if !defined(CONFIG_BAREMETAL_FREERTOS)
register void *stack_ptr asm("sp");

void *_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
	static void *current_heap_end = NULL;

	if (current_heap_end == NULL) {
		current_heap_end = &_heap_bottom;
	}

	void *previous_heap_end = current_heap_end;
	if (current_heap_end + incr > stack_ptr) {
		ptr->_errno = ENOMEM;
		return (void *)-1;
	}

	current_heap_end += incr;
	return previous_heap_end;
}
#endif

_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t count)
{
    int written = 0;

    if (fd != 1 && fd != 2) {
        ptr->_errno = EBADF;
        return -1;
    }

    for (; count != 0; --count) {
        if (*(char *)buf == '\n') {
            uart0_writeb('\r');
        }
        uart0_writeb(*(char *)buf++);
        ++written;
    }
    return written;
}


#if defined(CONFIG_BAREMETAL_FREERTOS)
void __env_lock()
{
    vTaskSuspendAll();
};

void __env_unlock()
{
    (void)xTaskResumeAll();
};
#endif