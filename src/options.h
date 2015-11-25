#pragma once
#include "splitFileContents.h"

#define TRUE 1
#define FALSE 0

typedef enum OutputMode OutputMode;
enum OutputMode
{
	NORMAL_OUTPUT_MODE = 0x01,
	UNIFIED_OUTPUT_MODE = 0x02,

	SENSITIVE_CASE = 0x04,
	NO_SENSITIVE_CASE = 0x08,

	BRIEF_REPORT = 0x16,
	IDENTICAL_REPORT = 0x32
};


OutputMode getOptions(int argc, char** argv);
int getLongOption(char** argv, int* i, OutputMode* option, int* checkTab, int longChar);
void initTab(int* tab, int size);
int printReport(FileContent* file1, FileContent* file2, int option, OutputMode options, int caseSensitive);
void redirectOutput(OutputMode option, char* path1, char* path2, FileContent* file1, FileContent* file2);