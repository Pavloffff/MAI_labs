#include "tree.h"
#include "transform.h"
#include "lexer.h"
#include <math.h>

Tree *tree_copy(Tree t)
{
    if (t == NULL) {
        return NULL;
    }
    Tree left = NULL;
    Tree right = NULL;
    if (t->left != NULL) {
        Tree left = tree_copy(t->left);
    }
    if (t->right != NULL) {
        Tree right = tree_copy(t->right);
    }
    Tree new_t = (Tree) malloc(sizeof(struct tree_node));
    new_t->node.type = t->node.type;
    if (new_t->node.type == INTEGER) {
        new_t->node.data.value_int = t->node.data.value_int; 
    } else 
    if (new_t->node.type == FLOATING) {
        new_t->node.data.value_float = t->node.data.value_float; 
    } else 
    if (new_t->node.type == OPERATOR) {
        new_t->node.data.operator_name = t->node.data.operator_name; 
    } else 
    if (new_t->node.type == VARIABLE) {
        new_t->node.data.variable_name = t->node.data.variable_name; 
    }
    
    if (left != NULL) {
        new_t->left = left;
    }
    if (right != NULL) { 
        new_t->right = right;
    }
    return new_t;
}

int match_plus(Tree *t)
{
    return ((*t) != NULL) && ((*t)->node.type == OPERATOR)
           && (((*t)->node.data.operator_name == '+') || ((*t)->node.data.operator_name == '-'))
           && (((*t)->left->node.type == OPERATOR) && ((*t)->left->node.data.operator_name == '/'))
           && (((*t)->right->node.type == OPERATOR) && ((*t)->right->node.data.operator_name == '/'));
}

void transform_div(Tree *t)
{
    Tree b = tree_copy((*t)->left->right);
    Tree d = tree_copy((*t)->right->right);

    char oper = (*t)->node.data.operator_name;
    (*t)->node.data.operator_name = '/';
    (*t)->right->node.data.operator_name = '*';
    

    (*t)->left->node.data.operator_name = oper;
    Tree left_mul = (Tree) malloc(sizeof(struct tree_node));
    left_mul->node.type = OPERATOR;
    left_mul->node.data.operator_name = '*';
    left_mul->left = (*t)->left->left;
    left_mul->right = d;

    Tree right_mul = (Tree) malloc(sizeof(struct tree_node));
    right_mul->node.type = OPERATOR;
    right_mul->node.data.operator_name = '*';
    right_mul->left = (*t)->right->left;
    right_mul->right = b;

    (*t)->right->left = (*t)->left->right;
    (*t)->left->left = left_mul;
    (*t)->left->right = right_mul;

    return;
}

void tree_transform(Tree *t)
{
    if ((*t) != NULL) {
        tree_transform(&((*t)->left));
        tree_transform(&((*t)->right)); 
        if (match_plus(t)) {
            transform_div(t);
//            printf("YES\n");
        }
    }
}
