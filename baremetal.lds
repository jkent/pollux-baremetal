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

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
  . = 0x0;
  .text : {
    *(.text.startup)
    *(.text)
  }

  .rodata : { *(.rodata) }

  .data : { *(.data) }

  __bss_start__ = .;
  .bss : { *(.bss) }
  __bss_end__ = .;
  . = ALIGN(8);

  /* 512kB shared heap/stack */
  __heap_bottom__ = .;
  . = . + 0x80000;
  __stack_top__ = .;

  /* mthumb-interwork things */
  /DISCARD/ : { *(.glue_7 .glue_7t .vfp11_veneer .v4_bx) }
}

