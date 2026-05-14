#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.h"
#include "instruction.h"
#include "memory.h"
#include "utils.h"

/*
    Reads program.txt line by line, converts assembly into 16-bit instructions,
    and stores only the encoded instructions in instruction memory.
*/

void loadProgram(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: could not open %s\n", filename);
        return;
    }

    char line[128];

    while (fgets(line, sizeof(line), file) != NULL) {
        removeComment(line);
        char *clean = trim(line);

        if (isEmptyLine(clean)) {
            continue;
        }

        uint16_t instruction = parseLine(clean);
        storeInstruction(instruction);
    }

    fclose(file);

    printf("Loaded %d instruction(s) into instruction memory.\n", loadedInstructionCount);
}

static void toUpperCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }
}

uint16_t parseLine(char *line) {
    char copy[128];
    strcpy(copy, line);

    char *mnemonic = strtok(copy, " \t,\n\r");

    if (mnemonic == NULL) {
        return 0;
    }

    toUpperCase(mnemonic);

    int opcode = getOpcodeFromMnemonic(mnemonic);

    if (opcode == -1) {
        printf("Error: unknown mnemonic: %s\n", mnemonic);
        return 0;
    }

    char *arg1 = strtok(NULL, " \t,\n\r");
    char *arg2 = strtok(NULL, " \t,\n\r");

    if (arg1 == NULL) {
        printf("Error: missing first operand in line: %s\n", line);
        return 0;
    }

    int r1 = parseRegister(arg1);

    if (r1 == -1) {
        printf("Error: invalid register: %s\n", arg1);
        return 0;
    }

    if (arg2 == NULL) {
        printf("Error: missing second operand/immediate in line: %s\n", line);
        return 0;
    }

    switch (opcode) {
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_AND:
        case OP_OR:
        case OP_JR: {
            int r2 = parseRegister(arg2);
            if (r2 == -1) {
                printf("Error: invalid register: %s\n", arg2);
                return 0;
            }
            return encodeR((Opcode)opcode, r1, r2);
        }

        case OP_LDI:
        case OP_BEQZ:
        case OP_SAL:
        case OP_SAR:
        case OP_LB:
        case OP_SB: {
            int imm = parseNumber(arg2);
            return encodeI((Opcode)opcode, r1, imm);
        }

        default:
            printf("Error: unsupported opcode in parser.\n");
            return 0;
    }
}

int getOpcodeFromMnemonic(const char *mnemonic) {
    if (strcmp(mnemonic, "ADD") == 0)  return OP_ADD;
    if (strcmp(mnemonic, "SUB") == 0)  return OP_SUB;
    if (strcmp(mnemonic, "MUL") == 0)  return OP_MUL;
    if (strcmp(mnemonic, "LDI") == 0)  return OP_LDI;
    if (strcmp(mnemonic, "BEQZ") == 0) return OP_BEQZ;
    if (strcmp(mnemonic, "AND") == 0)  return OP_AND;
    if (strcmp(mnemonic, "OR") == 0)   return OP_OR;
    if (strcmp(mnemonic, "JR") == 0)   return OP_JR;
    if (strcmp(mnemonic, "SAL") == 0)  return OP_SAL;
    if (strcmp(mnemonic, "SAR") == 0)  return OP_SAR;
    if (strcmp(mnemonic, "LB") == 0)   return OP_LB;
    if (strcmp(mnemonic, "SB") == 0)   return OP_SB;

    return -1;
}

int parseRegister(const char *token) {
    if (token == NULL) {
        return -1;
    }

    if (token[0] != 'R' && token[0] != 'r') {
        return -1;
    }

    int index = atoi(token + 1);

    if (index < 0 || index >= 64) {
        return -1;
    }

    return index;
}
