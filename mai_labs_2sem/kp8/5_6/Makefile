CC = gcc
CFLAGS ?= -g -Wall -Wextra -pedantic -std=c99 -w -pipe -O3 -lm	
main: main.o list.o
	$(CC) -o main main.o list.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

clean:
	rm -rf *.o main