#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct {
    int *begin;         
    int size;           
    int allocated;      
} vector;               

typedef struct {        
    int val;
    int i;
    int j;
} element;

typedef struct
{
    vector matrix;
    int n, m;
} matrix;


void v_create(vector *d);

void v_push_back(vector *d, int value);

int v_size(vector *d);

matrix m_create(int n, int m);

int m_diag(matrix *A);

int m_div_elem(matrix *A, int val);

void m_print(matrix *A);

void v_print(matrix *A);

#endif