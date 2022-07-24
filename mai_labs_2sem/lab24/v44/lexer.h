#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdbool.h>

typedef enum {
    FINAL,
    INTEGER,
    OPERATOR,
    VARIABLE,
    BRACKET,
    ERROR,
} TokenType;

typedef struct {
    TokenType type;
    union {
        int   value_int;
        char  operator_name;
        bool  is_left_bracket;
        char  variable_name;
    } data;
} Token;

void token_print(Token *t);
void token_next(Token *t);

#endif
