#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int mod(int a, int b)
{
    return abs(a - floor(((float) a / b)) * b);
}

bool check(int x, int y)
{
    if (x <= 15 && x >= 5 && y <= -5 && y >= -15) {
        return true;
    }
    return false;
}

int main(void)
{
    int i, j, l, k, i2, j2, l2;
    scanf("%d%d%d", &i, &j, &l);
    for (k = 0; k < 50 && check(i, j) == false; k++) {
        i2 = abs(k - 15) - min(floor(i / 3.0) , mod(j + l , 10)) - 20;
        j2 = (-1) * floor((j + k) / 5.0) + abs(mod(i * l, 8));
        l2 = max(mod(i + j , 15) , mod(l + k , 14));
        i = i2;
        j = j2;
        l = l2;
    }
    if (check(i, j)) {
        printf("Yes\n");
        printf("%d %d %d %d\n", i, j, l, k);
    } else {
        printf("No\n");
        printf("%d %d %d %d\n", i, j, l, k);
    }
    return 0;
}
