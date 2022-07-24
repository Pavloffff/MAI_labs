#ifndef _TREE_H_
#define _TREE_H_

typedef enum {
	black,
	charcoal,
	gray,
	white,
	pink,
	fushia,
	red,
	plum,
	purple,
	cobalt,
	navy,
	blue,
	blue_green,
	turquoise,
	emerald,
	dark_gray,
	light_gray,
	bone,
	light_pink,
	mauve,
	violet,
	periwinkle,
	light_blue,
	sea_foam,
	dark_brown,
	brown,
	beige,
	cream,
	peach,
	coral,
	rust,
	orange,
	mustard,
	banana,
	green,
	olive,
	hunter,
	teal,
	camel,
	copper,
	yellow,
	chartreuse,
	celery,
} value_type;

typedef struct node
{
	value_type data;
	struct node *left;
	struct node *right;
} node;

node *add(node *tree, value_type value);

node *minimal_node(node *tree);

node *delete(node *tree, value_type value);

void print(node *tree, size_t depth_value);

size_t depth(node *tree);

size_t width(node *tree, size_t depth);

size_t task(node *tree);

node *destroy(node *tree);

value_type str_to_enum(char *elem);

void print_colors(value_type elem);

#endif 
