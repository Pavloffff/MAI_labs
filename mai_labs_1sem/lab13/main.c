#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define set unsigned long long

set son_set = 0;
set not_set = 0;
set lu = 1;

set set_symbol(set s, char c)
{
    return s | (lu << ((set) c - (set) 'a'));
}

char to_lowercase(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    } else {
        return c;
    }
}

bool is_alpha(char c)
{
    c = to_lowercase(c);
    if (c == ' ' || c == '\t' || c == '\n' || c == EOF || c == ',' || c == '\r') {
        return false;
    }
    return true;
}

int is_son(set n_set)
{
    set pr = 0;
    if ((n_set & not_set) == pr) {
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    char son[] = {'b', 'v', 'g', 'd', 'z'};
    char notson[] = {'c', 'f', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'x', 'y', 'w'};
    for (int i = 0; i < 5; i++) {
        son_set = set_symbol(son_set, son[i]);
    }
    for (int i = 0; i < 16; i++) {
        not_set = set_symbol(not_set, notson[i]);
    }
    set n_set = 0;
    char c;
    bool result = false, flag = true, empt = true , iseof = false;
    int state = 0;
    while (flag) {
        c = getchar();
        c = to_lowercase(c);
        switch (state) {
            case 0:
                if (c == EOF) {
                    iseof = true;
                } else {
                    state = 1;
                }
                break;
            case 1:
                if (is_alpha(c)) {
                    state = 2;
                    n_set = set_symbol(n_set, c);
                } else {
                    state = 1;
                }
                break;
            case 2:
                empt = false;
                if (is_alpha(c)) {
                    n_set = set_symbol(n_set, c);
                } else {
                    result = result || is_son(n_set);
                    n_set = 0;
                    state = 1;
                }
                break;

        }
        if (c == EOF) {
            flag = false;
        }

    }
    if ((result || empt) && !(iseof)) {
        printf("Yes\n");
        return 0;
    }
    printf("No\n");
    return 0;
}
