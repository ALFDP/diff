#include <stdio.h>
#include <stdlib.h>

#include "splitFileContents.h"

int main(int argc, char** argv)
{
	printf("Entry point : \n");
	printf("1. Checking argc parameter:\n");

	if (argc != 2) {
		printf("ERROR: invalid argc parameter\n");
		return 1;
	}
	unsigned int i = 0;
	printf("Valid argc parameter ... \n");

	FileContent* file1;
	printf("File 1 path: %s\n", argv[1]);
	file1 = getFileElem(argv[1]);
	printf("Struct number of line: %d", file1->nbLine);

	for (i = 0; i < file1->nbLine; i++)
	{
		printf("%d %s\n", i + 1, file1->elem[i]);
	}

	freeStruct(file1);

	system("PAUSE");

	return 0;

}