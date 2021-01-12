#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "label_handler.h"
#include "assembler.h"
#include "defines.h"
#include "data_memory_handler.h"

void first_run(FILE *program)
{
	init_labels_array();
	int PC = 0;
	line_type lt;
	char line[MAX_LINE_SIZE];
	char *label = (char *)malloc(MAX_LABEL_SIZE * sizeof(char));
	char *addr = (char *)malloc(ADDRESS_SIZE * sizeof(char));
	while (fgets(line, MAX_LINE_SIZE, program) != NULL) /*get current line*/
	{
		char only_label = 0;
		lt = get_line_type(line);
		if (lt & LABEL)
		{
			only_label = extract_label_from_cmd(line, label);
			decimal_to_hex(PC, addr, ADDRESS_SIZE);
			insert_label(label, addr);
		}
		if (lt == COMMENT || only_label || lt == EMPTY_LINE)
			continue;
		if (lt & IMMEDIATE)
			PC++; /*immediate require an additional line*/
		PC++;
	}
	free(label);
	free(addr);
}

void second_run(FILE *program)
{
	int PC = 0;
	line_type lt;
	char line[MAX_LINE_SIZE];
	char cmd[2 * MAX_LINE_SIZE + 1];
	FILE *output_imem = fopen(IMEMIN_FILE, "w");
	FILE *output_dmem = fopen(DMEMIN_FILE, "w");

	init_data_memory_handler();

	while (fgets(line, MAX_LINE_SIZE, program) != NULL) /*get current line*/
	{
		lt = get_line_type(line);
		if (lt == COMMENT || lt == EMPTY_LINE)
			continue;
		if (lt == WORD)
		{
			add_data_from_line(line);
			continue;
		}
		char is_writing = parse_command(line, cmd, PC, lt);
		if (is_writing)
		{
			fputs(cmd, output_imem);
			PC++;
		}
	}
	write_data_to_file(output_dmem);
	fclose(output_imem);
	fclose(output_dmem);
	free_labels_array();
}
