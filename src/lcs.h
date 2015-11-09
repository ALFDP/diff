#ifndef LCS_H
    #define LCS_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "logger/logger.h"

    unsigned int LCS_getLength(char **leftIn, char **rightIn, unsigned int leftSize, unsigned int rightSize);
    unsigned int** allocateSeqs(unsigned int xSize, unsigned int ySize);

#endif // LCS_H
