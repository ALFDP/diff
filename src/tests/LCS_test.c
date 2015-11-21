#include "logger/logger.h"
#include "lcs.h"

int main(int argc, char** argv)
{

    char **testIn1 = malloc(5 * sizeof(char*));
    char **testIn2 = malloc(4 * sizeof(char*));
    char **lcs = NULL;
    unsigned int sz1 = 5, sz2 = 4;
    unsigned int **matrix = NULL;
    int i;
    for(i = 0 ; i < sz1 ; i++)
        testIn1[i] = malloc(100 * sizeof(char));

    for(i = 0 ; i < sz2 ; i++)
        testIn2[i] = malloc(100 * sizeof(char));

    sprintf(testIn1[0], "How are you?");
    sprintf(testIn1[1], "I am fine,");
    sprintf(testIn1[2], "Hello,");
    sprintf(testIn1[3], "Hi,");
    sprintf(testIn1[4], "Thank you.");

    sprintf(testIn2[0], "How are you?");
    sprintf(testIn2[1], "I am fine.");
    sprintf(testIn2[2], "Hello,");
    sprintf(testIn2[3], "Hi,");

    matrix = LCS_buildMatrix(testIn1, testIn2, sz1, sz2, 0);

    lcs = LCS_extract(matrix, testIn1, testIn2, sz1, sz2, 0);

    free(matrix);

    return 0;
}
