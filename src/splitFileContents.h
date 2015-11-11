#pragma once

// Definition of the fileContent Structure

typedef struct FileContent FileContent;
struct FileContent
{
	char** elem;
	unsigned int nbLine;
};

// Function's prototype

FileContent* getFileElem(char *filePath);
int getLineNumber(FILE* file);
char* cpyLineToBuff(FILE* file);
void freeStruct(FileContent* structToFree);