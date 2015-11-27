#include "splitFileContents.h"



// This function is the main function to set up the structure from file
// The parameter is the path of the file
// The function a pointer to the new structure
FileContent* pushFileToStruct(char *filePath) {
	// Checking if the file path is empty, if null the program will be close by exit function
	if (filePath == NULL)
		exit(EXIT_FAILURE);

	FILE* file = NULL;

	file = fopen(filePath, "r");

	// Checking if the file is open, if the opening has failed we close the program
	if (file == NULL)
		exit(EXIT_FAILURE);

	FileContent* elem = NULL;
	int nbLine = 0, i = 0;

	elem = malloc(sizeof(FileContent));

	// Getting file info
	elem->fileInfo = getDataFile(filePath);

	// Transform Latest Modification Time to string
	elem->modifiedTime = getFTime(elem->fileInfo->st_mtime);

	// Getting line number from the file
	nbLine = getLineNumber(file);

	// Here, all the line of the file are put in char tab, one char tab for one line
	// The char** of the struct point to all the char tab (i.e the line)
	elem->elem = malloc(nbLine * sizeof(char*));
	for (i = 0; i < nbLine; i++)
	{
		elem->elem[i] = getLine(file);
	}
	elem->path = malloc((strlen(filePath) + 1)*sizeof(char));
	strcpy(elem->path, filePath);
	elem->nbLine = nbLine;
	fclose(file);

	return elem;
}

// Get data associated with file in parameter
struct _stat* getDataFile(char* path)
{
	struct _stat* buf;
	int result;

	buf = malloc(sizeof(struct _stat));

	// Get data
	result = _stat(path, buf);

	if (result != 0)
	{
		perror("Problem getting information");
		switch (errno)
		{
		case ENOENT:
			printf("File %s not found.\n", path);
			break;
		case EINVAL:
			printf("Invalid parameter to _stat.\n");
			break;
		default:
			/* Should never be reached. */
			printf("Unexpected error in _stat.\n");
		}
	}

	return buf;
}


// This function get the number of line in the file in parameter
unsigned int getLineNumber(FILE* file)
{
	unsigned int count = 0;
	char c[512];

	// Obtain number of line

	while (fgets(c,512,file))
	{
			count++;
	}


	// rewind put the cursor to the first char in the file
	rewind(file);

	return count;
}

// This function get line in the file and return it as char*
char* getLine(FILE* file)
{
	char *line = NULL;
	char buffer[BUFSIZ];
	int i = 0, c = 0;




	// This while get char by char in the file and put them in buffer var
	// If the buffer is full, we flush it in the line char*
	// This method limite malloc use

		fgets(buffer, 512, file);
		line = malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(line, buffer);
		line[strlen(line) - 1] = '\0';
		/*
		// If the cursor reach the end of the line or the fil, we break the while
		if (c == '\n' || c== '\0' || c == EOF)
			break;

		buffer[i] = c;
		i++;
		if (i == BUFSIZ)
		{
			realloc_s(&line, buffer, i);
			i = 0;
		}

		c = fgetc(file);*/



	return line;
}

// As we set our struct with ptr we need to free them when we don't use them
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
		free(structToFree->fileInfo);
		free(structToFree);
	}

}

// This function display all the line in the struct
// The second paramter is a bool to display or not the line number
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

// This is a custom realloc functon to set up our line
// First paramter is the string to change size, second the string to cpy in the first, and the third the number of elements to cpy
int realloc_s(char** line, char* toCpy, int nbELem)
{
	char* temp = NULL;
	int i = 0, length = 0;

	// We check if it's the first allocation or not
	if (line[0] != NULL)
	{
		length = strlen(line[0]);
		temp = malloc(length * sizeof(char));

		if (temp == NULL)
		{
			printf("ERROR: Failed Memory Allocation\n");
			return 1;
		}

		// First we cpy our string in temp string
		for (i = 0; i < length; i++)
		{
			temp[i] = line[0][i];
		}

		// Then we free the string to realloc the string in the new size
		free(line);
		line[0] = malloc((length + nbELem + 1) * sizeof(char));

		if (line == NULL)
		{
			printf("ERROR: Failed Memory Allocation");
			free(temp);
			return 1;
		}
		// We reput our first content in his place
		for (i = 0; i < length; i++)
		{
			line[0][i] = temp[i];
		}

		// We free the temp string we won't use it anymore
		free(temp);

		// We concat the new content after the old one in our string
		for (i = 0; i < nbELem; i++)
		{
			line[0][length + i] = toCpy[i];
		}
		line[0][length + nbELem] = '\0';
	}
	// Here is almost the same step but for an empty string
	// We put only the new content
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

// This function initalize string (char tab) to 0
void initBuffer(char *buffer, int size)
{
	while (size > 0)
	{
		buffer[size - 1] = 0;
		size--;
	}
}

char* getFTime(__time64_t timeToCpy)
{

	char* timeBuf = malloc(26 * sizeof(char));
	initBuffer(timeBuf, 26);

	if (timeBuf == NULL)
	{
		printf("ERROR: Failed Memory Allocation\n");
		exit(EXIT_FAILURE);
	}

	time(&timeToCpy);
	timeBuf = ctime(&timeToCpy);


	return timeBuf;
}
