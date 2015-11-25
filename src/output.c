#include "output.h"

/**

Defines the LCS algorithm output treatments.

@author Aurélien DUVAL

**/

/**

Prints the standard diff output

@param leftFile The older file of both
@param rightFile The newer file of both
@param lcs The extracted lcs matrix
@param lcsSize The lcs array size
@param leftSize The left file buffered array size
@param rightSize The right file buffered array size

**/
void printStandardDiff(char** leftFile, char** rightFile, char** lcs, unsigned int lcsSize, unsigned int leftSize,
                        unsigned int rightSize, unsigned char isCaseSensitive)
{
    StringComparator compare = getComparisonMethod(isCaseSensitive);
    FileFinderMask fileFinder = NOT_FOUND;
    unsigned int i, leftIndex, rightIndex;
    unsigned int nbLeftDiffs;
    unsigned int nbRightDiffs;

    for (i = 0, leftIndex = 0, rightIndex = 0 ; i < lcsSize ; i++, leftIndex++, rightIndex++ )
    {
        nbLeftDiffs = 0;
        nbRightDiffs = 0;

        fileFinder = (compare(lcs[i], leftFile[leftIndex])?NOT_FOUND: FOUND_LEFT)
                        | (compare(lcs[i], rightFile[rightIndex])?NOT_FOUND:FOUND_RIGHT);

        if (fileFinder != NOT_FOUND)
        {
            nbLeftDiffs = getNbDiffLines(leftFile, lcs[i], leftIndex, leftSize, isCaseSensitive);
            nbRightDiffs = getNbDiffLines(rightFile, lcs[i], rightIndex, rightSize, isCaseSensitive);

            printEdit(leftFile, rightFile, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, fileFinder);
        }

        leftIndex += nbLeftDiffs;
        rightIndex += nbRightDiffs;
    }

    if (leftIndex < leftSize || rightIndex < rightSize)
    {
        nbLeftDiffs = leftSize - leftIndex;
        nbRightDiffs = rightSize - rightIndex;

        fileFinder = (leftIndex < leftSize?FOUND_LEFT:NOT_FOUND) | (rightIndex < rightSize?FOUND_RIGHT:NOT_FOUND);

        printEdit(leftFile, rightFile, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, fileFinder);
    }

}

/**

Prints the standard diff output

@param leftFilePath The left file's path
@param rightFilePath The right file's path
@param leftFile The older file of both
@param leftSize The left file buffered array size
@param rightFile The newer file of both
@param rightSize The right file buffered array size
@param lcs The extracted lcs matrix
@param lcsSize The lcs array size
@param isCaseSensitive Check string using case sensitive or insensitive process
@param nbContextLines The number of context lines you want to show before and after each output

**/
void printUnifiedDiff(char* leftFilePath, char* rightFilePath, char** leftFile, unsigned int leftSize,
						char** rightFile, unsigned int rightSize, char** lcs, unsigned int lcsSize,
						 unsigned char isCaseSensitive, unsigned int nbContextLines)
{
	StringComparator compare = getComparisonMethod(isCaseSensitive);
    FileFinderMask fileFinder = NOT_FOUND;
    unsigned int i, leftIndex = 0, rightIndex = 0;
    unsigned int nbLeftDiffs;
    unsigned int nbRightDiffs;

    printLabel("---", leftFilePath);
    printLabel("+++", rightFilePath);
    printf("\n");

    for (i = 0 ; i < lcsSize ; i++, leftIndex++,rightIndex++)
    {
        nbLeftDiffs = 0;
        nbRightDiffs = 0;

        fileFinder = (compare(lcs[i], leftFile[leftIndex])?NOT_FOUND: FOUND_LEFT)
                        | (compare(lcs[i], rightFile[rightIndex])?NOT_FOUND:FOUND_RIGHT);

		if (fileFinder != NOT_FOUND)
        {
            nbLeftDiffs = getNbDiffLines(leftFile, lcs[i], leftIndex, leftSize, isCaseSensitive);
            nbRightDiffs = getNbDiffLines(rightFile, lcs[i], rightIndex, rightSize, isCaseSensitive);

            printUnifiedEdit(leftFile, leftSize, rightFile, rightSize, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, nbContextLines);
        }

        rightIndex += nbRightDiffs;
        leftIndex += nbLeftDiffs;
    }

    if (leftIndex < leftSize || rightIndex < rightSize)
    {
        nbLeftDiffs = leftSize - leftIndex;
        nbRightDiffs = rightSize - rightIndex;

        fileFinder = (leftIndex < leftSize?FOUND_LEFT:NOT_FOUND) | (rightIndex < rightSize?FOUND_RIGHT:NOT_FOUND);

        printUnifiedEdit(leftFile, leftSize, rightFile, rightSize, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, nbContextLines);
    }

}

