#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct comp
{
    char surname[50];
    int num_of_proc;
    char type_of_proc[50];
    int mem_size_ram;
    char type_of_contr[50];
    int mem_size_video_proc;
    char type_of_disk[50];
    int num_of_disk;
    int cap_of_disk;
    int num_of_intcontr;
    int num_of_dev;
    char os[50];
} pc;

int main(int argc, char const *argv[])
{
	int p, k, s, g, h;
	char name[100];
	FILE *data;
	scanf("%s", name);
    data = fopen(name, "rb");
    sscanf(argv[1], "%d", &p);
    for (int i = 0; i < p; ++i) {
    	pc ran;
    	k = rand() % 2;
    	s = rand() % 2;
    	g = rand() % 2;
    	h = rand() % 2;
    	data = fopen(name, "a");
    	for (int i = 0; i < 10; ++i) {
    		ran.surname[i] = (char)(rand()%26+0x61);	
    	}
    	ran.num_of_proc = 2 + rand()%(12 - 2 + 1);
    	if (k == 0) {
    		ran.type_of_proc[0] = 'x';
    		ran.type_of_proc[1] = '8';
    		ran.type_of_proc[2] = '6'; 
    	} else {
    		ran.type_of_proc[0] = 'x';
    		ran.type_of_proc[1] = '6';
    		ran.type_of_proc[2] = '4'; 
    	}
    	ran.mem_size_ram = 2 + rand()%(64 - 2 + 1);
    	if (s == 0) {
    		ran.type_of_contr[0] = 'A';
    		ran.type_of_contr[1] = 'G';
    		ran.type_of_contr[2] = 'P'; 
    	} else {
    		ran.type_of_contr[0] = 'P';
    		ran.type_of_contr[1] = 'C';
    		ran.type_of_contr[2] = 'I'; 
    	}
    	ran.mem_size_video_proc = 2 + rand()%(3 - 2 + 1);
    	if (g == 0) {
    		ran.type_of_disk[0] = 'S';
    		ran.type_of_disk[1] = 'S';
    		ran.type_of_disk[2] = 'D'; 
    	} else {
    		ran.type_of_disk[0] = 'H';
    		ran.type_of_disk[1] = 'D';
    		ran.type_of_disk[2] = 'D'; 
    	}
    	ran.num_of_disk = 2 + rand()%(4 - 2 + 1);
    	ran.cap_of_disk = 128 + rand()%(1024);
    	ran.num_of_intcontr = 2 + rand()%(16 - 2 + 1);
    	ran.num_of_dev = 2 + rand()%(16 - 2 + 1);
    	if (h == 0) {
    		ran.os[0] = 'U';
    		ran.os[1] = 'b';
    		ran.os[3] = 'u';
    		ran.os[4] = 'n';
    		ran.os[5] = 't';
    		ran.os[6] = 'u'; 
    	} else {
    		ran.os[0] = 'W';
    		ran.os[1] = 'i';
    		ran.os[3] = 'n';
    		ran.os[4] = 'd';
    		ran.os[5] = 'o';
    		ran.os[6] = 'w';
    		ran.os[7] = 's'; 
    	}
//    	printf("%d %d %d\n", i, ran.mem_size_ram, ran.num_of_proc);
    	fwrite(&ran, sizeof(pc), 1, data);
        fclose(data);
    }
	return 0;
}