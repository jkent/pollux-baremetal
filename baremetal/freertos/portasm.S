#include <mach/irq.h>
#include <mach/timer.h>

.section .data

ulCriticalNesting: .long 9999

.section .text
.arm

.macro portSAVE_CONTEXT
	push {r0}

	/* Set r0 to point to the task stack pointer. */
	stmdb sp, {sp}^
	nop
	sub sp, sp, #4
	ldmia sp!, {r0}

	/* Push the return address onto the stack. */
	stmdb r0!, {lr}

	/* Now we have saved lr we can use it instead of r0. */
	mov lr, r0

	/* Pop r0 so we can save it onto the system mode stack. */
	pop {r0}

	/* Push all the system mode registers onto the task stack. */
	stmdb lr, {r0-lr}^
	nop
	sub lr, lr, #60

	/* Push the spsr onto the task stack. */
	mrs r0, spsr
	stmdb lr!, {r0}

	ldr r0, =ulCriticalNesting
	ldr r0, [r0]
	stmdb lr!, {r0}

	/* Store the new top of stack for the task. */
	ldr r1, =pxCurrentTCB
	ldr r0, [r1]
	str lr, [r0]
.endm

.macro portRESTORE_CONTEXT
	ldr r1, =pxCurrentTCB
	ldr r0, [r1]
	ldr lr, [r0]

	/* The critical nesting depth is the first item on the stack. */
	/* Load it into the ulCriticalNesting variable. */
	ldr r0, =ulCriticalNesting
	ldmfd lr!, {r1}
	str r1, [r0]

	/* Get the spsr from the stack. */
	ldmfd lr!, {r0}
	msr spsr, r0

	/* Restore all system mode registers for the task. */
	ldmfd lr, {r0-r14}^
	nop

	/* Restore the return address. */
	ldr lr, [lr, #60]

	/* And return - correcting the offset in the lr to obtain the */
	/* correct address. */
	subs pc, lr, #4
.endm

.globl vPortStartFirstTask
.type vPortStartFirstTask, %function
vPortStartFirstTask:
    portRESTORE_CONTEXT

/*
 * Called by portYIELD() or taskYIELD() to manually force a context switch.
 *
 * When a context switch is performed from the task level the saved task 
 * context is made to look as if it occurred from within the tick ISR.  This
 * way the same restore context function can be used when restoring the context
 * saved from the ISR or that saved from a call to vPortYieldProcessor.
 */
.globl vPortYieldProcessor 
.type vPortYieldProcessor, %function
vPortYieldProcessor:
    add lr, lr, #4

    portSAVE_CONTEXT
    ldr r0, =vTaskSwitchContext
    mov lr, pc
    bx r0
    portRESTORE_CONTEXT

.globl vTimerIRQHandler
.type vTimerIRQHandler, %function
vTimerIRQHandler:
	push {r0-r3, lr}

//	portSAVE_CONTEXT	

	mov r0, #'t'
	blx uart0_writeb

	blx xTaskIncrementTick
//	cmp r0, #0
//	beq 1f
//	blx vTaskSwitchContext
//1:

	ldr r0, =TIMER0_BASE
	ldr r1, [r0, #TIMER_TMRCONTROL]
	orr r1, r1, #TIMER_INTPEND
	str r1, [r0, #TIMER_TMRCONTROL]

	ldr r0, =IRQ_BASE
	mov r1, #(1 << IRQ_TIMER0)
	str r1, [r0, #IRQ_PENDL]

//	portRESTORE_CONTEXT

	pop {r0-r3, pc}

.globl vPortDisableInterrupts
.type vPortDisableInterrupts, %function
vPortDisableInterrupts:
	push {r0}
	mrs r0, cpsr
	orr r0, r0, #0xC0
	msr cpsr_c, r0
	pop {r0}
	bx lr

.globl vPortEnableInterrupts
.type vPortEnableInterrupts, %function
vPortEnableInterrupts:
	push {r0}
	mrs r0, cpsr
	bic r0, r0, #0xC0
	msr cpsr_c, r0
	pop {r0}
	bx lr

.globl vPortEnterCritical
.type vPortEnterCritical, %function
vPortEnterCritical:
	push {r0-r1}
	mrs r0, cpsr
	orr r0, r0, #0xC0
	msr cpsr_c, r0
	ldr r0, =ulCriticalNesting
	ldr r1, [r0]
	add r1, r1, #1
	str r1, [r0]
	pop {r0-r1}
	bx lr

.globl vPortExitCritical
.type vPortExitCritical, %function
vPortExitCritical:
	push {r0-r1}
	ldr r0, =ulCriticalNesting
	ldr r1, [r0]
	cmp r1, #0
	ble 1f
	sub r1, r1, #1
	str r1, [r0]
	cmp r1, #0
	bne 1f
	mrs r0, cpsr
	bic r0, r0, #0xC0
	msr cpsr_c, r0
1:	pop {r0-r1}
	bx lr

.ltorg

.end
