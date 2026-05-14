#include <stdio.h>
#include "memory.h"

uint16_t instructionMemory[INSTRUCTION_MEMORY_SIZE];
int8_t dataMemory[DATA_MEMORY_SIZE];
int loadedInstructionCount = 0;

void initializeMemory(void) {
    for (int i = 0; i < INSTRUCTION_MEMORY_SIZE; i++) {
        instructionMemory[i] = 0;
    }

    for (int i = 0; i < DATA_MEMORY_SIZE; i++) {
        dataMemory[i] = 0;
    }

    loadedInstructionCount = 0;
}

int isValidInstructionAddress(int address) {
    return address >= 0 && address < INSTRUCTION_MEMORY_SIZE;
}

int isValidDataAddress(int address) {
    return address >= 0 && address < DATA_MEMORY_SIZE;
}

void storeInstruction(uint16_t instruction) {
    if (!isValidInstructionAddress(loadedInstructionCount)) {
        printf("Error: invalid instruction memory address %d\n", loadedInstructionCount);
        return;
    }

    instructionMemory[loadedInstructionCount] = instruction;
    loadedInstructionCount++;
}

uint16_t fetchInstruction(int address) {
    if (!isValidInstructionAddress(address)) {
        printf("Error: invalid instruction memory address %d\n", address);
        return 0;
    }

    return instructionMemory[address];
}

void storeData(int address, int8_t value) {
    if (!isValidDataAddress(address)) {
        printf("Error: invalid data memory address %d\n", address);
        return;
    }

    dataMemory[address] = value;
}

int8_t loadData(int address) {
    if (!isValidDataAddress(address)) {
        printf("Error: invalid data memory address %d\n", address);
        return 0;
    }

    return dataMemory[address];
}
