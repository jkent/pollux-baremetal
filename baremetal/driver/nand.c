#include <string.h>

#include <asm/io.h>
#include <asm/types.h>
#include <mach/mcus.h>
#include <mach/nand.h>

#include "driver/nand.h"

static void __iomem *mcus = (void __iomem *)MCUS_BASE;
static void __iomem *nand = (void __iomem *)NAND_BASE;

nand_chip_t nand_chips[2];
static nand_chip_t *active_chip = &nand_chips[0];

static void nand_clear_intpend()
{
    u32 ctrl;
    ctrl = readl(mcus + MCUS_NFCONTROL);
    ctrl |= MCUS_NFCONTROL_INTPEND;
    writel(ctrl, mcus + MCUS_NFCONTROL);
}

static void nand_wait_intpend()
{
    u32 ctrl;
    while (1) {
        ctrl = readl(mcus + MCUS_NFCONTROL);
        if (ctrl & MCUS_NFCONTROL_INTPEND) {
            break;
        }
    }
    nand_clear_intpend();
}

static void nand_wait_busy()
{
    u32 ctrl;
    while(1) {
        ctrl = readl(mcus + MCUS_NFCONTROL);
        if (ctrl & MCUS_NFCONTROL_RNB) {
            break;
        }
    }
    nand_clear_intpend();
}

static int nand_wait_status()
{
    int status;
    nand_wait_intpend();
    writeb(NAND_CMD_STATUS, nand + NAND_CMD);
    status = (int)readb(nand + NAND_DATA);
    return status;
}

static void nand_command(nand_chip_t *chip, u8 cmd, s32 column, s32 page_addr)
{
    if (!chip->present) {
        return;
    }

    nand_wait_busy();

    if (active_chip != chip) {
        u32 ctrl = readl(mcus + MCUS_NFCONTROL);
        if (chip->num == 0) {
            ctrl &= ~MCUS_NFCONTROL_NFBANK;
        } else {
            ctrl |= MCUS_NFCONTROL_NFBANK;
        }
        writel(ctrl, mcus + MCUS_NFCONTROL);
        active_chip = chip;
    }

    if (chip->page_size <= 512) {
        if (cmd == NAND_CMD_SEQIN) {
            if (column >= chip->page_size) {
                column -= chip->page_size;
                writeb(NAND_CMD_READOOB, nand + NAND_CMD);
            } else if (column < 256) {
                writeb(NAND_CMD_READ0, nand + NAND_CMD);
            } else {
                column -= 256;
                writeb(NAND_CMD_READ1, nand + NAND_CMD);
            }
        }
        writeb(cmd, nand + NAND_CMD);

        if (column != -1) {
            writeb(column & 0xFF, nand + NAND_ADDR);
        }
        if (page_addr != -1) {
            writeb(page_addr & 0xFF, nand + NAND_ADDR);
            writeb((page_addr >> 8) & 0xFF, nand + NAND_ADDR);
            if (chip->chip_bits > 25) { /* 32 MiB */
                writeb((page_addr >> 16) & 0xFF, nand + NAND_ADDR);
            }
        }

        switch (cmd) {
        case NAND_CMD_PAGEPROG:
        case NAND_CMD_ERASE1:
        case NAND_CMD_ERASE2:
        case NAND_CMD_SEQIN:
        case NAND_CMD_STATUS:
            return;
        }
    } else {
        if (cmd == NAND_CMD_READOOB) { /* compatability */
            column += chip->page_size;
            cmd = NAND_CMD_READ0;
        }

        writeb(cmd, nand + NAND_CMD);

        if (column != -1) {
            writeb(column & 0xFF, nand + NAND_ADDR);
            writeb((column >> 8) & 0xFF, nand + NAND_ADDR);
        }
        if (column != -1) {
            writeb(page_addr & 0xFF, nand + NAND_ADDR);
            writeb((page_addr >> 8) & 0xFF, nand + NAND_ADDR);
            if (chip->chip_bits > 27) { /* 128 MiB */
                writeb((page_addr >> 16) & 0xFF, nand + NAND_ADDR);
            }
        }

        switch (cmd) {
        case NAND_CMD_CACHEDPROG:
        case NAND_CMD_PAGEPROG:
        case NAND_CMD_ERASE1:
        case NAND_CMD_ERASE2:
        case NAND_CMD_SEQIN:
        case NAND_CMD_RNDIN:
        case NAND_CMD_STATUS:
            return;

        case NAND_CMD_RNDOUT:
            writeb(NAND_CMD_RNDOUTSTART, nand + NAND_CMD);
            return;

        case NAND_CMD_READ0:
            writeb(NAND_CMD_READ0, nand + NAND_CMD);
            break;
        }
    }

    nand_wait_intpend();
}

