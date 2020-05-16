/*
 * Copyright (C) 2013-2020 Jeff Kent <jeff@jkent.net>
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

#pragma once

#define IRQ_BASE (0xC0000800)

#define IRQ_REG(x) (x)

#define IRQ_MODEL           IRQ_REG(0x08)
#define IRQ_MODEH           IRQ_REG(0x0C)
#define IRQ_MASKL           IRQ_REG(0x10)
#define IRQ_MASKH           IRQ_REG(0x14)
#define IRQ_PRIORDER        IRQ_REG(0x18)
#define IRQ_PENDL           IRQ_REG(0x20)
#define IRQ_PENDH           IRQ_REG(0x24)

#define IRQ_PDISPLAY        (0)
#define IRQ_SDISPLAY        (1)
#define IRQ_DMA             (3)
#define IRQ_TIMER0          (4)
#define IRQ_CLKPWR          (5)
#define IRQ_UART0           (10)
#define IRQ_TIMER1          (11)
#define IRQ_SSPSPI0         (12)
#define IRQ_GPIO            (13)
#define IRQ_SDIO            (14)
#define IRQ_TIMER2          (15)
#define IRQ_UDC             (20)
#define IRQ_TIMER3          (21)
#define IRQ_AUDIO           (24)
#define IRQ_ADC             (25)
#define IRQ_MCUS            (26)
#define IRQ_GRP3D           (27)
#define IRQ_UHC             (28)
#define IRQ_RTC             (31)
#define IRQ_I2C0            (32)
#define IRQ_I2C1            (33)
#define IRQ_UART1           (34)
#define IRQ_UART2           (35)
#define IRQ_UART3           (36)
#define IRQ_SSPSPI1         (39)
#define IRQ_SSPSPI2         (40)
#define IRQ_CSC             (41)
#define IRQ_SDI1            (42)
#define IRQ_TIMER4          (43)

#define IRQ_ARBSEL11(_x)    (((_x) & 7) << 22)
#define IRQ_ARBSEL10(_x)    (((_x) & 3) << 20)
#define IRQ_ARBSEL9(_x)     (((_x) & 3) << 18)
#define IRQ_ARBSEL8(_x)     (((_x) & 3) << 16)
#define IRQ_ARBSEL7(_x)     (((_x) & 3) << 14)
#define IRQ_ARBSEL6(_x)     (((_x) & 3) << 12)
#define IRQ_ARBSEL5(_x)     (((_x) & 3) << 10)
#define IRQ_ARBSEL4(_x)     (((_x) & 3) << 8)
#define IRQ_ARBSEL3(_x)     (((_x) & 3) << 6)
#define IRQ_ARBSEL2(_x)     (((_x) & 3) << 4)
#define IRQ_ARBSEL1(_x)     (((_x) & 3) << 2)
#define IRQ_ARBSEL0(_x)     (((_x) & 3) << 0)
