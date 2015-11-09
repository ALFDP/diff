#include "lcs.h"

/**

Counts the length of the longest common sequence

@param leftIn The left-handed sequence to compare, the older one
@param rightIn The right-handed sequence to compare, the newer one
@param leftSize The size of the left-handed sequence
@param rightSize The size of the right-handed sequence

@return The length of the longest common sequence

**/
unsigned int LCS_getLength(char **leftIn, char **rightIn, unsigned int leftSize, unsigned int rightSize)
{
    unsigned int **seqs = allocateSeqs(leftSize, rightSize);
    register unsigned int i, j;

    for (i = 1 ; i < leftSize ; i++)
    {
        for (j = 1 ; j < rightSize ; j++)
        {
            if (!strcmp(leftIn[i], rightIn[j]))
            {
                seqs[i][j] = seqs[i-1][j-1] + 1;
            }
            else
            {
                seqs[i][j] = seqs[i][j-1]>seqs[i-1][j]?seqs[i][j-1]:seqs[i-1][j];
            }
        }
    }
    return seqs[--i][--j];
}

/**

Allocates and initializes the LCS matrix

@param xSize The X axis size of the LCS matrix
@param ySize The Y axis size of the LCS matrix

@return The LCS matrix

**/
unsigned int** allocateSeqs(unsigned int xSize, unsigned int ySize)
{
    unsigned int **seqs = (unsigned int**)malloc(xSize * sizeof(unsigned int*));
    register unsigned int i, j;
    char log[100] = "";

    if(seqs == NULL)
    {
        sprintf(log, "First dimension sequence allocation has failed for size %u", xSize);
        logWrite(log, ERROR);
        return 0;
    }

    for (i = 0 ; i < xSize ; i++)
    {
        seqs[i] = (unsigned int*)malloc(ySize * sizeof(unsigned int));

        if(seqs == NULL)
        {
            sprintf(log, "Second dimension sequence allocation has failed for size %u at index %u", xSize, i);
            logWrite(log, ERROR);
            return 0;
        }

        seqs[i][0] = 0;
    }
    for (j = 0 ; j < ySize  ; j++)
    {
        seqs[0][j] = 0;
    }

    return seqs;
}
