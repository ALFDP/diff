#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"
#include "folder.h"
#include "options.h"
#include "output.h"

// This pragma disable CRT warning 
#pragma warning (disable : 4996)

int main(int argc, char** argv)
{
	if (argc < 3) {
		printf("ERROR: invalid argc parameter\n");
		return 1;
	}
	unsigned int i = 0;
	int folderStatus1 = 0, folderStatus2 = 0;


	if (argc == 3)
	{
		unsigned int** matrix = NULL;
		char ** lcs = NULL;
		
		folderStatus1 = isFolder(argv[1]);
		folderStatus2 = isFolder(argv[2]);

		if (folderStatus1 == TRUE && folderStatus2 == TRUE)
		{
			// TO FOLDER 
		}
		else if (folderStatus1 == FALSE && folderStatus2 == FALSE)
		{
			FileContent* file1;
			FileContent* file2;

			file1 = pushFileToStruct(argv[1]);
			file2 = pushFileToStruct(argv[2]);


			structDisplay(file1, TRUE);
			structDisplay(file2, TRUE);


			printf("%s \n", file1->modifiedTime);

			matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
			lcs = LCS_extract(matrix, file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
			printNormalDiff(file1->elem, file2->elem, lcs, file1->nbLine, file2->nbLine, TRUE);

			freeStruct(file1);
			freeStruct(file2);
		}
	}

	else if (argc == 4)
	{
		unsigned int** matrix = NULL;
		char ** lcs = NULL;

		folderStatus1 = isFolder(argv[1]);
		folderStatus2 = isFolder(argv[2]);

		if (folderStatus1 == TRUE && folderStatus2 == TRUE)
		{
			// TO FOLDER 
		}
		else if (folderStatus1 == FALSE && folderStatus2 == FALSE)
		{
			FileContent* file1;
			FileContent* file2;
			OutputMode option;

			option = getOptions(0, argv);

			printf("option %d\n", option);

			file1 = pushFileToStruct(argv[1]);
			file2 = pushFileToStruct(argv[2]);

			if (option == 0x16)
				printReport(file1, file2, 0);
			else if (option == 0x32)
				printReport(file1, file2, 1);





			matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
			lcs = LCS_extract(matrix, file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
			printNormalDiff(file1->elem, file2->elem, lcs, file1->nbLine, file2->nbLine, TRUE);

			freeStruct(file1);
			freeStruct(file2);
		}
	} 
	return 0;
}
