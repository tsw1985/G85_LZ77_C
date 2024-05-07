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
    char *buffer_data = (char*)malloc(buffer_size * sizeof(char));
    
    //DEMO STRINGS
    strcpy(buffer_data, "ESTE Y DESCOMPRIMIDOOO 445");
    //strcpy(buffer_data, "aaaaaaaaaaaaaaaaa kkkkkkkkkkkk          kkkkkkkkkkkkkkkkkkk         aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbb bbbbbbbbbbbbbbbbbbbbbbbbccccccccccc ccccccccccccccccccccc  aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbb ccccddddddddddddddddddddddddddddP");
    printf("TO ZIP  : [%s] LENGTH: [%d]\n",buffer_data,(int)strlen(buffer_data));

    tuple_array *_tuples_array;
    _tuples_array = create_tuple_array();

    // ZIP
    add_firts_element_on_tuple_list(_tuples_array,buffer_data[0]);
    zip_data(_tuples_array , buffer_data);

    if(argc > 1){
        if(strcmp(argv[1], "show_tuples")){
            show_tuples_list(_tuples_array);
        }
            
    }
    

    // UNZIP
    char *data_unzip;
    data_unzip = unzip_data(_tuples_array);
    
    //data_unzip[strlen(data_unzip)] = '\0';
    //data_unzip[strlen(data_unzip)-1] = '\0';
    //data_unzip[strlen(data_unzip)-1] = '\0';
    //data_unzip[strcspn(data_unzip, "\n")] = '\0';
    //data_unzip[strcspn(data_unzip, "\0")] = '\0';
    
    printf("UNZIPED : [%s] LENGTH: [%d]\n",data_unzip,(int)strlen(data_unzip));

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