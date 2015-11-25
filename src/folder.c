#include "folder.h"
#include "splitFileContents.h"
#include "options.h"

char** getFolder(char* path, int* fileNameLen)
{

	DIR* rep = NULL;
	char** fileName = NULL;
	int c = 0;
	struct dirent* readFile = NULL;
	rep = opendir(path);

	if (rep == NULL)
		exit(EXIT_FAILURE);

	while ((readFile = readdir(rep)) != NULL)
	{
		c++;
	}

	if (closedir(rep) == -1)
		exit(EXIT_FAILURE);

	rep = opendir(path);

	if (rep == NULL)
		exit(EXIT_FAILURE);

	fileName = malloc(c * sizeof(char*));
	c = 0;

	while ((readFile = readdir(rep)) != NULL)
	{
		fileName[c] = malloc((strlen(readFile->d_name)+1) * sizeof(char));
		strcpy(fileName[c], readFile->d_name);
		c++;
		*fileNameLen = c;
	}

	if (closedir(rep) == -1)
		exit(EXIT_FAILURE);

	return fileName;
}

int isFolder(char* path)
{
	DIR* rep = NULL;
	rep = opendir(path);

	if (rep == NULL)
		return FALSE;
	else
	{
		closedir(rep);
		return TRUE;
	}
}

void compareFolderFile(char** argv, int option, char* folderPath1, char* folderPath2, char** fileFolder1, char** fileFolder2, int fileFolderLen1, int fileFolderLen2)
{
#ifdef WIN32
	char separator[2] = "\\";
#else
	char separator = '/';
#endif
	int i, j;

	if (fileFolderLen1 < 3 || fileFolderLen2 < 3)
	{
		printf("Empty folders : Folder 1 or 2 is/are empty\n");
	}
	else
	{
		for (i = 2; i < fileFolderLen1; i++)
		{
			for (j = 2; j < fileFolderLen2; j++)
			{
				if (strcmp(fileFolder1[i], fileFolder2[j]) == 0)
				{
					char* path1 = malloc((strlen(fileFolder1[i]) + 2 + strlen(folderPath1)) * sizeof(char));
					char* path2 = malloc((strlen(fileFolder2[j]) + 2 + strlen(folderPath2)) * sizeof(char));

					strcpy(path1, folderPath1);
					strcat(path1, separator);
					strcat(path1, fileFolder1[i]);

					strcpy(path2, folderPath2);
					strcat(path2, separator);
					strcat(path2, fileFolder2[j]);

					Output(path1, path2, option, argv);
				}
			}
		}
	}
}

void compareFileAndFolder(char** argv, int option, char* folderPath, char** fileFolder, int fileFolderLen, char* fileName)
{
#ifdef WIN32
	char separator[2] = "\\";
#else
	char separator = '/';
#endif
	int i, j;

	if (fileFolderLen < 3)
	{
		printf("Empty folder\n");
	}
	else
	{
		for (i = 2; i < fileFolderLen; i++)
		{
			if (strcmp(fileFolder[i], fileName) == 0)
			{
				char* path1 = malloc((strlen(fileFolder[i]) + 2 + strlen(folderPath)) * sizeof(char));
				
				strcpy(path1, folderPath);
				strcat(path1, separator);
				strcat(path1, fileFolder[i]);

				Output(path1, fileName, option, argv);
			}
		}
	}
}

void Output(char* filePath1, char* filePath2, int option, char** argv)
{
	FileContent* file1;
	FileContent* file2;
	OutputMode options;

	file1 = pushFileToStruct(filePath1);
	file2 = pushFileToStruct(filePath2);

	if (option == 0)
	{
		options = NORMAL_OUTPUT_MODE + SENSITIVE_CASE + IDENTICAL_REPORT;
		redirectOutput(options, filePath1, filePath2, file1, file2);
		freeStruct(file1);
		freeStruct(file2);
	}

	if (option == 1)
	{
		OutputMode options;

		options = getOptions(0, argv);

		file1 = pushFileToStruct(filePath1);
		file2 = pushFileToStruct(filePath2);

		redirectOutput(options, filePath1, filePath2, file1, file2);

		freeStruct(file1);
		freeStruct(file2);
	}


}