#include "utils.h"
#include "label_handler.h"
#include "data_memory_handler.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_to_reg(char *reg, char *res)
{
	int reg_num = -1;
	if (!strcmp(reg, "$zero"))
		reg_num = ZERO;
	if (!strcmp(reg, "$imm"))
		reg_num = IMM;
	if (!strcmp(reg, "$v0"))
		reg_num = V0;
	if (!strcmp(reg, "$a0"))
		reg_num = A0;
	if (!strcmp(reg, "$a1"))
		reg_num = A1;
	if (!strcmp(reg, "$t0"))
		reg_num = T0;
	if (!strcmp(reg, "$t1"))
		reg_num = T1;
	if (!strcmp(reg, "$t2"))
		reg_num = T2;
	if (!strcmp(reg, "$t3"))
		reg_num = T3;
	if (!strcmp(reg, "$s0"))
		reg_num = S0;
	if (!strcmp(reg, "$s1"))
		reg_num = S1;
	if (!strcmp(reg, "$s2"))
		reg_num = S2;
	if (!strcmp(reg, "$gp"))
		reg_num = GP;
	if (!strcmp(reg, "$sp"))
		reg_num = SP;
	if (!strcmp(reg, "$fp"))
		reg_num = FP;
	if (!strcmp(reg, "$ra"))
		reg_num = RA;

	decimal_to_hex(reg_num, res, REGISTER_SIZE);
	return reg_num;
}

int string_to_opcode(char *opcode, char *res)
{
	int opcode_num = -1;
	if (!strcmp(opcode, "add"))
		opcode_num = ADD;
	if (!strcmp(opcode, "sub"))
		opcode_num = SUB;
	if (!strcmp(opcode, "and"))
		opcode_num = AND;
	if (!strcmp(opcode, "or"))
		opcode_num = OR;
	if (!strcmp(opcode, "xor"))
		opcode_num = XOR;
	if (!strcmp(opcode, "mul"))
		opcode_num = MUL;
	if (!strcmp(opcode, "sll"))
		opcode_num = SLL;
	if (!strcmp(opcode, "sra"))
		opcode_num = SRA;
	if (!strcmp(opcode, "srl"))
		opcode_num = SRL;
	if (!strcmp(opcode, "beq"))
		opcode_num = BEQ;
	if (!strcmp(opcode, "bne"))
		opcode_num = BNE;
	if (!strcmp(opcode, "blt"))
		opcode_num = BLT;
	if (!strcmp(opcode, "bgt"))
		opcode_num = BGT;
	if (!strcmp(opcode, "ble"))
		opcode_num = BLE;
	if (!strcmp(opcode, "bge"))
		opcode_num = BGE;
	if (!strcmp(opcode, "jal"))
		opcode_num = JAL;
	if (!strcmp(opcode, "lw"))
		opcode_num = LW;
	if (!strcmp(opcode, "sw"))
		opcode_num = SW;
	if (!strcmp(opcode, "reti"))
		opcode_num = RETI;
	if (!strcmp(opcode, "in"))
		opcode_num = IN;
	if (!strcmp(opcode, "out"))
		opcode_num = OUT;
	if (!strcmp(opcode, "halt"))
		opcode_num = HALT;

	decimal_to_hex(opcode_num, res, OPCODE_SIZE);
	return opcode_num;
}

void decimal_to_hex(int dec, char *res, int size)
{
	dec = dec & 0xFFFFF;
	char format[5];
	sprintf(format, "%%0%dX", size);
	sprintf(res, format, dec);
}

void skip_white_spaces(char **line)
{
	while ((*line)[0] == ' ' || (*line)[0] == '\t')
	{
		(*line)++;
	}
}

line_type get_line_type(char *line)
{
	line_type lt = NONE;
	int i = 0;
	while (line[i] == ' ' || line[i] == '\t')
	{
		i++;
	}
	if (line[i] == 0 || line[i] == '\n') return EMPTY_LINE;
	if (line[i] == '#') {
		return COMMENT;
	}
	if (line[i] == '.') {/*TODO: compare*/
		return WORD;
	}
	for (; i < MAX_LINE_SIZE; i++)
	{
		char c = line[i];
		if (c == '#' || c == '\n' || c == '\0')
		{
			return lt;
		}
		if (c == ':')
			lt = lt | LABEL;
		if (c == '$' && line[i + 1] == 'i' && line[i + 2] == 'm' && line[i + 3] == 'm')
		{
			lt = lt | IMMEDIATE;
		}
	}
	return lt;
}

