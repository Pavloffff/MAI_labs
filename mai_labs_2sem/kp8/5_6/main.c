#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int main(int argc, char const *argv[])
{
    list* l;
    l = list_create();
    int choose, flag = 1;
    value_type value;
    int key;
    while(flag) {
        printf("1: print;\t2: print size;\t3: push front;\t4: push back;\t5: is empty;\n");
        printf("6: delete;\t7: swap_second_and_penultimate;\tother: exit;\n");
        scanf("%d", &choose);
        switch(choose) {
        case 1:
            print(l);
            break;
        case 2:
            printf("size is %d\n", count(l));
            break;
        case 3:
            printf("enter Re & Im: ");
            scanf("%d %d", &value.Re, &value.Im);
            front_insert(l, value);
            break;
        case 4:
            printf("enter Re & Im: ");
            scanf("%d %d", &value.Re, &value.Im);
            back_insert(l, value);
            break;
        case 5:
            if (count(l) == 0) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }
            break;
        case 6:
            printf("enter key: ");
            scanf("%d", &key);
            delete(l, key);
            break;
        case 7:
            swap_second_and_penultimate(l);
            break;
        default:
            flag = 0;
            break;
        }
    }
    if (count(l) != 0) {
        destroy(l);
    }
    free(l);
    return 0;
}