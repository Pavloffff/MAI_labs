#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdbool.h>
#include <string.h>

typedef int key_type;
typedef struct 
{
	char key[7];
	char value[100];
} value_type;

typedef struct {
	value_type *begin;
	size_t size;
	size_t allocated;
} vector;

void create(vector *v);

void destroy(vector *v);

bool is_empty(vector *v);

bool is_full(vector *v);

void push(vector *v, value_type value);

value_type pop(vector *v);

void print(vector *v);

size_t size(vector *v);

int comparator(value_type x, value_type y);

void bin_insertion_sort(vector *v);

value_type bin_search(vector *v, char key[7]);

#endif