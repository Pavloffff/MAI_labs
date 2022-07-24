#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void)
{
    int m, n, num;
    vector CIP, PI, YE;
    
    printf("Input size: ");
    scanf("%d%d", &m, &n);

    int count = 0;
    create(&CIP);
    create(&PI);
    create(&YE);
    for (int i = 1; i <= m; i++) {
        push(&CIP, count);
        for (int j = 1; j <= n; j++) {
            scanf("%d", &num);
            if (num != 0) {
                push(&PI, j);
                push(&YE, num);
                count++;
            }
        }
    }

    printf("\n");
    
    if (is_empty(&YE)) {
        printf("Can't divide by zero\n");
        destroy(&CIP);
        return 1;
    }

    task(&CIP, &YE);
    print_matrix(&CIP, &PI, &YE, m, n);
    printf("\n");
    printf("CIP: ");
    print(&CIP);
    printf("PI: ");
    print(&PI);
    printf("YE: ");
    print(&YE);

    destroy(&CIP);
    destroy(&PI);
    destroy(&YE);

    return 0;
}