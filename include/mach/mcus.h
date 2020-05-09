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

#pragma once

#define MCUS_BASE (0xC0015800)

#define MCUS_REG(x) (x)

#define MCUS_BW				MCUS_REG(0x00)
#define MCUS_TIMEACS			MCUS_REG(0x04)
#define MCUS_TIMECOS			MCUS_REG(0x08)
#define MCUS_TIMEACCL			MCUS_REG(0x0c)
#define MCUS_TIMEACCH			MCUS_REG(0x10)
#define MCUS_TIMESACCL			MCUS_REG(0x14)
#define MCUS_TIMESACCH			MCUS_REG(0x18)
#define MCUS_TIMECOH			MCUS_REG(0x24)
#define MCUS_TIMECAH			MCUS_REG(0x28)
#define MCUS_BURSTL			MCUS_REG(0x2c)
#define MCUS_BURSTH			MCUS_REG(0x30)
#define MCUS_WAIT			MUCS_REG(0x34)
#define MCUS_NFCONTROL			MCUS_REG(0x74)
#define MCUS_NFCONTROL_INTPEND		(1 << 15)
#define MCUS_NFCONTROL_ECCRST		(1 << 11)
#define MCUS_NFCONTROL_RNB		(1 <<  9)
#define MCUS_NFCONTROL_INTENB		(1 <<  8)
#define MCUS_NFCONTROL_NFBOOTENB	(1 <<  5)
#define MCUS_NFCONTROL_NFTYPE_MASK	(3 <<  3)
#define MCUS_NFCONTROL_NFTYPE_SB3	(0 <<  3)
#define MCUS_NFCONTROL_NFTYPE_SB4	(1 <<  3)
#define MCUS_NFCONTROL_NFTYPE_LB4	(2 <<  3)
#define MCUS_NFCONTROL_NFTYPE_LB5	(3 <<  3)
#define MCUS_NFCONTROL_NFBANK		(1 <<  0)
#define MCUS_NFECCL			MCUS_REG(0x78)
#define MCUS_NFECCH			MCUS_REG(0x7c)
#define MCUS_NFORGECCL			MCUS_REG(0x80)
#define MCUS_NFORGECCH			MCUS_REG(0x84)
#define MCUS_NFCNT			MCUS_REG(0x88)
#define MCUS_NFECCSTATUS		MCUS_REG(0x8c)
#define MCUS_NFSYNDROME31		MCUS_REG(0x90)
#define MCUS_NFSYNDROME75		MCUS_REG(0x94)
