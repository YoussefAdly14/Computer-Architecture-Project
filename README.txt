CSEN601 Package 4 C Project Template
===================================

This is a starter multi-file C template for Package 4.

Package 4 Summary:
- Harvard architecture
- Separate instruction memory and data memory
- Instruction memory: 1024 x 16 bits
- Data memory: 2048 x 8 bits
- Registers: R0 to R63, each 8 bits
- PC: 16 bits
- SREG: 8 bits, only bits 0 to 4 are used
- Pipeline: Fetch, Decode, Execute

Files:
- main.c
  Main controller. Initializes memory/registers, loads program.txt, runs pipeline, prints final output.

- config.h
  Stores all constants like memory sizes, register count, and instruction size.

- instruction.h / instruction.c
  Encodes and decodes 16-bit instructions.

- memory.h / memory.c
  Contains instruction memory and data memory functions.

- registers.h / registers.c
  Contains R0-R63, PC, and SREG functions.

- flags.h / flags.c
  Handles C, V, N, S, and Z flags.

- parser.h / parser.c
  Reads program.txt and stores encoded instructions in instruction memory.

- pipeline.h / pipeline.c
  Simulates the 3-stage pipeline.

- execute.h / execute.c
  Executes the actual instructions.

- hazards.h / hazards.c
  Placeholder for data hazard logic. Start by implementing stalling here.

- printer.h / printer.c
  Handles printing pipeline stages, registers, and memory.

- utils.h / utils.c
  Helper functions like trimming strings and sign extending 6-bit immediates.

- program.txt
  Sample assembly input file.

How to compile:
-------------
Using Makefile:
    make

Or manually:
    gcc -Wall -Wextra -std=c11 main.c memory.c registers.c parser.c instruction.c pipeline.c execute.c flags.c printer.c hazards.c utils.c -o processor

How to run:
----------
On Linux/Mac:
    ./processor

On Windows:
    processor.exe

Important TODOs:
---------------
1. Complete data hazard handling in hazards.c and pipeline.c.
2. Make printing more detailed according to your TA's requirements.
3. Test every instruction.
4. Add more assembly programs for testing.
5. Write your report and record the demo video.
