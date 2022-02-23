CC = gcc
CFLAGS = *.c -o ej1 -g -std=c99 -Wall -Wconversion -pedantic -Werror -O0

build:
	$(CC) $(CFLAGS)

run: build
	./ej1

debug: build
	gdb ./ej1
