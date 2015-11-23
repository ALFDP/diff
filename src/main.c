#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"

// This pragma disable CRT warning 
#pragma warning (disable : 4996)

int main(int argc, char** argv)
{
	if (argc != 3) {
		printf("ERROR: invalid argc parameter\n");
		return 1;
	}
	unsigned int i = 0;
	FileContent* file1;
	FileContent* file2;

	if (argc == 3)
	{
		file1 = pushFileToStruct(argv[1]);
		file2 = pushFileToStruct(argv[2]);

		structDisplay(file1, TRUE);
		printf("TIME : %s", file1->modifiedTime);
		structDisplay(file2, TRUE);

		freeStruct(file1);
		freeStruct(file2);
	}

	else if (argc == 4)
	{
	
		file1 = pushFileToStruct(argv[2]);
		file2 = pushFileToStruct(argv[3]);

		structDisplay(file1, TRUE);
		structDisplay(file2, TRUE);

		freeStruct(file1);
		freeStruct(file2);
	}
	
	return 0;
}
