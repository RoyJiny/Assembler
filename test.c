#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char* argv) {
	char* s = (char*)malloc(50*sizeof(char));
	char* s1 = (char*)malloc(50 * sizeof(char));
	char* s2 = (char*)malloc(50 * sizeof(char));
	string_to_reg("$t2", s);
	s[4] = '\0';
	printf("%s\n", s);
	hex_to_binary("0xE4F", s1, 12);
	s1[12] = '\0';
	printf("%s\n", s1);
	string_to_opcode("lw", s2);
	s2[5] = '\0';
	printf("%s\n", s2);
	free(s);
	free(s1);
	free(s2);
}