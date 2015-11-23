#include "lcs.h"
#pragma warning (disable : 4996)


/**

Defines the LCS algorithm treatments.

@author Aurélien DUVAL
@see https://en.wikipedia.org/wiki/Longest_common_subsequence_problem

**/

/**

Builds the LCS matrix

@param leftIn The left-handed sequence to compare, the older one
@param rightIn The right-handed sequence to compare, the newer one
@param leftSize The size of the left-handed sequence
@param rightSize The size of the right-handed sequence

@return The LCS matrix

**/
unsigned int** LCS_buildMatrix(char **leftIn, char **rightIn, unsigned int leftSize, unsigned int rightSize, unsigned char isCaseSensitive)
{
	unsigned int defaultValue = 0;
    unsigned int **matrix = (unsigned int**) allocateMatrix(leftSize+1, rightSize+1, sizeof(unsigned int), &defaultValue);
    StringComparator compare = getComparisonMethod(isCaseSensitive);
    register unsigned int i, j;

    for (i = 1 ; i < leftSize ; i++)
    {
        for (j = 1 ; j < rightSize ; j++)
        {
            if (!compare(leftIn[i], rightIn[j]))
            {
                matrix[i][j] = matrix[i-1][j-1] + 1;
            }
            else
            {
                matrix[i][j] = matrix[i][j-1]>matrix[i-1][j]?matrix[i][j-1]:matrix[i-1][j];
            }
        }
    }
    return matrix;
}

char** LCS_extract(unsigned int** matrix, char** leftIn, char** rightIn, int leftSize, int rightSize, unsigned char isCaseSensitive)
{
    StringComparator compare = getComparisonMethod(isCaseSensitive);
	int taille = leftSize > rightSize ? leftSize : rightSize;
    char **lcs = (char**)malloc((leftSize>rightSize?leftSize:rightSize) * sizeof(char*));

    LCS_recursiveExtract(&lcs, matrix, leftIn, rightIn, leftSize, rightSize, compare, 0);

    return lcs;
}

void LCS_recursiveExtract(char*** lcs, unsigned int** matrix, char** leftIn, char** rightIn, int leftSize, int rightSize,
                          StringComparator compare, unsigned int index)
{
    if (leftSize == 0 || rightSize == 0)
        return;

    if (compare(leftIn[leftSize - 1], rightIn[rightSize - 1]) == 0)
    {
        LCS_recursiveExtract(lcs, matrix, leftIn, rightIn, leftSize - 1, rightSize - 1, compare, index);
        (*lcs)[index] = leftIn[leftSize - 1];
    }
    else if (matrix[leftSize][rightSize] != matrix[leftSize][rightSize - 1])
    {
        LCS_recursiveExtract(lcs, matrix, leftIn, rightIn, leftSize, rightSize - 1, compare, index);
    }

    else
    {
        LCS_recursiveExtract(lcs, matrix, leftIn, rightIn, leftSize - 1, rightSize, compare, index);
    }
}

/**

Allocates and initializes a matrix

@param xSize The X axis size of the matrix
@param ySize The Y axis size of the matrix
@param elementSize The size of one single element
@param defaultValue The defaultValue to apply to each element

@return The allocated matrix

**/
void** allocateMatrix(unsigned int xSize, unsigned int ySize, unsigned int elementSize, void* defaultValue)
{
    void **matrix = NULL;
	unsigned int *mat = NULL;
    register unsigned int i, j;

    matrix = smalloc(xSize * sizeof(void*));

    for (i = 0 ; i < xSize ; i++)
    {
        if(ySize > 0)
        {
            matrix[i] = (void*)smalloc(ySize * elementSize);
        }
    }

    for (j = 0 ; j < ySize  ; j++)
    {
		memcpy((void**)(&(matrix[i])) + j * elementSize, defaultValue, elementSize);
    }

    return matrix;
}

/**

Returns the correct string comparator

@param isCaseSensitive defines if comparison will or will not be case-sensitive.

@return The corresponding input comparator.

**/
StringComparator getComparisonMethod(unsigned char isCaseSensitive)
{
    return isCaseSensitive?strcmp:stricmp;
}
