#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include "config.h"

extern int8_t registersFile[REGISTER_COUNT];
extern uint8_t SREG;
extern uint16_t PC;

void initializeRegisters(void);

int8_t getRegisterValue(int index);
void setRegisterValue(int index, int8_t value);

uint16_t getPC(void);
void setPC(uint16_t value);
void incrementPC(void);

void printRegisters(void);

#endif
