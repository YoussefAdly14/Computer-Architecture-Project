#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *trim(char *str) {
    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    char *end = str + strlen(str) - 1;

    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

void removeComment(char *line) {
    char *comment = strstr(line, "//");

    if (comment != NULL) {
        *comment = '\0';
    }

    comment = strchr(line, '#');

    if (comment != NULL) {
        *comment = '\0';
    }
}

int isEmptyLine(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return 0;
        }
        line++;
    }

    return 1;
}

int signExtend6Bit(int value) {
    value &= 0x3F;

    if (value & 0x20) {
        return value | ~0x3F;
    }

    return value;
}

int parseNumber(const char *token) {
    return (int)strtol(token, NULL, 0);
}
