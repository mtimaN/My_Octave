CC=gcc
CFLAGS=-I. -std=c99
DEPS=main.c checks.h matrix_array.h matrix_operations.h number_operations.h

OBJ := checks.o
OBJ += matrix_array.o
OBJ += matrix_operations.o
OBJ += number_operations.o


%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

my_octave: $(OBJ) $(DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

pack:
	zip -Fsr MateiMantuTema2PCLP.zip *.c Makefile

clean:
	rm -f *.o my_octave