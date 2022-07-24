#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void v_create(vector *d)
{
    d->allocated = 1;       
    d->size = 0;           
    d->begin = malloc(d->allocated * sizeof(int)); 
}

void v_push_back(vector *d, int value)
{
    if (d->size + 1 >= d->allocated) {  
        d->allocated *= 2;              
        d->begin = realloc(d->begin, sizeof(int) * d->allocated + 1); 
    }
    d->begin[d->size++] = value; 
}

int v_size(vector *d)
{
    return d->size;
}

matrix m_create(int n, int m)
{
    matrix A;
    int val;                
    v_create(&(A.matrix));  

    A.n = n;               
    A.m = m;                

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            scanf("%d", &val);
            if (val != 0) {
                v_push_back(&(A.matrix), val); 
                v_push_back(&(A.matrix), i);
                v_push_back(&(A.matrix), j);
            }
        }
    }

    return A;
}

void v_print(matrix *A) {
    for (int i = 0; i < A->matrix.size; ++i) {
        printf("%d ", A->matrix.begin[i]);
    }
    printf("\n");
}

void m_print(matrix *A)
{
    int it = 0;
    for (int i = 0; i < A->n; i ++) {
        for (int j = 0; j < A->m; j ++) {
            if (A->matrix.begin[it + 1] == i && A->matrix.begin[it + 2] == j) {
                printf("%d ", A->matrix.begin[it]);
                it += 3;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int abs(int a)
{
    if (a < 0) {
        return -a;
    }
    return a;
}

element m_find_elem(matrix *A)
{
    element el = {0, 0, 0};
    int max = 0;
    
    for (int i = 0; i < v_size(&(A->matrix)); i += 3) {
        if (abs(A->matrix.begin[i]) > max) {
            el.val = A->matrix.begin[i];
            el.i = A->matrix.begin[i + 1];
            el.j = A->matrix.begin[i + 2];
            max = abs(A->matrix.begin[i]);
        }
    }

    return el;
}

void m_div_str(matrix *A, int string, int div)
{
    for (int i = 0; i < v_size(&(A->matrix)); i += 3) {
        if (A->matrix.begin[i + 1] == string) {
                A->matrix.begin[i] /= div;
        }
    }
}

int m_div_elem(matrix *A, int val)
{
    element el_div = m_find_elem(A);

    for (int i = 0; i < v_size(&(A->matrix)); i += 3) {
        if (A->matrix.begin[i] == el_div.val && A->matrix.begin[i + 1] != el_div.i) {
            m_div_str(A, A->matrix.begin[i + 1], el_div.val);
        }
    }
    m_div_str(A, el_div.i, el_div.val);
}
