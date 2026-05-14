#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdint.h>

typedef struct {
    int branchTaken;
    uint16_t newPC;
} ExecuteResult;

ExecuteResult executeInstruction(uint16_t instruction, uint16_t pcOfInstruction);

#endif
