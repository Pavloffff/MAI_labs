#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "tree.h"
#include "transform.h"
#include "vector.h"

int main(void)
{
	vector tokens;
	create(&tokens);

	Token token;
	token_next(&token);

	while (token.type != FINAL) {
		push(&tokens, token);
		token_next(&token);
	}
	
	printf("\n");
	for (int i = 1; i < size(&tokens); i++) {
		if ((tokens.begin[i].type == tokens.begin[i - 1].type) || 
			((tokens.begin[i - 1].type == INTEGER) && (tokens.begin[i].type == VARIABLE)) || 
			((tokens.begin[i - 1].type == VARIABLE) && (tokens.begin[i].type == INTEGER)) ||
			(tokens.begin[i - 1].type == ERROR) || (tokens.begin[i].type == ERROR)) {
			printf("\nWrong input\n");
			return 1;
		}
	}
	printf("\n");
	
	Tree tree = tree_create(&tokens, 0, size(&tokens) - 1);

	printf("\nExpression tree:\n");
	tree_print(tree, 0);
	printf("\nTree's infix linearization:\n");
	tree_infix(tree);
	printf("\n");
	printf("Checking:\n");
	if ((check_reverse(tree) == 1) && (check_right(tree) == 1)) {
		printf("Polinom in reverse & in right order");
	} else if ((check_reverse(tree) == 0) && (check_right(tree) == 1)) {
		printf("Polinom in right order");
	} else if ((check_reverse(tree) == 1) && (check_right(tree) == 0)) {
		printf("Polinom in reverse order");
	} else if ((check_reverse(tree) == 0) && (check_right(tree) == 0)) {
		printf("Polinom is not ordered");
	} else {
		printf("this is no polinom");
	}
        
	printf("\n");
	destroy(&tokens);
	return 0;
}

