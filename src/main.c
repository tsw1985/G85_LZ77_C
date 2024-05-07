#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"

//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main()
{
    //print_head_info();
    printf("ESPACIO EN BLANCO [%d]\n",' ');
    char *buffer_data = (char*)malloc(150 * (int)sizeof(char));
    
    //DEMO STRINGS
    //strcpy(buffer_data, "TUNTUNCAS_RASCA_LA_CACHARRAaaaaaAAAAAAAaaaAAAAaaI");
    strcpy(buffer_data, "SUPER CALIFRISTICO CALIFRISTICO ESPIALIDOSO 12345");
    //strcpy(buffer_data,   "ABCDE FGHIJKMLOPQR STUVWXYAAAAA BBBB CCCC");

    printf("TO ZIP  : [%s] LENGTH: [%d]\n",buffer_data,(int)strlen(buffer_data));

    tuple_array *_tuples_array;
    _tuples_array = create_tuple_array();

    add_firts_element_on_tuple_list(_tuples_array,buffer_data[0]);
    //zip_data(_tuples_array , remove_emty_spaces(buffer_data));
    zip_data(_tuples_array , buffer_data);

    printf("TUPLA RESULTANTE\n");
    show_tuples_list(_tuples_array);
    //printf("***************** MENSAJE DESCOMPRIMIDO ***************************\n");

    
    char *data_unzip;
    data_unzip = unzip_data(_tuples_array , strlen(buffer_data));
    printf("UNZIPED : [%s] LENGTH: [%d]\n",data_unzip,(int)strlen(data_unzip));

    free(_tuples_array->tuple_list);
    free(_tuples_array);
    return 0;
}

void print_head_info(){
    printf("********************************************\n");
    printf("Bienvenido al compresor Descompresor G85\n");
    printf("Uso para comprimir : g85 file.g85 -c\n");
    printf("Uso para descomprimir : g85 file.g85 -d\n");
    printf("********************************************\n");
}