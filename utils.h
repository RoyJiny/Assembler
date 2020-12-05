#pragma once


typedef enum { LABEL=1, IMMEDIATE=2, BRANCH=4, JUMP=8, NONE=0 } line_type;

line_type get_line_type(char* line);


/*
 * TODO: add description.
 *
 * @param register string to be converted , e.g $t1.
 * @param string which stored the return value, required size is 4.
 * @ret return the register number that was written to res
 */
int string_to_reg(char* reg, char* res);


/*
 * TODO: add description.
 *
 * @param opcode string to be converted , e.g add.
 * @param string which stored the return value.
 */
void string_to_opcode(char* opcode, char* res);

void decimal_to_hex(int dec, char *res, int size);

/*
 *edit cmd string to add a delimiter between each part of the command.
 *use | between each part, and a @ as the ending of the command.
 * @ret returns if the line was a label or not
*/
char parse_command(char *cmd, char *res, line_type lt);