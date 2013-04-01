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

#ifndef __ASM_IO_H__
#define __ASM_IO_H__

#include "asm/types.h"

static inline void __raw_writeb(u8 val, volatile void __iomem *addr)
{
	asm volatile("strb %1, %0"
	             : "+Qo" (*(volatile u8 __force *)addr)
	             : "r" (val));
}

static inline void __raw_writew(u16 val, volatile void __iomem *addr)
{
	asm volatile("strh %1, %0"
	             : "+Q" (*(volatile u16 __force *)addr)
	             : "r" (val));
}

static inline void __raw_writel(u32 val, volatile void __iomem *addr)
{
	asm volatile("str %1, %0"
	             : "+Qo" (*(volatile u32 __force *)addr)
	             : "r" (val));
}

static inline u8 __raw_readb(const volatile void __iomem *addr)
{
	u8 val;
	asm volatile("ldrb %1, %0"
		     : "+Qo" (*(volatile u8 __force *)addr),
		       "=r" (val));
	return val;
}

static inline u16 __raw_readw(const volatile void __iomem *addr)
{
	u16 val;
	asm volatile("ldrh %1, %0"
	             : "+Q" (*(volatile u16 __force *)addr),
	               "=r" (val));
	return val;
}

static inline u32 __raw_readl(const volatile void __iomem *addr)
{
	u32 val;
	asm volatile("ldr %1, %0"
	             : "+Qo" (*(volatile u32 __force *)addr),
	               "=r" (val));
	return val;
}

#define __iormb()
#define __iowmb()

#define readb(c)		({ u8  __v = __raw_readb(c); __iormb(); __v; })
#define readw(c)		({ u16 __v = __raw_readw(c); __iormb(); __v; })
#define readl(c)		({ u32 __v = __raw_readl(c); __iormb(); __v; })

#define writeb(v,c)		({ __iowmb(); __raw_writeb(v,c); })
#define writew(v,c)		({ __iowmb(); __raw_writew(v,c); })
#define writel(v,c)		({ __iowmb(); __raw_writel(v,c); })

#endif /* __ASM_IO_H__ */

