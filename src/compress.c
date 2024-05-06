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
    char current_chars_readed[(int)strlen(buffer)];
    memset(current_chars_readed,' ',(int)strlen(buffer));
    current_chars_readed[(int)strlen(buffer)+1] = '\0';
    current_chars_readed[0] = buffer[0];
    
    //printf("-TUPLA : back [%d] - pick[%d] - next_char [%c] NO\n",0 , 0 , buffer[0]);

    for(int buffer_index = 0 ; buffer_index < strlen(buffer) ; buffer_index ++){

        char current_char = buffer[buffer_index];
        char next_char = buffer[buffer_index+1];
        //add current char to readed chars list
        current_chars_readed[buffer_index] = current_char;
        //printf("CURRENT CHAR [%c] - NEXT CHAR [%c] y BUFFER CHAR [%c]\n",current_char,next_char,current_chars_readed[buffer_index]);
        
        if(next_char != '\0'){

            int position_existing_char = get_position_existing_char_on_current_chars_readed(next_char,current_chars_readed);
            if(position_existing_char != -1){
                buffer_index++;
                int go_back_positions = (buffer_index - position_existing_char) ;
                char next_next_char = buffer[buffer_index+1];
                //printf("-TUPLA : back [%d] - pick[%d] - next_char [%c]\n",go_back_positions , 1 , next_next_char);
                _tuple_array = add_tuple_on_list(go_back_positions, 1, next_next_char, _tuple_array);
            }else{
                //printf("-TUPLA : back [%d] - pick[%d] - next_char [%c] NO\n",0 , 0 , next_char);
                _tuple_array = add_tuple_on_list(0,0,next_char ,_tuple_array);
            }
        }
    }
    return _tuple_array;
}


int get_position_existing_char_on_current_chars_readed(char _char, char current_chars_readed[]){
    int position = -1;
    for(int i = 0 ; i < (int)strlen(current_chars_readed) -1 ; i++){
        if(current_chars_readed[i] == _char){
            position = i;
            //break;
        }
    }
    return position;
}


void show_current_chars_readed(char current_chars_readed[]){
    for( int i = 0 ; i < (int)strlen(current_chars_readed)-1 ; i++){
        printf("CHARS [%d] READED [%c]\n" ,i, current_chars_readed[i]);
    }
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
        tuple tuple_item = _tuples_array->tuple_list[i];
        printf("TUPLA : [%d] - go_back_positions: [%d] - get_number_chars[%d] - next_char[%c]\n",i,
                                                                                               tuple_item.go_back_positions ,
                                                                                               tuple_item.get_number_chars,
                                                                                               tuple_item.next_char);
    }
}


char *descompress(tuple_array *_tuple_array){
    int size_list = _tuple_array->size;
    //char data_unziped[size_list];
    char *data_unziped;
    for(int i = 0; i < _tuple_array->size ; i++){
        tuple tuple_item = _tuple_array->tuple_list[i];
        if(tuple_item.go_back_positions == 0){
            data_unziped[i] = tuple_item.next_char;
        }
    }
    return data_unziped;
}
