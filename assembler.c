#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "utils.h"
#include "label_handler.h"
#include "assembler.h"


void first_run(FILE* proggram) 
{
	init_labels_array(); /*TODO: free somewhere*/
	int PC = 0;
	line_type lt;
	char line[MAX_LINE_SIZE];
	char *label = (char*)malloc(MAX_LABEL_SIZE * sizeof(char));
	char *addr  = (char*)malloc(ADDRESS_SIZE * sizeof(char));
	while (fgets(line, MAX_LINE_SIZE, proggram) != NULL) /*get current line*/
	{
		lt = get_line_type(line);
		if (lt == LABEL)
		{
			extract_label_from_cmd(line, label);
			decimal_to_hex(PC, addr, ADDRESS_SIZE);
			insert_label(label, addr);
			printf("the label from extraction: %s, and addr: %s.\n", label,addr);
		}
		if (lt == IMMEDIATE) PC++; /*immidiate require an additional line*/
		PC++;
	}
	free(label);
	free(addr);
}




