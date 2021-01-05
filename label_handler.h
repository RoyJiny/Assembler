#pragma once


/*
* extract the label string from cmd line
*
* @param cmd string that has the label inside
* @param pre allocated space to write the label in.
* @ret return 1 if the cmd containes only a label , return 0 o.w.
*/
char extract_label_from_cmd(char *cmd, char *res);

/*
* allocate space for labels array and addresses array. 
* should be called before any use of the handler.
*/
void init_labels_array();

/*
* free labels array and addresses array
*/
void free_labels_array();

/*
 insert label to array, and her address in the corresponding index
 * @param label : the label to be inserted.
*  @param address: the correspondind address of the label.
*/
void insert_label(char *label, char *address);

/*
* convert label into address
* @param label: the label to be converted
* @param res: stored the return value, required size is ADDRESS_SIZE.
* @ret if found or not
*/
char get_address_from_label(char *label, char *res);