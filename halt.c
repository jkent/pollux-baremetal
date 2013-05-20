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

#include "asm/io.h"
#include "mach/clkpwr.h"

static void __iomem *clkpwr = (void __iomem *) CLKPWR_BASE;

void __attribute__((noreturn)) halt(void)
{
	u32 tmp;
	while (1) {
		tmp = readl(clkpwr + CLKPWR_PWRMODE);
		tmp |= CLKPWR_PWRMODE_CURPWRMODE_STOP;
		writel(tmp, clkpwr + CLKPWR_PWRMODE);
	}
}

