#pragma once

#include <time.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Define to simulate bool 
#define TRUE 1
#define FALSE 0


// Definition of the fileContent Structure
typedef struct FileContent FileContent;
struct FileContent
{
	char** elem;
	unsigned int nbLine;
	struct _stat* fileInfo;
	char* modifiedTime;
	char* path;
};

// Function's prototype
FileContent* pushFileToStruct(char *filePath);
int getLineNumber(FILE* file);
char* getLine(FILE* file);
void freeStruct(FileContent* structToFree);
void structDisplay(FileContent* structToDisplay, int displayLine);
int realloc_s(char **line, char* toCpy, int nbELem);
void initBuffer(char *buffer, int size);
struct _stat* getDataFile(char* path);
char* getFTime(__time64_t time);
