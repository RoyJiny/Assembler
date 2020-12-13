#include "data_memory_handler.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define NO_DATA "00000000"

static int highest_address = 0;

typedef struct _node
{
    int address;
    char *data;
    struct _node *next;
} node;

node *addresses_start = NULL;
node *addresses_current = NULL;

int convert_string_num_to_integer(char *number)
{
    if (number[0] == '0' && number[1] == 'x')
    { //hex
        return (int)strtol(number, NULL, 16);
    }
    else
    { // decimal
        return atoi(number);
    }
}

void add_data(char *data, char *address)
{
    int addr = convert_string_num_to_integer(address);
    if (addr > highest_address)
    {
        highest_address = addr;
    }
    node new_addr = {addr, data, NULL};
    if (addresses_start == NULL)
    {
        *addresses_start = new_addr;
        *addresses_current = new_addr;
    }
    else
    {
        addresses_current->next = &new_addr;
        addresses_current = &new_addr;
    }
}

void add_data_from_line(char *line)
{
    while (line[0] == ' ' || line[0] == '\t')
    {
        line++;
    }
    // reached '.word'
    line += 5;
    while (line[0] == ' ' || line[0] == '\t')
    {
        line++;
    }
    // reached address
    char address[8];
    int i = 0;
    while (line[0] != ' ' || line[0] != '\t')
    {
        address[i] = line[0];
        line++;
        i++;
    }
    while (line[0] == ' ' || line[0] == '\t')
    {
        line++;
    }
    // reached data
    char data[8];
    i = 0;
    while (line[0] != ' ' || line[0] != '\t')
    {
        data[i] = line[0];
        line++;
        i++;
    }
    add_data(data, address);
}

void write_data_to_file(FILE *output_file)
{
    // allocate an array for all addresses
    char **data = malloc((highest_address + 1) * sizeof(char *));
    memset(data, 0, (highest_address + 1) * sizeof(char *));

    // add data to the array so we have it sorted
    node *runner = addresses_start;
    while (runner != NULL)
    {
        data[runner->address] = runner->data;
        runner = runner->next;
    }

    // write the data to the file
    for (int i = 0; i <= highest_address; i++)
    {
        char *data_entry = data[i];
        if (data_entry == 0)
        {
            fputs(NO_DATA, output_file);
        }
        else
        {
            int value = convert_string_num_to_integer(data_entry);
            char entry[8];
            sprintf(entry, "%08X", value);
            fputs(entry, output_file);
        }
    }

    free(data);
}