#include "../header/compress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char replace = '_';
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

tuple_array *zip_data(tuple_array *_tuple_array, char *buffer){

    //Estructura de entrada de datos
    data_ziped_struct *data_ziped = (data_ziped_struct*)malloc(sizeof(data_ziped_struct));
    data_ziped->length = 0; // iniciamos la longitud a 0

    //Array de letras leidas
    char *current_chars_readed = (char*)malloc(sizeof(char));
    //metemos array de letras en la estructura
    data_ziped->pointer_data_ziped = current_chars_readed;
    data_ziped->pointer_data_ziped[0] = buffer[0];
    data_ziped->length = data_ziped->length +1;

    
    for(int buffer_index = 0 ; buffer_index < strlen(buffer) ; buffer_index ++){

        char current_char = buffer[buffer_index];
        char next_char = buffer[buffer_index+1];

        data_ziped->length = data_ziped->length +1;
        data_ziped->length = data_ziped->length +1;

        data_ziped->pointer_data_ziped = (char*)realloc(data_ziped->pointer_data_ziped , data_ziped->length * sizeof(char));

        data_ziped->pointer_data_ziped[buffer_index] = current_char;
        
        int position_existing_char = get_position_existing_char_on_current_chars_readed(next_char,data_ziped);
        //printf("POSITION EXISTING CHAR %d\n",position_existing_char);
        if(position_existing_char != -1){

            buffer_index++;
            int go_back_positions = (buffer_index - position_existing_char) ;
            char next_next_char = buffer[buffer_index+1];

            _tuple_array = add_tuple_on_list(go_back_positions, 1, next_next_char, _tuple_array);
        }else{
            _tuple_array = add_tuple_on_list(0,0,next_char ,_tuple_array);
        }
     
    }

    return _tuple_array;
}

int get_position_existing_char_on_current_chars_readed(char _char, data_ziped_struct *data_ziped){
    printf("NEXT CHAR -> %c\n",_char);
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
    _tuple_array->tuple_list = (tuple*)realloc(_tuple_array->tuple_list , (_tuple_array->size) * sizeof(tuple));
    
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
        printf("TUPLA : [%d] - go_back_positions: [%d] - get_number_chars[%d] - next_char[%c]\n",i,
                                                                                               tuple_item.go_back_positions ,
                                                                                               tuple_item.get_number_chars,
                                                                                               tuple_item.next_char);
    }
}


char *unzip_data(tuple_array *_tuple_array , int buffer_data_length){
    int size_list = _tuple_array->size;
    //char data_unziped[buffer_data_length+1];
    //memset(data_unziped,' ',buffer_data_length);
    //data_unziped[buffer_data_length + 1] = '\0';

    data_unziped_struct *data_unziped;
    data_unziped = (data_unziped_struct*)malloc(sizeof(data_unziped_struct));


    char *data_unziped_array = (char*)malloc(1 * (int)sizeof(char));

    data_unziped->pointer_data_unziped = data_unziped_array;
    data_unziped->length = 0;

    //get first element on tupple
    int char_realloc_counter = 0;
    tuple tuple_item = _tuple_array->tuple_list[0];
    data_unziped->pointer_data_unziped[0] = tuple_item.next_char;
    data_unziped->length = 1;
    char_realloc_counter++;
    
    //show_current_chars_readed(data_unziped);

    
    for(int i = 1; i < (_tuple_array->size) ; i++){
        //printf("************** ITERACION NUMERO [%d]*******************\n",i);
        //tuple tuple_item = _tuple_array->tuple_list[i];
        tuple_item = _tuple_array->tuple_list[i];

        /*if(tuple_item.next_char == replace){
            tuple_item.next_char = ' ';
        }  */

        if(tuple_item.go_back_positions == 0){

            data_unziped->pointer_data_unziped = (char*)realloc(data_unziped->pointer_data_unziped,data_unziped->length * (int)sizeof(char));
            /*if(tuple_item.next_char == replace){
                tuple_item.next_char = ' ';
            }*/

            data_unziped->pointer_data_unziped[data_unziped->length] = tuple_item.next_char;
            data_unziped->length = data_unziped->length +1;
            //printf("-------------|----------------\n");
            //printf("1-VALOR DE REALLOC COUNTER %d\n",char_realloc_counter);
            //show_current_chars_readed(data_unziped);
        }else{

            char next_char = tuple_item.next_char;
            //if(next_char != '\0'){

                /*if(tuple_item.next_char == replace){
                    tuple_item.next_char = ' ';
                } */  
            
                char picked_char = get_char_from_data_unziped(data_unziped , tuple_item.go_back_positions);
                /*if(picked_char == replace){
                    picked_char = ' ';
                }*/
                //printf("PICKED CHAR [%c] y NEXT CHAR -> %c\n",picked_char, tuple_item.next_char);

                data_unziped->length = data_unziped->length +1;
                data_unziped->length = data_unziped->length +1;

                data_unziped->pointer_data_unziped = (char*)realloc(data_unziped->pointer_data_unziped,data_unziped->length * (int)sizeof(char));
                data_unziped->pointer_data_unziped[data_unziped->length-2] = picked_char;
                data_unziped->pointer_data_unziped[data_unziped->length-1] = next_char;

                //show_current_chars_readed(data_unziped);

            //}
            
        }
    }
    

    

    return data_unziped->pointer_data_unziped;
}

void show_current_chars_readed(data_unziped_struct *data_unziped){
    for( int i = 0 ; i < data_unziped->length ; i++){
        printf("CHARS [%d] READED [%c]\n" ,i, data_unziped->pointer_data_unziped[i]);
    }
}

char get_char_from_data_unziped(data_unziped_struct *data_unziped, int go_back_positions){
    char picked_char = data_unziped->pointer_data_unziped[data_unziped->length - go_back_positions];
    if(picked_char == replace){
        picked_char = ' ';
    }
    //printf("CHAR a devolver [%c]\n",picked_char);
    return picked_char;
}

char *remove_emty_spaces(char *buffer){
    unsigned long buffer_length = (unsigned long)strlen(buffer);
    for(int i = 0; i < buffer_length ; i++){
        if(buffer[i] == 32){
            buffer[i] = replace;
        }
    }


    /*printf("BUFFER REEMPLAZADO\n");
    for(int i = 0; i < buffer_length ; i++){
        printf("LETRAS LIMPIAS [%c]\n",buffer[i]);
    }*/


    return buffer;
}