#include "list.h"

void help(int k) {
    if (k == 0) {
        printf("Enter 'c' to create your list\n");
        printf("Enter 'o' to get your list size\n");
        printf("Enter 'e' for the end\n");
    } else {
        printf("Enter 'p' to print your list\n");
        printf("Enter 'i' to insert in your list comlpex item \n");
        printf("Enter 'd' to delete your last item in list\n");
        printf("Enter 's' to swap second and penultimate\n");
        printf("Enter 'o' to get your list size\n");
        printf("Enter 'e' for the end\n");
    }
}

int main() {
    int k = 0;
    help(k);
    char input;
    complex tmp;
    list *a;
    int n = 0;
    int Re; int Im;
    while ((input = getchar()) != 'e') {
        switch (input) {
            case 'c':
            {
                k++;
                a = create();
                printf("Im and Re\n");
                scanf("%d %d", &tmp.Re, &tmp.Im);
                a->data = tmp;
                help(k);
                break;
            }
            case 'p':
            {
                print(a);
                break;
            }
            case 'i':
            {
                printf("Im and Re\n");
                scanf("%d %d", &tmp.Re, &tmp.Im);
                printf("Write your distance about last item\n");
                scanf("%d", &n);
                if (n >= 0) {
                    insert(a, n, tmp);
                }
                else {
                    printf("Введите нормальные данные\n");
                }
                help(k);
                break;
            }
            case 'd':
            {
                if (size(a) == 1) {
                    k = 0;
                    delete(a->next);
                    help(k);
                } else {
                    delete(a->next);
                }
                break;
            }
            case 's':
            {
                swap_second_and_penultimate(a);
                break;
            }
            case 'o':
            {
                printf("%d\n", size(a));
                break;
            }
            default:
            {
                if (input != '\n' && input != '\r' && input != '\t') {
                    printf("Enter correct data plz\n");
                    help(k);
                }
            }
        }
    }
    return 0;
}
