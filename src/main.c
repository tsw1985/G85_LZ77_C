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
    printf("BUFFER SIZE %d\n",buffer_size);
    char *buffer_data = (char*)malloc(buffer_size * sizeof(char));
    
    //DEMO STRINGS + 398 chars, pete.
    strcpy(buffer_data, "ESsTE jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjiiiiiiiiiiiiiiiiiiiiiiiiiipppppppppppppppppppppppppp oooooooooooooooooooooooooooooooo iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiijhkjhiiiiiiiiiiiiiiiiioooooooooooooooooooooojjjjjjjjjjjjjjjjjjjjjjjjjjjYyyyyyjijiojoij oij oij oij oij oij oij oij yyy jejeejejejelggggggggggggggzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzddddooodddddssssssssksssllssllllsssss4");
    //strcpy(buffer_data, "TUN TUN CAS RASCA LA CACHARRA jaja jeje");
    unsigned long zip_data_size = (unsigned long)strlen(buffer_data);
    printf("TO ZIP  : [%s] LENGTH: [%d]\n",buffer_data,zip_data_size);

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
    unsigned long unzip_data_size = (unsigned int)strlen(data_unzip);
    if(unzip_data_size > zip_data_size){
        //data_unzip[strlen(data_unzip)-1] = '\0';
    }

    printf("\n");
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