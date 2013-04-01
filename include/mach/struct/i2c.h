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

#ifndef _MACH_I2C_H
#define _MACH_I2C_H

#include <stdint.h>

#define POLLUX_I2C_BASE 0xC000E000
#define POLLUX_I2C_OFFSET 0x800
#define POLLUX_I2C_COUNT 2

struct pollux_i2c_regs_t {
	uint32_t iccr;
	uint32_t icsr;
	uint32_t iar;
	uint32_t idsr;
	uint32_t qcnt_max;
	uint32_t _reserved[4];
	uint32_t irq_pend;
	uint32_t _reserved2[54];
	uint32_t clkenb;
};

#define pollux_i2c(n) ((volatile struct pollux_i2c_regs_t *) \
	(POLLUX_I2C_BASE + (POLLUX_I2C_OFFSET * (n))))

/* iccr */
#define I2C_ACK_GEN			7
#define I2C_CLK_SRC			6
#define I2C_IRQ_ENB			5
#define I2C_CLK_SCALER			0

/* icsr */
#define I2C_ST_ENB			12
#define I2C_SLAVE_MATCH_OCCUR		10
#define I2C_GENERAL_CALL_OCCUR		9
#define I2C_SLV_RX_STOP			8
#define I2C_MASTER_SLV			7
#define I2C_TX_RX			6
#define I2C_ST_BUSY			5
#define I2C_TXRX_ENB			4
#define I2C_ARBIT_FAIL			3
#define I2C_ACK_STATUS			0

/* irq_pend */
#define I2C_OP_HOLD			1
#define I2C_PEND			0

/* clkenb */
#define I2C_PCLKMODE			3

#endif /* _MACH_I2C_H */