static void nand_probe_onfi(void)
{
    onfi_data_t onfi;
    nand_chip_t *chip = active_chip;

    writeb(NAND_CMD_RESET, nand + NAND_CMD);
    writeb(NAND_CMD_PARAM, nand + NAND_CMD);
    writeb(0, nand + NAND_ADDR);
    nand_wait_busy();
    for (int i = 0; i < sizeof(onfi); i++) {
        onfi.data[i] = readb(nand + NAND_DATA);
    }

    /* Make sure the ONFI structure is v1.0 compliant */
    if (memcmp(&onfi.signature, "ONFI", 4) != 0 || (onfi.revision_number & 0x02) == 0) {
        return;
    }
    
    chip->present = true;
    chip->badblock_pos = 0;
    chip->page_size = onfi.data_bytes_per_page;
    chip->oob_size = onfi.spare_bytes_per_page;
    chip->block_size = chip->page_size * onfi.pages_per_block / 1024;
    chip->chip_size = chip->block_size * onfi.blocks_per_lun / 1024;
    chip->read_size = chip->page_size + chip->oob_size;
    /* we ignore the number of LUNs, as we only support one */

    chip->page_bits = fls(chip->page_size - 1);
    chip->oob_bits = fls(chip->oob_bits - 1);
    chip->block_bits = fls(chip->block_bits - 1);
    chip->chip_bits = fls(chip->chip_size - 1);
}

static void nand_probe_id(u8 *chip_id)
{
    nand_chip_t *chip = active_chip;

    switch (chip_id[0]) {
    case 0x2C: /* Micron */
        switch (chip_id[1]) {
        case 0xDA: /* 256 MiB / 2 KiB */
            chip->badblock_pos = 0;
            chip->page_bits = 11;
            chip->oob_bits = 6;
            chip->block_bits = 17;
            chip->chip_bits = 28;
            break;

        default:
            return;
        }
        break;

    case 0xEC: /* Samsung */
        switch (chip_id[1]) {
        case 0x76: /* 64 MiB / 512 B */
            chip->badblock_pos = 5;
            chip->page_bits = 9;
            chip->oob_bits = 4;
            chip->block_bits = 14;
            chip->chip_bits = 26;
            break;

        default:
            return;
        }
        break;

    default:
        return;
    }

    chip->present = true;
    chip->page_size = 1U << chip->page_bits;
    chip->oob_size = 1U << chip->oob_bits;
    chip->block_size = 1U << (chip->block_bits - 10);
    chip->chip_size = 1U << (chip->chip_bits - 20);
    chip->pages_per_block = 1U << (chip->block_bits - chip->page_bits);
    chip->read_size = chip->page_size + chip->oob_size;
}

void nand_probe(void)
{
    nand_chip_t *chip;
    int i;

    for (int n = 0; n < 2; n++) {
        active_chip = chip = &nand_chips[n];
        chip->num = n;
        chip->present = false;

        u32 ctrl = readl(mcus + MCUS_NFCONTROL);
        if (chip->num == 0) {
            ctrl &= ~MCUS_NFCONTROL_NFBANK;
        } else {
            ctrl |= MCUS_NFCONTROL_NFBANK;
        }
        writel(ctrl, mcus + MCUS_NFCONTROL);

        /* read ONFI signature */
        u8 onfi_sig[4];
        writeb(NAND_CMD_READID, nand + NAND_CMD);
        writeb(0x20, nand + NAND_ADDR);
        for (i = 0; i < 4; i++) {
            onfi_sig[i] = readb(nand + NAND_DATA);
        }

        if (memcmp(onfi_sig, "ONFI", 4) == 0) {
            nand_probe_onfi();
            continue;
        }

        /* read id */
        u8 chip_id[8];
        writeb(NAND_CMD_READID, nand + NAND_CMD);
        writeb(0, nand + NAND_ADDR);
        /* TODO: may need delay here for capacitance of floating bus */
        for (i = 0; i < 8; i++) {
            chip_id[i] = readb(nand + NAND_DATA);
        }

        /* detect floating bus */
        u8 first = chip_id[0];
        for (i = 1; i < 8; i++) {
            if (first != chip_id[i]) {
                break;
            }
        }
        if (i == 8) {
            continue;
        }

        nand_probe_id(chip_id);
    }
}

void nand_read_id(u8 *id)
{
    writeb(NAND_CMD_READID, nand + NAND_CMD);
    for (size_t i = 0; i < 8; i++) {
        id[i] = readb(nand + NAND_DATA);
    }
}

/* BCH polynomial is 0x25af */

static s16 bch_pow[8192];
static s16 bch_log[8192];

