@echo off
gcc -Wall -Wextra -std=c11 main.c memory.c registers.c parser.c instruction.c pipeline.c execute.c flags.c printer.c hazards.c utils.c -o processor.exe
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b %errorlevel%
)
echo Compilation successful.
processor.exe
pause
