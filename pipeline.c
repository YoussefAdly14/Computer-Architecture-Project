#include <stdio.h>
#include "pipeline.h"
#include "memory.h"
#include "registers.h"
#include "execute.h"
#include "printer.h"
#include "flags.h"
#include "hazards.h"

PipelineStage fetchStage;
PipelineStage decodeStage;
PipelineStage executeStage;

static int adly_cycle = 1;

void initializePipeline(void) {
    fetchStage.valid = 0;
    decodeStage.valid = 0;
    executeStage.valid = 0;

    fetchStage.instruction = 0;
    decodeStage.instruction = 0;
    executeStage.instruction = 0;

    fetchStage.pcOfInstruction = 0;
    decodeStage.pcOfInstruction = 0;
    executeStage.pcOfInstruction = 0;

    adly_cycle = 1;
}

int pipelineIsEmpty(void) {
    return !fetchStage.valid && !decodeStage.valid && !executeStage.valid;
}

void flushFetchAndDecode(void) {
    fetchStage.valid = 0;
    decodeStage.valid = 0;
}

void runPipeline(void) {
    initializePipeline();

    while (getPC() < loadedInstructionCount || !pipelineIsEmpty()) {
        printf("\n================ Clock Cycle %d ================\n", adly_cycle);

        ExecuteResult exResult;
        exResult.branchTaken = 0;
        exResult.newPC = 0;

        if (executeStage.valid) {
            printf("Execute Stage: ");
            printCompactInstruction(executeStage.instruction);
            printf("\n");

            exResult = executeInstruction(
                executeStage.instruction,
                executeStage.pcOfInstruction
            );
        } else {
            printf("Execute Stage: Empty\n");
        }

        if (exResult.branchTaken) {
            setPC(exResult.newPC);
            flushFetchAndDecode();
            printf("Control hazard handled: Fetch and Decode stages flushed.\n");
        }

        if (exResult.branchTaken) {
            executeStage.valid = 0;
        } else if (hasDataHazard()) {
            printf("Data hazard detected: stalling Fetch and Decode, inserting Execute bubble.\n");
            executeStage.valid = 0;
        } else {
            executeStage = decodeStage;
            decodeStage = fetchStage;

            if (getPC() < loadedInstructionCount) {
                fetchStage.valid = 1;
                fetchStage.pcOfInstruction = getPC();
                fetchStage.instruction = fetchInstruction(getPC());

                printf("Fetch Stage: fetched instruction at PC = %u\n", getPC());

                incrementPC();
            } else {
                fetchStage.valid = 0;
            }
        }

        printPipelineStages();
        printFlags();

        adly_cycle++;
    }

    printf("\nProgram finished after %d clock cycle(s).\n", adly_cycle - 1);
}
