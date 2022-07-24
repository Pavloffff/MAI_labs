#ifndef computer_h
#define computer_h

#include <stdio.h>
#include <stdlib.h>

typedef struct comp
{
    char surname[50];
    int num_of_proc;
    char type_of_proc[50];
    int mem_size_ram;
    char type_of_contr[50];
    int mem_size_video_proc;
    char type_of_disk[50];
    int num_of_disk;
    int cap_of_disk;
    int num_of_intcontr;
    int num_of_dev;
    char os[50];
} pc;

void create();

void add();

void print();

void table_print();

void delete();

void func(int p);

#endif