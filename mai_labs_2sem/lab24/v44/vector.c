#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "lexer.h"
#include "tree.h"
#include "transform.h"

bool is_empty(vector *v) {
	return v->size == 0;
}

bool is_full(vector *v) {
	return v->size == v->allocated;
}

size_t size(vector *v) {
	return v->size;
}

void create(vector *v) {
	v->size = 0;
	v->allocated = 0;
	v->begin = NULL;
}

void destroy(vector *v) {
	free(v->begin);
	v->size = 0;
	v->allocated = 0;
	v->begin = NULL;
}

void push(vector *v, Token value) {
	if (is_full(v)) {
		v->allocated += 10;
		v->begin = realloc(v->begin, v->allocated * sizeof(Token));
	}
	v->begin[v->size] = value;
	v->size++;
}

Token pop(vector *v) {
	Token res = v->begin[v->size - 1];
	v->size--;
	return res;
}
