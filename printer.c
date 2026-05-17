#include <stdio.h>
#include "printer.h"
#include "pipeline.h"
#include "instruction.h"
#include "memory.h"
#include "utils.h"

void printCompactInstruction(uint16_t instruction) {
    int opcode = getOpcode(instruction);
    int r1 = getR1(instruction);
    int last = getR2(instruction);

    if (opcode == OP_LDI || opcode == OP_BEQZ) {
        last = signExtend6Bit(getImmediate6(instruction));
    }

    printf("%s R%d %d", opcodeToString(opcode), r1, last);
}

static void adly_printStage(const char *stageName, PipelineStage stage) {
    printf("%-14s: ", stageName);

    if (!stage.valid) {
        printf("Empty\n");
        return;
    }

    printf("PC=%u | ", stage.pcOfInstruction);
    printCompactInstruction(stage.instruction);
    printf("\n");
}

void printPipelineStages(void) {
    printf("\nPipeline after cycle:\n");
    adly_printStage("Fetch", fetchStage);
    adly_printStage("Decode", decodeStage);
    adly_printStage("Execute", executeStage);
}

void printFinalMemory(void) {
    printf("\n========== Instruction Memory ==========\n");

#if PRINT_FULL_MEMORY
    for (int i = 0; i < INSTRUCTION_MEMORY_SIZE; i++) {
        printf("IM[%d] = %u", i, instructionMemory[i]);

        if (i < loadedInstructionCount) {
            printf(" -> ");
            printCompactInstruction(instructionMemory[i]);
        }

        printf("\n");
    }
#else
    for (int i = 0; i < loadedInstructionCount; i++) {
        printf("IM[%d] = %u -> ", i, instructionMemory[i]);
        printCompactInstruction(instructionMemory[i]);
        printf("\n");
    }
#endif

    printf("\n========== Data Memory ==========\n");

#if PRINT_FULL_MEMORY
    for (int i = 0; i < DATA_MEMORY_SIZE; i++) {
        printf("DM[%d] = %d\n", i, dataMemory[i]);
    }
#else
    int found = 0;

    for (int i = 0; i < DATA_MEMORY_SIZE; i++) {
        if (dataMemory[i] != 0) {
            printf("DM[%d] = %d\n", i, dataMemory[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("All data memory values are 0.\n");
    }
#endif
}
