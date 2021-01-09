#include "assembler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
	FILE* file = fopen("./assembly_files/circle.asm", "r");
	first_run(file);
	rewind(file);
	second_run(file);
	fclose(file);
	return 0;
}