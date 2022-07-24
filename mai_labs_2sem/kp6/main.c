#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "computer.h"

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Need two or three arguments:\n");
        printf("\n -c \t\t for creating new dataset\n -a \t\t for adding new record\n -p \t\t for printing dataset\n -d \t\t for deleting dataset\n -f value\t for make a task sample\n");
        exit(1);
    }
    if (!strcmp(argv[1], "-a")) {
        add();
    } else if (!strcmp(argv[1], "-p")) {
        table_print();
    } else if (!strcmp(argv[1], "-d")) {
        delete();
    } else if (!strcmp(argv[1], "-c")) {
        create();
    } else if (!strcmp(argv[1], "-f")) {
        int p;
        sscanf(argv[2], "%d", &p);
        func(p);
    } 
    else {
        printf("Command not found\n");
        printf("\n -c \t\t for creating new dataset\n -a \t\t for adding new record\n -p \t\t for printing dataset\n -d \t\t for deleting dataset\n -f value\t for make a task sample\n");
    }
    return 0;
}