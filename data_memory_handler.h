#pragma once

#include <stdio.h>

#define NO_DATA "00000000"
#define MAX_ADDRESS 4096

void init_data_memory_handler();

void add_data_from_line(char *line);

void add_data(char *data, char *address);

void write_data_to_file(FILE *output_file);