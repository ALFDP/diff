#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"
#include "splitFileContents.h"
#include "lcs.h"

OutputMode getOptions(int argc, char** argv) {

	int length = strlen(argv[1]), i = 0;
	int* tabOption = malloc(4 * sizeof(int));
	OutputMode options = 0;

	initTab(tabOption, 4);

	for (i = 0; i < length; i++)
	{
		if (argv[1][i] == '-')
		{
			if (argv[1][i + 1] == '-')
			{
				i += 2;
				getLongOption(argv, &i, &options, tabOption, TRUE);
			}

			else
			{
				i++;
				getLongOption(argv, &i, &options, tabOption, FALSE);
			}
		}
	}

	if (tabOption[0] == FALSE)
		options = options + NORMAL_OUTPUT_MODE;
	if (tabOption[1] == FALSE)
		options = options + SENSITIVE_CASE;

	return options;
}

int getLongOption(char** argv, int* val, OutputMode* option,int* checkTab, int longChar)
{
	char* tab = malloc(50 * sizeof(char));
	int j = 0, i = *val;

	initBuffer(tab, 50);

	if (longChar == FALSE)
	{
		while ((argv[1][i] != '-') ||( argv[1][i] != '\0'))
		{
			if (argv[1][i] == '\0')
				return 0;

			tab[j] = argv[1][i];
			*val = i++;

			if (tab[j] == 'u')
			{
				if (checkTab[0] == FALSE)
				{
					*option = *option + UNIFIED_OUTPUT_MODE;
					checkTab[0] = TRUE;
				}
			}
			else if (tab[j] == 'i')
			{
				if (checkTab[1] == FALSE)
				{
					*option = *option + SENSITIVE_CASE;
					checkTab[1] = TRUE;
					
				}
			}
			else if (tab[j] == 'q')
			{
				if (checkTab[2] == FALSE)
				{
					*option = *option + BRIEF_REPORT;
					checkTab[2] = TRUE;
					
				}
				
			}
			else if (tab[j] == 's')
			{
				if (checkTab[2] == FALSE && checkTab[3] == FALSE)
				{
					*option = *option + IDENTICAL_REPORT;
					checkTab[3] = TRUE;	
				}
			}
			j++;
		}
		return 0;
	}

	else
	{

		while (argv[1][i] != '\0')
		{
			if (argv[1][i] == '-')
			{
				if (argv[1][i + 2] == '-' || (argv[1][i + 2] == '\0'))
				{
					i--;
					break;
				}
			}
			tab[j] = argv[1][i];

			j++;
			i++;

		}

		*val = i;
		tab[j] = '\0';

		if (strcmp(tab, "brief") == 0)
		{
			if (checkTab[2] == FALSE)
			{
				*option = *option + BRIEF_REPORT;
				checkTab[2] = TRUE;
				return TRUE;
			}
		}
		if (strcmp(tab, "report-identical-files") == 0)
		{
			if (checkTab[2] == FALSE && checkTab[3] == FALSE)
			{
				*option = *option + IDENTICAL_REPORT;
				checkTab[3] = TRUE;
				return TRUE;
			}
		}
		if (strcmp(tab, "normal") == 0)
		{
			if (checkTab[0] == FALSE)
			{
				*option = *option + NORMAL_OUTPUT_MODE;
				checkTab[0] = TRUE;
				return TRUE;
			}
		}
	}
	return 0;
}

void initTab(int* tab, int size)
{
	while (size > 0)
	{
		tab[size - 1] = 0;
		size--;
	}
}

