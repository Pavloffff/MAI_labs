#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int Equal(Iterator *lhs, Iterator *rhs)
{
    return lhs->node == rhs->node;
}

Iterator *Next(Iterator *i)
{
    i->node = i->node->next;
    return i;
}

Iterator *Prev(Iterator *i)
{
    i->node = i->node->prev;
    return i;
}

float Fetch(const Iterator *i)
{
    return i->node->data;
}

void Store(const Iterator *i, const float t)
{
    i->node->data = t;
}

void Create(List *l)
{
    l->head = malloc(sizeof(struct Item));
    l->head->next = l->head->prev = l->head;
    l->size = 0;
}

Iterator First(const List *l)
{
    Iterator res = { l->head->next };
    return res;
}

Iterator Last(const List *l)
{
    Iterator res = { l->head };
    return res;
}

int Empty(const List *l)
{
    Iterator fst = First(l);
    Iterator lst = Last(l);
    return Equal(&fst, &lst);
}

Iterator search_prev(const List *l, const int n)
{
    Iterator res = Last(l);
    for (int i = 0; i <= n - 1; i++) {
        Next(&res);
    }
    return res;
}

Iterator Insert(List *l, Iterator *i, const float t)
{
    Iterator res = { malloc(sizeof(struct Item)) };
    if(!res.node)
        return Last(l);
    res.node->data = t;
    res.node->next = i->node;
    res.node->prev = i->node->prev;
    res.node->prev->next = res.node;
    i->node->prev = res.node;
    l->size++;
    return res;
}

Iterator Delete(List *l, Iterator *i)
{
    Iterator res = Last(l);
    if (l->head == NULL) {
        printf("List doesn't exists\n");
        return res;
    }
    if (Equal(i, &res))
        return res;
    res.node = i->node->next;
    res.node->prev = i->node->prev;
    i->node->prev->next = res.node;
    l->size--;
    free(i->node);
    i->node = NULL;
    return res;
}

int Size(const List *l)
{
    if (l->head == NULL) {
        printf("List doesn't exists\n");
        return 0;
    }
    return l->size;
}

void print_list(const List *l)
{
    if (l->head == NULL) {
        printf("List doesn't exists\n");
        return;
    }
    Iterator fst = First(l);
    Iterator lst = Last(l);
    for (Iterator i = First(l); !Equal(&i, &lst); Next(&i)) {
        printf("%.4f -> ", Fetch(&i));
    }
    printf("NULL\n");   
}

void Task(List *l)
{
    if (l->head == NULL || l->head == NULL) {
        printf("List doesn't exists\n");
    }
    Iterator lst = Last(l);
    Iterator fst = First(l);
    float tmp;
    
    if (Equal(&lst, &fst) || Size(l) < 2) {
        printf("Nesessary nodes doesn't exists\n");
        return;
    }
    if (Equal(Next(&fst), Prev(&lst)) || Size(l) == 2) {
        lst = *Prev(&lst);
        tmp = fst.node->data;
        fst.node->data = lst.node->data;
        lst.node->data = tmp;
        return;
    }
    lst = *Prev(&lst);
    tmp = fst.node->data;
    fst.node->data = lst.node->data;
    lst.node->data = tmp;
}

void Destroy(List *l) 
{   
    struct Item *i = l->head->next;
    while (i != l->head) {
        struct Item *pi = i;
        i = i->next;
        free(pi);
    }
    free(l->head);
    l->head = 0;
    l->size = 0;
}