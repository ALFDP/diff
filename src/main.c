#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"

// This pragma disable CRT warning 
#pragma warning (disable : 4996)

int main(int argc, char** argv)
{
	printf("Entry point : \n");
	printf("1. Checking argc parameter:\n");

	if (argc != 3) {
		printf("ERROR: invalid argc parameter\n");
		return 1;
	}
	unsigned int i = 0;
	FileContent* file1;
	FileContent* file2;

	if (argc == 3)
	{
		printf("2. No parameter\n");
		printf("File 1 path: %s\n", argv[1]);
		printf("File 2 path: %s\n", argv[2]);

		file1 = pushFileToStruct(argv[1]);
		printf("Struct->elem: number of line: %d\n", file1->nbLine);

		file2 = pushFileToStruct(argv[2]);
		printf("Struct->elem: number of line: %d\n", file2->nbLine);

		structDisplay(file1, TRUE);
		printf("TIME : %s", file1->modifiedTime);
		structDisplay(file2, TRUE);

		freeStruct(file1);
		freeStruct(file2);
	}

	else if (argc == 4)
	{
		printf("2. Parameter: \n");
		printf("Valid argc parameter: %d\n", argc);
		printf("3. Options: %s\n", argv[1]);
		printf("File 1 path: %s\n", argv[2]);
		printf("File 2 path: %s\n", argv[3]);

		file1 = pushFileToStruct(argv[2]);
		printf("Struct->elem: number of line: %d\n", file1->nbLine);

		file2 = pushFileToStruct(argv[3]);
		printf("Struct->elem: number of line: %d\n", file2->nbLine);

		structDisplay(file1, TRUE);
		structDisplay(file2, TRUE);

		freeStruct(file1);
		freeStruct(file2);
	}
	
	return 0;
}
