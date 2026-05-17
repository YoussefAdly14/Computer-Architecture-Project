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

    int8_t prevVal;
    int8_t ResultValue;

    switch (opcode) {
        case OP_ADD:
            prevVal = getRegisterValue(r1);
            ResultValue = prevVal + getRegisterValue(r2);
            setRegisterValue(r1, ResultValue);
            updateAddFlags(prevVal, getRegisterValue(r2), ResultValue);
            printf("EX: R%d = R%d + R%d -> %d\n", r1, r1, r2, ResultValue);
            break;

        case OP_SUB:
            prevVal = getRegisterValue(r1);
            ResultValue = prevVal - getRegisterValue(r2);
            setRegisterValue(r1, ResultValue);
            updateSubFlags(prevVal, getRegisterValue(r2), ResultValue);
            printf("EX: R%d = R%d - R%d -> %d\n", r1, r1, r2, ResultValue);
            break;

        case OP_MUL:
            prevVal = getRegisterValue(r1);
            ResultValue = prevVal * getRegisterValue(r2);
            setRegisterValue(r1, ResultValue);
            updateNZFlags(ResultValue);
            printf("EX: R%d = R%d * R%d -> %d\n", r1, r1, r2, ResultValue);
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
            ResultValue = getRegisterValue(r1) & getRegisterValue(r2);
            setRegisterValue(r1, ResultValue);
            updateNZFlags(ResultValue);
            printf("EX: R%d = R%d & R%d -> %d\n", r1, r1, r2, ResultValue);
            break;

        case OP_OR:
            ResultValue = getRegisterValue(r1) | getRegisterValue(r2);
            setRegisterValue(r1, ResultValue);
            updateNZFlags(ResultValue);
            printf("EX: R%d = R%d | R%d -> %d\n", r1, r1, r2, ResultValue);
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
            ResultValue = getRegisterValue(r1) << shift;
            setRegisterValue(r1, ResultValue);
            updateNZFlags(ResultValue);
            printf("EX: R%d = R%d << %d -> %d\n", r1, r1, shift, ResultValue);
            break;
        }

        case OP_SAR: {
            int shift = immRaw;  // shift immediate is positive
            ResultValue = getRegisterValue(r1) >> shift;
            setRegisterValue(r1, ResultValue);
            updateNZFlags(ResultValue);
            printf("EX: R%d = R%d >> %d -> %d\n", r1, r1, shift, ResultValue);
            break;
        }

        case OP_LB: {
            int address = immRaw;
            ResultValue = loadData(address);
            setRegisterValue(r1, ResultValue);
            printf("EX: LB R%d, %d -> %d\n", r1, address, ResultValue);
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
