/* vim: set ts=8 sw=8 noexpandtab
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

.section .text.early
.arm
.align 0

.global _entry
.org	_entry

_entry:
_start:

#if defined(CONFIG_BAREMETAL_RELOCATE)

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
	/* relocate to high memory */
	ldr	r0, =__early_start__
	ldr r1, =__reloc_start__
	ldr r2, =__early_start__ + (16 * 1024)
#endif

1:
	ldmia r0!, {r10-r11}
	stmia r1!, {r10-r11}
	cmp	r0, r2
	blo	1b
#endif

	/* initialize stack */
	ldr	sp, =__initial_stack_top__

	/* jump to loader in thumb mode */
	ldr r3, =startup
	bx r3

.ltorg

.end
