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
    unsigned int **matrix = (unsigned int**) allocateMatrix(leftSize+1, rightSize+1, sizeof(unsigned int));
    StringComparator compare = getComparisonMethod(isCaseSensitive);
    register unsigned int i, j;

    for (i = 0 ; i < leftSize ; i++)
    {
        for (j = 0 ; j < rightSize ; j++)
        {
            if (!compare(leftIn[i], rightIn[j]))
            {
                matrix[i+1][j+1] = matrix[i][j] + 1;
            }
            else
            {
                matrix[i+1][j+1] = matrix[i+1][j]>matrix[i][j+1]?matrix[i+1][j]:matrix[i][j+1];
            }
        }
    }
    return matrix;
}

/**

Extracts the LCS matrix as a string array

@param lcsSize The lcs array size
@param matrix The lcs matrix
@param leftIn The older file of both
@param rightIn The newer file of both
@param leftSize The left file buffered array size
@param rightSize The right file buffered array size
@param isCaseSensitive Check string using case sensitive or insensitive process

**/
char** LCS_extract(unsigned int *lcsSize, unsigned int** matrix, char*** leftIn, char*** rightIn,
                    int leftSize, int rightSize, unsigned char isCaseSensitive)
{
    StringComparator compare = getComparisonMethod(isCaseSensitive);
    char **lcs = (char**)scalloc((leftSize>rightSize?leftSize:rightSize) * sizeof(char*));

    *lcsSize = LCS_recursiveExtract(&lcs, matrix, leftIn, rightIn, leftSize, rightSize, compare, 1);

    return lcs;
}

/**

Extracts the LCS matrix as a string array - recursive hidden form

@param lcs The extracted lcs array
@param matrix The lcs matrix
@param leftIn The older file of both
@param rightIn The newer file of both
@param leftSize The left file buffered array size
@param rightSize The right file buffered array size
@param compare The string comparison function
@param isFirstCall The flag which specifies if this is the head of the recursive tree

**/
unsigned int LCS_recursiveExtract(char*** lcs, unsigned int** matrix, char*** leftIn, char*** rightIn, int leftSize, int rightSize,
                          StringComparator compare, unsigned char isFirstCall)
{
    static unsigned int i = 0;

    if(isFirstCall)
    {
        i = 0;
    }

    if (leftSize < 1 || rightSize < 1)
        return i;

    if (compare((*leftIn)[leftSize - 1], (*rightIn)[rightSize - 1]) == 0)
    {
        LCS_recursiveExtract(lcs, matrix, leftIn, rightIn, leftSize - 1, rightSize - 1, compare, 0);
        (*lcs)[i] = (*leftIn)[leftSize - 1];
        i++;
    }

    else if (matrix[leftSize][rightSize] == matrix[leftSize][rightSize - 1])
    {
        LCS_recursiveExtract(lcs, matrix, leftIn, rightIn, leftSize, rightSize - 1, compare, 0);
    }

    else
    {
        LCS_recursiveExtract(lcs, matrix, leftIn, rightIn, leftSize - 1, rightSize, compare, 0);
    }
    return i;
}

/**

Allocates and initializes a matrix

@param xSize The X axis size of the matrix
@param ySize The Y axis size of the matrix
@param elementSize The size of one single element

@return The allocated matrix

**/
void** allocateMatrix(unsigned int xSize, unsigned int ySize, unsigned int elementSize)
{
    void **matrix = NULL;
    register unsigned int i;

    matrix = scalloc(xSize * sizeof(void*));

    for (i = 0 ; i < xSize ; i++)
    {
        if(ySize > 0)
        {
            matrix[i] = (void*)scalloc(ySize * elementSize);
        }
    }

    return matrix;
}

/**

Cleans a matrix

@param matrix The pointer to the matrix to free
@param ySize The Y axis size of the matrix

**/
void freeMatrix(void ***matrix, unsigned int xSize)
{
    register unsigned int i;

    for (i = 0 ; i < xSize ; i++)
    {
        free((*matrix)[i]);
    }

    free(*matrix);
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
