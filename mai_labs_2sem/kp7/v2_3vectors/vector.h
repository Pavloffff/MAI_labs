#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdbool.h>
#include <string.h>

typedef int key_type;
typedef int value_type;

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

void print_matrix(vector *CIP, vector *PI, vector *YE, int m, int n);

int abs(int a);

int max(vector *YE);

void task(vector *CIP, vector *YE);

#endif