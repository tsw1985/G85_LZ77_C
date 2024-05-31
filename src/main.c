#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/main.h"
#include "../header/compress.h"

#define DEBUG_ON 1
#define DEBUG_OFF 0

//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main(int argc, char *argv[])
{

    //char *output_file_name = (char*)malloc(sizeof(char));
    //printf("Hola\n");
    //return 0;

    int DEBUG_MODE = DEBUG_ON;

   print_head_info();
    char *file_name;

    if (DEBUG_MODE == DEBUG_OFF && argc < 2){
        printf("Usage to zip   : g85zip path/your/file.ext -c\n");
        printf("Usage to unzip : g85zip path/your/file.g85z -d\n");
    }else{

        
        if(DEBUG_MODE == 1){
            printf("[ *** INFO *** ] - DEBUG MODE ENABLED\n");
            char *file_name_debug = "/home/gabriel/datos.csv";
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
                start_zip_process(file,file_name);

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
    //tuple_array *_tuples_to_unzip = zip_data(_tuples_array, buffer_data);
    zip_data(buffer_data,file_size_bytes);

    
    // Una vez tenemos la tupla, pasamos a guardar esta misma estructura en un fichero de forma binaria
    //printf("- [ INFO ] - Tuples to write: [ %d ]\n",_tuples_array->size);
    //show_tuples_list(&_tuples_array);


    
    //write tuple on file
    
    //char *output_file_name = (char*)malloc(50 * sizeof(char));
    //strcpy(output_file_name,"ficheroDeSalida.txt");
    //printf("OUTPUTFILENAME-> %s\n",output_file_name);
    //strcat(output_file_name,".g85");
    //printf("FINAL NAME -> %s" , output_file_name);

    /*FILE *output_file = fopen(strcat(file_name,".g85"), "wb");
    if(output_file == NULL){
        printf("- [ ERROR ] - Error creating output file.\n");
        fclose(output_file);
    }else{
        //printf("- [ INFO ] - Creating ziped file [ %s ]\n", output_file_name);
        printf("- [ INFO ] - Creating ziped file [ %s ]\n", file_name);
        //show_tuples_list(_tuples_to_unzip);
    }*/


    
    //fclose(output_file);

    free(buffer_data);

    return 0;

}

void print_head_info(){
    printf(" - G85Zip: Zip -> 'g85 yourfile.xxx -zip | Unzip -> g85 yourfile.g85 -unzip \n");
}

FILE* print_file_info(char* file_name){
    FILE* file = fopen(file_name, "rb");
    if(NULL == file){
        printf("ERROR ! - File not found!\n");
    }else{
        printf("- [ INFO ] - File to zip : %s\n",file_name);
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