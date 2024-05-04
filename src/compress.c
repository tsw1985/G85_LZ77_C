#include "../header/compress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//CREATE TUPLE LIST
tuple_array *create_tuple_array(){

    int window_length = 4;

    //Asign tuples to tuple_array struct
    tuple_array *_tuple_array = (tuple_array*)malloc(sizeof(tuple_array));
    _tuple_array->size = 0;

    // Init tuples array
    tuple *tuples;
    tuples = (tuple*)malloc(sizeof(tuple));

    return _tuple_array;
}

//ADD FIRST ELEMENT ON TUPLE ELEMENT ON LIST
tuple_array *add_firts_element_on_tuple_list(tuple_array *_tuples_array , char _next_char){

        _tuples_array->tuple_list = (tuple*)realloc(_tuples_array->tuple_list , 1 * sizeof(tuple));
        _tuples_array->size = 1;

        tuple tuple_item;
        tuple_item.get_number_chars = 0;
        tuple_item.go_back_positions = 0;
        tuple_item.next_char = _next_char;

        _tuples_array->tuple_list[0] = tuple_item;

        return _tuples_array;
}

//GET A LIST OF TUPLES
tuple_array *compress_data(tuple_array *_tuple_array, char *buffer){

    int window_length = 4;


    char searching[4];
    //char next_search[4];
    for(int buffer_index = 0 ; buffer_index < strlen(buffer) ; buffer_index ++){
        char _buffer_item = buffer[buffer_index];
        if(_buffer_item != '\0'){
            //printf("1-BUFFER ITEM %c\n",_buffer_item);

            int char_is_on_tuple_index = is_char_in_tuples_list(_buffer_item,_tuple_array);
            if(char_is_on_tuple_index != -1){
                printf("EL ELEMENTO EXISTE EN POSICION [%d]\n",char_is_on_tuple_index);
            }
        }
    }
    return _tuple_array;
}


int is_char_in_tuples_list(char _char , tuple_array *_tuple_array){

    int exists_on_index = -1;
    int tupla_index = 0;
    for(int i = _tuple_array->size ; i > 0 ; i--){

        tuple _tuple_item = _tuple_array->tuple_list[tupla_index];
        if(_tuple_item.next_char == _char){
           exists_on_index = i;
           break; 
        }
        tupla_index++;
    }
    return exists_on_index;
}

int is_tuple_list_empty(tuple_array *_tuple_array){
    int size = 0;
    for(int i = 0 ; i < _tuple_array->size ; i++){
        size++;
    }
    return size;
}


int add_tuple_on_list(int go_back_positions, int get_number_chars , int next_char){
    return 0;
}

void show_tuples_list(tuple_array *_tuples_array){
    for(int i = 0; i < _tuples_array->size ; i++){
        tuple tuple_item = _tuples_array->tuple_list[i];
        printf("TUPLA : [%d] - go_back_positions: [%d] - get_number_chars[%d] - next_char[%c]\n",i,
                                                                                               tuple_item.go_back_positions ,
                                                                                               tuple_item.get_number_chars,
                                                                                               tuple_item.next_char);
    }
}