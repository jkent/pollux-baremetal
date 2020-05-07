/*
 * Copyright (C) 2013-2020 Jeff Kent <jeff@jkent.net>
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

#ifndef __ASM_TYPES_H
#define __ASM_TYPES_H

#include <stdint.h>

#define __iomem
#define __force

typedef uint64_t	u64;
typedef int64_t		s64;
typedef unsigned int	u32;
typedef signed int	s32;
typedef unsigned short	u16;
typedef signed short	s16;
typedef unsigned char	u8;
typedef signed char	s8;

#endif /* __ASM_TYPES_H */

