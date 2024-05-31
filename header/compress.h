#include "../header/compresor_struct.h"
#include <stdio.h>
//Global functions
tuple_array create_tuple_array();
void add_tuple_on_list(unsigned short go_back_positions, int get_number_chars , char next_char , tuple_array *_tuple_array);
void show_tuples_list(tuple_array _tuples_array);
//compresion functions
tuple_array zip_data(char *data , int length_bytes);
//descompresion functions
char *unzip_data(tuple_array *_tuple_array);
void print_loading();
