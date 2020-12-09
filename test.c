#include "assembler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
	FILE* file = fopen("./cmd.txt", "r");
	printf("running first run\n");
	first_run(file);
	rewind(file);
	printf("\nrunning second run\n");
	second_run(file);
	fclose(file);
	return 0;
}