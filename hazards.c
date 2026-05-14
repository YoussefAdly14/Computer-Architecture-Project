#include "hazards.h"
#include "pipeline.h"
#include "instruction.h"

/*
    This is intentionally a starter placeholder.

    Package 4 requires data hazard handling.
    The easiest first implementation is stalling.

    Suggested logic:
    - Find which register the Execute stage instruction will write to.
    - Find which registers the Decode stage instruction needs to read.
    - If they overlap, stall Fetch and Decode until safe.

    You can also implement forwarding instead of stalling.
*/

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

    /*
        Basic detection idea.
        You may refine this because not all I-format instructions read both fields.
    */

    if (decR1 == exDestination) {
        return 1;
    }

    if (decOpcode == OP_ADD ||
        decOpcode == OP_SUB ||
        decOpcode == OP_MUL ||
        decOpcode == OP_AND ||
        decOpcode == OP_OR ||
        decOpcode == OP_JR) {
        if (decR2 == exDestination) {
            return 1;
        }
    }

    return 0;
}
