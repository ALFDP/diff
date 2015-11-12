#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"

FileContent* getFileElem(char *filePath) {
	if (filePath == NULL)
		exit(EXIT_FAILURE);

	FILE* file = NULL;

	file = fopen(filePath, "r");

	if (file == NULL)
		exit(EXIT_FAILURE);

	FileContent* elem;
	elem = malloc(sizeof(FileContent));
	int nbLine = 0, i = 0;
	nbLine = getLineNumber(file);

	elem->elem = malloc(nbLine * sizeof(char*));
	for (i = 0; i < nbLine; i++)
	{
		elem->elem[i] = cpyLineToBuff(file);
	}

	elem->nbLine = nbLine;
	fclose(file);

	return elem;
}

int getLineNumber(FILE* file)
{
	int c = 0, count = 0;

	// Obtain number of line
	fseek(file, 0, SEEK_END);
	rewind(file);
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n')
			count++;
	}

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

	while (c != EOF)
	{
		c = fgetc(file);
		lenght++;
		if (c == '\n')
		{
			buffer = realloc(buffer, (lenght + 1) * sizeof(char));
			buffer[lenght] = '\0';
			break;
		}
		buffer = realloc(buffer, (lenght + 1) * sizeof(char));
		buffer[lenght] = c;	
	}
	return buffer;
}

void freeStruct(FileContent* structToFree)
{
	if (structToFree == NULL)
	{
		printf("ERROR: The structure is empty, nothing to free\n");
		exit(EXIT_FAILURE);
	}
	unsigned int i = 0;

	for (i = 0; i < structToFree->nbLine; i++)
	{
		free(structToFree->elem[i]);
	}

	free(structToFree->elem);
	free(structToFree);

}