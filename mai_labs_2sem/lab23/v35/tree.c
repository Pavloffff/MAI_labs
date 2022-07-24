#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

node *add(node *tree, value_type value)
{
	if (tree == NULL) {
		node *tmp = malloc(sizeof(node));
		tmp->data = value;
		tmp->left = NULL;
		tmp->right = NULL;
		return tmp;
	}
	if (value < tree->data) {
		tree->left = add(tree->left, value);
	}
	if (value > tree->data) {
		tree->right = add(tree->right, value);
	}
	return tree;
}

node *minimal_node(node *tree)
{
	if (tree->left == NULL)
		return tree;
	return minimal_node(tree->left);
} 

node *delete(node *tree, value_type value)
{
	if (tree == NULL) {
		return tree;
	}
	if (value < tree->data) {
		tree->left = delete(tree->left, value);
	} else if (value > tree->data) {
		tree->right = delete(tree->right, value);
	} else if (tree->left != NULL && tree->right != NULL) {
		tree->data = minimal_node(tree->right)->data;
		tree->right = delete(tree->right, tree->data);
	} else if (tree->left != NULL) {
		node *left_undertree = tree->left;
		free(tree);
		tree = left_undertree;
	} else if (tree->right != NULL) {
		node *right_undertree = tree->right;
		free(tree);
		tree = right_undertree;
	} else {
		free(tree);
		tree = NULL;
	}
	return tree;
}

size_t depth(node *tree)
{
	if (tree == NULL)
		return 0;
	else {
		size_t left_depth = depth(tree->left);
		size_t right_depth = depth(tree->right);
		return (left_depth > right_depth) ? (left_depth + 1) : (right_depth + 1);
	}
}

size_t width(node *tree, size_t level)
{
	if (tree == NULL)
		return 0;
	if (level == 1)
		return 1;
	else if (level > 1) {
		return width(tree->left, level - 1) + width(tree->right, level - 1);
	}
	return 0;
}

size_t task(node *tree)
{
	if (tree == NULL) {
		return 0;
	}
	int max_level = 0;
	int max_width = 0;
	int width_tmp;
	int depth_tmp = depth(tree);
	for (int i = 1; i <= depth_tmp; i++) {
		width_tmp = width(tree, i);
		if (width_tmp > max_width) {
			max_width = width_tmp;
			max_level = i;
		}
	}
	return max_level;
}

void print(node *tree, size_t depth_value)
{
	if (tree != NULL) {
		for (int i = 0; i < depth_value; ++i) {
			printf("\t\t");
		}
		print_colors(tree->data);
		printf("\t\t\n");
		print(tree->left,  depth_value + 1);
		print(tree->right, depth_value + 1);
	}
}

node *destroy(node *tree)
{
	if (tree == NULL)
		return tree;
	if (tree->left == NULL && tree->right == NULL) {
		free(tree);
		return NULL;
	}
	if (tree->left != NULL)
		tree->left = destroy(tree->left);
	if (tree->right != NULL)
		tree->right = destroy(tree->right);
	return destroy(tree);
}

