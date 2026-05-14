#ifndef UTILS_H
#define UTILS_H

char *trim(char *str);
void removeComment(char *line);
int isEmptyLine(const char *line);

int signExtend6Bit(int value);
int parseNumber(const char *token);

#endif
