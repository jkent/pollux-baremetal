/*
 * This is a derivative work of arch/arm/include/asm/io.h from the
 * Linux 3.9-rc6 kernel source.
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

#ifndef __ASM_ARM_IO_H
#define __ASM_ARM_IO_H

#include "asm/types.h"

#define __raw_readb(a)         (*(volatile u8 __force *)(a))
#define __raw_readw(a)         (*(volatile u16 __force *)(a))
#define __raw_readl(a)         (*(volatile u32 __force *)(a))
#define __raw_readq(a)         (*(volatile u64 __force *)(a))

#define __raw_writeb(v,a)      ((void)(*(volatile u8 __force *)(a) = (v)))
#define __raw_writew(v,a)      ((void)(*(volatile u16 __force *)(a) = (v)))
#define __raw_writel(v,a)      ((void)(*(volatile u32 __force *)(a) = (v)))
#define __raw_writeq(v,a)      ((void)(*(volatile u64 __force *)(a) = (v)))

#define __iormb()
#define __iowmb()

#define readb(c)		({ u8  __v = __raw_readb(c); __iormb(); __v; })
#define readw(c)		({ u16 __v = __raw_readw(c); __iormb(); __v; })
#define readl(c)		({ u32 __v = __raw_readl(c); __iormb(); __v; })
#define readq(c)		({ u64 __v = __raw_readq(c); __iormb(); __v; })

#define writeb(v,c)		({ __iowmb(); __raw_writeb(v,c); })
#define writew(v,c)		({ __iowmb(); __raw_writew(v,c); })
#define writel(v,c)		({ __iowmb(); __raw_writel(v,c); })
#define writeq(v,c)		({ __iowmb(); __raw_writeq(v,c); })

#endif /* __ASM_ARM_IO_H */

