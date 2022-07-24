#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char const *argv[])
{
	List *l = malloc(sizeof(List));
	Create(l);
	int num = 0;
	int choose;
	int g = 1;
	while (g) {
		printf("1. Print list\t 2. Insert in list\t 3. Delete from list\t 4. Size\t 5. Task\t other. Exit\n");
		scanf("%d", &choose);
		switch (choose) {
			case 1: {
				print_list(l);
				break;
			}
			case 2: {
				Iterator i = Last(l);
				float val;
				printf("Write value\n");
				scanf("%f", &val);
				if (Size(l) != 0) {
					printf("Write the number where you want insert element\n");
					scanf("%d", &num);
					if (0 <= num && num <= Size(l)) {
						i = search_prev(l, num);
					} else {
						printf("Element with %d number doesn't exists\n", num);
						break;
					}
				}
				Insert(l, &i, val);
				break;
			}
			case 3: {
				float prev;
				printf("Write number of deleted element\n");
				scanf("%d", &num);
				if (Size(l) == 1) {
					Destroy(l);
					Create(l);
					break;
				}
				if (0 < num && num < Size(l)) {
					Iterator i = search_prev(l, num);
					Delete(l, &i);
				} else {
					printf("Element with %d number doesn't exists\n", num);
				}
				break;
			}
			case 4: {
				printf("Size is %d\n", Size(l));
				break;
			}
			case 5: {
				Task(l);
				break;
			}
			default: {
				Destroy(l);
				g = 0;
				break;
			}

		}
	}
	free(l);
	return 0;
}