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

#ifndef _MACH_MCUY_H
#define _MACH_MCUY_H

#define MCUY_BASE (0xC0014800)

#define MCUY_REG(x) (x)

#define MCUY_CFG				MCUY_REG(0x00)
#define MCUY_TIME0				MCUY_REG(0x02)
#define MCUY_TIME1				MCUY_REG(0x04)
#define MCUY_REFRESH				MCUY_REG(0x08)
#define MCUY_CONTROL				MCUY_REG(0x0A)
#define MCUY_CLKDELAY				MCUY_REG(0x0C)
#define MCUY_DQSOUTDELAY			MCUY_REG(0x0E)
#define MCUY_DQSINDELAY				MCUY_REG(0x10)

#endif /* _MACH_MCUY_H */

