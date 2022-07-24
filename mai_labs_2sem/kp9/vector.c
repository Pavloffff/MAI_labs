#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void print(vector *v)
{
	for (int i = 0; i < v->size; ++i) {
		printf("%s ", v->begin[i].value);
	}
	printf("\n");
}

bool is_empty(vector *v)
{
	return v->size == 0;
}

bool is_full(vector *v)
{
	return v->size == v->allocated;
}

size_t size(vector *v)
{
	return v->size;
}

void create(vector *v)
{
	v->size = 0;
	v->allocated = 0;
	v->begin = NULL;
}

void destroy(vector *v)
{
	free(v->begin);
	v->size = 0;
	v->allocated = 0;
	v->begin = NULL;
}

void push(vector *v, value_type value)
{
	if (is_full(v)) {
		v->allocated += 10;
		v->begin = realloc(v->begin, v->allocated * sizeof(value_type));
	}
	v->begin[v->size] = value;
	v->size++;
}

value_type pop(vector *v)
{
	value_type res = v->begin[v->size - 1];
	v->size--;
	return res;
}

int comparator(value_type x, value_type y)
{
	if (strcmp(x.key, y.key) > 0) {
		return 1;
	} else if (strcmp(x.key, y.key) < 0) {
		return -1;
	} else {
		return 0;
	}
}

void bin_insertion_sort(vector *v)
{
	for (int i = 1; i < size(v); i++) {
		int left = 0, right = i - 1, mid = -1;
		while (left <= right) {
			mid = (left + right) / 2;
			if (comparator(v->begin[i], v->begin[mid]) >= 0) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		int k = left;
		value_type temp = v->begin[i];
		for (int j = i - 1; j >= k; j--) {
			v->begin[j + 1] = v->begin[j];
		}
		v->begin[k] = temp;
	}
}

value_type bin_search(vector *v, char key[7])
{
	int left = 0, right = size(v) - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (strcmp(key, v->begin[mid].key) <= -1) {
			right = mid - 1;
		} else if (strcmp(key, v->begin[mid].key) >= 1) {
			left = mid + 1;
		} else {
			return v->begin[mid];
		}
	}
}