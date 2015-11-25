#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"
#include "folder.h"
#include "options.h"
#include "output.h"




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
			unsigned int lcsSize = 0;

			file1 = pushFileToStruct(argv[1]);
			file2 = pushFileToStruct(argv[2]);

			matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
			lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, TRUE);
			printStandardDiff(file1->elem, file2->elem, matrix, lcsSize, file1->nbLine, file2->nbLine, TRUE);
			
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
			unsigned int lcsSize = 0;
			int res;

			option = getOptions(0, argv);

			file1 = pushFileToStruct(argv[2]);
			file2 = pushFileToStruct(argv[3]);

			matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
			lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, TRUE);

			if (option == NORMAL_OUTPUT_MODE + SENSITIVE_CASE)
			{
				matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
				lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, TRUE);
				printStandardDiff(file1->elem, file2->elem, matrix, lcsSize, file1->nbLine, file2->nbLine, TRUE);
			}
			else if (option == UNIFIED_OUTPUT_MODE + SENSITIVE_CASE)
			{
				matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
				lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, TRUE);
				printUnifiedDiff(argv[2], argv[3], file1->elem, file1->nbLine, file2->elem, file2->nbLine, matrix, lcsSize, TRUE, 3);
			}

			else if (option == NORMAL_OUTPUT_MODE + NO_SENSITIVE_CASE)
			{
				matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, FALSE);
				lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, FALSE);
				printStandardDiff(file1->elem, file2->elem, matrix, lcsSize, file1->nbLine, file2->nbLine, FALSE);
			}
			else if (option == UNIFIED_OUTPUT_MODE + NO_SENSITIVE_CASE)
			{
				matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, FALSE);
				lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, FALSE);
				printUnifiedDiff(argv[2], argv[3], file1->elem, file1->nbLine, file2->elem, file2->nbLine, matrix, lcsSize, FALSE, 3);
			}

			else if (option == BRIEF_REPORT + SENSITIVE_CASE + NORMAL_OUTPUT_MODE)
				res = printReport(file1, file2, 0, TRUE);

			else if (option == IDENTICAL_REPORT + SENSITIVE_CASE + NORMAL_OUTPUT_MODE)
				res = printReport(file1, file2, 1, TRUE);

			else if (option == BRIEF_REPORT + NO_SENSITIVE_CASE + NORMAL_OUTPUT_MODE)
				res = printReport(file1, file2, 0, TRUE);

			else if (option == IDENTICAL_REPORT + NO_SENSITIVE_CASE + NORMAL_OUTPUT_MODE)
				res = printReport(file1, file2, 1, TRUE);



			freeStruct(file1);
			freeStruct(file2);
		}
	} 
	return 0;
}
