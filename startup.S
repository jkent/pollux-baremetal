/*
 * Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
 *
 * Copyright 2009-2010 LeapFrog Enterprises Inc.
 * Andrey Yurovsky <andrey@cozybit.com>
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

.section .text.startup
.arm
.align 0

.global _start
.org _start

_start:
    /* Primary vector table */
	ldr	pc, _reset_addr
	ldr	pc, _undef_addr
	ldr	pc, _swi_addr
	ldr	pc, _pabt_addr
	ldr	pc, _dabt_addr
	nop	/* reserved */
	ldr	pc, _irq_addr
	ldr	pc, _fiq_addr


_reset_addr:	.word   _reset_handler
_undef_addr:	.word   _undef_handler
_swi_addr:	.word   _swi_handler
_pabt_addr:	.word   _pabt_handler
_dabt_addr:	.word   _dabt_handler
_irq_addr:	.word   _irq_handler
_fiq_addr:	.word   _fiq_handler

_undef_handler:
_swi_handler:
_pabt_handler:
_dabt_handler:
_fiq_handler:

	ldr	r12, =uart_putchar
	ldr	r4, =halt_str
1:
	ldrb	r0, [r4], #1
	cmp	r0, #0
	beq	.
	blx	r12
	b	1b				

halt_str:
	.asciz	"Halted."

.align 0

_irq_handler:
	sub	lr, lr, #4
	stmfd	sp!, {lr}		/* save adjusted lr_irq */

	mrs	r14, spsr
	stmfd	sp!, {r0-r3, r12, r14}	/* save working and spsr_irq */

	msr	cpsr_c, #0x93		/* change to Supervisor mode and enable FIQ */

	stmfd	sp!, {lr}		/* save lr_usr */

	ldr	r14, INTPENDL
	ldr	r0, [r14]		/* fetch INTPENDL */
	add	r14, #4
	ldr	r1, [r14]		/* fetch INTPENDH */

	ldr	r14, =irq_handler
	blx	r14			/* call handler */

	ldmfd	sp!, {lr}		/* restore lr_usr */
	
	msr	cpsr_c, #0x92		/* Return to IRQ mode */

	ldmfd	sp!, {r0-r3, r12, r14}	/* restore workreg and spsr_irq */
	msr	spsr_cf, r14

	ldmfd	sp!, {pc}^		/* Return */

INTPENDL:	.word	0xc0000820


_reset_handler:
	/* enable I-cache */
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, r0, #(1 << 12)
	mcr	p15, 0, r0, c1, c0, 0
	
	/*
	 * Initialize the stack pointers for the various processor modes.  
	 * FIQ, ABT, and UND have small stacks (0x100).
	 * IRQ has a 0x2D00-byte stack.  SVC (the usual mode during boot)
	 * uses all but 12K (0x3000) of the reserved stack space.
	 */
	ldr	r0, =__stack_top__
	msr	cpsr_cxsf, #0xd1	/* Mode_FIQ */
	sub	sp, r0, #0x0
	msr	cpsr_cxsf, #0xd7	/* Mode_ABT */
	sub	sp, r0, #0x100
	msr	cpsr_cxsf, #0xdb	/* Mode_UND */
	sub	sp, r0, #0x200
	msr	cpsr_cxsf, #0xd2	/* Mode_IRQ */
	sub	sp, r0, #0x300
	msr	cpsr_cxsf, #0xd3	/* Mode_SVC */
	sub	sp, r0, #0x3000	

	/* clear .bss */
	ldr	r0, =__bss_start__
	ldr	r1, =__bss_end__
	mov	r2, #0
1:	cmp	r0, r1
	strlo	r2, [r0], #4
	blo	1b

	ldr	r12, =main
	blx	r12

.global enable_interrupts
enable_interrupts:
	mrs	r0, cpsr
	bic	r0, r0, #0x80
	msr	cpsr_cxsf, r0
	bx	lr

.global disable_interrupts
disable_interrupts:
	mrs	r0, cpsr
	orr	r0, r0, #0x80
	msr	cpsr_cxsf, r0
	bx	lr

.end

