#include <stdio.h>
#include "printer.h"
#include "pipeline.h"
#include "instruction.h"
#include "memory.h"

void printCompactInstruction(uint16_t instruction) {
    int opcode = getOpcode(instruction);
    int r1 = getR1(instruction);
    int last = getImmediate6(instruction);

    printf("%s R%d %d", opcodeToString(opcode), r1, last);
}

static void printStage(const char *stageName, PipelineStage stage) {
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
    printStage("Fetch", fetchStage);
    printStage("Decode", decodeStage);
    printStage("Execute", executeStage);
}

void printFinalMemory(void) {
    printf("\n========== Instruction Memory ==========\n");

    for (int i = 0; i < loadedInstructionCount; i++) {
        printf("IM[%d] = %u -> ", i, instructionMemory[i]);
        printCompactInstruction(instructionMemory[i]);
        printf("\n");
    }

    printf("\n========== Data Memory - Non-Zero Values ==========\n");

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
}