void nand_bch_init(void)
{
	u32 i, x = 1;
	const u32 k = 1 << 13;

	for (i = 0; i < 8191; i++) {
		bch_pow[i] = x;
		bch_log[x] = i;
		x <<= 1;
		if (x & k) {
			x ^= 0x25af;
        }
	}
	bch_pow[8191] = 1;
	bch_log[0] = 0;
}

int nand_bch_correct(u8 *sector, u8 *ecc)
{
    s32 syn[8];             // Syndromes
    s32 elp[9][10] = { 0 }; // Error locator polynomial (ELP)
    s32 L[9] = { 0 };       // Degree of ELP
    s32 B[9][10] = { 0 };   // Scratch polynomial
    s32 reg[9] = { 0 };     // Register state

    void __iomem *mcus = (void __iomem *)MCUS_BASE;

    u64 syndromes = readq(mcus + MCUS_NFSYNDROME31);
    syn[0] = syndromes & 0x1FFF;
    syn[2] = (syndromes >> 13) & 0x1FFF;
    syn[4] = (syndromes >> 32) & 0x1FFF;
    syn[6] = (syndromes >> 45) & 0x1FFF;

    // Even syndrome = (Odd syndrome) ** 2
    for (s32 i = 1, j = 0; i < 8; i += 2, j++) {
        if (syn[j] == 0) {
            syn[i] = 0;
        } else {
            syn[i] = bch_pow[(2 * bch_log[syn[j]]) % 8191];
        }
    }

    elp[1][0] = 1 ;
    elp[1][1] = syn[0] ;

    L[1] = 1 ;
    if (syn[0] != 0) {
        B[1][0] = bch_pow[(8191 - bch_log[syn[0]]) % 8191];
    } else {
        B[1][0] = 0;
    }

    for (s32 r = 3; r <= 7; r += 2) {
        // Compute discrepancy
        s32 Delta = syn[r - 1];
        for (s32 i = 1; i <= L[r - 2]; i++) {
            if ((syn[r - i - 1] != 0) && (elp[r - 2][i] != 0))
                Delta ^= bch_pow[(bch_log[syn[r - i - 1]] + bch_log[elp[r - 2][i]]) % 8191];
        }

        if (Delta == 0) {
            L[r] = L[r - 2] ;
            for (s32 i = 0; i <= L[r - 2]; i++) {
                elp[r][i] = elp[r - 2][i];
                B[r][i + 2] = B[r - 2][i] ;
            }
        } else {
            // Form new error locator polynomial
            for (s32 i = 0; i <= L[r - 2]; i++) {
                elp[r][i] = elp[r - 2][i];
            }

            for (s32 i = 0; i <= L[r - 2]; i++) {
                if (B[r - 2][i] != 0) {
                    elp[r][i + 2] ^= bch_pow[(bch_log[Delta] + bch_log[B[r - 2][i]]) % 8191];
                }
            }

            // Form new scratch polynomial and register length
            if (2 * L[r - 2] >= r) {
                L[r] = L[r - 2] ;
                for (s32 i = 0; i <= L[r - 2]; i++) {
                    B[r][i + 2] = B[r - 2][i];
                }
            } else {
                L[r] = r - L[r - 2];
                for (s32 i = 0; i <= L[r - 2]; i++) {
                    if (elp[r - 2][i] != 0) {
                        B[r][i] = bch_pow[(bch_log[elp[r - 2][i]] + 8191 - bch_log[Delta]) % 8191];
                    } else {
                        B[r][i] = 0;
                    }
                }
            }
        }
    }

    if (L[7] <= 4) {
        // Chien's search to find roots of the error location polynomial
        // Ref: L&C pp.216, Fig.6.1
        for (s32 i = 1; i <= L[7]; i++) {
            reg[i] = elp[7][i];
        }

        s32 count = 0;
        for (s32 i = 1; i <= 8191; i++) {
            s32 elp_sum = 1;
            for (s32 j = 1; j <= L[7]; j++) {
                if (reg[j] != 0) {
                    reg[j] = bch_pow[(bch_log[reg[j]] + j) % 8191] ;
                    elp_sum ^= reg[j] ;
                }
            }

            if (!elp_sum) {
                // Correct bit flip
                u32 loc = 8191 - i;

                if (loc >= 4148) {
                    return -1;
                }

                if (loc >= 52) {
                    loc = 4095 - (loc - 52);
                    sector[loc >> 3] ^= 1 << (loc & 7);
                } else {
                    ecc[loc >> 3] ^= 1 << (loc & 7);
                }
                count++;
            }
        }

        if (count == L[7]) {
            // Number of roots == degree of elp hence <= 4 errors        
            return count;
        } else {
            // Number of roots != degree of ELP => >4 errors and cannot solve
            return -1;
        }
    } else {
        // Uncorrectable
        return -1;
    }
}
