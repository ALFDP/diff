#ifndef FOLDER_H_INCLUDED

    #define FOLDER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <sys\types.h>
#include <dirent.h>
#include <errno.h>

char** getFolder(char* path, int* fileNameLen);
int isFolder(char* path);
void compareFolderFile(char** argv, int option, char* folderPath1, char* folderPath2, char** fileFolder1, char** fileFolder2, int fileFolderLen1, int fileFolderLen2);
void compareFileAndFolder(char** argv, int option, char* folderPath, char** fileFolder, int fileFolderLen, char* fileName);
void getStrucutre(char* file1, char* file2, int argc, char** argv);
void Output(char* filePath1, char* filePath2, int option, char** argv);

#endif // FOLDER_H_INCLUDED
