#include <stdio.h>
#include <stdint.h>
#include "registers.h"
#include "flags.h"

void clearUnusedSREGBits(void) {
    SREG &= 0x1F;
}

void setFlag(int flag, int value) {
    if (value) {
        SREG |= (1 << flag);
    } else {
        SREG &= ~(1 << flag);
    }

    clearUnusedSREGBits();
}

int getFlag(int flag) {
    return (SREG >> flag) & 1;
}

void updateNZFlags(int8_t result) {
    setFlag(FLAG_N, result < 0);
    setFlag(FLAG_Z, result == 0);
}

/*
    ADD flag update:
    - C is checked using the 9th bit of unsigned addition.
    - V checks signed overflow.
    - N checks negative result.
    - S = N XOR V.
    - Z checks zero result.
*/
void updateAddFlags(int8_t a, int8_t b, int8_t result) {
    uint16_t ua = (uint8_t)a;
    uint16_t ub = (uint8_t)b;
    uint16_t unsignedResult = ua + ub;

    int carry = (unsignedResult & 0x100) != 0;
    int overflow = ((a >= 0 && b >= 0 && result < 0) ||
                    (a < 0 && b < 0 && result >= 0));

    setFlag(FLAG_C, carry);
    setFlag(FLAG_V, overflow);
    setFlag(FLAG_N, result < 0);
    setFlag(FLAG_S, getFlag(FLAG_N) ^ getFlag(FLAG_V));
    setFlag(FLAG_Z, result == 0);
}

/*
    SUB flag update:
    - V is updated for SUB.
    - N, S, Z are also updated.
    - C is not updated by SUB in Package 4.
*/
void updateSubFlags(int8_t a, int8_t b, int8_t result) {
    int overflow = ((a >= 0 && b < 0 && result < 0) ||
                    (a < 0 && b >= 0 && result >= 0));

    setFlag(FLAG_V, overflow);
    setFlag(FLAG_N, result < 0);
    setFlag(FLAG_S, getFlag(FLAG_N) ^ getFlag(FLAG_V));
    setFlag(FLAG_Z, result == 0);
}

void printFlags(void) {
    printf("Flags: C=%d V=%d N=%d S=%d Z=%d\n",
           getFlag(FLAG_C),
           getFlag(FLAG_V),
           getFlag(FLAG_N),
           getFlag(FLAG_S),
           getFlag(FLAG_Z));
}
