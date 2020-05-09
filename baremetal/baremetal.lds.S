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
#if defined(CONFIG_BAREMETAL_SHADOW)
  ram : o = 0x00000000, l = 256M
  rom : o = 0x80000000, l = 64M
#else
  rom : o = 0x00000000, l = 64M
  ram : o = 0x80000000, l = 256M
#endif
}

SECTIONS
{
  .entry : {
    *(.text.entry .rodata.entry)
  } > ram 

  .early CONFIG_BAREMETAL_RUNTIME_ADDRESS + SIZEOF(.entry) :
  AT(ADDR(.entry) + SIZEOF(.entry))
  {
    __reloc_start__ = . - SIZEOF(.entry);
    *(.text.early .rodata.early)
#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART) || defined(BAREMETAL_BOOT_SOURCE_NAND)
    . = ALIGN(512);
#endif
  } > ram

  .text :
  {
    *(.text._startup)
    *(.text.startup) /* place main first */
    *(.text.* .text .stub)
  } > ram

  .rodata :
  {
    *(.rodata)
  } > ram

	.got :
  {
    *(.got.plt) *(.igot.plt) *(.got) *(.igot)
  } > ram

  .data :
  {
    *(.data .data.*)
  } > ram
  . = ALIGN(8);
  __reloc_end__ = .;

  .bss :
  {
    __bss_start__ = .;
    *(.bss .bss.*)
    *(COMMON)
#if defined(CONFIG_BAREMETAL_ENABLE_MMU)
    main_tlb = ALIGN(0x4000);
    . = main_tlb + 0x4000;
#endif
    __bss_end__ = .;
  } > ram

  __heap_start__ = .;
  __initial_stack_end__ = .;
  .stack :
  {
    . += CONFIG_BAREMETAL_INITIAL_STACK_SIZE;
  } > ram
  __initial_stack_top__ = .;
}

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART) || defined(BAREMETAL_BOOT_SOURCE_NAND)
ASSERT(SIZEOF(.entry) + SIZEOF(.early) <= 512,
        "Early boot does not fit within 512 bytes")
#endif
