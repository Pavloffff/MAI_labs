#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
	node root;
	node *d = &root;
	create(d);
	int choose, flag = 1;
	int value;
	int key;
	while(flag) {
		printf("1: print;\t2: print size;\t3: push front;\t4: push back;\t5: insert;\t6: is empty;\n");
		printf("7: pop front;\t8: pop back;\t9: erase;\t10: procedure;\t11: sort;\tother: exit;\n");
		scanf("%d", &choose);
		switch(choose) {
		case 1:
			print(d);
			break;
		case 2:
			printf("size is %d\n", size(d));
			break;
		case 3:
			printf("enter value: ");
			scanf("%d", &value);
			push_front(d, value);
			break;
		case 4:
			printf("enter value: ");
			scanf("%d", &value);
			push_back(d, value);
			break;
		case 5:
			printf("enter key: ");
			scanf("%d", &key);
			printf("enter value: ");
			scanf("%d", &value);
			list_insert(d, key, value);
			break;
		case 6:
			if (is_empty(d)) {
				printf("Yes\n");
			} else {
				printf("No\n");
			}
			break;
		case 7:
			pop_front(d);
			break;
		case 8:
			pop_back(d);
			break;
		case 9:
			printf("enter key: ");
			scanf("%d", &key);
			erease(d, key);
			break;
		case 10:
			procedure(d, d->prev);
			break;
		case 11:
			insertion_sort(d);
			break;
		default:
			flag = 0;
			break;
		}
	}
	destroy(d);
}