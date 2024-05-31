#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"


//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main(int argc, char *argv[])
{

   print_head_info();
    

    if (argc < 2){
        printf("Usage to zip   : g85zip path/your/file.ext -c\n");
        printf("Usage to unzip : g85zip path/your/file.g85z -d\n");
    }else{

        char *file_name = (char*)malloc(strlen(argv[1] + 1));
        strcpy(file_name,argv[1]);
        FILE* file = print_file_info(file_name);
        if(NULL != file){

            if(argv[2][0] == '-') {

                switch (argv[2][1]){
                    case 'c':{
                        printf("_-: Starting compression :-_\n");
                        start_zip_process(file,file_name);
                        break;
                    }

                    case 'd':{
                        printf("_-: Starting descompression :-_\n");
                        
                        break;
                    }
                }

             }
        }
    }

    return 0;
}

size_t file_size(FILE* file){
    size_t file_size;
    if(NULL == file){
        printf("ERROR ! - File not found to get size!\n");
    }else{
        fseek(file,0L,SEEK_END);
        file_size = ftell(file);
        fseek(file,0L,SEEK_SET);
    }
    return file_size;
}


int start_zip_process(FILE* file , char* file_name){

    fseek(file, 0L, SEEK_SET);
    size_t readed_bytes = file_size(file);

    printf(" - BUFFER SIZE: [ %d ]\n", search_buf);
    char *buffer_data = (char*)malloc(readed_bytes * sizeof(char));
    
    tuple_array *_tuples_array = create_tuple_array(); // Creamos objeto para guardar las tuplas

    int first_time = 0; // Variable para controlar y guardar el primer byte leido del fichero
    size_t blocks_counter = 0; // Variable para controlar los bloques que vamos leyendo, de 10 en 10 bytes (test)

    // Creamos fichero objetivo binario
    FILE* target_file = fopen("demotext_ziped.g85", "wb");
    if (!target_file) {
        perror("Error al abrir el fichero objetivo");
        free(buffer_data);
        free(_tuples_array->tuple_list);
        free(_tuples_array);
        return -1;
    }

    //me vuelvo a poner en el principio del fichero
    fseek(file, 0L, SEEK_SET);

    tuple_ziped *_tuple_ziped = (tuple_ziped*)malloc(sizeof(tuple_ziped));

    fread(buffer_data, sizeof(char), readed_bytes, file);

    // ---------------- ZIP DATA -----------------------
    add_firts_element_on_tuple_list(_tuples_array, buffer_data[0]);
    tuple_array *_tuples_to_unzip = zip_data(_tuples_array, buffer_data);

    // Una vez tenemos la tupla, pasamos a guardar esta misma estructura en un fichero de forma binaria
    //printf("TUPLA NUMERO [%d]\n",_tuples_to_unzip->size);
    show_tuples_list(_tuples_to_unzip);


    fclose(file);
    fclose(target_file);

    free(buffer_data);
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

FILE* print_file_info(char* file_name){
    FILE* file = fopen(file_name, "rb");
    if(NULL == file){
        printf("ERROR ! - File not found!\n");
    }else{
        printf("SUCCESS ! - File founded!\n");
        fseek(file,0L,SEEK_END);
        unsigned long file_size = ftell(file);
        printf("File size : %lu bytes\n",file_size);
        fseek(file,0L,SEEK_SET);
    }
    return file;
}