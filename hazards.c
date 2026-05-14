#include "hazards.h"
#include "pipeline.h"
#include "instruction.h"

static int instructionWritesToRegister(int opcode) {
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

static int instructionReadsR1(int opcode) {
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

static int instructionReadsR2(int opcode) {
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

    if (!instructionWritesToRegister(exOpcode)) {
        return 0;
    }

    int decOpcode = getOpcode(decodeStage.instruction);
    int decR1 = getR1(decodeStage.instruction);
    int decR2 = getR2(decodeStage.instruction);

    if (instructionReadsR1(decOpcode) && decR1 == exDestination) {
        return 1;
    }

    if (instructionReadsR2(decOpcode) && decR2 == exDestination) {
        return 1;
    }

    return 0;
}
