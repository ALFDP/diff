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
<<<<<<< HEAD
	char *line = NULL;
	char buffer[BUFSIZ];
	int i = 0, c = 0;

	initBuffer(&buffer[0], BUFSIZ);
=======
	char *buffer = NULL;
	int length = 0, c = 0;
	
>>>>>>> 456336d0a1b275590bb88a57257f7c00e1024f4a
	c = fgetc(file);

	while (1)
	{
<<<<<<< HEAD
		if (c == 10 || c == '\0' || c == EOF)
=======
		c = fgetc(file);
		length++;
		if (c == '\n' || c== '\0' || c == EOF)
		{
			buffer = realloc(buffer, (length + 1) * sizeof(char));
			buffer[length] = '\0';
>>>>>>> 456336d0a1b275590bb88a57257f7c00e1024f4a
			break;
		buffer[i] = c;
		i++;
		if (i == BUFSIZ)
		{
			realloc_s(&line, buffer, i);
			i = 0;
		}
<<<<<<< HEAD
		c = fgetc(file);
=======
		buffer = realloc(buffer, (length + 1) * sizeof(char));
		buffer[length] = c;
>>>>>>> 456336d0a1b275590bb88a57257f7c00e1024f4a
	}
	realloc_s(&line, buffer, i);

	return line;
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

int realloc_s(char** line, char* toCpy, int nbELem)
{
	char* temp = NULL;
	int i = 0, length = 0;

	if (line[0] != NULL)
	{
		length = strlen(line[0]);
		temp = malloc(length * sizeof(char));

		if (temp == NULL)
		{
			printf("ERROR: Failed Memory Allocation\n");
			return 1;
		}

		for (i = 0; i < length; i++)
		{
			temp[i] = line[0][i];
		}

		free(line);
		line[0] = malloc((length + nbELem + 1) * sizeof(char));

		if (line == NULL)
		{
			printf("ERROR: Failed Memory Allocation");
			free(temp);
			return 1;
		}
		for (i = 0; i < length; i++)
		{
			line[0][i] = temp[i];
		}

		free(temp);

		for (i = 0; i < nbELem; i++)
		{
			line[0][length + i] = toCpy[i];
		}
		line[0][length + nbELem] = '\0';
	}
	else
	{
		line[0] = malloc((nbELem + 1) * sizeof(char));

		for (i = 0; i < nbELem; i++)
		{
			line[0][i] = toCpy[i];
		}
		line[0][nbELem] = '\0';
	}
	
	return 0;
}

void initBuffer(char *buffer, int size)
{
	while (size > 0)
	{
		buffer[size - 1] = 0;
		size--;
	}
}
