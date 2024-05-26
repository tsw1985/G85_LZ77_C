#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"

//DEVELOP PHASE
char file_name[] = "/home/gabriel/demotext.txt";
char unzip_file_name[] = "/media/gabriel/1C20FACF20FAAF40/DEVELOPER/C/code/LZ77_C/demotext_ziped.g85";

//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main(int argc, char *argv[])
{

    print_head_info();

    
    FILE* file = print_file_info(file_name);
    if(NULL != file){
        start_zip_process(file);
    }

    //TODO UNZIP PROCESS HERE
    return 0;
}



int start_zip_process(FILE* file){

    // Ponemos el fichero en el principio y preparamos buffer y variable de bytes leidos
    fseek(file, 0L, SEEK_SET);
    size_t readed_bytes;

    long buffer_size = 100; // 128 * 1024;
    printf("BUFFER SIZE: [ %lu ]\n", buffer_size);
    char *buffer_data = (char*)malloc(buffer_size * sizeof(char));
    memset(buffer_data,0,buffer_size);

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

    // Empezamos a leer el fichero y contamos cuantas tuplas van a haber
    int total_tuplas = 0;

    while ((readed_bytes = fread(buffer_data, sizeof(char), buffer_size, file)) > 0 ) {
        total_tuplas++;
    }


    printf("EN COMPRESION : Se han encontrado %d tuplas\n",total_tuplas);

    //me vuelvo a poner en el principio del fichero
    fseek(file, 0L, SEEK_SET);


    total_tuplas = 0;

    tuple_ziped *_tuple_ziped = (tuple_ziped*)malloc(sizeof(tuple_ziped));

    while ((readed_bytes = fread(buffer_data, sizeof(char), buffer_size, file)) > 0 ) {
        
        //printf("DATOS LEIDOS %s\n",buffer_data);

        if (readed_bytes < buffer_size) {
            //printf("REDIMENSIONANDO BUFFER_DATA\n");
            buffer_data = (char*)realloc(buffer_data, readed_bytes * sizeof(char));
            
        }

        // ---------------- ZIP DATA -----------------------
        add_firts_element_on_tuple_list(_tuples_array, buffer_data[0]);
        tuple_array *_tuple_to_file = zip_data(_tuples_array, buffer_data);
        memset(buffer_data,0,readed_bytes);
        printf("---------------------------\n");

         // Una vez tenemos la tupla, pasamos a guardar esta misma estructura en un fichero de forma binaria
         //printf("TUPLA NUMERO [%d]\n",total_tuplas);
         show_tuples_list(_tuple_to_file);


   
        // ---------------- end ZIP DATA -----------------------
            // UNZIP
        char *data_unzip = unzip_data(_tuples_array);
        clean_return_buffer(data_unzip);
        printf("- TUPLE UNZIPED: [%s] LENGTH: [%lu]\n",data_unzip, strlen(data_unzip));

        

        
        total_tuplas++;

    } // fin while read file

    printf("EL FICHERO TUVO [%d] total de tuplas\n",total_tuplas);




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