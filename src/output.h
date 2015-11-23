#ifndef OUTPUT_H_INCLUDED

    #define OUTPUT_H_INCLUDED

    #include <stdio.h>
    #include <string.h>

    #include "lcs.h"

    typedef enum
    {
        FOUND = 0x03,
        FOUND_RIGHT = 0x02,
        FOUND_LEFT = 0x01,
        NOT_FOUND = 0x00
    } FileFinderMask;

    typedef enum
    {
        MOD = 0x03,
        DEL = 0x02,
        ADD = 0x01,
        NONE = 0x00
    }FileOperationMask;
	
	void printNormalDiff(char** leftFile, char** rightFile, unsigned int** lcs, unsigned int leftSize,
                        unsigned int rightSize, unsigned int lcsSize, unsigned char isCaseSensitive);
	void printUnifiedDiff(char* leftFilePath, char* rightFilePath, char** leftFile, unsigned int leftSize, 
						char** rightFile, unsigned int rightSize, char** lcs, unsigned int lcsSize, unsigned char isCaseSensitive) ;
    void printLabel(char* mark, char* path);
    void printEdit(char** leftFile, char** rightFile, unsigned int leftIndex, unsigned int rightIndex, unsigned int nbLeftDiffs,
					unsigned int nbRightDiffs,  FileOperationMask editOperation);
	void printUnifiedEdit(char** leftFile, unsigned int leftSize, char** rightFile, unsigned int rightSize, unsigned int leftIndex,
							unsigned int rightIndex, unsigned int nbLeftDiffs, unsigned int nbRightDiffs, unsigned int nbContextLines);
    void printLabel(char* mark, char* path);
	unsigned int getNbDiffLines(char** file, char* input, unsigned int start, unsigned int size, unsigned char isCaseSensitive);
    void printLines(char** file, unsigned int start, unsigned int count, char symbol);
    void printLines2(char** file, unsigned int size, unsigned int start, unsigned int count, char symbol);
    void printRange(unsigned int start, unsigned int count);

#endif // OUTPUT_H_INCLUDED
