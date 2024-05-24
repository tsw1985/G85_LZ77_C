#include "../header/compresor_struct.h"
#include <stdio.h>
//Global functions
tuple_array *create_tuple_array();
int is_tuple_list_empty(tuple_array *_tuple_array);
tuple_array * add_tuple_on_list(int go_back_positions, int get_number_chars , char next_char , tuple_array *_tuple_array);
tuple_array *add_firts_element_on_tuple_list(tuple_array *_tuples_array,char next_char);
void show_tuples_list(tuple_array *_tuples_array);
void show_current_chars_readed(data_unziped_struct *data_unziped);
int get_position_existing_char_on_current_chars_readed(char _char, data_ziped_struct *_data_ziped_struct);
//compresion functions
tuple_array *zip_data(tuple_array *_tuples_array,char *data);
//descompresion functions
char *unzip_data(tuple_array *_tuple_array);
char get_char_from_data_unziped(data_unziped_struct *data_unziped, int go_back_positions);
int byte_is_valid(char c);
void clean_return_buffer(char *cadena);