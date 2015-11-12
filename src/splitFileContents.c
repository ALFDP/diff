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
	count++;

	rewind(file);
	return count;
}

char* cpyLineToBuff(FILE* file)
{
	char *buffer = NULL;
	int lenght = 0, c = 0;
	
	c = fgetc(file);
	buffer = malloc(sizeof(char));
	buffer[0] = c;

	while (1)
	{
		c = fgetc(file);
		lenght++;
		if (c == '\n' || c== '\0' || c == EOF)
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
		printf("WARNING: The structure is empty, nothing to free\n");
	}
	else
	{
		unsigned int i = 0;

		for (i = 0; i < structToFree->nbLine; i++)
		{
			free(structToFree->elem[i]);
		}

		free(structToFree->elem);
		free(structToFree);
	}

}

void structDisplay(FileContent* structToDisplay, int displayLine)
{
	if (structToDisplay == NULL)
	{
		printf("WARNING: Structure is empty, nothing to display\n");
	}
	else
	{
		unsigned int i = 0;
		if (displayLine == TRUE)
		{
			for (i = 0; i < structToDisplay->nbLine; i++)
				printf("%d %s\n", i+1, structToDisplay->elem[i]);
		}
		else
		{
			for (i = 0; i < structToDisplay->nbLine; i++)
				printf("%s\n", structToDisplay->elem[i]);
		}
	}
}