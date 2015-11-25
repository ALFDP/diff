#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "splitFileContents.h"
#include "folder.h"
#include "options.h"
#include "output.h"




int main(int argc, char** argv)
{
	if (argc < 3) {
		printf("ERROR: invalid argc parameter\n");
		return 1;
	}

	int folderStatus1 = 0, folderStatus2 = 0;

	if (argc == 3)
	{
		folderStatus1 = isFolder(argv[1]);
		folderStatus2 = isFolder(argv[2]);

		if (folderStatus1 == TRUE && folderStatus2 == TRUE)
		{
			char** fileName1 = NULL;
			char** fileName2 = NULL;
			int fileNameLen1 = 0, fileNameLen2 = 0, i = 0;

			fileName1 = getFolder(argv[1], &fileNameLen1);
			fileName2 = getFolder(argv[2], &fileNameLen2);
			compareFolderFile(argv, 0, argv[1], argv[2], fileName1, fileName2, fileNameLen1, fileNameLen2);

			for (i = 0; i < fileNameLen1; i++)
				free(fileName1[i]);
			free(fileName1);
			for (i = 0; i < fileNameLen2; i++)
				free(fileName2[i]);
			free(fileName2);
		}
		else if (folderStatus1 == FALSE && folderStatus2 == FALSE)
		{
			FileContent* file1;
			FileContent* file2;
			OutputMode option;

			file1 = pushFileToStruct(argv[1]);
			file2 = pushFileToStruct(argv[2]);

			option = NORMAL_OUTPUT_MODE + SENSITIVE_CASE;

			redirectOutput(option, argv[1], argv[2], file1, file2);
			
			freeStruct(file1);
			freeStruct(file2);
		}
		else
		{
			char** filesName = NULL;
			int filesNameLen = 0, i = 0;

			if (folderStatus1 == TRUE)
			{
				filesName = getFolder(argv[1], &filesNameLen);
				compareFileAndFolder(argv, 0, argv[1], filesName, filesNameLen, argv[2]);
				for (i = 0; i < filesNameLen; i++)
					free(filesName[i]);
				free(filesName);

			}
			else if (folderStatus2 == TRUE)
			{
				filesName = getFolder(argv[2], &filesNameLen);
				compareFileAndFolder(argv, 0, argv[2], filesName, filesNameLen, argv[1]);
				for (i = 0; i < filesNameLen; i++)
					free(filesName[i]);
				free(filesName);
			}
		}
	}

	else if (argc == 4)
	{


		folderStatus1 = isFolder(argv[2]);
		folderStatus2 = isFolder(argv[3]);

		if (folderStatus1 == TRUE && folderStatus2 == TRUE)
		{
			char** fileName1 = NULL;
			char** fileName2 = NULL;
			int fileNameLen1 = 0, fileNameLen2 = 0, i = 0;

			fileName1 = getFolder(argv[2], &fileNameLen1);
			fileName2 = getFolder(argv[3], &fileNameLen2);
			compareFolderFile(argv, 1, argv[2], argv[3], fileName1, fileName2, fileNameLen1, fileNameLen2);

			for (i = 0; i < fileNameLen1; i++)
				free(fileName1[i]);
			free(fileName1);
			for (i = 0; i < fileNameLen2; i++)
				free(fileName2[i]);
			free(fileName2);
		}
		else if (folderStatus1 == FALSE && folderStatus2 == FALSE)
		{
			FileContent* file1;
			FileContent* file2;
			OutputMode option;
			
			option = getOptions(0, argv);

			file1 = pushFileToStruct(argv[2]);
			file2 = pushFileToStruct(argv[3]);

			redirectOutput(option, argv[2], argv[3], file1, file2);

			freeStruct(file1);
			freeStruct(file2);
		}
		else
		{
			char** filesName = NULL;
			int filesNameLen = 0, i = 0;

			if (folderStatus1 == TRUE)
			{
				filesName = getFolder(argv[2], &filesNameLen);
				compareFileAndFolder(argv, 0, argv[2], filesName, filesNameLen, argv[3]);
				for (i = 0; i < filesNameLen; i++)
					free(filesName[i]);
				free(filesName);

			}
			else if (folderStatus2 == TRUE)
			{
				filesName = getFolder(argv[3], &filesNameLen);
				compareFileAndFolder(argv, 0, argv[3], filesName, filesNameLen, argv[2]);
				for (i = 0; i < filesNameLen; i++)
					free(filesName[i]);
				free(filesName);
			}
		}

	} 
	return 0;
}
