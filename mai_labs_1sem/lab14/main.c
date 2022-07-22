#include <stdio.h>

int main(void)
{
    int cnt, max;
    scanf("%d%d", &cnt, &max);
    int a[max][max];
    for (int t = 0; t < cnt; ++t) {
        int n;
        scanf("%d", &n);
        if (n == 0) {
            continue;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &a[i][j]);
            }
        }
        if (n == 1) {
            printf("%d\n", a[0][0]);
            continue;
        }
        int p = n - 1;
        int i, j;
        while (p >= 0) {
            printf("%d ", a[p][p]);
            p--;
        }
        p = n - 1;
        while (p > 0) {
            i = 0;
            j = n - p;
            while (j <= n - 1) {
                printf("%d ", a[i][j]);
                ++i;
                ++j;
            }
            i = n - 1;
            j = p - 1;
            while (j >= 0) {
                printf("%d ", a[i][j]);
                --i;
                --j;
            }
            p--;
        }
        printf("\n");
    }
    return 0;
}
