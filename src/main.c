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
	FileContent* file1;
	FileContent* file2;

	if (argc == 3)
	{
		unsigned int** matrix = NULL;
		char ** lcs = NULL;
		unsigned int lcsSize = 0;
		file1 = pushFileToStruct(argv[1]);
		file2 = pushFileToStruct(argv[2]);


		structDisplay(file1, TRUE);
		structDisplay(file2, TRUE);

		matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
		lcs = LCS_extract(&lcsSize, matrix, &(file1->elem), &(file2->elem), file1->nbLine, file2->nbLine, TRUE);
		//printStandardDiff(file1->elem, file2->elem, lcs, lcsSize, file1->nbLine, file2->nbLine, TRUE);
		printUnifiedDiff(file1->path, file2->path, file1->elem, file1->nbLine, file2->elem, file2->nbLine, lcs, lcsSize, TRUE, 1);

        freeMatrix((void***)&matrix, file1->nbLine);
		free(lcs);
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

	//getFolder(argv[1]);

	return 0;
}
