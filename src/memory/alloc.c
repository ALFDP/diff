#include "alloc.h"
#pragma warning (disable : 4996)
/**

Safer memory treatments in order to abort redefining them everywhere

@author Aurélien DUVAL

**/

/**

Safely allocates memory

@param size The number of bytes to allocate

@return A pointer to the allocated memory or NULL in case of error

**/
void* smalloc(unsigned int size)
{
    void *array = NULL;
    char log[50] = "";

    if(size > 0)
    {
        array = (void*)malloc(size);

        if(array == NULL)
        {
            sprintf(log, "Error : Allocation of %d bytes has failed", size);
            logWrite(log, ERROR);
        }
    }

    return array;
}

/**

Safely allocates memory and initializes all segments to 0

@param size The number of bytes to allocate

@return A pointer to the allocated memory or NULL in case of error

**/
void* scalloc(unsigned int size)
{
    void *array = NULL;
    char log[50] = "";
	
	unsigned char defaultValue = 0x00;

    if(size > 0)
    {
        array = (void*)malloc(size);

		memcpy(array, &defaultValue, 1);

        if(array == NULL)
        {
            sprintf(log, "Error : Allocation of %d bytes has failed", size);
            logWrite(log, ERROR);
        }
    }

    return array;
}
