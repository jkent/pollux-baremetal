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

#pragma once

#include <asm/types.h>

#define EARLY_CODE __attribute__((section (".text.early")))
#define EARLY_RODATA __attribute__((section (".rodata.early")))
#define STARTUP_CODE __attribute__((seciton (".text._startup")))
#define STARTUP_RODATA __attribute__((seciton (".rodata._startup")))
#define NAKED __attribute__((naked))

extern u32 __reloc_start__;
extern u32 __reloc_end__;
