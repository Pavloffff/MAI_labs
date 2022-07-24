#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct
{
    int Re;
    int Im;
} value_type;

typedef struct _list_node
{
    value_type data;
    struct _list_node *next;
    struct _list_node *prev;
} node;

typedef struct _iterator
{
    node* nod;
} iterator;

typedef struct _list
{
    node* head;
    node* tail;
    size_t size;
} list;

list* list_create();
iterator* iterator_create(list* lst);
iterator* iterator_next(iterator* it);
iterator* iterator_prev(iterator* it);
node* iterator_get(iterator* it);
void iterator_destroy(iterator* it);
void back_insert(list* lst, value_type value);
void front_insert(list* lst, value_type value);
void delete(list* lst, int k);
void print(list* lst);
void function(list* lst, int k);
int count(list* lst);
void destroy(list* lst);
void swap_second_and_penultimate(list *a);
#endif