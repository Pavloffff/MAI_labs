#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

void print_help()
{
	printf("add VALUE    - add an element VALUE to the appropriate position of the tree\n");
	printf("delete VALUE - delete an element VALUE from his position of the tree\n");
	printf("Correct names of VALUE are: apple, banana, pear, plum, pomegranate, grapes, mandarin, orange, apricot, peach, melon, watermelon, pineapple, kivi, mango\n");
	printf("print        - print a tree diagram\n");
	printf("AVL         - check if the tree is AVL\n");
	printf("help         - print information about valid commands\n");
	printf("exit         - finish the execution\n");
	printf("----------------------------------------------------------------------------\n");
}

bool take_order(node **t)
{
	char order[100];
	if (scanf("%s", order) != 1) {
		return true;
	} else if (strcmp(order, "exit") != 0) {
		if (strcmp(order, "help") == 0) {
			print_help();
		} else if (strcmp(order, "print") == 0) {
			print_tree(*t);
		} else if (strcmp(order, "add") == 0) {
			char c[100];
			scanf("%s", c);
			value_type value;
			if (!get_value(&value, c)) {
				print_error(strcat(c, " is not a correct argument. Use help"));
			} else {
				add(t, value);
			}
		} else if (strcmp(order, "delete") == 0) {
			char c[100];
			scanf("%s", c);
			value_type value;
			if (!get_value(&value, c)) {
				print_error(strcat(c, " is not a correct argument. Use help"));
			} else {
				node **tmp = find_val(t, value);
				if (tmp != NULL) {
					delete(tmp);
				} else {
					print_error("there is not this value");
				}
			}
		} else if (strcmp(order, "AVL") == 0) {
			printf("%d\n", is_AVL(t));
		} else {
			print_error(strcat(order, " is not a correct order. Use help"));
		}
		return false;
	} else {
		return true;
	}
}

int main()
{
	node *t;
	t = NULL;
	
	bool stop = take_order(&t);
	while (!stop)
	{
		stop = take_order(&t);
	}
	
	return 0;
}
