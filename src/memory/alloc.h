#ifndef MEM_ALLOC_H
    #define MEM_ALLOC_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

    #include "../logger/logger.h"

    void* smalloc(unsigned int size);
    void* scalloc(unsigned int size);

#endif // MEM_ALLOC_H
