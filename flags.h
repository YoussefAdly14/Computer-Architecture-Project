#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>

/*
    SREG bits for Package 4:

    Bit 0: Carry flag C
    Bit 1: Overflow flag V
    Bit 2: Negative flag N
    Bit 3: Sign flag S
    Bit 4: Zero flag Z

    Bits 7, 6, 5 must always stay 0.
*/

#define FLAG_C 0
#define FLAG_V 1
#define FLAG_N 2
#define FLAG_S 3
#define FLAG_Z 4

void setFlag(int flag, int value);
int getFlag(int flag);
void clearUnusedSREGBits(void);

void updateAddFlags(int8_t a, int8_t b, int8_t result);
void updateSubFlags(int8_t a, int8_t b, int8_t result);
void updateNZFlags(int8_t result);

void printFlags(void);

#endif
