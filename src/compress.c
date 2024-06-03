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

    printf("- [ INFO ] - File %s founded ...\n",file_name);

    data_unziped_struct *data_unziped;
    char *new_name_file_to_unzip = (char*)malloc(sizeof(file_name) + 500);
    strcpy(new_name_file_to_unzip, file_name);
    strcat(new_name_file_to_unzip,".g85");

    FILE* file_to_unzip = fopen(new_name_file_to_unzip , "rb");
    if(NULL == file_to_unzip){
        printf("ERROR ! - File to unzip not found!\n");
    }else{

        printf("- [ INFO ] - Opening ziped file to get data ...\n");
        //get file size
        fseek(file_to_unzip, 0L, SEEK_END);
        int len = ftell(file_to_unzip);
        rewind(file_to_unzip);
        
        char *buf = (char*)malloc(sizeof(char) * len);
        //read all data to unzip
        fread(buf, len, 1, file_to_unzip);

        
        //start decompress data process
        decompressed_bytes bytes_data;
        bytes_data.buf       = (char*)malloc(sizeof(char) * search_buf);
        bytes_data.len       = 0;
        bytes_data.capacity  = search_buf;


        tuple aux;
        for(int i = 0; i < len; i += 4) {
            memcpy(&aux, buf+i, sizeof(tuple));
            if(aux.get_number_chars == 0) {
                insert(&bytes_data, aux.next_char);
            } else {
                int ax = bytes_data.len;
                for(int i = 0; i < aux.get_number_chars; i++) {
                    insert(&bytes_data, bytes_data.buf[ax-aux.go_back_positions+i]);
                }

                if(i+4 < len && aux.get_number_chars > 0)
                    insert(&bytes_data, aux.next_char);
            }
        }

        //when all is descompressed... create the original file
        string_remove(new_name_file_to_unzip,".g85");
        FILE* file_to_write_original_unziped = fopen(new_name_file_to_unzip, "wb");
        if(file_to_write_original_unziped == NULL) {
            printf("[  ERROR ] - Error creating output unziped file\n");
            exit(0);
        }

        //write all data on output file
        fwrite(bytes_data.buf, bytes_data.len, 1, file_to_write_original_unziped);
        fclose(file_to_write_original_unziped);
        free(bytes_data.buf);
        
    }

    free(new_name_file_to_unzip);
    fclose(file_to_unzip);
}

void string_remove(char *str, const char *substr) {
    char *ptr = strstr(str, substr);
    if (ptr != NULL) {
        memmove(ptr, ptr + strlen(substr), strlen(ptr + strlen(substr)) + 1);
    }
}


void insert(decompressed_bytes* bytes_data, char data) {
    if(bytes_data->len < bytes_data->capacity) {
        bytes_data->buf[bytes_data->len] = data;
    } else {
        // double capacity
        char* resized_buf = (char*)malloc(sizeof(char) * bytes_data->capacity * 2);

        // copy data to new buff
        for(int i = 0; i < bytes_data->capacity; i++) {
            resized_buf[i] = bytes_data->buf[i];
        }

        // free old data buf
        free(bytes_data->buf);

        // updating new capacity
        bytes_data->capacity      = bytes_data->capacity * 2;
        bytes_data->buf           = resized_buf;
		bytes_data->buf[bytes_data->len] = data;
    }

    bytes_data->len++;
}