#include "../header/compress.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//GET A LIST OF TUPLES
tuple_array *compress_data(char *buffer){

    // Init tuples array
    tuple *tuples;
    tuples = (tuple*)malloc(1*sizeof(tuple));

    //Asign tuples to tuple_array struct
    tuple_array *_tuple_array = (tuple_array*)malloc(sizeof(tuple_array));
    _tuple_array->tuple_list = tuples;

    char searching[4];
    char next_search[4];
    for(int buffer_index =0 ; buffer_index < strlen(buffer) ; buffer_index ++){
        printf("LETRA -->[%d] - %c\n",buffer_index,buffer[buffer_index]);
    }




    return _tuple_array;
}

