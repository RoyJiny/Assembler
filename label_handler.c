#include "label_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "utils.h"

char *labels_array;
char *addresses_array;
int next_free_slot;

char is_null(char c) { return c == 0; }


void extract_label_from_cmd(char *cmd, char *res)
{
	char *cmd_runner = cmd;
	char *res_runner = res;
	while (cmd_runner[0] == ' ') { cmd_runner++; }
	while (cmd_runner[0] != ':' && cmd_runner[0] != ' ') {
		*res_runner = *cmd_runner;
		res_runner++;
		cmd_runner++;
	}
	*res_runner = 0;
}

void init_labels_array()
{
	labels_array = (char*)malloc(MAX_AMOUNT_OF_LABELS * MAX_LABEL_SIZE * sizeof(char));
	memset(labels_array, 0, MAX_AMOUNT_OF_LABELS * MAX_LABEL_SIZE);
	addresses_array = (char*)malloc(MAX_AMOUNT_OF_LABELS * ADDRESS_SIZE * sizeof(char));
	memset(addresses_array, 0, MAX_AMOUNT_OF_LABELS * ADDRESS_SIZE);
	next_free_slot = 0;
}

void free_labels_array()
{
	free(labels_array);
	free(addresses_array);
}

char is_full()
{
	return next_free_slot == MAX_AMOUNT_OF_LABELS;
}

void insert_label(char *label, char *address)
{
	printf("trying to insert the label '%s' with address '%s'\n", label, address);
	printf("next free slot is on index '%d'\n", next_free_slot);
	if (!is_full()) {
		/* copy label into the label array */
		char *insert_location = labels_array + next_free_slot * MAX_LABEL_SIZE;
		int char_counter = 0;
		char *label_runner = label;
		while (!is_null(label_runner[0]) && char_counter < MAX_LABEL_SIZE) {
			*insert_location = *label_runner;
			label_runner++;
			insert_location++;
			char_counter++;
		}
		/* copy address into the address array */
		insert_location = addresses_array + next_free_slot * ADDRESS_SIZE;
		char_counter = 0;
		char *address_runner = address;
		while (!is_null(address_runner[0]) && char_counter < ADDRESS_SIZE) {
			*insert_location = *address_runner;
			address_runner++;
			insert_location++;
			char_counter++;
		}
		next_free_slot++;
	}
}

char compare_label_in_array_index(int index, char *label)
{
	char *array_runner = labels_array + index * MAX_LABEL_SIZE;
	char *label_runner = label;
	int compared_chars_counter = 0;
	while (!is_null(array_runner[0]) && !is_null(label_runner[0]) && compared_chars_counter < MAX_LABEL_SIZE) {
		if (label_runner[0] != array_runner[0]) {
			return 0;
		}
		array_runner++;
		label_runner++;
		compared_chars_counter++;
	}
	return (is_null(array_runner[0]) && is_null(label_runner[0])) || compared_chars_counter == MAX_LABEL_SIZE;
}

char get_address_from_label(char *label, char *res, int PC, char cmd_type)
{
	printf("coverting label %s to address\n", label);
	char temp[ADDRESS_SIZE+1];
	for (int index = 0; index < MAX_AMOUNT_OF_LABELS; index++) {
		if (compare_label_in_array_index(index, label)) {
			char *address_position = addresses_array + index * ADDRESS_SIZE;
			for (int j = 0; j < ADDRESS_SIZE; j++) {
				temp[j] = *(address_position + j);
			}
			temp[ADDRESS_SIZE] = 0;
			int label_PC = strtol(temp, NULL, 16);
			printf("label number is %d\n",label_PC);
			if(cmd_type == 0) decimal_to_hex(label_PC - PC, res, ADDRESS_SIZE); /*relative*/
			else 			  decimal_to_hex(label_PC, res, ADDRESS_SIZE);		/*absolute*/
			printf("the written result is: %s\n", res);
			return 1;
		}
	}
	return 0;
}