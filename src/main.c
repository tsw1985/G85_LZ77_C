#include <stdio.h>
#include <stdlib.h>
#include "../header/main.h"
//#include "../header/compresor_struct.h"
#include "../header/compress.h"


//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main()
{
    //print_head_info();
    char *compress_text = "ABRACADABRA";
    printf("A COMPRIMIR: %s\n",compress_text);

    tuple_array *_tuples_array;
    _tuples_array = create_tuple_array();

    add_firts_tuple_on_list(_tuples_array,compress_text[0]);


    if(is_tuple_list_empty(_tuples_array) == 0){
        printf("LISTA DE TUPLAS VACIA\n");
        
        

    }else{
        printf("LISTA DE TUPLAS LLENA\n");
        show_tuples_list(_tuples_array);
    }

    //_info_tuples_array = compress_data(compress_text);
    //if(_info_tuples_array != NULL){

    //}



    

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