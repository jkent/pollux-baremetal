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

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_entry)

MEMORY
{
#if defined(CONFIG_BAREMETAL_RELOCATE)
  ram : o = CONFIG_BAREMETAL_RELOCATE_ADDRESS, l = CONFIG_BAREMETAL_ENTRY_ADDRESS + 128M - CONFIG_BAREMETAL_RELOCATE_ADDRESS 
#else
  ram : o = CONFIG_BAREMETAL_ENTRY_ADDRESS, l = 128M
#endif
}

SECTIONS
{
  .text : AT(CONFIG_BAREMETAL_ENTRY_ADDRESS) {
    __reloc_start__ = .;
    */entry.*(.text.early .rodata.early)
    *(.text.early .rodata.early)
#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART) || defined(BAREMETAL_BOOT_SOURCE_NAND)
    . = ALIGN(512);
#endif

		*(.text .stub .text.*)
	} > ram

	.rodata : {
    *(.rodata)
  } > ram

	.got : {
    *(.got.plt) *(.igot.plt) *(.got) *(.igot)
  } > ram

  .data : {
    *(.data .data.*)
  } > ram

  .bss : {
    __bss_start__ = .;
    *(.bss .bss.*)
    *(COMMON)
#if defined(CONFIG_BAREMETAL_ENABLE_DCACHE)
    main_tlb = ALIGN(0x4000);
    . = main_tlb + 0x4000;
#endif
    __bss_end__ = .;
  } > ram

#if defined(CONFIG_BAREMETAL_RELOCATE)
  __reloc_end__ = .;
#endif

  __heap_start__ = .;
#if defined(CONFIG_BAREMETAL_HEAP_FIXED)
  . += CONFIG_BAREMETAL_HEAP_FIXED_SIZE;
  __heap_end__ = .;
#endif

  __initial_stack_end__ = .;
  .stack : {
    . += CONFIG_BAREMETAL_INITIAL_STACK_SIZE;
  } > ram
  __initial_stack_top__ = .;
}
