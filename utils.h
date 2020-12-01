#pragma once
#include "defines.h"

#define MAX_LABEL_SIZE 50
#define OPCODE_SIZE 2
#define REGISTER_SIZE 1

/*
 * TODO: add description.
 *
 * @param register string to be converted , e.g $t1.
 * @param string which stored the return value, required size is 4.
 */
void string_to_reg(char* reg, char* res);


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
*/
void parse_command(char *cmd, char *res);