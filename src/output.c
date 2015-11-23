
#include "output.h"

void printNormalDiff(char** leftFile, char** rightFile, unsigned int** lcs, unsigned int leftSize,
                        unsigned int rightSize, unsigned int lcsSize
                         /*Options* options*/)
{
    StringComparator compare = getComparisonMethod(options->ignore_case_content);
    FileFinderMask fileFinder = NOT_FOUND;
    unsigned int i, leftIndex, rightIndex;
    unsigned int nbLeftDiffs;
    unsigned int nbRightDiffs;

    for (i = 0, leftIndex = 0, rightIndex = 0 ; i < lcsSize ; i++, leftIndex++, rightIndex++ )
    {
        nbLeftDiffs = 0;
        nbRightDiffs = 0;

		/* found in left or in right file or none of them */
        fileFinder = !compare(lcs[i], leftFile[leftIndex])?FOUND_LEFT:NOT_FOUND
                        | !compare(lcs[i], rightFile[rightIndex])?FOUND_RIGHT:NOTFOUND;

        if (!fileFinder == NOT_FOUND)
        {
			/* counting successive diffs */
            nbLeftDiffs = get_nb_lines_until_found(leftFile, lcs[i], leftIndex, leftSize, options->ignore_case_content);
            nbRightDiffs = get_nb_lines_until_found(rightFile, lcs[i], rightIndex, rightSize, options->ignore_case_content);

            print_edit(leftFile, rightFile, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, fileFinder);
        }

		/* repositionning cursors in both files */
        leftIndex += nbLeftDiffs;
        rightIndex += nbRightDiffs;
    }

	/* Last execution for the last lines [could be refactored easily by using a function] */
    if (leftIndex < leftSize || rightIndex < rightSize)
    {
        nbLeftDiffs = leftSize - leftIndex;
        nbRightDiffs = rightSize - rightIndex;

        edit_type = (rightIndex < rightSize) + (leftIndex < leftSize) * 2;

        print_edit(leftFile, rightFile, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, fileFinder);
    }

}

/* not fully modified but same algo as previously at 99% */
void printUnifiedDiff(char** leftFile, unsigned int leftSize, char** rightFile, unsigned int rightSize, char** lcs, unsigned int lcsSize, Options* options) {

    FileFinderMask fileFinder = NOT_FOUND;
    unsigned int i, leftIndex = 0, rightIndex = 0;
    unsigned int nbLeftDiffs;
    unsigned int nbRightDiffs;
    unsigned int leftHunkSize = 0;
    unsigned int rightHunkSize = 0;
    unsigned int leftStarter = 0;
    unsigned int rightStarter = 0;

    print_label("---", options->path_a);
    print_label("+++", options->path_b);

    for (i = 0 ; i < lcsSize ; i++, leftIndex++,rightIndex++)
    {
        nbLeftDiffs = 0;
        nbRightDiffs = 0;

        fileFinder = !compare(lcs[i], leftFile[leftIndex])?FOUND_LEFT:NOT_FOUND
                        | !compare(lcs[i], rightFile[rightIndex])?FOUND_RIGHT:NOTFOUND;

        if (!found_in_a || !found_in_b)
        {
            nbLeftDiffs = get_nb_lines_until_found(leftFile, lcs[i], leftIndex, leftSize, options->ignore_case_content);
            nbRightDiffs = get_nb_lines_until_found(rightFile, lcs[i], rightIndex, rightSize, options->ignore_case_content);

            leftStarter = fmax(1, leftIndex+1 - options->nb_context_lines);
            rightStarter = fmax(1, rightIndex+1 - options->nb_context_lines);
            leftHunkSize = nbLeftDiffs + options->nb_context_lines * 2;
            rightHunkSize = nbRightDiffs + options->nb_context_lines * 2;

//            end = fmaxf(leftIndex + nbLeftDiffs, rightIndex + nbRightDiffs) + options->nb_context_lines;
//            start = fminf(leftIndex, rightIndex) - options->nb_context_lines;

            print_edit_unified(leftFile, leftSize, rightFile, rightSize, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, options->nb_context_lines);
        }

        rightIndex += nbRightDiffs;
        leftIndex += nbLeftDiffs;
    }

    /* La boucle précédente s'arrête quand la dernière ligne lcs a été trouvée
    Ici on traite donc les éventuelles modifications faites en fin de fichier, après la dèrnire ligne lcs*/

    if (leftIndex < leftSize || rightIndex < rightSize)
    {
        nbLeftDiffs = leftSize - leftIndex;
        nbRightDiffs = rightSize - rightIndex;

            print_edit_unified(leftFile, leftSize, rightFile, rightSize, leftIndex, rightIndex, nbLeftDiffs, nbRightDiffs, options->nb_context_lines);
    }

}

