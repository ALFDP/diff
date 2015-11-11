#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	printf("Entry point : \n");
	printf("1. Checking argc parameter:\n");

	if (argc != 3) {
		printf("ERROR: invalid argc parameter\n");
		return 1;
	}

	printf("Valid argc parameter ... \n");

	return 0;

}