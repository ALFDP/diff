#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

OutputMode getOptions(int argc, char** argv) {

	int length = strlen(argv[1]), i = 0, tabOption[2] = { 0,0 };
	OutputMode options = 0;

	for (i = 1; i < length; i++)
	{
		if (argv[1][i] == '-')
			continue;

		if (argv[1][i] == 'u')
		{
			if (tabOption[0] == FALSE)
			{
				options = options | UNIFIED_OUTPUT_MODE;
				tabOption[0] = TRUE;
			}
		}

		if (argv[1][i] == 'i')
		{
			if (tabOption[1] == FALSE)
			{
				options = options | NO_SENSITIVE_CASE;
				tabOption[1] = TRUE;
			}
		}
	}

	if (tabOption[0] == FALSE)
		options = options | UNIFIED_OUTPUT_MODE;
	if (tabOption[1] == FALSE)
		options = options | SENSITIVE_CASE;

	printf("Options: %d\n", options);

	return options;
}