/*TODO: add helper function s.a ignore_white_spaces()*/

void add_new_line(char **res)
{
	//printf("adding a new line\n");
	*res[0] = '\n';
	(*res)++;
}

/* add the value of the immediate constant as a new line */
void write_const(char **res, char *imm)
{
	if (imm[0] == '0' && imm[1] == 'x')
	{
		imm += 2;
		char hex_imm[IMMEDIATE_SIZE];
		int count = 0;
		while (imm[0] != ' ' && imm[0] != '\t' && imm[0] != '#' && imm[0] != '\n' && imm[0] != 0)
		{
			hex_imm[count] = imm[0];
			imm ++;
			count ++;
		}
		memset(*res, '0', IMMEDIATE_SIZE-count);
		strncpy(*res+(IMMEDIATE_SIZE-count), hex_imm, count);
	}
	else
	{
		char *imm_runner = imm;
		while (imm_runner[0] != ' ' && imm_runner[0] != '\t' && imm_runner[0] != '#' && imm_runner[0] != '\n' && imm_runner[0] != 0)
		{
			imm_runner++;
		}
		imm_runner[0] = 0;
		int dec = atoi(imm);
		decimal_to_hex(dec, *res, IMMEDIATE_SIZE);
		imm_runner[0] = '@';
	}
	(*res) += IMMEDIATE_SIZE;
}

/* if const is a label: add the address of the label as a new line.
 * else, writes the immediate to a new line*/
void write_immediate(char **res, char *label, int PC, line_type lt)
{
	//printf("writing jump/branch value as address value\n");
	char *label_runner = label;
	while (label_runner[0] != ' ' && label_runner[0] != '\t' && label_runner[0] != '#' && label_runner[0] != '\n')
	{
		label_runner++;
	}
	*label_runner = 0;
	if ((label[0] >= 48 && label[0] <= 57) || label[0] == '-')
	{ /*checks if the first char is a number*/
		write_const(res, label);
	}
	else
	{
		char is_label = get_address_from_label(label, *res);
		if (is_label)
		{
			//printf("the value was a label, written to output\n");
			(*res) += ADDRESS_SIZE;
			*label_runner = '@';
		}
	}
}

char parse_command(char *cmd, char *res, int PC, line_type lt)
{
	char is_writing = 1; /* will be 0 only if the line is only a label */
	//printf("\nnext command to be parsed: '%s'\n", cmd);
	char *runner = cmd;
	if (lt & LABEL)
	{
		//printf("line starts with a label\n");
		while (runner[0] != ':')
		{
			runner++;
		}
		runner++;
		//printf("leftover after skipping label: '%s'\n", runner);
		is_writing = 0;
	}
	/* parsing a regular command */
	char is_op = 1;
	while (runner[0] == ' ' || runner[0] == '\t')
	{
		runner++;
	}
	while (runner[0] != '#' && runner[0] != '\n' && runner[0] != 0 && runner[0] != '\r')
	{
		while (runner[0] == ' ' || runner[0] == '\t' || runner[0] == ',')
		{
			runner++;
		}
		is_writing = 1;
		char *word_ending = runner;
		while (word_ending[0] != ',' && word_ending[0] != ' ' && word_ending[0] != '\n' && word_ending[0] != '\t' && word_ending[0] != '\r')
		{
			word_ending++;
		}
		*word_ending = 0;
		if (is_op == 1)
		{
			//printf("parsing op code\n");
			int opcode = string_to_opcode(runner, res);
			handle_errors("parse command", "illegal opcode:", runner, opcode == -1);
			is_op = 0;
			res = res + OPCODE_SIZE;
			//printf("opcode number is %d\n", opcode);
			if (opcode == 15)
				lt = lt | JUMP;
			if (opcode >= 9 && opcode <= 14)
				lt = lt | BRANCH;
		}
		else if (runner[0] == '$')
		{
			//printf("parsing register\n");
			int reg = string_to_reg(runner, res);
			handle_errors("parse command", "illegal register:", runner, reg == -1);
			res = res + REGISTER_SIZE;
		}
		else
		{
			//printf("parsing an imm const, ");
			if (lt & IMMEDIATE)
			{
				//printf("line has jump/branch\n");
				add_new_line(&res);
				write_immediate(&res, runner, PC, lt);
			}
			*res = '\n';
			*(res + 1) = 0;
			return is_writing;
		}
		*word_ending = '@';
		runner = word_ending + 1;
		//printf("line leftovers: '%s'\n", runner);
	}
	return is_writing;
	/* check if \0 is needed at the end of res */
}