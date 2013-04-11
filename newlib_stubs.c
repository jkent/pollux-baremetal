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

#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#include "baremetal/uart.h"
#include "baremetal/util.h"

#undef errno
extern int errno;

char *__env[1] = { 0 };
char **environ = __env;

int _write(int file, char *ptr, int len);

void _exit(int status)
{
	printf("exit with status %d", status);
	halt();
}

int _close(int file)
{
	return -1;
}

int _execve(char *name, char **argv, char **env)
{
	errno = ENOMEM;
	return -1;
}

int _fork()
{
	errno = EAGAIN;
	return -1;
}

int _fstat(int file, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

int _getpid()
{
	return 1;
}

int _isatty(int file)
{
	switch (file) {
	case STDOUT_FILENO:
	case STDERR_FILENO:
	case STDIN_FILENO:
		return 1;
	default:
		errno = EBADF;
		return 0;
	}
}

int _kill(int pid, int sig)
{
	errno = EINVAL;
	return -1;
}

int _link(char *old, char *new)
{
	errno = EMLINK;
	return -1;
}

int _lseek(int file, int ptr, int dir)
{
	return 0;
}

int _open(const char *name, int flags, int mode)
{
	return -1;
}

int _read(int file, char *ptr, int len)
{
	int n;
	int num = 0;

	switch (file) {
	case STDIN_FILENO:
		for (n = 0; n < len; n++) {
			*ptr++ = uart_getchar();
			num++;
		}
		break;

	default:
		errno = EBADF;
		return -1;
	}
	return num;
}

caddr_t _sbrk(int incr)
{
	extern void *__heap_start__;
	extern void *__heap_end__;
	static char *heap_end;
	char *prev_heap_end;
	char *stack;
	register int *sp asm("sp");


	if (heap_end == 0) {
		heap_end = (char *)&__heap_start__;
	}
	prev_heap_end = heap_end;

	stack = (char *)sp;
	if (heap_end + incr > (char *)&__heap_end__) {
		_write(STDERR_FILENO, "Heap full\n", 10);
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

int _stat(const char *filepath, struct stat *st)
{
	st->st_mode = S_IFCHR;
	return 0;
}

clock_t _times(struct tms *buf)
{
	return -1;
}

int _unlink(char *name)
{
	errno = ENOENT;
	return -1;
}

int _wait(int *status)
{
	errno = ECHILD;
	return -1;
}

int _write(int file, char *ptr, int len)
{
	int n;

	switch (file) {
	case STDOUT_FILENO: 
		for (n = 0; n < len; n++) {
			if (*ptr == '\n')
				uart_putchar('\r');
			uart_putchar(*ptr++);
		};
		break;

	case STDERR_FILENO:
		for (n = 0; n < len; n++) {
			if (*ptr == '\n')
				uart_putchar('\r');
			uart_putchar(*ptr++);
		};
		break;

	default:
		errno = EBADF;
		return -1;
	}
	return len;
}

