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
  ram : o = 0x00000000, l = CONFIG_BAREMETAL_RAM_SIZE
  rom : o = 0x80000000, l = 64M
#else
  rom : o = 0x00000000, l = 64M
  ram : o = 0x80000000, l = CONFIG_BAREMETAL_RAM_SIZE
#endif
}

SECTIONS
{
  .entry : {
    *(.text.entry)
  } > ram 

  .entry_thumb CONFIG_BAREMETAL_RUNTIME_ADDRESS + SIZEOF(.entry) :
  AT(ADDR(.entry) + SIZEOF(.entry))
  {
    _reloc_start = . - SIZEOF(.entry);
    *(.text.entry_thumb)
    . = ALIGN(8);
  } > ram

  .text : {
    *(.text.* .text)
    . = ALIGN(8);
  } > ram

  .preinit_array : {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(8);
  } > ram

  .init_array : {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(8);
  } > ram

  .fini_array : {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(8);
  } > ram

  .rodata :
  {
    *(.rodata)
    . = ALIGN(8);
  } > ram

	.got :
  {
    *(.got.plt) *(.igot.plt) *(.got) *(.igot)
    . = ALIGN(8);
  } > ram

  .data :
  {
    *(.data .data.*)
    . = ALIGN(8);
  } > ram
  _reloc_end = .;

  .bss :
  {
    _bss = .;
    *(.bss*)
    *(COMMON)
#if defined(CONFIG_BAREMETAL_MMU)
    . = ALIGN(4096);
    _main_tlb = .;
    . += 4096;
#if defined(CONFIG_BAREMETAL_EXCEPTION)
    . = ALIGN(4096);
    _exc_tlb = .;
    . += 4096;
    _exc_phys = .;
    . += 1024;
#endif
#endif
#if defined(CONFIG_BAREMETAL_EXCEPTION)
    _swi_table = .;
    . += 1024;
    _irq_table = .;
    . += 256;
#endif
    . = ALIGN(8);
    _ebss = .;
  } > ram

  _heap_bottom = .;

#if defined(CONFIG_BAREMETAL_SHADOW)
  _stack_top = CONFIG_BAREMETAL_RAM_SIZE;
#else
  _stack_top = CONFIG_BAREMETAL_RAM_SIZE + 0x80000000;
#endif
}

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
ASSERT(SIZEOF(.entry) + SIZEOF(.entry_thumb) <= 512,
  "Entry code does not fit within 512 bytes")
#elif defined(CONFIG_BAREMETAL_BOOT_SOURCE_NAND)
ASSERT(SIZEOF(.entry) + SIZEOF(.entry_thumb) <= CONFIG_BAREMETAL_NAND_PAGE_SIZE,
  "Entry code does not fit within " #CONFIG_BAREMETAL_NAND_PAGE_SIZE " bytes")
#endif
