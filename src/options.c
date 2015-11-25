#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"
#include "splitFileContents.h"

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
			tab[j] = argv[1][i];

			j++;

		*val = i;

		if (tab[0] == 'u')
		{
			if (checkTab[0] == FALSE)
			{
				*option = *option + UNIFIED_OUTPUT_MODE;
				checkTab[0] = TRUE;
			}
		}
		if (tab[0] == 'i')
		{
			if (checkTab[1] == FALSE)
			{
				*option = *option + SENSITIVE_CASE;
				checkTab[1] = TRUE;
				return TRUE;
			}
			return FALSE;
		}
		if (tab[0] == 'q')
		{
			if (checkTab[2] == FALSE)
			{
				*option = *option + BRIEF_REPORT;
				checkTab[2] = TRUE;
				return TRUE;
			}
			return FALSE;
		}
		if (tab[0] == 's')
		{
			if (checkTab[2] == FALSE && checkTab[3] == FALSE)
			{
				*option = *option + IDENTICAL_REPORT;
				checkTab[3] = TRUE;
				return TRUE;
			}
			return FALSE;
		}

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

int printReport(FileContent* file1, FileContent* file2, int option, int caseSensitive)
{
	int i = 0, j = 0, lineF1 = file1->nbLine, lineF2 = file2->nbLine;
	char** txt1 = file1->elem;
	char** txt2 = file2->elem;
	int res = 0;
	
	if(file1->nbLine != file2->nbLine)
	{
		if (option == 0)
		{
			printf("Files are different\n");
			return 0;
		}
		else
			return 0;
	}
	
	res = isEqual(txt1, txt2, lineF1, lineF2, caseSensitive);
	
	if(res == TRUE)
	{
		if(option == 0)
		{
			printf("Files are different\n");
			return 0;
		}
		else
			return 0;
	}
	else 
	{
		if(option != 0)
		{
			printf("File are identical");
			return 0;
		}
		else
			return 0;
	}
	

}

int isEqual (char** txt1, char** txt2, int lineF1, int lineF2, int caseSensitive)
{
	int i = 0;
	if (caseSensitive == TRUE)
	{
		for (i = 0; i < lineF1; i++)
		{
			if (strcmp(txt1[i], txt2[i]) != 0)
			{
				return FALSE;
			}
		}

		return TRUE;
	}
	else
	{
		for (i = 0; i < lineF1; i++)
		{
			if (stricmp(txt1[i], txt2[i]) != 0)
			{
				return FALSE;
			}
		}

		return TRUE;		
	}
	
}