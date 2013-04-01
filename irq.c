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

#include <stdint.h>

#include "irq.h"

irq_handler_t irq_handlers[64] = {0};

#if 0
static const uint8_t magic_lut[64] = {
	 0,  1,  2, 53,  3,  7, 54, 27,
	 4, 38, 41,  8, 34, 55, 48, 28,
	62,  5, 39, 46, 44, 42, 22,  9,
	24, 35, 59, 56, 49, 18, 29, 11,
	63, 52,  6, 26, 37, 40, 33, 47,
	61, 45, 43, 21, 23, 58, 17, 10,
	51, 25, 36, 32, 60, 20, 57, 16,
	50, 31, 19, 15, 30, 14, 13, 12
};
#endif

/* pending is guaranteed to have only one bit set at a time */
void irq_handler(uint64_t pending)
{
#if 0
	irq_handler_t handler;
	uint8_t irq;

	pending &= 0x00000FFFFFFFFFFFull;
	irq = magic_lut[(uint64_t)(pending * 0x022fdd63cc95386dull) >> 58];
	handler = irq_handlers[irq];
	handler();
#endif

	irq_handler_t *handler = irq_handlers;

	while (pending) {
		if ((pending & 1) && *handler) {
			(*handler)();
			break;
		}
		pending >>= 1;
		handler++;
	}
}

