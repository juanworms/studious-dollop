CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -pedantic -Werror -O0

build:
	$(CC) $(CFLAGS) ej2.c -o ej2
	$(CC) $(CFLAGS) crear_rango.c -o crearRango
	$(CC) $(CFLAGS) crear_tarjeta.c -o crearTarjeta

crearRango: build
	./crearRango

crearTarjeta: build
	./crearTarjeta

run: build
	./ej2
	
debug: build
	gdb ./ej2
