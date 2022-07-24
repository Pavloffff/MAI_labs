#ifndef LIST_H
#define LIST_H

struct Item
{
    struct Item *prev;
    struct Item *next;
    float data;
};

typedef struct
{
    struct Item *node;
} Iterator;

typedef struct
{
    struct Item *head;
    int size;
} List;

int Equal(Iterator *lhs, Iterator *rhs);

Iterator *Next(Iterator *i);

Iterator *Prev(Iterator *i);

float Fetch(const Iterator *i);

void Store(const Iterator *i, const float t);

void Create(List *l);

Iterator First(const List *l);

Iterator Last(const List *l);

int Empty(const List *l);

Iterator search_prev(const List *l, const int n);

Iterator Insert(List *l, Iterator *i, const float t);

Iterator Delete(List *l, Iterator *i);

int Size(const List *l);

void print_list(const List *l);

void Task(List *l);

void Destroy(List *l);

#endif