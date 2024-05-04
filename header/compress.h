#include "../header/compresor_struct.h"
tuple_array *create_tuple_array();
int is_char_in_tuples_list(char _char , tuple_array *_tuple_array);
int is_tuple_list_empty(tuple_array *_tuple_array);
int add_tuple_on_list(int go_back_positions, int get_number_chars , int next_char);
tuple_array *add_firts_tuple_on_list(tuple_array *_tuples_array,char next_char);
void show_tuples_list(tuple_array *_tuples_array);






tuple_array *compress_data(char *data);
