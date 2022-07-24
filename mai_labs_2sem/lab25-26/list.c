#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void create(node *list)
{
	list->next = list;
	list->prev = list;
}

void insert(node *m, node *p)
{
	node *n = m->next;
	p->prev = m;
	p->next = n;
	m->next = p;
	n->prev = p;
}

void list_remove(node *t)
{
	node *s = t->prev;
	node *u = t->next;
	s->next = u;
	u->prev = s;
}

node *push_front(node *list, int value)
{
	node *tmp = malloc(sizeof(node));
	tmp->key = value;
	insert(list, tmp);
	return tmp;
}

node *push_back(node *list, int value)
{
	push_front(list->prev, value);
}

void list_delete(node *list)
{
	list_remove(list);
	free(list);
	return;
}

void pop_front(node *list)
{
	if (list->next != list) {
		list_delete(list->next);	
	}
	return;
}

void pop_back(node *list)
{
	if (list->prev != list) {
		list_delete(list->prev);
	}
	return;
}

int is_empty(node * list) 
{
	return list->prev == list && list->next == list;
}

void print(node *list)
{
	for (node *tmp = list->next; tmp != list; tmp = tmp->next) {
		printf("%d ", tmp->key);
	}
	printf("\n");
}

void erease(node *list, int value)
{
	for (node *tmp = list->next; tmp != list; tmp = tmp->next) {
		if (tmp->key == value) {
			list_delete(tmp);
			return;
		}
	}
}

void list_insert(node *list, int k, int value)
{
	for (node *tmp = list->next; tmp != list; tmp = tmp->next) {
		if (tmp->key == k) {
			node *res = malloc(sizeof(node));
			res->key = value;
			insert(tmp->prev, res);
			return;
		}
	}
}

void destroy(node *list)
{
    while(!is_empty(list)) { 
        pop_front(list);
    }
}

int size(node *list)
{
	int cnt = 0;
	for (node *tmp = list->next; tmp != list; tmp = tmp->next) {
		cnt++;
	}
	return cnt * sizeof(node);
}

void procedure(node *list, node* tmp)
{
	int value = tmp->key;
	node *tmp_prev = tmp->prev;
	while ((tmp_prev != list) && (tmp_prev->key > value)) {
            tmp_prev->next->key = tmp_prev->key;
            tmp_prev = tmp_prev->prev;
    }
    tmp_prev->next->key = value;
}

void insertion_sort(node* list)
{
    node *tmp = NULL;
    for (tmp = list->next; tmp != list; tmp = tmp->next)
    {
        procedure(list, tmp);
    }
}