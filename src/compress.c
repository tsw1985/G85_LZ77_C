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

        char _current_buffer_item = buffer[buffer_index];
        char _next_to_current_buffer_item = buffer[buffer_index+1];
        if(_current_buffer_item != '\0'){

            int char_is_on_tuple_index = is_char_in_tuples_list(_next_to_current_buffer_item , _tuple_array);
            if(char_is_on_tuple_index != -1){ // EXISTS

                //typedef struct
                //{
                //    int go_back_positions;
                //    int get_number_chars;
                //    char next_char;   
                //} tuple;
                
                _tuple_array = add_tuple_on_list(char_is_on_tuple_index,0,_next_to_current_buffer_item,_tuple_array);
                printf("LETRA [%c] SI existe en posicion [%d] !\n",_next_to_current_buffer_item,char_is_on_tuple_index);

            }else{ //NOT EXISTS
                //printf("NO EXISTE LETRA %c\n",_current_buffer_item);
                printf("LETRA %c NO EXISTE - La ponemos\n",_next_to_current_buffer_item);
                _tuple_array = add_tuple_on_list(0,0,_current_buffer_item,_tuple_array);
            }
        
        }
    }
    return _tuple_array;
}

tuple_array *add_tuple_on_list(int _go_back_positions, int _get_number_chars , char _next_char , tuple_array *_tuple_array){
    _tuple_array->size = _tuple_array->size +1;
    _tuple_array->tuple_list = (tuple*)realloc(_tuple_array->tuple_list , (_tuple_array->size) * sizeof(tuple));
    
    tuple tuple_item;
    tuple_item.go_back_positions = _go_back_positions;
    tuple_item.get_number_chars = _get_number_chars;
    tuple_item.next_char = _next_char;

    _tuple_array->tuple_list[_tuple_array->size -1] = tuple_item;
    return _tuple_array;
}

//FIX THISSSSSSSSSSSSSSSSSSSSSSSSSSS
int is_char_in_tuples_list(char _char , tuple_array *_tuple_array){

    int exists_on_index = -1;
    printf("---------------------\n");
    for(int i = _tuple_array->size-1 ; i >= 0 ; i--){
        tuple _tuple_item = _tuple_array->tuple_list[i];
        if(_tuple_item.next_char == _char){
           exists_on_index = i;
           break; 
        }
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




void show_tuples_list(tuple_array *_tuples_array){
    for(int i = 0; i < _tuples_array->size ; i++){
    //for(int i = 0; i < 4 ; i++){
        tuple tuple_item = _tuples_array->tuple_list[i];
        printf("TUPLA : [%d] - go_back_positions: [%d] - get_number_chars[%d] - next_char[%c]\n",i,
                                                                                               tuple_item.go_back_positions ,
                                                                                               tuple_item.get_number_chars,
                                                                                               tuple_item.next_char);
    }
}