#include "data_memory_handler.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

static char word_buffers[MAX_ADDRESS][8];

void init_data_memory_handler()
{
    memset(word_buffers, '0', MAX_ADDRESS * 8);
}

int convert_string_num_to_integer(char *number)
{
    char tmp[8];
    strncpy(tmp, number, 8);
    if (tmp[0] == '0' && tmp[1] == 'x')
    { //hex
        return (int)strtol(tmp, NULL, 16);
    }
    else
    { // decimal
        return atoi(tmp);
    }
}

void add_data(char *data, char *address)
{
    int addr = convert_string_num_to_integer(address);
    if (addr >= MAX_ADDRESS) {
        fprintf(stderr, "got addrs %d. The largest addrs supported is %d'\n" ,addr ,MAX_ADDRESS);
		exit(1);
    }
    strncpy(word_buffers[addr], data, 8);
}

void add_data_from_line(char *line)
{
    char *line_runner = line;
    while (line_runner[0] == ' ' || line_runner[0] == '\t')
    {
        line_runner++;
    }
    // reached '.word'
    line_runner += 5;
    while (line_runner[0] == ' ' || line_runner[0] == '\t')
    {
        line_runner++;
    }
    // reached address
    char *address = malloc(9);
    int i = 0;
    while (line_runner[0] != ' ' && line_runner[0] != '\t')
    {
        address[i] = line_runner[0];
        line_runner++;
        i++;
    }
    while (line_runner[0] == ' ' || line_runner[0] == '\t')
    {
        line_runner++;
    }
    // reached data
    char *data = malloc(9);
    i = 0;
    while (line_runner[0] != ' ' && line_runner[0] != '\t' && line_runner[0] != 0 && line_runner[0] != '\n')
    {
        data[i] = line_runner[0];
        line_runner++;
        i++;
    }
    add_data(data, address);
}

void write_data_to_file(FILE *output_file)
{
    for (int i = 0; i < MAX_ADDRESS; i++)
    {
        int value = convert_string_num_to_integer(word_buffers[i]);
        char entry[9];
        sprintf(entry, "%08X", value);
        fputs(entry, output_file);
        fputs("\n", output_file);
    }
}