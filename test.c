#define _CRT_SECURE_NO_WARNINGS
#include "assembler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void main(int argc, char* argv) {
	FILE* file = fopen("C:/Users/ItamarS/source/repos/ASS/ASS/cmd.txt", "r");
	first_run(file);
	while (1) {}
}