#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		printf("Choose 1 file\n");
		return 1;
	}
	
	FILE *test = fopen(argv[1],"r");
	
	vector v;
	create(&v);
	
	value_type t;
	while (fscanf(test, "%s%s", t.key, t.value) == 2) {
		push(&v, t);
	}

	print(&v);
	bin_insertion_sort(&v);
	print(&v);

	char find[7];
	printf("Enter key: ");
	scanf("%6s", find);
	printf("%s\n", bin_search(&v, find).value);

	destroy(&v);
	fclose(test);

	return 0;
}