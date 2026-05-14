#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

void loadProgram(const char *filename);

uint16_t parseLine(char *line);
int getOpcodeFromMnemonic(const char *mnemonic);
int parseRegister(const char *token);

#endif
