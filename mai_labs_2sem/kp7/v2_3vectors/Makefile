CC = gcc
CFLAGS ?= -g -Wall -Wextra -pedantic -std=c99 -w -pipe -O3 -lm	
main: main.o vector.o
	$(CC) -o main main.o vector.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -rf *.o main