#pragma once


/*
* extract the label string from cmd line
*
* @param cmd string that has the label inside
* @param pre allocated space to write the label in.
*/
void extract_label_from_cmd(char *cmd, char *res);

/*
* allocate space for labels array and addresses array
*/
void init_labels_array();

/*
* free labels array and addresses array
*/
void free_labels_array();

/*
 insert label to array, anb her address in the corresponding index
*/
void insert_label(char *label, char *address);

/*
* convert label into address
* @param the label to be converted
* @param pre allocated space to write the address in
* @param PC = current line number
* @param cmd_type: 0 - jump, 1- branch
* @ret if found or not
*/
char get_address_from_label(char *label, char *res, int PC, char cmd_type);