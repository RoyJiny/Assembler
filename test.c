#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char* argv) {
	//char s[] = (char*)malloc(100*sizeof(char));
	char s[] = "     add $sp, $sp, $imm, -3		# 1f: adjust stack for 3 items\n";
	char *s1 = (char*)malloc(100 * sizeof(char));
	memset(s1, 'a', 100);
	s1[49] = 0;
	parse_command(s, s1);
	printf("res1 is: %s\n\n", s1);
	
	//free(s);
	free(s1);

	char label_cmd[] = "fib:\n";
	char *s2 = (char*)malloc(100 * sizeof(char));
	memset(s2, 'a', 100);
	s2[49] = 0;
	parse_command(label_cmd, s2);

	//free(s);
	free(s2);

	while (1) {}
}