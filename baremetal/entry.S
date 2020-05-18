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

#include <mach/alive.h>
#include <mach/gpio.h>
#include <mach/uart.h>

.section .text.entry
.arm

.global _entry
_entry:
	b _exc_reset
	b .
	b .
	b .
	b .
	b .
	b .
	b .

_vectors:
.word _exc_reset
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0

_exc_reset:

/* setup stack */
#if defined(CONFIG_BAREMETAL_EXCEPTION)
	ldr r0, =_stack_top - CONFIG_BAREMETAL_FIQ_STACK_SIZE - \
		CONFIG_BAREMETAL_IRQ_STACK_SIZE - CONFIG_BAREMETAL_ABT_STACK_SIZE - \
		CONFIG_BAREMETAL_UND_STACK_SIZE
#else
	ldr r0, =_stack_top
#endif
	mov sp, r0

/* clear .bss */
	ldr r0, =_bss
	ldr r1, =_ebss
	mov r2, #0
1:	cmp r0, r1
	strne r2, [r0], #4
	bne 1b

#if defined(CONFIG_BAREMETAL_AUTO_RELOCATE)
/* relocation code is position independent code */
	sub r0, pc, #8 + . - _entry /* _entry_address running in RAM */
	ldr r1, =_reloc_start
	cmp r0, r1
	beq 2f

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART) || defined(CONFIG_BAREMETAL_BOOT_SOURCE_NAND)
	ldr r2, =CONFIG_BAREMETAL_RUNTIME_ADDRESS + (16 * 1024)
#elif defined (CONFIG_BAREMETAL_BOOT_SOURCE_RAM)
	ldr r2, =_reloc_end
#endif

1:
	ldmia r0!, {r10-r11}
	stmia r1!, {r10-r11}
	cmp r1, r2
	blo 1b
2:
#endif /* defined(CONFIG_BAREMETAL_AUTO_RELOCATE) */

	ldr r0, =entry_thumb
	bx r0
.ltorg

.section .text.entry_thumb
.thumb

.type entry_thumb, %function
entry_thumb:
#if defined(CONFIG_BAREMETAL_LATCH_POWER)
	ldr r0, =ALIVE_BASE
	mov r1, #ALIVE_PWRGATEREG_NPOWERGATING
	str r1, [r0, #ALIVE_PWRGATEREG]	
	mov r1, #0
	str r1, [r0, #ALIVE_GPIORSTREG]
	mov r1, #ALIVE_GPIO_VDDPWRONRST
	str r1, [r0, #ALIVE_GPIOSETREG]
	mov r1, #0
	str r1, [r0, #ALIVE_GPIOSETREG]
	str r1, [r0, #ALIVE_PWRGATEREG]
#endif

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
/* enable TXD pin */
	ldr r0, =GPIOA_BASE
	ldr r1, =(3 << (8 * 2))
	ldr r2, =(1 << (8 * 2))
	ldr r3, [r0, #GPIO_ALTFNL]
	bic r3, r3, r1
	orr r3, r3, r2
	str r3, [r0, #GPIO_ALTFNL]
/* enable TX and RX */	
	ldr r0, =UART0_BASE
	mov r1, #(UART_UCON_TRANSMODE_INTPOLL | UART_UCON_RECVMODE_INTPOLL)
	strh r1, [r0, #UART_UCON]
/* send "UART" magic */
	ldr r0, =0x54524155
	bl uart0_writel
/* set baudinfo */
	bl uart0_readl
	mov r4, r0
	mov r0, #1
	bl uart0_writeb
	mov r0, r4
	bl uart0_set_baudinfo
/* wait for 0xAA55 magic */
1:	bl uart0_readb
	cmp r0, #0x55
	bne 1b
	bl uart0_readb
	cmp r0, #0xAA
	bne 1b
	mov r0, #1
	bl uart0_writeb
/* load rest of code */
	ldr r0, =0xA4000000
	ldr r1, [r0]
	ldr r2, =0x400
	ldr r4, =CONFIG_BAREMETAL_RUNTIME_ADDRESS
	tst r1, r2
	beq 2f
	ldr r0, =(512 * 31) 
	add r4, r4, r0
2:	ldr r0, =512
	add r4, r4, r0
/* read size */
	bl uart0_readl
	add r5, r4, r0
	cmp r5, r4
	ble 4f
/* read code dword */
3:	bl uart0_readl
	str r0, [r4]
	add r4, r4, #4
	cmp r5, r4
	bgt 3b
4:
#endif /* defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART) */

#if defined(CONFIG_BAREMETAL_STARTUP)
	ldr r4, =startup
#else
	ldr r4, =main
#if defined(CONFIG_BAREMETAL_NEWLIB)
	ldr r4, =exit
	blx r4
#endif /* defined(CONFIG_BAREMETAL_NEWLIB) */
#endif /* defined(CONFIG_BAREMETAL_STARTUP) */
	blx r4
	b .
.ltorg

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
.type set_baudinfo, %function
uart0_set_baudinfo:
	push {r4, lr}
/* set default value if 0 */
	cmp r0, #0
	bne 1f
	ldr r0, =(11 << 16) | (39 << 4) | (1 << 1)
1:	ldr r1, =0xFFFF
	and r1, r1, r0 /* R1 contains clkgen */
	lsr r0, r0, #16 /* R0 contains brd */
/* wait for txdone */
	ldr r2, =UART0_BASE
	mov r3, #UART_TRSTATUS_TXDONE
2:	ldrh r4, [r2, #UART_TRSTATUS]
	tst r4, r3
	beq 2b
	strh r0, [r2, #UART_BRD]
	mov r3, #UART_CLKGEN
	str r1, [r2, r3]
	pop {r4, pc}

.type uart0_writeb, %function
uart0_writeb:
/* wait for txempty */
	ldr r1, =UART0_BASE
	mov r2, #UART_TRSTATUS_TXEMPTY
1:	ldrh r3, [r1, #UART_TRSTATUS]
	tst r2, r3
	beq 1b
	strb r0, [r1, #UART_THB]
	bx lr

.type uart0_readb, %function
uart0_readb:
/* wait for rxready */
	ldr r1, =UART0_BASE
	mov r2, #UART_TRSTATUS_RXREADY
1:	ldrh r3, [r1, #UART_TRSTATUS]
	tst r2, r3
	beq 1b
	mov r2, #UART_RHB
	ldrb r0, [r1, r2]
	bx lr
	nop

.type uart0_writel, %function
uart0_writel:
	push {lr}
	bl uart0_writeb
	lsr r0, r0, #8
	bl uart0_writeb
	lsr r0, r0, #8
	bl uart0_writeb
	lsr r0, r0, #8
	bl uart0_writeb
	pop {pc}

.type uart0_readl, %function
uart0_readl:
	push {r4, lr}
	bl uart0_readb
	movs r4, r0
	bl uart0_readb
	lsl r0, r0, #8
	orr r4, r4, r0
	bl uart0_readb
	lsl r0, r0, #16
	orr r4, r4, r0
	bl uart0_readb
	lsl r0, r0, #24
	orr r0, r0, r4
	pop {r4, pc}
#endif /* defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART) */
.ltorg

.end
