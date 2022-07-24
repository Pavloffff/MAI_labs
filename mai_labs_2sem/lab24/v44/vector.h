#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdbool.h>
#include <string.h>
#include "lexer.h"

typedef struct {
	Token *begin;
	size_t size;
	size_t allocated;
} vector;

void create(vector *v);

void destroy(vector *v);

bool is_empty(vector *v);

bool is_full(vector *v);

void push(vector *v, Token value);

Token pop(vector *v);

void print(vector *v);

size_t size(vector *v);

#endif
