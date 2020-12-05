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
	char format[5];
	sprintf(format, "%%0%dx", size);
	sprintf(res, format, dec);
}


line_type get_line_type(char* line)
{
	line_type lt = NONE;
	for (int i = 0; i < MAX_LINE_SIZE; i++) {
		char c = line[i];
		if (c == '#' || c == '\n' || c == '\0') {
			return lt;
		}
		if (c == ':') lt = lt | LABEL;
		if (c == '$' && line[i+1] == 'i' && line[i+2] == 'm' && line[i+3] == 'm') {
			lt = lt | IMMEDIATE;
		}
		if (c == 'j' && line[i+1] == 'a' && line[i+2] == 'l') {
			lt = lt | JUMP;
		}
		if (c == 'b' && (line[i+1] == 'l' || line[i+1] == 'n' || line[i+1] == 'g')) {
			/* TODO: test that the string is not a label with same letters */
			lt = lt | BRANCH;
		}
	}
	return lt;
}

void switch_label(char *res, char *label)
{
	printf("changing label with value\n");
	char *label_runner = label;
	while (label_runner[0] != ' ' && label_runner[0] != '\t' && label_runner[0] != '#' && label_runner[0] != '\n') {
		label_runner++;
	}
	*label_runner = 0;
	get_address_from_label(label, res);
	res += ADDRESS_SIZE;
	*label_runner = '@';
}

void write_immediate(char *res, char *imm)
{
	printf("adding imm line\n");
	res[0] = '\n';
	res++;
	if (imm[0] == '0' && imm[1] == 'x') {
		while (imm[0] != ' ' && imm[0] != '\t' && imm[0] != '#' && imm[0] != '\n') {
			*res = *imm;
			res++;
			imm++;
		}
	} else {
		char *imm_runner = imm;
		while(imm_runner[0] != ' ' && imm_runner[0] != '\t' && imm_runner[0] != '#' && imm_runner[0] != '\n') {
			imm_runner++;
		}
		imm_runner[0] = 0;
		int dec = atoi(imm);
		printf("writing imm %d\n", dec);
		decimal_to_hex(dec, res, 5);
		res += 5;
		imm_runner[0] = '@';
	}
}

char parse_command(char *cmd, char *res, line_type lt)
{
	char is_writing = 1;
	printf("command to be parsed: %s", cmd);
	char *runner = cmd;
	if (lt == LABEL) {
		printf("got a label line");
		while(runner[0] != ':') { runner++; }
		runner ++;
		printf("after skipping: .%s.", runner);
		is_writing = 0;
	}
	/* parsing a regular command */
	char is_op = 1;
	while (runner[0] == ' ' || runner[0] == '\t') { runner++; }
	while (runner[0] != '#' && runner[0] != '\n') {
		while (runner[0] == ' ' || runner[0] == '\t') { runner++; }
		is_writing = 1;
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
			string_to_reg(runner, res);
			res = res + REGISTER_SIZE;
		}
		else {
			printf("got a imm const, ");
			if (lt & IMMEDIATE) {
				printf("should use it\n");
				write_immediate(res, runner);
			} else if (lt & (BRANCH | JUMP)) {
				printf("has jump/branch\n");
				switch_label(res, runner);
			} else {
				printf("shouldnt use it\n");
			}
			*res = '\n';
			*(res+1) = 0;
			return is_writing;
		}
		*word_ending = '@';
		runner = word_ending + 1;
		printf("line leftovers: %s\n", runner);
	}
	return is_writing;
	/* check if \0 is needed at the end of res */
}