value_type str_to_enum(char *elem)
{
	if (!strcmp(elem, "BLACK")) {
		return black;
	} else if (!strcmp(elem, "CHARCOAL")) {
		return charcoal;
	} else if (!strcmp(elem, "GRAY")) {
		return gray;
	} else if (!strcmp(elem, "WHITE")) {
		return white;
	} else if (!strcmp(elem, "PINK")) {
		return pink;
	} else if (!strcmp(elem, "FUSHIA")) {
		return fushia;
	} else if (!strcmp(elem, "RED")) {
		return red;
	} else if (!strcmp(elem, "PLUM")) {
		return plum;
	} else if (!strcmp(elem, "PURPLE")) {
		return purple;
	} else if (!strcmp(elem, "COBALT")) {
		return cobalt;
	} else if (!strcmp(elem, "NAVY")) {
		return navy;
	} else if (!strcmp(elem, "BLUE")) {
		return blue;
	} else if (!strcmp(elem, "BLUE_GREEN")) {
		return blue_green;
	} else if (!strcmp(elem, "TURQUOISE")) {
		return turquoise;
	} else if (!strcmp(elem, "EMERALD")) {
		return emerald;
	} else if (!strcmp(elem, "DARK_GRAY")) {
		return dark_gray;
	} else if (!strcmp(elem, "LIGHT_GRAY")) {
		return light_gray;
	} else if (!strcmp(elem, "BONE")) {
		return bone;
	} else if (!strcmp(elem, "LIGHT_PINK")) {
		return light_pink;
	} else if (!strcmp(elem, "MAUVE")) {
		return mauve;
	} else if (!strcmp(elem, "VIOLET")) {
		return violet;
	} else if (!strcmp(elem, "PERIWINCLE")) {
		return periwinkle;
	} else if (!strcmp(elem, "LIGHT_BLUE")) {
		return light_blue;
	} else if (!strcmp(elem, "SEA_FOAM")) {
		return sea_foam;
	} else if (!strcmp(elem, "DARK_BROWN")) {
		return dark_brown;
	} else if (!strcmp(elem, "BROWN")) {
		return brown;
	} else if (!strcmp(elem, "BEIGE")) {
		return beige;
	} else if (!strcmp(elem, "CREAM")) {
		return cream;
	} else if (!strcmp(elem, "PEACH")) {
		return peach;
	} else if (!strcmp(elem, "CORAL")) {
		return coral;
	} else if (!strcmp(elem, "RUST")) {
		return rust;
	} else if (!strcmp(elem, "ORANGE")) {
		return orange;
	} else if (!strcmp(elem, "MUSTARD")) {
		return mustard;
	} else if (!strcmp(elem, "BANANA")) {
		return banana;
	} else if (!strcmp(elem, "GREEN")) {
		return green;
	} else if (!strcmp(elem, "OLIVE")) {
		return olive;
	} else if (!strcmp(elem, "HUNTER")) {
		return hunter;
	} else if (!strcmp(elem, "TEAL")) {
		return teal;
	} else if (!strcmp(elem, "CAMEL")) {
		return camel;
	} else if (!strcmp(elem, "COPPER")) {
		return copper;
	} else if (!strcmp(elem, "YELLOW")) {
		return yellow;
	} else if (!strcmp(elem, "CHARTREUSE")) {
		return chartreuse;
	} else if (!strcmp(elem, "CELERY")) {
		return celery;
	} else {
		return -1;
	}
}

void print_colors(value_type elem)
{
	if (elem == 0) {
		printf("BLACK");
	} else if (elem == 1) {
		printf("CHARCOAL");
	} else if (elem == 2) {
		printf("GRAY");
	} else if (elem == 3) {
		printf("WHITE");
	} else if (elem == 4) {
		printf("PINK");
	} else if (elem == 5) {
		printf("FUSHIA");
	} else if (elem == 6) {
		printf("RED");
	} else if (elem == 7) {
		printf("PLUM");
	} else if (elem == 8) {
		printf("PURPLE");
	} else if (elem == 9) {
		printf("COBALT");
	} else if (elem == 10) {
		printf("NAVY");
	} else if (elem == 11) {
		printf("BLUE");
	} else if (elem == 12) {
		printf("BLUE_GREEN");
	} else if (elem == 13) {
		printf("TURQUOISE");
	} else if (elem == 14) {
		printf("EMERALD");
	} else if (elem == 15) {
		printf("DARK_GRAY");
	} else if (elem == 16) {
		printf("LIGHT_GRAY");
	} else if (elem == 17) {
		printf("BONE");
	} else if (elem == 18) {
		printf("LIGHT_PINK");
	} else if (elem == 19) {
		printf("MAUVE");
	} else if (elem == 20) {
		printf("VIOLET");
	} else if (elem == 21) {
		printf("PERIWINCLE");
	} else if (elem == 22) {
		printf("LIGHT_BLUE");
	} else if (elem == 23) {
		printf("SEA_FOAM");
	} else if (elem == 24) {
		printf("DARK_BROWN");
	} else if (elem == 25) {
		printf("BROWN");
	} else if (elem == 26) {
		printf("BEIGE");
	} else if (elem == 27) {
		printf("CREAM");
	} else if (elem == 28) {
		printf("PEACH");
	} else if (elem == 29) {
		printf("CORAL");
	} else if (elem == 30) {
		printf("RUST");
	} else if (elem == 31) {
		printf("ORANGE");
	} else if (elem == 32) {
		printf("MUSTARD");
	} else if (elem == 33) {
		printf("BANANA");
	} else if (elem == 34) {
		printf("GREEN");
	} else if (elem == 35) {
		printf("OLIVE");
	} else if (elem == 36){
		printf("HUNTER");
	} else if (elem == 37) {
		printf("TEAL");
	} else if (elem == 38) {
		printf("CAMEL");
	} else if (elem == 39) {
		printf("COPPER");
	} else if (elem == 40) {
		printf("YELLOW");
	} else if (elem == 41) {
		printf("CHARTREUSE");
	} else if (elem == 42) {
		printf("CELERY");
	}
}