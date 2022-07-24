CC = gcc
CFLAGS ?= -g -Wall -Wextra -pedantic -std=c99 -w -pipe -O3 -lm	
main: main.o computer.o
	$(CC) -o main main.o computer.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

computer.o: computer.c computer.h
	$(CC) $(CFLAGS) -c computer.c

clean:
	rm -rf *.o main