#include "../header/compresor_struct.h"
//Global functions
tuple_array *create_tuple_array();
int is_char_in_tuples_list(char _char , tuple_array *_tuple_array);
int is_tuple_list_empty(tuple_array *_tuple_array);
tuple_array * add_tuple_on_list(int go_back_positions, int get_number_chars , char next_char , tuple_array *_tuple_array);
tuple_array *add_firts_element_on_tuple_list(tuple_array *_tuples_array,char next_char);
void show_tuples_list(tuple_array *_tuples_array);
void show_current_chars_readed(char current_chars_readed[]);
int get_position_existing_char_on_current_chars_readed(char _char, char current_chars_readed[]);



//compresion functions
tuple_array *compress_data(tuple_array *_tuples_array,char *data);

//descompresion functions
char *descompress(tuple_array *_tuple_array);