#include "../header/compress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//const int search_buf    = 1024;
//const int lookahead_buf = 100; // limited to 255
#define min(a, b) (a < b ? a : b)

//CREATE TUPLE LIST
tuple_array *create_tuple_array(){

    //Asign tuples to tuple_array struct
    tuple_array *_tuple_array = (tuple_array*)malloc(sizeof(tuple_array));
    if(_tuple_array == NULL){
        printf("ERROR MALLOC() create_tuple_array()\n");
        exit(EXIT_FAILURE);
    }
    _tuple_array->size = 0;
    


    return _tuple_array;
}

//ADD FIRST ELEMENT ON TUPLE ELEMENT ON LIST
tuple_array *add_firts_element_on_tuple_list(tuple_array *_tuples_array , char _next_char){

        _tuples_array->tuple_list = (tuple*)realloc(_tuples_array->tuple_list , 1 * sizeof(tuple));
        if(_tuples_array->tuple_list == NULL){
            printf("ERROR MALLOC() add_firts_element_on_tuple_list()\n");
            exit(EXIT_FAILURE);
        }
        _tuples_array->size = 1;

        tuple tuple_item;
        tuple_item.get_number_chars = 0;
        tuple_item.go_back_positions = 0;
        tuple_item.next_char = _next_char;

        _tuples_array->tuple_list[0] = tuple_item;

        return _tuples_array;
}



/*
    Cuando hay \n \r en las tuplas , se vuelve medio loco esto
    habria que hacer un split por saltos de linea antes de enviar
    las tuplas a comprimir y asi quiza se vaya el problema
*/
tuple_array *zip_data(tuple_array *_tuple_array, char *buffer){

    //_tuple_array = add_tuple_on_list(go_back_positions, 1, next_next_char, _tuple_array);

    size_t len = strlen(buffer);

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

        _tuple_array = add_tuple_on_list(temp.go_back_positions, temp.get_number_chars, temp.next_char , _tuple_array);
        i += temp.get_number_chars ? temp.get_number_chars : 0;

        //_tuple_array->size++;
    }

    
    return _tuple_array;



}

int get_position_existing_char_on_current_chars_readed(char _char, data_ziped_struct *data_ziped){
    int position = -1;
    for(int i = 0 ; i < data_ziped->length ; i++){
        if(data_ziped->pointer_data_ziped[i] == _char){
            position = i;
        }
    }
    return position;
}

tuple_array *add_tuple_on_list(int _go_back_positions, int _get_number_chars , char _next_char , tuple_array *_tuple_array){
    
    _tuple_array->size = _tuple_array->size +1;
    printf("TUPLA SIZE %d\n",_tuple_array->size);
    tuple tuple_item;
    tuple_item.go_back_positions = _go_back_positions;
    tuple_item.get_number_chars = _get_number_chars;
    tuple_item.next_char = _next_char;

    _tuple_array->tuple_list[_tuple_array->size -1] = tuple_item;
    return _tuple_array;
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
        printf("TUPLA : [%d] - (%d , %d , %c)\n",i,
                                                                                               tuple_item.go_back_positions ,
                                                                                               tuple_item.get_number_chars,
                                                                                               tuple_item.next_char);
    }
}

//ABRACADABRAPATADECABRAA

char *unzip_data(tuple_array *_tuple_array){

    data_unziped_struct *data_unziped;
    data_unziped = (data_unziped_struct*)malloc(sizeof(data_unziped_struct));
    if(data_unziped == NULL){
        printf("ERROR MALLOC() data_unziped- unzip_data()\n");
        exit(EXIT_FAILURE);
    }


    char *data_unziped_array = (char*)malloc(1 * (int)sizeof(char));
    if(data_unziped == NULL){
        printf("ERROR MALLOC() unzip_data() - data_unziped_array\n");
        exit(EXIT_FAILURE);
    }

    data_unziped->pointer_data_unziped = data_unziped_array;
    data_unziped->length = 0;

    //get first element on tupple
    int char_realloc_counter = 0;
    tuple tuple_item = _tuple_array->tuple_list[0];
    data_unziped->pointer_data_unziped[0] = tuple_item.next_char;
    data_unziped->length = 1;
    char_realloc_counter++;
    
    for(int i = 1; i < (_tuple_array->size) ; i++){
        if(i >= 1 && i < _tuple_array->size){

            tuple_item = _tuple_array->tuple_list[i];
            if(tuple_item.go_back_positions == 0){

                if(byte_is_valid(tuple_item.next_char)){
                    data_unziped->pointer_data_unziped = (char*)realloc(data_unziped->pointer_data_unziped,data_unziped->length * (int)sizeof(char));
                    if(data_unziped->pointer_data_unziped==NULL){
                        printf("ERROR MALLOC() unzip_data() - data_unziped->pointer_data_unziped 1\n");
                        exit(EXIT_FAILURE);
                    }
                    data_unziped->pointer_data_unziped[data_unziped->length] = tuple_item.next_char;
                    data_unziped->length = data_unziped->length +1;
                }

            }else{

                char next_char = tuple_item.next_char;
                char picked_char = get_char_from_data_unziped(data_unziped , tuple_item.go_back_positions);

                if(byte_is_valid(next_char) && byte_is_valid(picked_char)){

                    data_unziped->length +=2;
                    data_unziped->pointer_data_unziped = (char*)realloc(data_unziped->pointer_data_unziped,data_unziped->length * (int)sizeof(char));

                    if(data_unziped->pointer_data_unziped==NULL){
                        printf("ERROR MALLOC() unzip_data() - data_unziped->pointer_data_unziped 2\n");
                        exit(EXIT_FAILURE);
                    }
                    data_unziped->pointer_data_unziped[data_unziped->length-2] = picked_char;
                    data_unziped->pointer_data_unziped[data_unziped->length-1] = next_char;
                }
            }
        }
    }

    clean_return_buffer(data_unziped->pointer_data_unziped);
    return data_unziped->pointer_data_unziped;
}



// Función para limpiar la cadena de caracteres basura al final
void clean_return_buffer(char *buffer) {
    size_t buffer_length = strlen(buffer);
    if (buffer_length > 0) {
        // Eliminar caracteres no válidos al final
        while (buffer_length > 0 && !byte_is_valid(buffer[buffer_length - 1])) {
            buffer[--buffer_length] = '\0';
        }
    }
}

int byte_is_valid(char c) {
    //return isprint((unsigned char)c) || isspace((unsigned char)c || c != '\r' || c != '\n' || c != '\0');
    return isprint((unsigned char)c) || isspace((unsigned char)c);
}

void show_current_chars_readed(data_unziped_struct *data_unziped){
    for( int i = 0 ; i < data_unziped->length ; i++){
        printf("CHARS [%d] READED [%c]\n" ,i, data_unziped->pointer_data_unziped[i]);
    }
}

char get_char_from_data_unziped(data_unziped_struct *data_unziped, int go_back_positions){
    char picked_char = data_unziped->pointer_data_unziped[data_unziped->length - go_back_positions];
    return picked_char;
}