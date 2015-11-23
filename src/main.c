#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"
#include "folder.h"
#include "output.h"

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
		unsigned int** matrix = NULL;
		char ** lcs = NULL;
		file1 = pushFileToStruct(argv[1]);
		file2 = pushFileToStruct(argv[2]);


		structDisplay(file1, TRUE);
		structDisplay(file2, TRUE);

		matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
		lcs = LCS_extract(matrix, file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
		printNormalDiff(file1->elem, file2->elem, lcs, file1->nbLine, file2->nbLine, TRUE);

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
	
	getFolder(argv[1]);

	return 0;
}
