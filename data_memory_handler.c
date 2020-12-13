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

static node *addresses_start;
static node *addresses_current;

void init_data_memory_handler()
{
    addresses_start = NULL;
    addresses_current = NULL;
}

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
    printf("data to node %s\n", data);
    printf("address to node %d\n", addr);
    node new_addr = {
        .address = addr,
        .data = data,
        .next = NULL
    };
    if (addresses_start == NULL)
    {
        addresses_start = &new_addr;
        addresses_current = &new_addr;
    }
    else
    {
        addresses_current->next = &new_addr;
        addresses_current = &new_addr;
    }
    printf("data: %s\n", addresses_start->data);
    printf("data: %d\n", addresses_start->address);
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
    printf("writing to file\n");
    if (highest_address == 0) {
        return;
    }
    // allocate an array for all addresses
    char **data = malloc((highest_address + 1) * sizeof(char *));
    memset(data, 0, (highest_address + 1) * sizeof(char *));

    // add data to the array so we have it sorted
    node *runner = addresses_start;
    printf("1loc %d\n", addresses_start->address);
    printf("1data %s\n", addresses_start->data);
    while (runner != NULL)
    {
        printf("writing to array\n");
        printf("2loc %d\n", runner->address);
        printf("2data %s\n", runner->data);
        data[runner->address] = runner->data;
        printf("1\n");
        runner = runner->next;
        printf("done\n");
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
            char entry[9];
            sprintf(entry, "%08X", value);
            fputs(entry, output_file);
        }
    }

    free(data);
}