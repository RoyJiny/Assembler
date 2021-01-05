#pragma once

#include <stdio.h>

#define NO_DATA "00000000"
#define MAX_ADDRESS 4096

/*
 * initialize data buffer. 
 * should be called before any use of the handler.
 */
void init_data_memory_handler();

/*
 * store the data and address in a buffer.
 * @param line: command line which contains the opcode '.word'.
 */
void add_data_from_line(char *line);

/*
 * write data from buffer to memory.
 * @param output_file: memory file.
 */
void write_data_to_file(FILE *output_file);