#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"

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


    

    //primero hacer que el comprimido ocupe menos , no mas :)
    /*FILE* file_unzip = print_file_info(unzip_file_name);
    if(NULL != file_unzip){
        start_unzip_process(file_unzip);
    }*/





    return 0;
}



int start_zip_process(FILE* file){

    // Ponemos el fichero en el principio y preparamos buffer y variable de bytes leidos
    fseek(file, 0L, SEEK_SET);
    size_t readed_bytes;

    long buffer_size = 10; // 128 * 1024;
    printf("BUFFER SIZE: [ %lu ]\n", buffer_size);
    char *buffer_data = (char*)malloc(buffer_size * sizeof(char));

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


    //me vuelvo a poner en el principio del fichero
    fseek(file, 0L, SEEK_SET);

    // Primero escribimos el tamaño de la estructura tuple_array
    fwrite(&total_tuplas, sizeof(size_t), 1, target_file);


    total_tuplas = 0;

    while ((readed_bytes = fread(buffer_data, sizeof(char), buffer_size, file)) > 0 ) {
        
        //printf("DATOS LEIDOS %s\n",buffer_data);

        if (readed_bytes < buffer_size) {
            //printf("REDIMENSIONANDO BUFFER_DATA\n");
            buffer_data = (char*)realloc(buffer_data, readed_bytes * sizeof(char));
            
        }

        // ---------------- ZIP DATA -----------------------
        add_firts_element_on_tuple_list(_tuples_array, buffer_data[0]);
        tuple_array *_tuple_to_file = zip_data(_tuples_array, buffer_data);

         // Una vez tenemos la tupla, pasamos a guardar esta misma estructura en un fichero de forma binaria
         //printf("TUPLA NUMERO [%d]\n",total_tuplas);
         //show_tuples_list(_tuple_to_file);

         if (_tuple_to_file) {
            // Primero escribimos el tamaño de la estructura tuple_array
            //fwrite(&_tuple_to_file->size, sizeof(size_t), 1, target_file);

            // Luego escribimos las tuplas en sí
            fwrite(_tuple_to_file->tuple_list, sizeof(tuple), _tuple_to_file->size, target_file);
         }
        // ---------------- end ZIP DATA -----------------------

        // UNZIP
        //char *data_unzip = unzip_data(_tuples_array);
        //printf("-[%s] LENGTH: [%lu]\n",data_unzip, strlen(data_unzip));
        
        memset(buffer_data,0,readed_bytes);


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


tuple_array *start_unzip_process(FILE *file){
    

    printf("DESCOMPRIMIENDO !!\n");

    if (!file) {
        perror("Error al abrir el fichero para lectura");
        return NULL;
    }

    tuple_array *array = create_tuple_array();
    array->tuple_list = (tuple*)malloc(sizeof(tuple));

    // Leer el tamaño del array de tuplas
    fread(&array->size, sizeof(size_t), 1, file);
    printf("HAY [%d] TUPLAS en el fichero\n",array->size);


    //leemos primero el fichero para saber cuantas tuplas habran dentro
    size_t pre_readed_bytes;
    tuple *pre_buffer_data = (tuple*)malloc(sizeof(tuple));
    size_t pre_total_tuples = 0;
    
    //ponemos el fichero desde el inicio
    rewind(file);
    while ((pre_readed_bytes = fread(pre_buffer_data, 1, sizeof(tuple), file)) > 0) {
        pre_total_tuples++;
    }


    printf("PARA EL FOR HAY UN TOTAL DE %d tuplas\n",pre_total_tuples);

    fclose(file);

    file = fopen(file_name, "rb");
    array->tuple_list = (tuple*)realloc(array->tuple_list , pre_total_tuples * sizeof(tuple));

    //empezamos a leer las tuplas
    //ponemos el fichero desde el inicio
    rewind(file);

    size_t tupla_size = sizeof(tuple);
    size_t readed_bytes;
    tuple *buffer_data = (tuple*)malloc(sizeof(tuple));
    printf("EL TAMAÑO DE UNA TUPLA ES %d\n",tupla_size);
    size_t indice_tuplas = 0;
    
    for(size_t i = 0 ; i < pre_total_tuples ; i++){

    


        fread(buffer_data, 1, sizeof(tuple), file);

        if(buffer_data->next_char != '\n'){
            //printf("BYTES LEIDOS -> %d  y letra tupla -> %c\n",readed_bytes,buffer_data->next_char);
        }
        

        //printf("TUPLA NUMERO %d\n",i);
        
        //tuple tupla ;
        
        
        //fread(&tupla, sizeof(tuple), 1, file);
        //array->tuple_list[i]=tupla;
        
        //fseek(file, tupla_size*(i+1), SEEK_CUR);
        //printf("LETRA -> %c\n",tupla.next_char);

       


        
        //show_tuples_list(array);
    } //end for*/


    //char *data_unzip = unzip_data(array);
    //printf("-[%s] LENGTH: [%lu]\n",data_unzip, strlen(data_unzip));

    
   


    fclose(file);
    //fclose(fileUnziped);
    return array;
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