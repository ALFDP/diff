#pragma once

#define TRUE 1
#define FALSE 0

typedef enum OutputMode OutputMode;
enum OutputMode
{
	NORMAL_OUTPUT_MODE = 0x01,
	UNIFIED_OUTPUT_MODE = 0x02,
	SENSITIVE_CASE = 0x04,
	NO_SENSITIVE_CASE = 0x08
};


OutputMode getOptions(int argc, char** argv);