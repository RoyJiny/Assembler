#pragma once
#include "defines.h"

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


/*
 * convert num from decimal to binary.
 *
 * @param num in decimal representation.
 * @param string which stored the return value.
 */
void decimal_to_binary(int num, char* res, int size);

/*
 * convert num from hexadecimal to binary.
 *
 * @param num in hexadecimal representation - e.g 0xFF.
 * @param string which stored the return value.
 */
void hex_to_binary(char* num, char* res, int size);