#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"

FileContent* getFileElem (char *filePath) {
	if (filePath != NULL)
	{
		FILE* file = NULL;

		file = fopen(filePath, "r");
		
		if (file != NULL)
		{
			char* buffer = NULL;
			struct FileContent elem;
			int nbLine = getLineNumber(file), i = 0;

			elem.elem = malloc(nbLine * sizeof(char*));
			for (i = 0; i < nbLine; i++)
			{
				elem.elem[i] = cpyLineToBuff(file);
			}

			elem.nbLine = nbLine;
			fclose(file);
			return &elem;
		}
		printf("ERROR: Cannot open file! \n");
		return 1;
	}
	printf("ERROR: filepath is empty\n");
	return 1;
}

int getLineNumber(FILE* file)
{
	int c = 0, count = 0;

	// Obtain number of line
	fseek(file, 0, SEEK_END);
	while ((c = fgetc(file)) != EOF)
		if (c == '\n')
			count++;
	rewind(file);
	return count;
}

char* cpyLineToBuff(FILE* file)
{
	int i = 0, lenght = 0;
	char* buffer = NULL;
	int c = fgetc(file);

	buffer = malloc(sizeof(char));
	buffer[0] = c;
	lenght++;

	while (c != '\n')
	{
		char* tmp = malloc((lenght + 1) * sizeof(char));
		for (i = 0; i < lenght; i++)
			tmp[i] = buffer[i];
		c = fgetc(file);
		tmp[lenght] = c;
		lenght++;
		free(buffer);
		buffer = tmp;
		free(tmp);
	}
	return buffer;
}

void freeStruct(FileContent* structToFree)
{
	if (structToFree == NULL)
	{
		printf("ERROR: The structure is empty, nothing to free\n");
		return 1;
	}
	int i = 0;

	for (i = 0; i < structToFree->nbLine; i++)
	{
		free(structToFree->elem[i]);
	}
	free(structToFree->elem);
	free(structToFree);

	return 0;
}