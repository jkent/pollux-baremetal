/*
 * Copyright (C) 2020 Jeff Kent <jeff@jkent.net>
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

#include <stdio.h>

#include <asm/io.h>
#include <driver/nand.h>

int main(void)
{
    printf("Starting NAND probe...\n");

    nand_probe();

    for (int i = 0; i < 2; i++) {
        nand_chip_t *chip = &nand_chips[i];
        if (chip->present) {
            printf("NAND%u found\n", i);
            printf("  page size = %u B\n", chip->page_size);
            printf("  oob size = %u B\n", chip->oob_size);
            printf("  block size = %u KiB\n", chip->block_size);
            printf("  chip_size = %u MiB\n", chip->chip_size);
        }
    }

    return 0;
}
