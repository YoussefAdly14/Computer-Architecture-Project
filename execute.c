#include <stdio.h>
#include <stdint.h>

#include "execute.h"
#include "instruction.h"
#include "registers.h"
#include "memory.h"
#include "flags.h"
#include "utils.h"

ExecuteResult executeInstruction(uint16_t instruction, uint16_t pcOfInstruction) {
    ExecuteResult result;
    result.branchTaken = 0;
    result.newPC = 0;

    int opcode = getOpcode(instruction);
    int r1 = getR1(instruction);
    int r2 = getR2(instruction);
    int immRaw = getImmediate6(instruction);

    int8_t oldValue;
    int8_t newValue;

    switch (opcode) {
        case OP_ADD:
            oldValue = getRegisterValue(r1);
            newValue = oldValue + getRegisterValue(r2);
            setRegisterValue(r1, newValue);
            updateAddFlags(oldValue, getRegisterValue(r2), newValue);
            printf("EX: R%d = R%d + R%d -> %d\n", r1, r1, r2, newValue);
            break;

        case OP_SUB:
            oldValue = getRegisterValue(r1);
            newValue = oldValue - getRegisterValue(r2);
            setRegisterValue(r1, newValue);
            updateSubFlags(oldValue, getRegisterValue(r2), newValue);
            printf("EX: R%d = R%d - R%d -> %d\n", r1, r1, r2, newValue);
            break;

        case OP_MUL:
            oldValue = getRegisterValue(r1);
            newValue = oldValue * getRegisterValue(r2);
            setRegisterValue(r1, newValue);
            updateNZFlags(newValue);
            printf("EX: R%d = R%d * R%d -> %d\n", r1, r1, r2, newValue);
            break;

        case OP_LDI: {
            int imm = signExtend6Bit(immRaw);
            setRegisterValue(r1, (int8_t)imm);
            printf("EX: R%d = %d\n", r1, imm);
            break;
        }

        case OP_BEQZ: {
            int imm = signExtend6Bit(immRaw);
            if (getRegisterValue(r1) == 0) {
                result.branchTaken = 1;
                result.newPC = pcOfInstruction + 1 + imm;
                printf("EX: BEQZ taken -> PC = %u\n", result.newPC);
            } else {
                printf("EX: BEQZ not taken\n");
            }
            break;
        }

        case OP_AND:
            newValue = getRegisterValue(r1) & getRegisterValue(r2);
            setRegisterValue(r1, newValue);
            updateNZFlags(newValue);
            printf("EX: R%d = R%d & R%d -> %d\n", r1, r1, r2, newValue);
            break;

        case OP_OR:
            newValue = getRegisterValue(r1) | getRegisterValue(r2);
            setRegisterValue(r1, newValue);
            updateNZFlags(newValue);
            printf("EX: R%d = R%d | R%d -> %d\n", r1, r1, r2, newValue);
            break;

        case OP_JR: {
            uint16_t high = (uint8_t)getRegisterValue(r1);
            uint16_t low = (uint8_t)getRegisterValue(r2);
            result.branchTaken = 1;
            result.newPC = (high << 8) | low;
            printf("EX: JR -> PC = %u\n", result.newPC);
            break;
        }

        case OP_SAL: {
            int shift = immRaw;  // shift immediate is positive
            newValue = getRegisterValue(r1) << shift;
            setRegisterValue(r1, newValue);
            updateNZFlags(newValue);
            printf("EX: R%d = R%d << %d -> %d\n", r1, r1, shift, newValue);
            break;
        }

        case OP_SAR: {
            int shift = immRaw;  // shift immediate is positive
            newValue = getRegisterValue(r1) >> shift;
            setRegisterValue(r1, newValue);
            updateNZFlags(newValue);
            printf("EX: R%d = R%d >> %d -> %d\n", r1, r1, shift, newValue);
            break;
        }

        case OP_LB: {
            int address = immRaw;
            newValue = loadData(address);
            setRegisterValue(r1, newValue);
            printf("EX: LB R%d, %d -> %d\n", r1, address, newValue);
            break;
        }

        case OP_SB: {
            int address = immRaw;
            storeData(address, getRegisterValue(r1));
            printf("EX: SB R%d, %d -> memory[%d] = %d\n",
                   r1, address, address, getRegisterValue(r1));
            break;
        }

        default:
            printf("EX: unknown instruction\n");
            break;
    }

    return result;
}
