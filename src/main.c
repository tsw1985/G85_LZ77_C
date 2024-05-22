#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"

//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main(int argc, char *argv[])
{

    print_head_info();

    char file_name[] = "/home/gabriel/demotext.txt";
    FILE* file = print_file_info(file_name);
    if(NULL != file){
        start_zip_process(file);
    }


    char unzip_file_name[] = "/media/gabriel/1C20FACF20FAAF40/DEVELOPER/C/code/LZ77_C/demotext_ziped.g85";
    FILE* file_unzip = print_file_info(unzip_file_name);
    if(NULL != file_unzip){
        start_unzip_process(file_unzip);
    }





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

    // Empezamos a leer el fichero
    while ((readed_bytes = fread(buffer_data, sizeof(char), buffer_size, file)) > 0) {

        //if (readed_bytes < buffer_size) {
        //    printf("REDIMENSIONANDO BUFFER_DATA\n");
        //    buffer_data = (char*)realloc(buffer_data, readed_bytes * sizeof(char));
        //}

        // ---------------- ZIP DATA -----------------------
        add_firts_element_on_tuple_list(_tuples_array, buffer_data[0]);
        tuple_array *_tuple_to_file = zip_data(_tuples_array, buffer_data);

        // Una vez tenemos la tupla, pasamos a guardar esta misma estructura en un fichero de forma binaria
         //show_tuples_list(_tuple_to_file);

         if (_tuple_to_file) {
            // Primero escribimos el tamaño de la estructura tuple_array
            fwrite(&_tuple_to_file->size, sizeof(size_t), 1, target_file);

            // Luego escribimos las tuplas en sí
            fwrite(_tuple_to_file->tuple_list, sizeof(tuple), _tuple_to_file->size, target_file);
         }
        // ---------------- end ZIP DATA -----------------------

           // UNZIP
        //char *data_unzip = unzip_data(_tuples_array);
        //printf("-[%s] LENGTH: [%lu]\n",data_unzip, strlen(data_unzip));
        

    } // fin while read file

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

    // Leer el tamaño del array de tuplas
    fread(&array->size, sizeof(size_t), 1, file);

    // Asignar memoria para las tuplas
    array->tuple_list = (tuple *)malloc(array->size * sizeof(tuple));
    if (array->tuple_list == NULL) {
        printf("ERROR: malloc() failed for tuple_list\n");
        free(array);
        fclose(file);
        return NULL;
    }



    size_t readed_bytes;
    //empezamos a leer
    //while ((readed_bytes = fread(buffer_data, sizeof(char), buffer_size, file)) > 0) {




    // Leer las tuplas desde el archivo
    fread(array->tuple_list, sizeof(tuple), array->size, file);

    //show_tuples_list(array);

    char *data_unzip = unzip_data(array);
    printf("TUPLA DESCOMPRIMIDA -> [%s] LENGTH: [%lu]\n",data_unzip, strlen(data_unzip));



    //}//fin leer



    fclose(file);
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