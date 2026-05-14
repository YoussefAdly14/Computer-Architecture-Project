#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

/*
    CSEN601 - Package 4 Configuration

    Package 4:
    - Harvard Architecture
    - Instruction memory: 1024 x 16 bits
    - Data memory: 2048 x 8 bits
    - Registers: R0 to R63, each 8 bits
    - PC: 16 bits
    - SREG: 8 bits, only bits 0 to 4 are used
    - Pipeline: 3 stages: IF, ID, EX
*/

#define INSTRUCTION_MEMORY_SIZE 1024
#define DATA_MEMORY_SIZE        2048
#define REGISTER_COUNT          64

#define INSTRUCTION_BITS        16
#define DATA_BITS               8

#define OPCODE_BITS             4
#define REGISTER_BITS           6
#define IMMEDIATE_BITS          6

#define MAX_PROGRAM_LINES       1024
#define MAX_LINE_LENGTH         128

#endif
