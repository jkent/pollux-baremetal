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

#ifndef __BAREMETAL_CONFIG_H
#define __BAREMETAL_CONFIG_H

#define ABT_STACK_SIZE (   1 * 1024)
#define UND_STACK_SIZE (   1 * 1024)
#define FIQ_STACK_SIZE (   1 * 1024)
#define IRQ_STACK_SIZE (   4 * 1024)
#define SVC_STACK_SIZE (  64 * 1024)
#define USR_STACK_SIZE (  64 * 1024)
#define COMBINED_STACK_SIZE (ABT_STACK_SIZE + UND_STACK_SIZE + \
		FIQ_STACK_SIZE + IRQ_STACK_SIZE + SVC_STACK_SIZE + USR_STACK_SIZE)

#define HEAP_SIZE      ( 128 * 1024)

#endif /* __BAREMETAL_CONFIG_H */

