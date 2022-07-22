#include <stdio.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef enum {
    S0, S1, S2, S3, S4, S5, S6, S7, S8, S9
} State;

bool is_separator(char c)
{
    if (c == ' ' || c == '\n' || c == '\t') {
        return TRUE;
    }
    return FALSE;
}

int main(void)
{

    char c;
    State state = S0;
    long long cnt = 0;
    long long gcnt = 0;
    bool flag = TRUE;

    while (flag == TRUE) {
        c = getchar();
        switch (state) {
            case S0:
                if (!(is_separator(c)) && (c != '{') && (c != '(')) {
                    state = S1;
                } else if (c == '{') {
                    state = S2;
                } else if (c == '(') {
                    state = S4;
                }
                break;
            case S1:
                if ((c != '{') && (c != '(')) {
                    state = S1;
                } else if (c == '{') {
                    state = S2;
                } else if (c == '(') {
                    state = S4;
                } else {
                    state = S0;
                }
                break;
            case S2:
                if (!is_separator(c) && c != '}') {
                    state = S3;
                } else if (c == '}') {
                    gcnt += cnt;
                    cnt = 0;
                    state = S0;
                }
                break;
            case S3:
                if (!is_separator(c) && c != '}') {
                    state = S3;
                } else if (is_separator(c)) {
                    cnt++;
                    state = S2;
                } else if (c == '}') {
                    cnt++;
                    gcnt += cnt;
                    cnt = 0;
                    state = S0;
                } else {
                    cnt = 0;
                    state = S0;
                }
                break;
            case S4:
                if (c != '*') {
                    state = S1;
                } else if (c == '*') {
                    state = S8;
                }
                break;
            case S5:
                if ((c != '*') && !(is_separator(c))) {
                    state = S6;
                } else if (c == '*') {
                    state = S8;
                }
                break;
            case S6:
                if (!is_separator(c) && c != '*') {
                    state = S6;
                } else if (is_separator(c)) {
                    cnt++;
                    state = S5;
                } else if (c == '*') {
                    state = S7;
                } else {
                    state = S0;
                }
                break;
            case S7:
                if (c != ')') {
                    cnt++;
                    state = S9;
                } else if (c == ')') {
                    cnt++;
                    gcnt += cnt;
                    cnt = 0;
                    state = S0;
                } else {
                    cnt = 0;
                    state = S0;
                }
                break;
            case S8:
                if (c != ')' && c != '*') {
                    state = S6;
                } else if (c == ')') {
                    gcnt += cnt;
                    cnt = 0;
                    state = S0;
                } else if (c == '*') {
                    state = S9;
                } else if (is_separator(c)) {
                    cnt++;
                    state = S6;
                }
                break;
            case S9:
                if (c == '*') {
                    state = S9;
                } else if (c == ')') {
                    gcnt += cnt;
                    cnt = 0;
                    state = S0;
                } else {
                    state = S5;
                }
                break;
        }
        if (c == EOF) {
            flag = FALSE;
        }
    }

    printf("%lld\n", gcnt);

    return 0;
}
