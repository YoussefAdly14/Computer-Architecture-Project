#include <stdio.h>

#include "memory.h"
#include "registers.h"
#include "parser.h"
#include "pipeline.h"
#include "printer.h"

int main(void) {
    printf("CSEN601 Package 4 Processor Simulator\n");

    initializeMemory();
    initializeRegisters();

    loadProgram("program.txt");

    runPipeline();

    printRegisters();
    printFinalMemory();

    return 0;
}
