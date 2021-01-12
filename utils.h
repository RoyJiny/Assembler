#pragma once

typedef enum
{
    NONE = 0,
    LABEL = 1,
    IMMEDIATE = 2,
    BRANCH = 4,
    JUMP = 8,
    COMMENT = 16,
    WORD = 32,
    EMPTY_LINE = 64
} line_type;

/*
 *
 * @param line: command line to be evaluated.
 * @ret return the appropriate line_type of @line.
 */
line_type get_line_type(char *line);

/*
 *
 * @param reg: string to be converted , e.g $t1.
 * @param res: stored the return value, required size is REGISTER_SIZE.
 * @ret return the register number that was written to res
 */
int string_to_reg(char *reg, char *res);

/*
 *
 * @param opcode: string to be converted , e.g add.
 * @param res: stored the return value, required size is OPCODE_SIZE.
 */
int string_to_opcode(char *opcode, char *res);

void decimal_to_hex(int dec, char *res, int size);

/* encode a command line.
 * @param cmd: command line.
 * @param res: stored the return value, required size is 5.
*/
char parse_command(char *cmd, char *res, int PC, line_type lt);