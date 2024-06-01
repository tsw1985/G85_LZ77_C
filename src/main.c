#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"

#include <pthread.h>   // Para hilos
#include <unistd.h>    // Para usleep

volatile int STOP_SPINNER = 0;

#define DEBUG_ON 1
#define DEBUG_OFF 0


int main(int argc, char *argv[])
{

    int DEBUG_MODE = DEBUG_ON;

    pthread_t spinner_thread;

    // Crear el hilo para la animación de carga
    pthread_create(&spinner_thread, NULL, print_loading, NULL);


    print_head_info();
    char *file_name;

    if (DEBUG_MODE == DEBUG_OFF && argc < 2){
        printf("Usage to zip   : g85zip path/your/file.ext -c\n");
        printf("Usage to unzip : g85zip path/your/file.g85z -d\n");
    }else{

        
        if(DEBUG_MODE == 1){
            printf("[ *** INFO *** ] - DEBUG MODE ENABLED\n");
            char *file_name_debug = "/home/gabriel/FreeDOS.vdi";
            //char *file_name_debug = "/home/gabriel/demotext.txt";
            file_name = (char*)malloc(strlen(file_name_debug) * sizeof(char));
            strcpy(file_name,file_name_debug);
        }else{
            file_name = (char*)malloc(strlen(argv[1] + 1));
            strcpy(file_name,argv[1]);
        }
        
        FILE* file = print_file_info(file_name);
        if(NULL != file){


            if(DEBUG_MODE == DEBUG_ON){
                printf("- [ DEBUG ] - Starting compression ...\n");
                // Crear el hilo para la animación de carga
                pthread_create(&spinner_thread, NULL, print_loading, NULL);
                start_zip_process(file,file_name);
                // Esperar a que el hilo de la animación termine
                STOP_SPINNER = 1;
                pthread_join(spinner_thread, NULL);

            }else{

                if(argv[2][0] == '-') {

                switch (argv[2][1]){
                    case 'c':{
                        printf("- [ INFO ] - Starting compression ...\n");
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

        fclose(file);
    }

    return 0;
}


int start_zip_process(FILE* file , char* file_name){

    fseek(file, 0L, SEEK_SET);
    int file_size_bytes = file_size(file);
    printf("- [ INFO ] - File size: [ %d ] bytes\n", file_size_bytes);
    printf("- [ INFO ] - Search buffer size: [ %d ] bytes\n", search_buf);

    //Buffer to save bytes of file
    char *buffer_data = (char*)malloc(file_size_bytes * sizeof(char));

    //We read the hole file and we save all bytes on buffer_data
    fread(buffer_data, sizeof(char), file_size_bytes, file);

    //sent the array to save the tuples and the buffer data
    tuple_array _tuple_array_pointer = zip_data(buffer_data,file_size_bytes);
    printf("- [ INFO ] - Total tuples: [%d]\n",_tuple_array_pointer.size);

    //Create ouput file
    FILE* output_file = fopen(strcat(file_name,".g85") ,"wb");
    if(output_file == NULL){
        fclose(output_file);
        printf("- [ ERROR ] - Error creating output file %s.%s\n",file_name,"g85");    
    }else{
        fwrite(_tuple_array_pointer.tuple_list, sizeof(tuple) * _tuple_array_pointer.size, 1, output_file);
        printf("- [ INFO ] - File ziped on: [ %s ]\n",file_name,".g85");
    }
    

    fclose(output_file);
    free(buffer_data);

    return 0;
}


void* print_loading(void* arg) {
    char spinner[] = "-\\|/";
    int i = 0;

    while (STOP_SPINNER == 0) {
        printf("\r%c", spinner[i]);
        fflush(stdout);
        i = (i + 1) % 4;
        //usleep(100000); // Retardo de 100 milisegundos
    }

    return NULL;
}

void print_head_info(){
    printf(" - G85Zip: Zip -> 'g85 yourfile.xxx -zip | Unzip -> g85 yourfile.g85 -unzip \n");
}

FILE* print_file_info(char* file_name){
    printf("- [ INFO ] - File to zip : %s\n",file_name);
    FILE* file = fopen(file_name, "rb");
    if(NULL == file){
        printf("ERROR ! - File not found!\n");
    }
    return file;
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