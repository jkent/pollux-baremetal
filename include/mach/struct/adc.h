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

#ifndef _MACH_ADC_H
#define _MACH_ADC_H

#include <stdint.h>

#define POLLUX_ADC_BASE 0xC0005000

struct pollux_adc_regs_t {
	uint32_t ctrl;
	uint32_t data;
	uint32_t intenb;
	uint32_t intclr;
	uint32_t _reserved[12];
	uint32_t clkenb;
};

#define pollux_adc ((volatile struct pollux_adc_regs_t *) \
	(POLLUX_ADC_BASE))

/* ctrl */
#define ADC_APEN 			14
#define ADC_APSV			6
#define ADC_ASEL			3
#define ADC_STBY			2
#define ADC_ADEN			0

/* clkenb */
#define ADC_PCLKMODE			3

#endif /* _MACH_ADC_H */

