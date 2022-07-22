#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

long long absc(long long x)
{
    return (x < 0) ? (-1) * x : x;
}

long long powd(long long x)
{
    long long res = 1;
    for (long long i = 0; i < x; i++) {
        res *= 10;
    }
    return res;
}

long long len(long long x)
{
    if (x == 0) {
        return 1;
    } else {
        int res = 0;
        while (x != 0) {
            x /= 10;
            res++;
        }
        return res;
    }
}

long long sign(long long a)
{
    if (a == 0) {
        return 0;
    } else {
        return (a > 0) ? 1 : -1;
    }
}

int main(void)
{
    long long x, y;
    while ((scanf("%lld", &x)) != EOF) {
        if (sign(x) == -1) {
            printf("-");
        }
        x = absc(x);
        y = len(x) - 1;
        while (y >= 0) {
            if ((x / powd(y)) % 10 == 0) {
                printf("%d%d%d%d", 0, 0, 0, 0);
            } else if ((x / powd(y)) % 10 == 1) {
                printf("%d%d%d%d", 0, 0, 0, 1);
            } else if ((x / powd(y)) % 10 == 2) {
                printf("%d%d%d%d", 0, 0, 1, 0);
            } else if ((x / powd(y)) % 10 == 3) {
                printf("%d%d%d%d", 0, 0, 1, 1);
            } else if ((x / powd(y)) % 10 == 4) {
                printf("%d%d%d%d", 0, 1, 0, 0);
            } else if ((x / powd(y)) % 10 == 5) {
                printf("%d%d%d%d", 0, 1, 0, 1);
            } else if ((x / powd(y)) % 10 == 6) {
                printf("%d%d%d%d", 0, 1, 1, 0);
            } else if ((x / powd(y)) % 10 == 7) {
                printf("%d%d%d%d", 0, 1, 1, 1);
            } else if ((x / powd(y)) % 10 == 8) {
                printf("%d%d%d%d", 1, 0, 0, 0);
            } else if ((x / powd(y)) % 10 == 9) {
                printf("%d%d%d%d", 1, 0, 0, 1);
            }
            y -= 1;
        }
        printf("\n");
    }
    return 0;
}