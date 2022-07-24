#ifndef list_h
#define list_h

typedef struct node
{
	int key;
	struct node *prev;
	struct node *next;
} node;

void create(node *list);

void insert(node *m, node *p);

void list_remove(node *t);

node *push_front(node *list, int value);

node *push_back(node *list, int value);

void list_delete(node *list);

void pop_front(node *list);

void pop_back(node *list);

int is_empty(node * list);

void print(node *list);

void erease(node *list, int value);

void list_insert(node *list, int k, int value);

void destroy(node *list);

int size(node *list);

void procedure(node* list, node* tmp);

void insertion_sort(node* list);

#endif