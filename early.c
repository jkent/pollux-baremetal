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

#include "config.h"
#include "asm/io.h"

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_NAND)

#include "mach/mcus.h"
#include "mach/nand.h"

static void __iomem *mcus = (void __iomem *) MCUS_BASE;
static void __iomem *nand = (void __iomem *) NAND_BASE;
extern char __image_end__;


#define CLEAR_IRQ() \
	writel(readl(mcus + MCUS_NFCONTROL) | MCUS_NFCONTROL_INTPEND, \
			mcus + MCUS_NFCONTROL)

#define WAIT_IRQ() \
	while(!(readl(mcus + MCUS_NFCONTROL) & MCUS_NFCONTROL_INTPEND));


void *read_page(unsigned int page, void *mem)
{
	CLEAR_IRQ();

	writeb(NAND_CMD_READ0, nand + NAND_CMD);

	/* column address */
	writeb(0, nand + NAND_ADDR);
#if defined(BAREMETAL_NAND_LB4) || defined(BAREMETAL_NAND_LB5)
	writeb(0, nand + NAND_ADDR);
#endif

	/* row address */
	writeb(page, nand + NAND_ADDR);
	writeb(page>>8, nand + NAND_ADDR);
#if defined(BAREMETAL_NAND_SB4) || defined(BAREMETAL_NAND_LB5)
	writeb(page>>16, nand + NAND_ADDR);
#endif

#if defined(BAREMETAL_NAND_LB4) || defined(BAREMETAL_NAND_LB5)
	writeb(NAND_CMD_READSTART, nand + NAND_CMD);
#endif

	WAIT_IRQ();

	unsigned char *p = mem;
	for (unsigned int i = 0; i < CONFIG_BAREMETAL_NAND_PAGESIZE; i++)
		*p++ = readb(nand + NAND_DATA);

	return p;
}

void nand_startup(void *load_addr)
{
	CLEAR_IRQ();
	writeb(NAND_CMD_RESET, nand + NAND_CMD);
	WAIT_IRQ();

	unsigned int page = 1;
	while (load_addr < (void *)&__image_end__)
		load_addr = read_page(page++, load_addr);
}
#endif

#if defined(CONFIG_BAREMETAL_BOOT_SOURCE_UART)
void uart_startup(void *load_addr)
{
}
#endif
