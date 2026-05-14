#ifndef PIPELINE_H
#define PIPELINE_H

#include <stdint.h>

typedef struct {
    int valid;
    uint16_t instruction;
    uint16_t pcOfInstruction;
} PipelineStage;

extern PipelineStage fetchStage;
extern PipelineStage decodeStage;
extern PipelineStage executeStage;

void initializePipeline(void);
void runPipeline(void);
int pipelineIsEmpty(void);

void flushFetchAndDecode(void);

#endif
