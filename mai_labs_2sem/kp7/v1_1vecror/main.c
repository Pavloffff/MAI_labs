#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char const *argv[])
{
    int n, m, val;
    printf("Enter count of rows & columns: ");
    scanf("%d%d", &n, &m);

    matrix A = m_create(n, m);
    v_print(&A);
    printf("\n");
    m_div_elem(&A, val);
    m_print(&A);
    v_print(&A);
    return 0;
}