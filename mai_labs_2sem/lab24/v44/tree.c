#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "vector.h"

#include "tree.h"

int get_priority(char c)
{
    switch (c) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
    }
    return 100;
}

Tree tree_create(vector *tokens, int idx_left, int idx_right)
{
    Tree t = (Tree) malloc(sizeof(struct tree_node));
    if (idx_left > idx_right) {
        return NULL;
    }

    if (idx_left == idx_right) {
        t->node  = tokens->begin[idx_left];
        t->left  = NULL;
        t->right = NULL;
        return t;
    }

    int priority;
    int priority_min = get_priority('a');
    int brackets = 0;
    int op_pos;

    for (int i = idx_left; i <= idx_right; ++i) {
        if ((tokens->begin[i].type == BRACKET) && (tokens->begin[i].data.is_left_bracket)) {
            ++brackets;
            continue;
        }
        if ((tokens->begin[i].type == BRACKET) && !(tokens->begin[i].data.is_left_bracket)) {
            --brackets;
            continue;
        }
        if (brackets > 0) { 
            continue;
        }
        if (tokens->begin[i].type == OPERATOR) {
            priority = get_priority(tokens->begin[i].data.operator_name);
            if (priority <= priority_min) {
                priority_min = priority;
                op_pos = i;
            }
        }
    }
    if ((priority_min == get_priority('a')) &&
            (tokens->begin[idx_left].type == BRACKET) && 
            (tokens->begin[idx_left].data.is_left_bracket) &&
            (tokens->begin[idx_right].type  == BRACKET) && 
            !(tokens->begin[idx_right].data.is_left_bracket)) {
        free(t);
        return tree_create(tokens, idx_left + 1, idx_right - 1);
    }

    if (tokens->begin[op_pos].data.operator_name == '^') {
        brackets = 0;
        for (int i = op_pos; i >= idx_left; --i) {
            if ((tokens->begin[i].type == BRACKET) && !(tokens->begin[i].data.is_left_bracket)) {
                ++brackets;
                continue;
            }
            if ((tokens->begin[i].type == BRACKET) && (tokens->begin[i].data.is_left_bracket)) {
                --brackets;
                continue;
            }
            if (brackets > 0) {
                continue;
            }
            if (tokens->begin[i].type == OPERATOR) {
                priority = get_priority(tokens->begin[i].data.operator_name);
                if (priority == 3) {
                    op_pos = i;
                }
            }
        }
    }

    t->node  = tokens->begin[op_pos]; 
    t->left  = tree_create(tokens, idx_left, op_pos - 1);
    t->right = tree_create(tokens, op_pos + 1, idx_right);
    if (t->right == NULL) {
        printf("Operator at the expression's end\n");
        exit(1);
    }
    return t;
}

void tree_delete(Tree *t)
{
    if ((*t) != NULL) {
        tree_delete(&((*t)->left));
        tree_delete(&((*t)->right));
    }
    free(*t);
    *t = NULL;
}

void tree_infix(Tree t)
{
    if (t != NULL) {
        if (t->left && t->right)
            printf("(");

        tree_infix(t->left);
        token_print(&(t->node));
        tree_infix(t->right);

        if (t->right && t->left)
            printf(")");
    }
}

void tree_print(Tree t, size_t depth)
{
    if (t != NULL) {
        for (int i = 0; i < depth; ++i) {
            printf("\t");
        }
        token_print(&(t->node)); printf("\n");
        tree_print(t->left,  depth + 1);
        tree_print(t->right, depth + 1);
    }
}
