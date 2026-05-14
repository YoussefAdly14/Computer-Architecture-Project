CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c memory.c registers.c parser.c instruction.c pipeline.c execute.c flags.c printer.c hazards.c utils.c
OUT = processor

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) processor.exe
