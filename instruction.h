#ifndef INSTRUCTION_H
#define INSTRUCTION_H
//
#include <stdint.h>

/*
    Package 4 Instruction Set

    R-format:
    | opcode: 4 bits | R1: 6 bits | R2: 6 bits |

    I-format:
    | opcode: 4 bits | R1: 6 bits | immediate/address: 6 bits |
*/

typedef enum {
    OP_ADD  = 0,
    OP_SUB  = 1,
    OP_MUL  = 2,
    OP_LDI  = 3,
    OP_BEQZ = 4,
    OP_AND  = 5,
    OP_OR   = 6,
    OP_JR   = 7,
    OP_SAL  = 8,
    OP_SAR  = 9,
    OP_LB   = 10,
    OP_SB   = 11
} Opcode;

uint16_t encodeR(Opcode opcode, int r1, int r2);
uint16_t encodeI(Opcode opcode, int r1, int imm);

int getOpcode(uint16_t instruction);
int getR1(uint16_t instruction);
int getR2(uint16_t instruction);
int getImmediate6(uint16_t instruction);

const char *opcodeToString(int opcode);
void printInstruction(uint16_t instruction);

#endif
