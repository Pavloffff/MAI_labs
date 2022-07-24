CC=gcc
LD=gcc

CFLAGS=-std=c99 -pedantic -Wall
LDFLAGS=

OBJ=main.o tree.o
PROG=main

build=$(PROG)

$(PROG): $(OBJ)
		$(LD) $(LDFLAGS) $(OBJ) -o $(PROG)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

main.o: tree.h

tree.o: tree.h

clean:
		rm $(PROG) $(OBJ)