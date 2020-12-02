#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int string_to_reg(char* reg, char* res)
{
	int reg_num = 0;
	if (!strcmp(reg, "$zero")) reg_num = ZERO;
	if (!strcmp(reg, "$imm")) reg_num = IMM;
	if (!strcmp(reg, "$v0")) reg_num = V0;
	if (!strcmp(reg, "$a0")) reg_num = A0;
	if (!strcmp(reg, "$a1")) reg_num = A1;
	if (!strcmp(reg, "$t0")) reg_num = T0;
	if (!strcmp(reg, "$t1")) reg_num = T1;
	if (!strcmp(reg, "$t2")) reg_num = T2;
	if (!strcmp(reg, "$t3")) reg_num = T3;
	if (!strcmp(reg, "$s0")) reg_num = S0;
	if (!strcmp(reg, "$s1")) reg_num = S1;
	if (!strcmp(reg, "$s2")) reg_num = S2;
	if (!strcmp(reg, "$gp")) reg_num = GP;
	if (!strcmp(reg, "$sp")) reg_num = SP;
	if (!strcmp(reg, "$fp")) reg_num = FP;
	if (!strcmp(reg, "$ra")) reg_num = RA;

	decimal_to_hex(reg_num, res, REGISTER_SIZE);
	return reg_num;
}

void string_to_opcode(char* opcode, char* res) 
{
	int opcode_num = 0;
	if(!strcmp(opcode,"add")) opcode_num = ADD;
	if(!strcmp(opcode,"sub")) opcode_num = SUB;
	if(!strcmp(opcode,"and")) opcode_num = AND;
	if(!strcmp(opcode,"or")) opcode_num = OR;
	if(!strcmp(opcode,"xor")) opcode_num = XOR;
	if(!strcmp(opcode,"mul")) opcode_num = MUL;
	if(!strcmp(opcode,"sll")) opcode_num = SLL;
	if(!strcmp(opcode,"sra")) opcode_num = SRA;
	if(!strcmp(opcode,"srl")) opcode_num = SRL;
	if(!strcmp(opcode,"beq")) opcode_num = BEQ;
	if(!strcmp(opcode,"bne")) opcode_num = BNE;
	if(!strcmp(opcode,"blt")) opcode_num = BLT;
	if(!strcmp(opcode,"bgt")) opcode_num = BGT;
	if(!strcmp(opcode,"ble")) opcode_num = BLE;
	if(!strcmp(opcode,"bge")) opcode_num = BGE;
	if(!strcmp(opcode,"jal")) opcode_num = JAL;
	if(!strcmp(opcode,"lw")) opcode_num = LW;
	if(!strcmp(opcode,"sw")) opcode_num = SW;
	if(!strcmp(opcode,"reti")) opcode_num = LW;
	if(!strcmp(opcode,"in")) opcode_num = IN;
	if(!strcmp(opcode,"out")) opcode_num = OUT;
	if (!strcmp(opcode, "halt")) opcode_num = HALT;

	decimal_to_hex(opcode_num, res, OPCODE_SIZE);
}

void decimal_to_hex(int dec, char *res, int size)
{
	char format[5];	sprintf(format, "%%0%dx", size);	sprintf(res, format, dec);
}


line_type get_line_type(char* line)
{
	for (int i = 0; i < MAX_LINE_SIZE; i++) {
		char c = line[i];
		if (c == '#' || c == '\n' || c == '\0') {
			return NONE;
		}
		if (c == ':') return LABEL;
		if (c == '$') {
			if (strcmp("$imm", line + i) == 0) return IMMEDIATE;
		}
	}
	return NONE;
}

char parse_command(char *cmd, char *res)
{
	printf("command to be parsed: %s", cmd);
	if (get_line_type(cmd) == LABEL) {
		printf("got a label, trying to parse: \n");
		return 0;
	}
	/* parsing a regular command */
	char *runner = cmd;
	char is_op = 1;
	char has_imm = 0;
	while (runner[0] == ' ' || runner[0] == '\t') { runner++; }
	while (runner[0] != '#' && runner[0] != '\n') {
		char *word_ending = runner;
		while (word_ending[0] != ',' && word_ending[0] != ' ' && word_ending[0] != '\t') { word_ending++; }
		*word_ending = 0;
		if (is_op == 1) {
			printf("op code detected\n");
			string_to_opcode(runner, res);
			is_op = 0;
			res = res + OPCODE_SIZE;
		}
		else if (runner[0] == '$'){
			printf("reg detected\n");
			int reg = string_to_reg(runner, res);
			if (reg == IMM) {
				has_imm = 1;
			}
			res = res + REGISTER_SIZE;
		}
		else {
			printf("got a imm const, ");
			if (has_imm) {
				printf("should use it\n");
			} else {
				printf("shouldnt use it\n");
			}
		}
		*word_ending = '@';
		runner = word_ending + 1;
		while (runner[0] == ' ' || runner[0] == '\t') { runner++; }
		printf("line leftovers: %s\n", runner);
	}
	return 1;
	/* check if \0 is needed at the end of res */
}