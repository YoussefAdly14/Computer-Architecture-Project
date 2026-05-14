#include <stdio.h>
#include "registers.h"

int8_t registersFile[REGISTER_COUNT];
uint8_t SREG = 0;
uint16_t PC = 0;

void initializeRegisters(void) {
    for (int i = 0; i < REGISTER_COUNT; i++) {
        registersFile[i] = 0;
    }

    SREG = 0;
    PC = 0;
}

int8_t getRegisterValue(int index) {
    if (index < 0 || index >= REGISTER_COUNT) {
        printf("Error: invalid register R%d\n", index);
        return 0;
    }

    return registersFile[index];
}

void setRegisterValue(int index, int8_t value) {
    if (index < 0 || index >= REGISTER_COUNT) {
        printf("Error: invalid register R%d\n", index);
        return;
    }

    registersFile[index] = value;
}

uint16_t getPC(void) {
    return PC;
}

void setPC(uint16_t value) {
    PC = value;
}

void incrementPC(void) {
    PC++;
}

void printRegisters(void) {
    printf("\n========== Registers ==========\n");

    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("R%-2d = %4d", i, registersFile[i]);

        if ((i + 1) % 4 == 0) {
            printf("\n");
        } else {
            printf("    ");
        }
    }

    printf("PC   = %u\n", PC);
    printf("SREG = %u\n", SREG);
}
