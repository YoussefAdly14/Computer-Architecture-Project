#include <stdio.h>
#include "instruction.h"

uint16_t encodeR(Opcode opcode, int r1, int r2) {
    return ((opcode & 0xF) << 12) | ((r1 & 0x3F) << 6) | (r2 & 0x3F);
}

uint16_t encodeI(Opcode opcode, int r1, int imm) {
    return ((opcode & 0xF) << 12) | ((r1 & 0x3F) << 6) | (imm & 0x3F);
}

int getOpcode(uint16_t instruction) {
    return (instruction >> 12) & 0xF;
}

int getR1(uint16_t instruction) {
    return (instruction >> 6) & 0x3F;
}

int getR2(uint16_t instruction) {
    return instruction & 0x3F;
}

int getImmediate6(uint16_t instruction) {
    return instruction & 0x3F;
}

const char *opcodeToString(int opcode) {
    switch (opcode) {
        case OP_ADD:  return "ADD";
        case OP_SUB:  return "SUB";
        case OP_MUL:  return "MUL";
        case OP_LDI:  return "LDI";
        case OP_BEQZ: return "BEQZ";
        case OP_AND:  return "AND";
        case OP_OR:   return "OR";
        case OP_JR:   return "JR";
        case OP_SAL:  return "SAL";
        case OP_SAR:  return "SAR";
        case OP_LB:   return "LB";
        case OP_SB:   return "SB";
        default:      return "UNKNOWN";
    }
}

void printInstruction(uint16_t instruction) {
    int op = getOpcode(instruction);
    int r1 = getR1(instruction);
    int last = getImmediate6(instruction);

    printf("%s R%d %d", opcodeToString(op), r1, last);
}