int printReport(FileContent* file1, FileContent* file2, int option, OutputMode options, int caseSensitive)
{
	int i = 0, j = 0, lineF1 = file1->nbLine, lineF2 = file2->nbLine;
	char** txt1 = file1->elem;
	char** txt2 = file2->elem;
	
	

	if(file1->nbLine != file2->nbLine)
	{
		if (option == 0)
			printf("Files are different\n");
		else
		{
			options = options - IDENTICAL_REPORT;
			redirectOutput(options, file1->path, file2->path, file1, file2);
		}

		return 0;
	}
	else {
		StringComparator compare = getComparisonMethod(caseSensitive);

		for (i = 0; i < lineF1; i++)
		{
			if (compare(txt1[i], txt2[i]) != 0)
			{
				if (option == 0)
					printf("File are different\n");
				else
				{
					options = options - IDENTICAL_REPORT;
					redirectOutput(options, file1->path, file2->path, file1, file2);
				}
				return 0;
			}
		}
		if (option != 0)
			printf("File are identical\n");

		return 0;
	}
}


void redirectOutput(OutputMode option, char* path1, char* path2, FileContent* file1, FileContent* file2)
{
	unsigned int** matrix = NULL;
	char ** lcs = NULL;
	unsigned int lcsSize = 0, i = 0;

	if (option == NORMAL_OUTPUT_MODE + SENSITIVE_CASE)
	{
		matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
		lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, TRUE);
		printStandardDiff(file1->elem, file2->elem, matrix, lcsSize, file1->nbLine, file2->nbLine, TRUE);
		freeMatrix(&matrix, file1->nbLine + 1);
		free(lcs);

	}
	else if (option == UNIFIED_OUTPUT_MODE + SENSITIVE_CASE)
	{
		matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, TRUE);
		lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, TRUE);
		printUnifiedDiff(path1, path2, file1->elem, file1->nbLine, file2->elem, file2->nbLine, matrix, lcsSize, TRUE, 3);
		freeMatrix(&matrix, file1->nbLine +1);
		free(lcs);
	}

	else if (option == NORMAL_OUTPUT_MODE + NO_SENSITIVE_CASE)
	{
		matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, FALSE);
		lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, FALSE);
		printStandardDiff(file1->elem, file2->elem, matrix, lcsSize, file1->nbLine, file2->nbLine, FALSE);
		freeMatrix(&matrix, file1->nbLine + 1);
		free(lcs);
	}
	else if (option == UNIFIED_OUTPUT_MODE + NO_SENSITIVE_CASE)
	{
		matrix = LCS_buildMatrix(file1->elem, file2->elem, file1->nbLine, file2->nbLine, FALSE);
		lcs = LCS_extract(&lcsSize, matrix, &file1->elem, &file2->elem, file1->nbLine, file2->nbLine, FALSE);
		printUnifiedDiff(path1, path2, file1->elem, file1->nbLine, file2->elem, file2->nbLine, matrix, lcsSize, FALSE, 3);
		freeMatrix(&matrix, file1->nbLine + 1);
		free(lcs);
	}

	else if ((option == BRIEF_REPORT + SENSITIVE_CASE + NORMAL_OUTPUT_MODE) || (option == BRIEF_REPORT + SENSITIVE_CASE + UNIFIED_OUTPUT_MODE))
		printReport(file1, file2, 0, option, TRUE);

	else if (option == IDENTICAL_REPORT + SENSITIVE_CASE + NORMAL_OUTPUT_MODE || option == IDENTICAL_REPORT + SENSITIVE_CASE + UNIFIED_OUTPUT_MODE)
		printReport(file1, file2, 1, option, TRUE);

	else if (option == BRIEF_REPORT + NO_SENSITIVE_CASE + NORMAL_OUTPUT_MODE || option == BRIEF_REPORT + NO_SENSITIVE_CASE + UNIFIED_OUTPUT_MODE)
		printReport(file1, file2, 0, option, FALSE);

	else if (option == IDENTICAL_REPORT + NO_SENSITIVE_CASE + NORMAL_OUTPUT_MODE || option == IDENTICAL_REPORT + NO_SENSITIVE_CASE + UNIFIED_OUTPUT_MODE)
		printReport(file1, file2, 1, option, FALSE);
}