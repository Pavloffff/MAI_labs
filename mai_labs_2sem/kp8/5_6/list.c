#include "list.h"
#include <stdio.h>
#include <stdlib.h>

iterator* iterator_create(list* lst)
{
    iterator* it = (iterator*)malloc(sizeof(iterator));
    it->nod = lst->head;
    return it;
}

iterator* iterator_next(iterator* it)
{
    if (it != NULL) {
        it->nod = it->nod->next;
        return it;
    }
}

iterator* iterator_prev(iterator* it)
{
    if (it != NULL) {
        it->nod = it->nod->prev;
        return it;
    }
}

node* iterator_get(iterator* it)
{
    return it->nod;
}

list* list_create()
{
    list* lst = (list*) malloc(sizeof(list));
    lst->head = lst->tail = NULL;
    lst->size = 0;
    return lst;
}

void print(list* lst)
{
    if (lst == NULL || lst->head == NULL) {
        return;
    }
    iterator* iter = iterator_create(lst);
    if (iterator_get(iter) != NULL) {
        printf("%d+%di ", iterator_get(iter)->data.Re, iterator_get(iter)->data.Im);
    }
    iter = iterator_next(iter);
    while (iterator_get(iter) != lst->head) {
        printf("%d+%di ", iterator_get(iter)->data.Re, iterator_get(iter)->data.Im);
        iter = iterator_next(iter);
    }
    free(iter);
    printf("\n");
}

void back_insert(list* lst, value_type c)
{
    if (lst == NULL) {
        printf("The list not exists\n");
        return;
    }
    node* new = (node*)malloc(sizeof(node));
    if (lst->head == NULL) {
        lst->head = new;
        lst->head->data = c;
        lst->tail = lst->head;
        lst->head->next = lst->head->prev = lst->tail;
        lst->size++;
    } else {     
        lst->tail->next = new;
        new->prev = lst->tail;
        new->next = lst->head;
        lst->tail = new;
        lst->tail->data = c;
        lst->head->prev = lst->tail;
        lst->size++;
    }
}

void front_insert(list* lst, value_type c)
{
    if (lst == NULL) {
        printf("The list not exists\n");
        return;
    }
    node* new = (node*)malloc(sizeof(node));
    if (lst->head == NULL) {
        lst->head = new;
        lst->head->data = c;
        lst->tail = lst->head;
        lst->head->next = lst->head->prev = lst->tail;
        lst->size++;
    } else {
        lst->head->prev = new;
        new->data = c;
        new->next = lst->head;
        lst->tail->next = new;
        lst->head = new;
        lst->head->prev = lst->tail;
        lst->size++;
    }
}

void delete(list* lst, int k)
{
    if (count(lst) == 0) {
        printf("The list not exists\n");
        return;
    }
    if (count(lst) == 1 && k == 0) {
        lst->tail = lst->head = NULL;
		lst->size--;
        return;
    } else if (k != 0) {
		printf("The node not exists\n");
		return;
	}
    iterator* iter = iterator_create(lst);
    for (int i = 0; i < k; i++) {
        iter = iterator_next(iter);
    }
    node* first = iterator_get(iter);
    if (first != lst->head && first != lst->tail) {
        first->prev->next = first->next;
        first->next->prev = first->prev;
        free(first);
        lst->size--;
    } else if (first == lst->head) {
        lst->head = first->next;
        lst->tail->next = lst->head;
        first->next->prev = lst->tail;
        free(first);
        lst->size--;
    } else if (first == lst->tail) {
        lst->tail = first->prev;
        lst->head->prev = lst->tail;
        first->prev->next = lst->head;
        free(first);
        lst->size--;
    }
    free(iter);
}

int count(list* lst)
{
    return lst->size;
}

void destroy(list* lst)
{
    iterator* iter = iterator_create(lst);
    iter = iterator_next(iter);
    while (iterator_get(iter) != lst->head) {
        node *pi = iterator_get(iter);
        iter = iterator_next(iter);
        free(pi);
    }
    free(lst->head);
    free(iter);
    lst->head = 0;

    printf("\n");
}

void swap_second_and_penultimate(list *a) {
    if (count(a) > 3) {
        node *x = a->head->next;
        node *y = a->head->prev->prev;
        value_type tmp = x->data;
        x->data = y->data;
        y->data = tmp;
    }
}
