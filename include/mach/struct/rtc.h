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

#ifndef _MACH_RTC_H
#define _MACH_RTC_H

#include <stdint.h>

#define POLLUX_RTC_BASE 0xC000F080

struct pollux_rtc_regs_t {
	uint32_t cntwrite;
	uint32_t cntread;
	uint32_t alarm;
	uint32_t ctrl;
	uint32_t intenb;
	uint32_t intpend;
};

#define pollux_rtc ((volatile struct pollux_rtc_regs_t *) \
	(POLLUX_RTC_BASE))

/* ctrl */
#define RTC_CNTWAIT			4
#define RTC_ALARMWAIT			3
#define RTC_CNTWRITEENB			0

/* intenb */
#define RTC_ALARMINTENB			1
#define RTC_HZINTENB			0				

/* intpend */
#define RTC_ALARMINTPEND		1
#define RTC_HZINTPEND			0

#endif /* _MACH_RTC_H */

