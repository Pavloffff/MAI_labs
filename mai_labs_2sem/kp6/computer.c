#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "computer.h"

void create()
{
    char name[100];
    FILE *data;
    printf("Enter file name to create\n");
    scanf("%s", name);
    data = fopen(name, "rb");
    if (data != NULL) {
        printf("File already exists\n");
    } else {
        data = fopen(name, "a");
    }
    fclose(data);
}

void add()
{
    char name[100];
    FILE *data;
    pc rec;
    printf("Enter a file name\n");
    scanf("%s", name);
    data = fopen(name, "rb");
    if (!data) {
        printf("File not found\n");
    } else {
        data = fopen(name, "a");
        printf("Enter a surname\n");
        scanf("%s", rec.surname);
        printf("Enter a number of processors\n");
        scanf("%d", &rec.num_of_proc);
        printf("Enter a type of processors\n");
        scanf("%s", rec.type_of_proc);
        printf("Enter a RAM size\n");
        scanf("%d", &rec.mem_size_ram);
        printf("Enter a type of controller\n");
        scanf("%s", rec.type_of_contr);
        printf("Enter a video memory size\n");
        scanf("%d", &rec.mem_size_video_proc);
        printf("Enter a type of disk\n");            
        scanf("%s", rec.type_of_disk);
        printf("Enter a number of disks\n");
        scanf("%d", &rec.num_of_disk);
        printf("Enter a capacity of disk\n");
        scanf("%d", &rec.cap_of_disk);
        printf("Enter a number of integrated controllers\n");
        scanf("%d", &rec.num_of_intcontr);
        printf("Enter a number of peripheral devises\n");
        scanf("%d", &rec.num_of_dev);
        printf("Enter an OS\n");
        scanf("%s", rec.os);
        fwrite(&rec, sizeof(pc), 1, data);
        fclose(data);
    }
}

void table_print()
{
    FILE *data;
    pc read;
    char name[100];
    int count = 0;
    printf("Enter a file name\n");
    scanf("%s", name);
    data = fopen(name, "rb");
    if (!data) {
        printf("File not found\n");
    } else {
        printf(
        "Surname\t\tPNum\tPType\tRAM\t"
        "CType\tVMem\tDType\tDNum\tDCap\t"
        "ICNum\tPDNum\tOS\n");
        while (fread(&read, sizeof(pc), 1, data) != EOF && !feof(data)) {
            printf(
                    "%s\t%d\t%s\t%d\t%s\t%d\t%s\t%d\t%d\t%d\t%d\t%s\n", 
                    read.surname, read.num_of_proc, read.type_of_proc, read.mem_size_ram,
                    read.type_of_contr, read.mem_size_video_proc, read.type_of_disk,
                    read.num_of_disk, read.cap_of_disk, read.num_of_intcontr,
                    read.num_of_dev, read.os
                    );
        }
        fclose(data);  
    }
}

void delete()
{
    FILE *data;
    char name[100];
    printf("Enter file name\n");
    scanf("%s", name);
    data = fopen(name, "rb");
    if (!data) {
        printf("File not found\n");
    } else {
        remove(name);
        printf("File was deleted\n");
    }
}

void func(int p)
{
    pc find, select;
    char name[100];
    FILE *data;
    int count = 0;
    printf("Enter file name\n");
    scanf("%s", name);
    data = fopen(name, "rb");
    if (data == NULL) {
        printf("File not found\n");
        return;
    } else {
        data = fopen(name, "rb");
        
        printf("Enter minimal number of processors\n");
        scanf("%d", &select.num_of_proc);
        printf("Enter minimal size of RAM, GB\n");
        scanf("%d", &select.mem_size_ram);
        printf("Enter minimal size of video memory, GB\n");
        scanf("%d", &select.mem_size_video_proc);
        printf("Enter minimal number of disks\n");
        scanf("%d", &select.num_of_disk);
        printf("Enter minimal capacity of disk, GB\n");
        scanf("%d", &select.cap_of_disk);
        printf("Enter minimal number of integrated controllers\n");
        scanf("%d", &select.num_of_intcontr);
        printf("Enter necessary OS\n");
        scanf("%s", &select.os);

        while (fread(&find, sizeof(pc), 1, data) != EOF && !feof(data)) {
            if ((find.num_of_proc < select.num_of_proc) || (find.mem_size_ram < select.mem_size_ram) 
                || (find.mem_size_video_proc < select.mem_size_video_proc) || (find.num_of_disk < select.num_of_disk)
                || (find.cap_of_disk < select.cap_of_disk) || (find.num_of_intcontr < select.num_of_intcontr)
                || (!strcmp(find.os, select.os))) {
                    count++;
            }
        }
        if (count < p) {
            printf("Too few computers\n");
            fclose(data);
            return;
        } else {
            data = fopen(name, "rb");
            printf("\nList of student which computers need to upgrade\n");
            while (fread(&find, sizeof(pc), 1, data) != EOF && !feof(data)) {
                if (!((find.num_of_proc >= select.num_of_proc) && (find.mem_size_ram >= select.mem_size_ram) 
                    && (find.mem_size_video_proc >= select.mem_size_video_proc) && (find.num_of_disk >= select.num_of_disk)
                    && (find.cap_of_disk >= select.cap_of_disk) && (find.num_of_intcontr >= select.num_of_intcontr)
                    && (!strcmp(find.os, select.os) ))) {
                        printf("\t%s\n", find.surname);
                }
            }
        }
        fclose(data);
    }
}