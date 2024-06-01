#include "../header/compress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define min(a, b) (a < b ? a : b)

//CREATE TUPLE LIST
tuple_array create_tuple_array(){

    tuple_array _tuple_array;
    _tuple_array.capacity = search_buf;
    _tuple_array.size = 0;
    _tuple_array.tuple_list = (tuple*)malloc( search_buf * sizeof(tuple));

    if(_tuple_array.tuple_list == NULL){
        printf("ERROR MALLOC() add_firts_element_on_tuple_list()\n");
        exit(EXIT_FAILURE);
    }

    return _tuple_array;
}


tuple_array zip_data(char *buffer , int len){

    //Tuple array to save the buffer data on tuples ( the data is "ziped" on tuples )
    printf("- [ INFO ] - Please wait ...\n");
    tuple_array _tuple_array = create_tuple_array(); 

    //add first byte (first tuple);
    tuple tuple_item;
    tuple_item.get_number_chars = 0;
    tuple_item.go_back_positions = 0;
    tuple_item.next_char = buffer[0];

    add_tuple_on_list(tuple_item.go_back_positions, tuple_item.get_number_chars, tuple_item.next_char , &_tuple_array);

    for(int i = 1; i < len; i++) {

        tuple temp;
        temp.go_back_positions = 0;
        temp.get_number_chars = 0;
        temp.next_char = buffer[i];

        for(int j = i-1; j >= 0 && j >= i-search_buf; j--) {
            int cx = j;
            for(int p = i; p < min(i+lookahead_buf, len) && cx < i; p++) {
                if(buffer[cx] == buffer[p]) {
                    if(temp.get_number_chars < p-i+1) {
                        temp.go_back_positions = i-j;
                        temp.get_number_chars = p-i+1;
                        temp.next_char = buffer[p+1 >= len ? p : p+1];
                    }
                    cx++;
                } else {
                    break;
                }
            }
        }

        add_tuple_on_list(temp.go_back_positions, temp.get_number_chars, temp.next_char , &_tuple_array);
        i += temp.get_number_chars ? temp.get_number_chars : 0;
    }

    return _tuple_array;
}



void add_tuple_on_list(unsigned short _go_back_positions, int _get_number_chars , char _next_char , tuple_array *_tuple_array){
    
    //while the capacity of the list is less than his limit ...
    if(_tuple_array->size < _tuple_array->capacity){

        tuple tuple_item;
        tuple_item.go_back_positions = _go_back_positions;
        tuple_item.get_number_chars  = _get_number_chars;
        tuple_item.next_char         = _next_char;
        _tuple_array->tuple_list[_tuple_array->size] = tuple_item;

    }else{

        //if the limit is passed. We need more space. So we create a new space on memory.
        tuple *_tuple_array_resized = (tuple*)malloc(sizeof(tuple) * _tuple_array->capacity * 2);
        if(_tuple_array_resized == NULL){
            printf("ERROR MALLOC() add_firts_element_on_tuple_list()\n");
            exit(EXIT_FAILURE);
        }else{

            //create a new buffer with the double capacity and merge the current values on the new buffer
            for(int i= 0 ; i < _tuple_array->size ; i++){
                _tuple_array_resized[i] = _tuple_array->tuple_list[i];
            }

            free(_tuple_array->tuple_list);

            tuple tuple_item;
            tuple_item.go_back_positions = _go_back_positions;
            tuple_item.get_number_chars  = _get_number_chars;
            tuple_item.next_char         = _next_char;

            _tuple_array->capacity                 = _tuple_array->capacity * 2;
            _tuple_array->tuple_list               = _tuple_array_resized;
            _tuple_array->tuple_list[_tuple_array->size] = tuple_item;
        }
    }

    _tuple_array->size++;

}

void show_tuples_list(tuple_array _tuples_array){

    for(size_t i = 0; i < _tuples_array.size ; i++){
        tuple tuple_item = _tuples_array.tuple_list[i];
        printf("- [ INFO ] - TUPLE : [%d] - (%d , %d , %c)\n",i,
                        tuple_item.go_back_positions ,
                        tuple_item.get_number_chars,
                        tuple_item.next_char);
    }
}



void unzip_data(char *file_name){

    data_unziped_struct *data_unziped;
    FILE* file_to_unzip = fopen(strcat(file_name,".g85"), "rb");
    if(NULL == file_to_unzip){
        printf("ERROR ! - File not found!\n");
    }
    fclose(file_to_unzip);
   
    
}
