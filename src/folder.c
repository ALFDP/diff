#include "folder.h"

int getFolder(char* path)
{
	DIR* rep = NULL;
	struct dirent* readFile = NULL;
	rep = opendir(path);

	if (rep == NULL)
		exit(EXIT_FAILURE);

	while ((readFile = readdir(rep)) != NULL)
		printf(" %s\n",readFile->d_name);
	

	

	if (closedir(rep) == -1)
		exit(EXIT_FAILURE);

	return 0;
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