/* not rewritten, so it needs to be */
void print_label(char* mark, char* path) {

    char buffer[512] = {};
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

void print_edit(char** leftFile, char** rightFile, unsigned int leftIndex, unsigned int rightIndex, unsigned int nb_diff_a, unsigned int nb_diff_b, unsigned int edit_type) {

    char edit_code[] = {'a', 'd', 'c'};

    print_range(leftIndex, nb_diff_a);
    putchar(edit_code[edit_type-1]);
    print_range(rightIndex, nb_diff_b);

    putchar('\n');

    if (edit_type == ADDITION)
        print_lines(rightFile, rightIndex, nb_diff_b, '>');
    else if (edit_type == DELETION)
        print_lines(leftFile, leftIndex, nb_diff_a, '<');
    else if (edit_type == MODIFICATION)
    {
        print_lines(leftFile, leftIndex, nb_diff_a, '<');
        puts("---");
        print_lines(rightFile, rightIndex, nb_diff_b, '>');
    }

}

void print_edit_unified(char** leftFile, unsigned int leftSize, char** rightFile, unsigned int rightSize, unsigned int leftIndex, unsigned int rightIndex, unsigned int nb_diff_a, unsigned int nb_diff_b, unsigned int nb_context_lines) {

    unsigned int nb_context_lines_before = fminf(nb_context_lines, leftIndex);
    unsigned int nb_context_lines_after = fminf(nb_context_lines, leftSize - (leftIndex + nb_diff_a) );
    printf("context_lines_before: %d\n", nb_context_lines_before);
    printf("context_lines_after: %d\n", nb_context_lines_after);

    unsigned int start_hunk_a = leftIndex - nb_context_lines_before;
    unsigned int start_hunk_b = rightIndex - nb_context_lines_before;
    unsigned int end_hunk_a = leftIndex + nb_diff_a + nb_context_lines_after;
    unsigned int end_hunk_b = rightIndex + nb_diff_b + nb_context_lines_after;

    printf("@@ -%d,%d +%d,%d @@\n", start_hunk_a + 1, end_hunk_a - start_hunk_a, start_hunk_b + 1, end_hunk_b - start_hunk_b);

    print_lines2(leftFile, leftSize, start_hunk_a, nb_context_lines_before, ' ');
    print_lines2(leftFile, leftSize, leftIndex, nb_diff_a, '-');
    print_lines2(rightFile, rightSize, rightIndex, nb_diff_b, '+');
    print_lines2(leftFile, leftSize, leftIndex + nb_diff_a, nb_context_lines_after, ' ');

}

unsigned int get_nb_lines_until_found(char** file, char* string, unsigned int start, unsigned int size, bool ignore_case_content) {

    unsigned int i;

    if(ignore_case_content)
        for (i = 0 ; i < size && strcasecmp(file[i + start], string) != 0 ; i++ );
    else
        for (i = 0 ; i < size && strcmp(file[i + start], string) != 0 ; i++ );

    return i;

}
/**
    Affiche les lignes de l'intervalle [start, start + count-1]
**/
void print_lines(char** file, unsigned int start, unsigned int count, char symbol) {

    unsigned int i;
    for (i = 0 ; i < count ; i++ )
        printf("%c %s", symbol, file[start + i]);
}

void print_lines2(char** file, unsigned int size, unsigned int start, unsigned int count, char symbol) {

    unsigned int i;
    for (i = start ; i < (start + count) && i < size ; i++ )
        printf("%c %s", symbol, file[i]);
}

void print_range(unsigned int start, unsigned int count) {

    if (count == 0)
        printf("%d", start); // Ligne après laquelle une modif a été faite
    else if (count == 1)
        printf("%d", start + 1); // Numéro de ligne réel
    else
        printf("%d,%d", start + 1, start + count);
}
