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

#ifndef _MACH_PWM_H
#define _MACH_PWM_H

#include <stdint.h>

#define POLLUX_PWM_BASE 0xC000C000

struct pollux_pwm_regs_t {
	uint16_t pwm01pres;
	uint16_t pwm0duty;
	uint16_t pwm1duty;
	uint16_t pwm0period;
	uint16_t pwm1period;
	uint16_t _reserved[3];
	uint16_t pwm2pres;
	uint16_t pwm2duty;
	uint16_t _reserved2;
	uint16_t pwm2period;
	uint16_t _reserved3[20];
	uint32_t clkenb;
	uint32_t clkgen;
};

#define pollux_pwm ((volatile struct pollux_pwm_regs_t *) \
	(POLLUX_PWM_BASE))

/* pwm01pres */
#define PWM_PWM1POL			15
#define PWM_PWM1PRESCALE		8
#define PWM_PWM0POL			7
#define PWM_PWM0PRESCALE		0

/* pwm2pres */
#define PWM_PWM2POL			7
#define PWM_PWM2PRESCALE		0

/* clkenb */
#define PWM_PCLKMODE			3
#define PWM_CLKGENENB			2

/* clkgen */
#define PWM_CLKDIV			4
#define PWM_CLKSEL			1

#endif /* _MACH_PWM_H */

