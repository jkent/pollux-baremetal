#pragma once

#define EARLY_CODE __attribute__((section (".text.early")))
#define EARLY_RODATA __attribute__((section (".rodata.early")))
#define NAKED __attribute__((naked))