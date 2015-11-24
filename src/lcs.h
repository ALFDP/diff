#ifndef LCS_H
    #define LCS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "logger/logger.h"
    #include "memory/alloc.h"


    typedef int (*StringComparator)(const char*, const char*);

    unsigned int** LCS_buildMatrix(char **leftIn, char **rightIn, unsigned int leftSize, unsigned int rightSize, unsigned char isCaseSensitive);
    void** allocateMatrix(unsigned int xSize, unsigned int ySize, unsigned int elementSize);
    void freeMatrix(void ***matrix, unsigned int xSize);
    StringComparator getComparisonMethod(unsigned char isCaseSensitive);
    char** LCS_extract(unsigned int *lcsSize, unsigned int** matrix, char*** leftIn, char*** rightIn,
                    int leftSize, int rightSize, unsigned char isCaseSensitive);
    unsigned int LCS_recursiveExtract(char*** lcs, unsigned int** matrix, char*** leftIn, char*** rightIn, int leftSize, int rightSize,
                          StringComparator compare, unsigned char isFirstCall);

#endif // LCS_H
