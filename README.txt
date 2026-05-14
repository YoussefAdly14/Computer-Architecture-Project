CSEN601 Package 4 C Project
===========================

This is a multi-file C implementation for Package 4.

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
  Detects data hazards used by the pipeline stall logic.

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

Implemented behavior:
--------------------
1. Reads Package 4 assembly from program.txt.
2. Parses and stores 16-bit instructions in instruction memory.
3. Simulates the Package 4 three-stage pipeline: Fetch, Decode, Execute.
4. Handles data hazards by stalling Fetch and Decode and inserting an Execute bubble.
5. Handles taken BEQZ and JR control hazards by flushing Fetch and Decode.
6. Prints pipeline state and flags after each clock cycle.
7. Prints all registers, instruction memory, and data memory after execution.

Submission reminders:
--------------------
1. Test the demo program you want to show in program.txt.
2. Prepare the report and demo video required by the course submission.
