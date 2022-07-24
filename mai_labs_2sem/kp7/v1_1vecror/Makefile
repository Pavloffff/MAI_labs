CC = gcc
CCFLAGS = -g -Wall -pedantic -std=c99

OBJ = main.o matrix.o

TARGET = main

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)