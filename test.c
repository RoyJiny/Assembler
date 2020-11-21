#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char* argv) {
	//char s[] = (char*)malloc(100*sizeof(char));
	char *s1 = (char*)malloc(100 * sizeof(char));
	char s[] = "     add $sp, $sp, $imm, -3		# 1f: adjust stack for 3 items\n";
	memset(s1, 'a', 100);
	s1[49] = 0;
	parse_command(s, s1);
	printf("res is: %s", s1);
	//free(s);
	//free(s1);

	while (1) {}
}