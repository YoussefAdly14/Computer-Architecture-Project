#ifndef PRINTER_H
#define PRINTER_H

#include <stdint.h>

void printCompactInstruction(uint16_t instruction);
void printPipelineStages(void);
void printFinalMemory(void);

#endif
