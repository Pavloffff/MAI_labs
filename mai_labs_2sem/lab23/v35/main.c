#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

int main(int argc, char const *argv[])
{	
	printf("\nWrite:\nADD to add elem in tree\n");
	printf("DELETE to delete elem from tree\n");
	printf("PRINT to show tree\n");
	printf("TASK to print tree level with maximal width\n");
	printf("COLORS to show enum colors list\n");
	printf("HELP to see commands again\n");
	printf("BYE to exit\n\n");
	node *t = NULL;
	char choose[100];
	char elem[100];
	bool flag = true;
	while (flag) {
		if (scanf("%s", choose) != EOF) {
			if (!strcmp(choose, "ADD")) {
				printf("Write color from enum to add it to tree:\n");
				scanf("%s", elem);
				fflush(stdin);
				if (str_to_enum(elem) != -1) {
					t = add(t, str_to_enum(elem));
				} else {
					printf("This is no color\n");
				}
			} else if (!strcmp(choose, "DELETE")) {
				printf("Write color from enum to delete it from tree:\n");
				scanf("%100s", elem);
				if (str_to_enum(elem) != -1) {
					t = delete(t, str_to_enum(elem));
				} else {
					printf("This is no color\n");
				}
			} else if (!strcmp(choose, "PRINT")) {
				printf("\n");
				print(t, 0);
			} else if (!strcmp(choose, "TASK")) {
				printf("Tree level with maximal width: %ld\n", task(t));
			} else if (!strcmp(choose, "COLORS")) {
				printf("Colors enum list:\n");
				for (int i = 0; i < 43; i++) {
					printf("%d: ", i);
					print_colors(i);
					printf("\n");
				}
			} else if (!strcmp(choose, "BYE")) {
				flag = false;	
			} else if (!strcmp(choose, "HELP")) {
				printf("\nWrite:\nADD to add elem in tree\n");
				printf("DELETE to delete elem from tree\n");
				printf("PRINT to show tree\n");
				printf("TASK to print tree level with maximal width\n");
				printf("COLORS to show enum colors list\n");
				printf("HELP to see commands again\n");
				printf("BYE to exit\n\n");
			} else {
				printf("Wrong command. Please try another one.\n");
				continue;
			}
		} else {
			break;
		}
	}
	return 0;
}
