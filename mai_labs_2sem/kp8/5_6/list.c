#include "list.h"

list *create(){
    list *rez = (list*)malloc(sizeof(list));
    rez->next = rez;
    rez->prev = rez;
    return rez;
}

void print(list *a){
    printf("%d + %d * i,\t", a->data.Re, a->data.Im);
    list *start = a;
    a = a->next;
    while (a != start){
        printf("%d + %d * i,\t", a->data.Re, a->data.Im);
        a = a->next;
    }
    printf("\n");
}

void insert(list *a, int index, complex item){
    for (int i = 0; i < index; i++){
        a = a->next;
    }
    list *new_elem = create();
    new_elem->data = item;
    a->prev->next = new_elem;
    new_elem->prev = a->prev;
    a->prev = new_elem;
    new_elem->next = a;
}

void delete(list *a){
    a->next->prev = a->prev;
    a->prev->next = a->next;
    free(a);
}

int size(list *a){
    int rez = 1;
    list *start = a;
    a = a->next;
    while (a != start){
        rez++;
        a = a->next;
    }
    return rez;
}

void swap_second_and_penultimate(list *a) {
    list *x = a->next;
    list *y = a->prev;
    complex tmp = x->data;
    x->data = y->data;
    y->data = tmp;
}

