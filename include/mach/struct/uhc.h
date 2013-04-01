/*
 * Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
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

#ifndef _MACH_UHC_H
#define _MACH_UHC_H

#include <stdint.h>

#define POLLUX_UHC_BASE 0xC000D000

struct pollux_uhc_regs_t {
	uint32_t revision;
	uint32_t control;
	uint32_t common_status;
	uint32_t interrupt_status;
	uint32_t interrupt_enable;
	uint32_t interrupt_disable;
	uint32_t hcca;
	uint32_t period_current_ed;
	uint32_t control_head_ed;
	uint32_t control_current_ed;
	uint32_t bulk_head_ed;
	uint32_t bulk_current_ed;
	uint32_t bulk_done_head;
	uint32_t rm_interval;
	uint32_t fm_remaining;
	uint32_t fm_number;
	uint32_t perodic_start;
	uint32_t ls_threshold;
	uint32_t rh_descriptor_a;
	uint32_t rh_descriptor_b;
	uint32_t rh_status;
	uint32_t rh_port_status1;
	uint32_t rh_port_status2;
	uint32_t _reserved[9];
	uint32_t init_cfg;
	uint32_t _reserved2[15];
	uint32_t clkenb;
	uint32_t clkgen;
};

#define pollux_uhc ((volatile struct pollux_uhc_regs_t *) \
	(POLLUX_UHC_BASE))

#endif /* _MACH_UHC_H */

