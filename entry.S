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

#include "config.h"

.section .text
.arm
.align 0

.global _entry
.org _entry

_entry:
#if defined(CONFIG_BAREMETAL_IRQ)
	ldr	pc, _isr_rst_ptr
	ldr	pc, _isr_und_ptr
	ldr	pc, _isr_swi_ptr
	ldr	pc, _isr_pabt_ptr
	ldr	pc, _isr_dabt_ptr
	ldr	pc, _isr_rsv_ptr
	ldr	pc, _isr_irq_ptr
	ldr	pc, _isr_fiq_ptr

.global interrupt_vector_table
interrupt_vector_table:
_isr_rst_ptr:  .word _start
_isr_und_ptr:  .word _isr_und
_isr_swi_ptr:  .word _isr_swi
_isr_pabt_ptr: .word _isr_pabt
_isr_dabt_ptr: .word _isr_dabt
_isr_rsv_ptr:  .word _isr_rsv
_isr_irq_ptr:  .word _isr_irq
_isr_fiq_ptr:  .word _isr_fiq

_isr_und:
_isr_swi:
_isr_pabt:
_isr_dabt:
_isr_rsv:
_isr_irq:
_isr_fiq:
	ldr	r4, =halt
	blx	r4
#endif


_start:

	/* setup stacks */
#if defined(CONFIG_BAREMETAL_IRQ)
# define MODE_USER 0x10
# define MODE_FIQ 0x11
# define MODE_IRQ 0x12
# define MODE_SVC 0x13
# define MODE_ABT 0x17
# define MODE_UND 0x1B
# define MODE_SYS 0x1F
# define DISABLE_FIQ 0x40
# define DISABLE_IRQ 0x80

	ldr	r0, =__stack_top__
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_ABT
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_ABT_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_UND
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_UND_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_FIQ
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_FIQ_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_IRQ
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_IRQ_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_SVC
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_SVC_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_SYS
	mov	sp, r0

	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_SVC
#else
	ldr	sp, =__stack_top__
#endif

	/* clear .bss */
	ldr     r0, =__bss_start__
	ldr     r1, =__bss_end__
	mov     r2, #0
1:      cmp     r0, r1
	strlo   r2, [r0], #4
	blo     1b

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_NAND)
	ldr	r0, =__image_start__
	blx	nand_startup
#elif defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
	ldr	r0, =__image_start__
	blx	uart_startup
#elif defined(CONFIG_BAREMETAL_RELOCATE)
	adr	r0, _entry
	ldr	r1, =__early_end__
	add	r0, r0, r1
	ldr	r1, =__image_start__
	ldr	r2, =__image_end__
1:
	ldmia   r0!, {r10-r11}
	stmia   r1!, {r10-r11}
	cmp	r1, r2
	blo	1b
#endif

	ldr	r4, =startup
	bx	r4

.ltorg

.end

