#ifndef _TREE_H_
#define _TREE_H_

typedef enum {
	ein,
    zwei,
    drei,
    vier,
    funf,
    sechs,
    sieben,
    acht,
    neun,
    zehn,
    elf,
    zwolf,
    dreizehn,
    vierzehn,
    funfzehn,
    sechzehn,
    siebzehn,
    achzehn,
    neunzehn,
    zwanzig
} value_type;

typedef struct node node;
struct node
{
	value_type val;
	struct node *left;
	struct node *right;
};
typedef node * tree;

bool get_value(value_type *a, char *s);

char* get_text(value_type value);

void add(node **t, value_type val);

void delete(node **t);

void print_tree(node *t);

void print_error(char *str);

node ** find_val(node **t, value_type val);

int abs(int x);

int max_way(node **t, int len);

int min_way(node **t, int len);

bool is_AVL(node **t);

#endif