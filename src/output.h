#ifndef OUTPUT_H_INCLUDED

    #define OUTPUT_H_INCLUDED

    #include <stdio.h>
    #include <string.h>

    #include "lcs.h"

    typedef enum
    {
        FOUND = 0x03,
        FOUND_RIGHT = 0x02,
        FOUND_LEFT = 0x01,
        NOT_FOUND = 0x00
    } FileFinderMask;

    typedef enum
    {
        FULL = 0x07
        MODIF = 0x04,
        DELETION = 0x02,
        ADDITION = 0x01,
        NONE = 0x00
    }FileOperationMask;

    void print_edit(char** file_a, char** file_b, int idx_a, int idx_b, int nb_diff_a, int nb_diff_b, int edit_type);
    void print_edit_unified(char** file_a, int size_a, char** file_b, int size_b, int idx_a, int idx_b, int nb_diff_a, int nb_diff_b, int nb_context_lines);
    void print_label(char* mark, char* path);
    void print_lines(char** file, int start, int count, char symbol);
    void print_lines2(char** file, int size, int start, int count, char symbol);
    void print_range(int start, int count);
    int get_nb_lines_until_found(char** file, char* string, int start, int size, unsigned char ignore_case);

#endif // OUTPUT_H_INCLUDED
