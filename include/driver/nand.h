#pragma once

#include <stdbool.h>

#include <asm/types.h>

typedef struct nand_chip_t {
    u8 num;
    bool present;

    u8 page_bits;
    u8 oob_bits;
    u8 block_bits;
    u8 chip_bits;

    u8 badblock_pos;
    u16 page_size;  /* B */
    u16 oob_size;   /* B */
    u16 read_size;  /* B */
    u16 block_size; /* KiB */
    u16 chip_size;  /* MiB */
    u16 num_blocks;
    u16 pages_per_block;
} nand_chip_t;

typedef union onfi_data_t {
    u8 data[256];
    struct __attribute__((packed)) {
        u32 signature;
        u16 revision_number;
        u16 features_supported;
        u16 optional_commands;
        u8 _reserved1[22];
        char device_manufacturer[12];
        char device_model[20];
        u8 jedec_manufacturer;
        u16 date_code;
        u8 _reserved2[13];
        u32 data_bytes_per_page;
        u16 spare_bytes_per_page;
        u32 data_bytes_per_partial_page;
        u16 spare_bytes_per_partial_page;
        u32 pages_per_block;
        u32 blocks_per_lun;
        u8 num_luns;
        u8 num_address_cycles;
        u8 num_bits_per_cell;
        u16 max_bad_blocks_per_lun;
        u16 block_endurance;
        u8 guaranteed_valid_blocks;
        u16 block_endurance_for_guranteed_blocks;
        u8 number_of_programs_per_page;
        u8 partial_programming_attributes;
        u8 number_of_ecc_correction_bits;
        u8 number_of_interleved_address_bits;
        u8 interleved_operation_attributes;
        u8 _reserved3[13];
        u8 io_capacitance;
        u16 timing_mode;
        u16 program_cache_timing_mode;
        u16 max_page_program_time;
        u16 max_block_erase_time;
        u16 max_page_read_time;
        u16 min_change_column_time;
        u8 _reserved4[23];
        u16 vendor_revision;
        u8 vnedor_data[88];
        u16 crc;
    };
} onfi_data_t;

nand_chip_t nand_chips[2];

void nand_probe(void);
void nand_bch_init(void);
int nand_bch_correct(u8 *sector, u8 *ecc);
