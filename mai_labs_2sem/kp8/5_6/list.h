#ifndef UNTITLED9_LIST_H
#define UNTITLED9_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _complex{
    int Re;
    int Im;
} complex;

typedef struct _list
{
    complex data;
    int size;
    struct _list *next;
    struct _list *prev;
} list;

list *create();
void print(list *a);
void insert(list *a, int index, complex item);
void delete(list *a);
int size(list *a);
void swap_second_and_penultimate(list *a);

#endif //UNTITLED9_LIST_H
