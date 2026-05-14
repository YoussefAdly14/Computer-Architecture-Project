#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "config.h"

extern uint16_t instructionMemory[INSTRUCTION_MEMORY_SIZE];
extern int8_t dataMemory[DATA_MEMORY_SIZE];
extern int loadedInstructionCount;

void initializeMemory(void);

void storeInstruction(uint16_t instruction);
uint16_t fetchInstruction(int address);

void storeData(int address, int8_t value);
int8_t loadData(int address);

int isValidInstructionAddress(int address);
int isValidDataAddress(int address);

#endif
