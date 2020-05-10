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

#define MODE_USER 0x10
#define MODE_FIQ 0x11
#define MODE_IRQ 0x12
#define MODE_SVC 0x13
#define MODE_ABT 0x17
#define MODE_UND 0x1B
#define MODE_SYS 0x1F
#define DISABLE_FIQ 0x40
#define DISABLE_IRQ 0x80

.section .text
.arm
.align 0

.type startup, %function
.global startup
startup:
#if defined(CONFIG_BAREMETAL_ICACHE)
    bl icache_enable
#endif

#if defined(CONFIG_BAREMETAL_MMU)
    bl mmu_init
    bl mmu_enable
#endif

#if defined(CONFIG_BAREMETAL_DCACHE)
    bl dcache_enable
#endif

#if defined(CONFIG_BAREMETAL_PLL0_INIT_533)
    bl pll0_init
#endif

#if defined(CONFIG_BAREMETAL_DDR_INIT)
    bl ddr_init
#endif

    bl get_ram_size
#if !defined(CONFIG_BAREMETAL_SHADOW)
    orr r0, r0, #0x80000000
#endif
	mov sp, r0
#if defined(CONFIG_BAREMETAL_INTERRUPTS)
	mov	sp, r0
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_FIQ
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_FIQ_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_IRQ
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_IRQ_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_SVC
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_SVC_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_ABT
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_ABT_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_UND
	mov	sp, r0
	sub	sp, r0, #CONFIG_BAREMETAL_UND_STACK_SIZE
	msr	cpsr_c, #DISABLE_FIQ | DISABLE_IRQ | MODE_SYS
	mov	sp, r0

    bl enable_interrupts
#endif

	bl __libc_init_array
	ldr r0, =__libc_fini_array
	bl atexit

    bl main
	bl exit

.ltorg
.end
