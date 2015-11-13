#include <stdio.h>
#include <stdlib.h>

#include "splitFileContents.h"

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

	printf("Valid argc parameter: %d\n", argc);
	printf("File 1 path: %s\n", argv[1]);
	printf("File 2 path: %s\n", argv[2]);

	file1 = getFileElem(argv[1]);
	printf("Struct->elem: number of line: %d\n", file1->nbLine);

	file2 = getFileElem(argv[2]);
	printf("Struct->elem: number of line: %d\n", file2->nbLine);

	structDisplay(file1, TRUE);
	structDisplay(file2, TRUE);

	freeStruct(file1);
	freeStruct(file2);

	return 0;
}
