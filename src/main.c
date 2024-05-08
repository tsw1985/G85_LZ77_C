#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"

//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main(int argc, char *argv[])
{

    print_head_info();
    long buffer_size = 128 * 1024;
    printf("BUFFER SIZE: [ %lu ]\n",buffer_size);
    char *buffer_data = (char*)malloc(buffer_size * sizeof(char));
    
    //strcpy(buffer_data, "ABRACADABRAPATADECABRA");
    strcpy(buffer_data, "ESTO ES UN TEXTO QUE SERA COMPRIMIDO Y DESCOMPRIMIDO");
    unsigned long zip_data_size = (unsigned long)strlen(buffer_data);
    printf("TO ZIP  : [%s] LENGTH: [%lu]\n",buffer_data,zip_data_size);

    tuple_array *_tuples_array;
    _tuples_array = create_tuple_array();

    // ZIP
    add_firts_element_on_tuple_list(_tuples_array,buffer_data[0]);
    zip_data(_tuples_array , buffer_data);


    if(argc > 1){

        if(strcmp(argv[1], "show_tuples")){
            //show_tuples_list(_tuples_array);
        }
        if(strcmp(argv[1], "show_zip_length")){
            //printf("LONGITUD COMPRIMIDA [%lu]\n",_tuples_array->size);
        }
            
    }
    

    // UNZIP
    char *data_unzip;
    data_unzip = unzip_data(_tuples_array);
    printf("\n");
    printf("UNZIPED DATA: [%s] LENGTH: [%lu]\n",data_unzip, strlen(data_unzip));
    
    free(_tuples_array->tuple_list);
    free(_tuples_array);
    return 0;
}










void print_head_info(){
    printf("****************************************************************************************************\n");
    printf(" Welcome to G85Zip:\n");
    printf(" - Zip   : g85 'yourfile.xxx' -zip\n");
    printf(" - Unzip : g85 yourfile.g85 -unzip\n");
    printf("****************************************************************************************************\n");
}