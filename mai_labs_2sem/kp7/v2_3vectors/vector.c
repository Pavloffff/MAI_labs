#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

void print(vector *v)
{
    for (int i = 0; i < v->size; ++i) {
        printf("%d ", v->begin[i]);
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

void print_matrix(vector *CIP, vector *PI, vector *YE, int m, int n)
{
    int PI_i = 0;
    int CIP_i = 1;
    if (CIP && PI && YE) {
        for (int i = 0; i < size(CIP); i++) {
            for (int j = 1; j <= n; j++) {
                if (PI->begin[PI_i] == j) {
                    printf("%d ", YE->begin[PI_i]);
                    PI_i++;
                } else {
                    printf("0 ");
                }
                if (CIP_i < m) {
                    if (CIP->begin[CIP_i] == PI_i) {
                        CIP_i++;
                        for(int k = 0; k < n - j; k++)
                            printf("0 ");
                        printf("\n");
                        break;
                    }
                }
            }
        }
    }
    printf("\n");
}

int abs(int a)
{
    if (a < 0) {
        return -a;
    }
    return a;
}

int max(vector *YE)
{
    int max_el = YE->begin[0];
    for (int i = 0; i < size(YE); i++) {
        if (abs(YE->begin[i]) > max_el) {
            max_el = YE->begin[i];
        }
    }
    return max_el;
}

void task(vector *CIP, vector *YE)
{
    int begin = 0;
    int end = 0;
    int max_el = max(YE);
    for (int i = 0; i < size(YE); i++) {
        if (YE->begin[i] == max_el) {
            for (int j = 0; j < size(CIP); j++) {
                begin = CIP->begin[j];
                if (j == size(CIP) - 1) {
                    end = size(YE);
                } else {
                    end = CIP->begin[j + 1];    
                }
                if ((begin <= i) && (end > i)) {
                    for (int k = begin; k < end; k++) {
                        YE->begin[k] /= max_el;
                    }
                }
            }
        }
    }
}