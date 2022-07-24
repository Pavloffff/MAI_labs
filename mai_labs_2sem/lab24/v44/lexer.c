#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "lexer.h"
#include "vector.h"

void token_next(Token *t)
{
    static bool can_be_unary = true;
    char c;
    
    do {
        c = getchar();
    } while (c == ' ' || c == '\t');
    
    if (c == EOF || c == '\n') {
        t->type = FINAL;
    }
    
    else if (isalpha(c) && c == 'x') {
        t->type = VARIABLE;
        t->data.variable_name = c;
        can_be_unary = false;
    }

    else if (isdigit(c)) {
        int result;
        ungetc(c, stdin);
        scanf("%d", &result);
        t->type = INTEGER;
        t->data.value_int = result;
        can_be_unary = false;
    }
    
    else if (c == '(' || c == ')') {
        t->type = BRACKET;
        t->data.is_left_bracket = (c == '(');
        can_be_unary = t->data.is_left_bracket;
    }
    
    else if (can_be_unary && (c == '-' || c == '+')) {
        int sign = (c == '+') ? +1 : -1;
        
        do {
            c = fgetc(stdin);
        } while (c == ' ' || c == '\t');
        
        if (isdigit(c)) {
            ungetc(c, stdin);
            token_next(t);
            if (t->type == INTEGER) {
                t->data.value_int = sign * (t->data.value_int);
            }
        } else {
            ungetc(c, stdin);
            t->type = OPERATOR;
            t->data.operator_name = '-';
            can_be_unary = true;
        }
    }
    
    else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        t->type = OPERATOR;
        t->data.operator_name = c;
        can_be_unary = true;
    } else {
        t->type = ERROR;
    }
}

void token_print(Token *t)
{
    switch (t->type) {
        case FINAL:
            break;
        case INTEGER:
            printf("%d", t->data.value_int);
            break;
        case VARIABLE:
            printf("%c", t->data.variable_name);
            break;
        case OPERATOR:
            printf("%c", t->data.operator_name);
            break;
        case BRACKET:
            printf("%c", (t->data.is_left_bracket) ? '(' : ')');
            break;
        case ERROR:
            break;
    }
}
