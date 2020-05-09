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

.section .text.entry
.arm
.align 0

.global _entry
.org 0

_entry:
#if defined(CONFIG_BAREMETAL_AUTO_RELOCATE)
	/* relocation code is position independent code */
	sub r0, pc, #8 // address of _entry in RAM
	ldr r1, =__reloc_start__
	cmp r0, r1
	beq 2f

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART) || defined(CONFIG_BAREMETAL_BOOT_SOURCE_NAND)
	ldr r2, =CONFIG_BAREMETAL_RUNTIME_ADDRESS + (16 * 1024)
#elif defined (CONFIG_BAREMETAL_BOOT_SOURCE_RAM)
	ldr r2, =__reloc_end__
#endif

1:
	ldmia r0!, {r10-r11}
	stmia r1!, {r10-r11}
	cmp r1, r2
	blo 1b
2:
#endif

	/* clear .bss */
	ldr r0, =__bss_start__
	ldr r1, =__bss_end__
	mov r2, #0
1:	cmp r0, r1
	strlo r2, [r0], #4
	blo 1b

	/* setup temporary stack */
	ldr sp, =__initial_stack_top__

	ldr r3, =early_startup
	bx r3
.ltorg

.end
