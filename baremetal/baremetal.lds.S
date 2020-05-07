/* vim: set ts=4 sw=4 noexpandtab
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

#include "config.h"

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_entry)

SECTIONS
{
	. = CONFIG_BAREMETAL_ENTRY_ADDRESS;
	. = ALIGN(4);
  __early_start__ = .;
	.startup : { 
    */baremetal/entry.*(.text .rodata .data)
  }
  __early_end__ = .;

#if defined(CONFIG_BAREMETAL_RELOCATE)
  . = CONFIG_BAREMETAL_RELOCATE_ADDRESS;
  __reloc_start__ = .;
  . += __early_end__ - __early_start__;
#endif
	. = ALIGN(4);
	.text : AT(ADDR(.startup) + SIZEOF(.startup))
	{
		/* early code and data must fit in the first 512 bytes */
	  *(.text.early .rodata.early)
    . = ALIGN(512);

		*(.text .stub .text.*)
	}

	.rodata : {
    *(.rodata)
  }

	.got : {
    *(.got.plt) *(.igot.plt) *(.got) *(.igot)
  }

  .data : {
    *(.data .data.*)
  }

  .bss : {
    __bss_start__ = .;
    *(.bss .bss.*)
    *(COMMON)
#if defined(CONFIG_BAREMETAL_ENABLE_DCACHE)
    main_tlb = ALIGN(0x4000);
    . = main_tlb + 0x4000;
#endif
    . = ALIGN(0x4);
    __bss_end__ = .;
  }

#if defined(CONFIG_BAREMETAL_RELOCATE)
  __reloc_end__ = .;
#endif

  __heap_start__ = .;
#if defined(CONFIG_BAREMETAL_HEAP_STATIC)
  . += CONFIG_BAREMETAL_HEAP_STATIC_SIZE;
  . = ALIGN(0x4);
  __heap_end__ = .;
#endif

  __initial_stack_end__ = .;
  .stack : {
    . += CONFIG_BAREMETAL_INITIAL_STACK_SIZE;
    . = ALIGN(0x4);
  }
  __initial_stack_top__ = .;
}
