#include "folder.h"

int getFolder(char* path)
{
	DIR* rep = NULL;
	struct dirent* readFile = NULL;
	rep = opendir(path);

	if (rep == NULL)
		exit(EXIT_FAILURE);

	readFile = readdir(rep);

	if (closedir(rep) == -1)
		exit(EXIT_FAILURE);

	return 0;
}