/* TODO */
void printLabel(char* mark, char* path)
{

    char buffer[512];
    struct tm *info_time = NULL;
    time_t raw_time = 0;
    time(&raw_time);
    info_time = localtime(&raw_time);
    strftime(buffer, 512, "%Y-%m-%d %H:%M:%S", info_time);

    printf("%s %s\t", mark, path);

    #ifdef _WIN32
        printf("%s.%I64u ", buffer, (unsigned long long)raw_time);
    #else
        printf("%s.%llu ", buffer, (unsigned long long)raw_time);
    #endif

    strftime(buffer, 512, "%z", info_time);
    printf("%s\n", buffer);

}

/**

Prints the standard diff edition part of the output

@param leftFile The older file of both
@param rightFile The newer file of both
@param leftIndex The line number of the virtual cursor in left file
@param rightIndex The line number of the virtual cursor in right File
@param nbLeftDiffs Detected consecutive diffs number on the left file
@param lcsSize Detected consecutive diffs number on therightt file
@param fileFinder The binary mask of the result of the research

**/
void printEdit(char** leftFile, char** rightFile, unsigned int leftIndex, unsigned int rightIndex, unsigned int nbLeftDiffs,
				unsigned int nbRightDiffs, FileFinderMask fileFinder)
{

    char editCode[] = {'a', 'd', 'c'};

    printRange(leftIndex, nbLeftDiffs);
    printf("%c", editCode[fileFinder-1]);
    printRange(rightIndex, nbRightDiffs);

    printf("\n");

    /// ADD
    if (fileFinder == FOUND_LEFT)
        printLines(rightFile, rightIndex, nbRightDiffs, '>');
    /// DEL
    else if (fileFinder == FOUND_RIGHT)
        printLines(leftFile, leftIndex, nbLeftDiffs, '<');
    /// MOD
    else if (fileFinder == FOUND_BOTH)
    {
        printLines(leftFile, leftIndex, nbLeftDiffs, '<');
        printf("\n---\n");
        printLines(rightFile, rightIndex, nbRightDiffs, '>');
    }

     printf("\n");

}

/**

Prints the unified diff edition part of the output

@param leftFile The older file of both
@param leftSize The left file buffered array size
@param rightFile The newer file of both
@param leftSize The right file buffered array size
@param leftIndex The line number of the virtual cursor in left file
@param rightIndex The line number of the virtual cursor in right File
@param nbLeftDiffs Detected consecutive diffs number on the left file
@param lcsSize Detected consecutive diffs number on therightt file
@param nbContextLines The number of context lines you want to show before and after each output

**/
void printUnifiedEdit(char** leftFile, unsigned int leftSize, char** rightFile, unsigned int rightSize, unsigned int leftIndex,
						unsigned int rightIndex, unsigned int nbLeftDiffs, unsigned int nbRightDiffs, unsigned int nbContextLines)
{

    unsigned int nbContextLinesBefore = nbContextLines<leftIndex?nbContextLines:leftIndex;
    unsigned int nbContextLinesAfter = leftSize - leftIndex + nbLeftDiffs;
	nbContextLinesAfter = nbContextLines<nbContextLinesAfter?nbContextLines:nbContextLinesAfter;
	unsigned int leftStartHunk = leftIndex - nbContextLinesBefore;
    unsigned int rightStartHunk = rightIndex - nbContextLinesBefore;
    unsigned int leftEndHunk = leftIndex + nbLeftDiffs + nbContextLinesAfter;
    unsigned int rightEndHunk = rightIndex + nbRightDiffs + nbContextLinesAfter;
    printf("context_lines_before: %d\n", nbContextLinesBefore);
    printf("context_lines_after: %d\n", nbContextLinesAfter);

    printf("@@ -%d,%d +%d,%d @@\n", leftStartHunk + 1, leftEndHunk - leftStartHunk, rightStartHunk + 1, rightEndHunk - rightStartHunk);

    printLines2(leftFile, leftSize, leftStartHunk, nbContextLinesBefore, ' ');
    printLines2(leftFile, leftSize, leftIndex, nbLeftDiffs, '-');
    printLines2(rightFile, rightSize, rightIndex, nbRightDiffs, '+');
    printLines2(leftFile, leftSize, leftIndex + nbLeftDiffs, nbContextLinesAfter, ' ');
    printf("\n");

}

unsigned int getNbDiffLines(char** file, char* input, unsigned int start, unsigned int size, unsigned char isCaseSensitive)
{

    unsigned int i;
	StringComparator compare = getComparisonMethod(isCaseSensitive);

    for (i = 0 ; i < size && compare(file[i + start], input) != 0 ; i++ );

    return i;

}

void printLines(char** file, unsigned int start, unsigned int count, char symbol)
{

    unsigned int i;
    for (i = 0 ; i < count ; i++ )
        printf("%c %s\n", symbol, file[start + i]);
}

void printLines2(char** file, unsigned int size, unsigned int start, unsigned int count, char symbol)
{

    unsigned int i;
    for (i = start ; i < (start + count) && i < size ; i++ )
        printf("%c %s\n", symbol, file[i]);
}

void printRange(unsigned int start, unsigned int count)
{

    if (!count)
        printf("%d", start);
    else if (count != 1)
		printf("%d,%d", start + 1, start + count);
	else
        printf("%d", start + 1);
}
