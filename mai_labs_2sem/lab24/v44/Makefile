CC=gcc
LD=gcc

CFLAGS=-std=c99 -pedantic -Wall
LDFLAGS=

OBJ=main.o tree.o lexer.o transform.o vector.o
PROG=main

build=$(PROG)

main: $(OBJ)
		$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

main.o: tree.h lexer.h transform.h

tree.o: tree.h

lexer.o: lexer.h

transform.o: transform.h

vector.o: vector.h

clean:
		rm $(PROG) $(OBJ)