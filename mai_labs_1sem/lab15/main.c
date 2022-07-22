#include <stdio.h>

int main(void)
{
    long long cnt, max;
    scanf("%lld%lld", &cnt, &max);
    long long a[max][max];
    for (long long t = 0; t < cnt; ++t) {
        long long n;
        scanf("%lld", &n);
        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < n; ++j) {
                scanf("%lld", &a[i][j]);
            }
        }
        int nstr = 0, maxel = -500000;
        for (long long i = 0; i < n; ++i) {
            for (long long j = 0; j < n; ++j) {
                if (a[i][j] > maxel) {
                    maxel = a[i][j];
                    nstr = i;
                }
            }
        }
        if (n == 1) {
            printf("%lld\n", a[0][0]);
            continue;
        }
        long long s = 0;
        long long j = 0;
        while (j <= n - 1) {
            s += a[nstr][j];
            j++;
        }
        printf("%lld\n", s);
    }
    return 0;
}
