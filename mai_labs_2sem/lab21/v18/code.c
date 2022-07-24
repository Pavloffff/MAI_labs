#include <stdio.h>
#include <string.h>
#include <dirent.h>

//printf("%s/%d\n", dirname, entity->d_name[0]);

void listFiles(const char* dirname)
{
	int n = 0;
	char text[1024] = { 0 };
	char text_1[1024] = { 0 }; 
	DIR* dir = opendir(dirname);
	if (dir == NULL) {
		return;
	}

	struct dirent* entity;
	entity = readdir(dir);
	while (entity != NULL) {
		if (entity->d_type == DT_REG && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
				if (entity->d_name[0] == 77 && entity->d_name[1] == 97 && entity->d_name[2] == 107 && entity->d_name[3] == 101 && entity->d_name[4] == 102 && entity->d_name[5] == 105 && entity->d_name[6] == 108 && entity->d_name[7] == 101) {
					strcat(text, dirname);
					strcat(text, "/");
					strcat(text, entity->d_name);
					//printf("\n%s %d\n", text, n);
					while (text[n] != '\0') {
				        n++; 
				    }
				    //n--;
				
					for (int i = 0; i < n; i++) {
						if (text[i] == '/') {
							printf("\\");
							//text_1[i] = 92;
						} else {
							printf("%c", text[i]);
						}
					}
					printf("\n");
					//printf("%s\n", text_1);
					//printf("\n%s %d\n", text, n);
					memset(text,0,1024);
					memset(text_1,0,1024);
					n = 0;
				} else {
					printf("%s%s\n", dirname, entity->d_name);
				}
			
			//printf("\n%d\n", entity->d_name[0]);
		}
		if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
			char path[1024] = { 0 };
			strcat(path, dirname);
			strcat(path, "/");
			strcat(path, entity->d_name);
			listFiles(path);
		}
		entity = readdir(dir);
	}
	//printf("\n%s\n", text_1);
	closedir(dir);
}

int main(int argc, char const *argv[])
{
	char CONT;
	if (argv[1] == NULL) {
			listFiles(".");
	} else {
		if (strcmp(argv[1], "-p") == 0) {
			printf("Continue (y/n)?");
			scanf("%c", &CONT);
			if (CONT == 'y') {
				if (argv[2] == NULL) {
					listFiles(".");
				} else {
					listFiles(argv[2]);
				}
			} else {
				return 0;
			}
		} else {
			if (argv[1] == NULL) {
				listFiles(".");
			} else {
				listFiles(argv[1]);
			}
		}
	}
	return 0;
}