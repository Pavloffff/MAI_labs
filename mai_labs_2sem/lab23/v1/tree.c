#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

bool get_value(value_type *a, char *s)
{
	if (strcmp(s, "ein") == 0) *a = ein;
	else if (strcmp(s, "zwei") == 0) *a = zwei;
	else if (strcmp(s, "drei") == 0) *a = drei;
	else if (strcmp(s, "vier") == 0) *a = vier;
	else if (strcmp(s, "funf") == 0) *a = funf;
	else if (strcmp(s, "sechs") == 0) *a = sechs;
	else if (strcmp(s, "sieben") == 0) *a = sieben;
	else if (strcmp(s, "acht") == 0) *a = acht;
	else if (strcmp(s, "neun") == 0) *a = neun;
	else if (strcmp(s, "zehn") == 0) *a = zehn;
	else if (strcmp(s, "elf") == 0) *a = elf;
	else if (strcmp(s, "zwolf") == 0) *a = zwolf;
	else if (strcmp(s, "dreizehn") == 0) *a = dreizehn;
	else if (strcmp(s, "vierzehn") == 0) *a = vierzehn;
	else if (strcmp(s, "acht") == 0) *a = funfzehn;
	else if (strcmp(s, "neun") == 0) *a = sechzehn;
	else if (strcmp(s, "zehn") == 0) *a = siebzehn;
	else if (strcmp(s, "elf") == 0) *a = achzehn;
	else if (strcmp(s, "zwolf") == 0) *a = neunzehn;
	else if (strcmp(s, "zwanzig") == 0) *a = zwanzig;
	else return false;
	return true;
}

char* get_text(value_type value)
{
	if (value == ein) {
		return "ein";
	} else if (value == zwei) {
		return "zwei";
	} else if (value == drei) {
		return "drei";
	} else if (value == vier) {
		return "vier";
	} else if (value == funf) {
		return "funf";
	} else if (value == sechs) {
		return "sechs";
	} else if (value == sieben) {
		return "sieben";
	} else if (value == acht) {
		return "acht";
	} else if (value == neun) {
		return "neun";
	} else if (value == zehn) {
		return "zehn";
	} else if (value == elf) {
		return "elf";
	} else if (value == zwolf) {
		return "zwolf";
	} else if (value == dreizehn) {
		return "dreizehn";
	} else if (value == vierzehn) {
		return "vierzehn";
	} else if (value == funfzehn) {
		return "funfzehn";
	} else if (value == sechzehn) {
		return "sechzehn";
	} else if (value == siebzehn) {
		return "siebzehn";
	} else if (value == achzehn) {
		return "achzehn";
	} else if (value == neunzehn) {
		return "neunzehn";
	} else {
		return "zwanzig";
	}
}

void add(node **t, value_type val)
{
	if (*t == NULL) {
		*t = malloc(sizeof(node));
		(*t)->left = NULL;
		(*t)->right = NULL;
		(*t)->val = val;
	} else if (val < (*t)->val) {
		add(&(*t)->left, val);
	} else {
		add(&(*t)->right, val);
	}
}

void delete(node **t)
{
	if ((*t)->left == NULL && (*t)->right == NULL) {
		free(*t);
		*t = NULL;
	} else if ((*t)->right == NULL) {
		node *child = (*t)->left;
		free(*t);
		*t = child;
	} else if ((*t)->left == NULL) {
		node *child = (*t)->right;
		free(*t);
		*t = child;
	} else {
		node **maxleft = &(*t)->left;
		while ((*maxleft)->right != NULL)
		{
			maxleft = &(*maxleft)->right;
		}
		node *tmp = *maxleft;
		*maxleft = (*maxleft)->left;
		tmp->left = (*t)->left;
		tmp->right = (*t)->right;
		free(*t);
		*t = tmp;
	}
}

void print_tree(node *t)
{
	if (t != NULL) {
		if (t->right != NULL) {
			printf("   ");
			print_tree(t->right);
		}
		printf("%s\n", get_text(t->val));
		if (t->left != NULL) {
			printf("   ");
			print_tree(t->left);
		}
	} else {
		return;
	}
}

void print_error(char *str)
{
	int c;
	c = getchar();
	while (c != '\n') {
		c = getchar();
	}
	printf("ERROR: %s\n", str);
}

node ** find_val(node **t, value_type val)
{
	if (*t == NULL) {
		return NULL;
	}
	if (val == (*t)->val) {
		return t;
	}
	else if (val > (*t)->val) {
		if ((*t)->right == NULL) {
			return NULL;
		}
		return find_val(&(*t)->right, val);
	} else {
		if ((*t)->left == NULL) {
			return NULL;
		}
		return find_val(&(*t)->left, val);
	}
}

int abs(int x)
{
	return (x >= 0) ? x : (-1) * x;
}

int max_way(node **t, int len)
{
	len++;
	if ((*t)->right == NULL) {
		return len;
	}
	return max_way(&((*t)->right), len);
}

int min_way(node **t, int len)
{
	len++;
	if ((*t)->left == NULL) {
		return len;
	}
	return min_way(&((*t)->left), len);
}

bool is_AVL(node **t)
{
	if (abs(min_way(t, 0) - max_way(t, 0)) > 1) {
		return 0;
	}
	if ((*t)->left != NULL) {
		is_AVL(&((*t)->left));
	}
	if ((*t)->right != NULL) {
		is_AVL(&((*t)->right));
	}
	return 1;
}