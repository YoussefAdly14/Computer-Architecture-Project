#include "hazards.h"
#include "pipeline.h"
#include "instruction.h"

static int adly_instructionWritesToRegister(int opcode) {
    return opcode == OP_ADD ||
           opcode == OP_SUB ||
           opcode == OP_MUL ||
           opcode == OP_LDI ||
           opcode == OP_AND ||
           opcode == OP_OR ||
           opcode == OP_SAL ||
           opcode == OP_SAR ||
           opcode == OP_LB;
}

static int adly_instructionReadsR1(int opcode) {
    return opcode == OP_ADD ||
           opcode == OP_SUB ||
           opcode == OP_MUL ||
           opcode == OP_BEQZ ||
           opcode == OP_AND ||
           opcode == OP_OR ||
           opcode == OP_JR ||
           opcode == OP_SAL ||
           opcode == OP_SAR ||
           opcode == OP_SB;
}

static int adly_instructionReadsR2(int opcode) {
    return opcode == OP_ADD ||
           opcode == OP_SUB ||
           opcode == OP_MUL ||
           opcode == OP_AND ||
           opcode == OP_OR ||
           opcode == OP_JR;
}

int hasDataHazard(void) {
    if (!decodeStage.valid || !executeStage.valid) {
        return 0;
    }

    int exOpcode = getOpcode(executeStage.instruction);
    int exDestination = getR1(executeStage.instruction);

    if (!adly_instructionWritesToRegister(exOpcode)) {
        return 0;
    }

    int decOpcode = getOpcode(decodeStage.instruction);
    int decR1 = getR1(decodeStage.instruction);
    int decR2 = getR2(decodeStage.instruction);

    if (adly_instructionReadsR1(decOpcode) && decR1 == exDestination) {
        return 1;
    }

    if (adly_instructionReadsR2(decOpcode) && decR2 == exDestination) {
        return 1;
    }

    return 0;
}
