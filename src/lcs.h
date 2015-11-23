#ifndef LCS_H
    #define LCS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "logger/logger.h"
    #include "memory/alloc.h"

    typedef int (*StringComparator)(const char*, const char*);

    unsigned int** LCS_buildMatrix(char **leftIn, char **rightIn, unsigned int leftSize, unsigned int rightSize, unsigned char isCaseSensitive);
    void** allocateMatrix(unsigned int xSize, unsigned int ySize, unsigned int elementSize, void* defaultValue);
    StringComparator getComparisonMethod(unsigned char isCaseSensitive);
    char** LCS_extract(unsigned int** matrix, char** leftIn, char** rightIn, int leftSize, int rightSize, unsigned char isCaseSensitive);
    void LCS_recursiveExtract(char** lcs, unsigned int** matrix, char** leftIn, char** rightIn, int leftSize, int rightSize,
                          StringComparator compare, unsigned int index);

#endif // LCS_H
