CC = g++
CFLAGS = -g -Wall -Werror -ansi -pedantic

TARGETS = all rshell
all: rshell

rshell:
	@mkdir -p bin
	$(CC) $(CFLAGS) src/parentheseMain.cpp  -o bin/rshell

