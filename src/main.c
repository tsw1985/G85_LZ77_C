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

    return 0;
}



int start_zip_process(FILE* file){

    //Ponemos el fichero en el principio y preparamos buffer y variable de bytes leidos
    fseek(file,0L,SEEK_SET);
    size_t readed_bytes;


    long buffer_size = 10; //128 * 1024;
    printf("BUFFER SIZE: [ %lu ]\n",buffer_size);
    char *buffer_data = (char*)malloc(buffer_size * sizeof(char));
    

    tuple_array *_tuples_array = create_tuple_array(); //creamos objeto para guardar las tuplas

    int first_time = 0; //variable para controlar y guardar el primer byte leido del fichero
    size_t blocks_counter = 0; //variable para controlar los bloques que vamos leyendo, de 10 en 10 bytes (test)


    //creamos fichero objetivo binario
    FILE* target_file = fopen("demotext_ziped.g85","w");
 
    //empezamos a leer el fichero
    while ((readed_bytes = fread(buffer_data, sizeof(char), buffer_size, file)) > 0) {

        unsigned long zip_data_size = (unsigned long)strlen(buffer_data);
        printf("+: [%s] LENGTH: [%lu]\n",buffer_data,zip_data_size);

        // ---------------- ZIP DATA -----------------------
        add_firts_element_on_tuple_list(_tuples_array,buffer_data[0]);
        tuple_array *_tuple_to_file = zip_data(_tuples_array , buffer_data);

        //una vez tenemos la tupla , pasamos a guardar esta misma estructura
        //en un fichero de forma binaria

        show_tuples_list(_tuple_to_file);

        //if(_tuple_to_file){
            //write file zipped
            //fwrite(&_tuple_to_file,sizeof(tuple_array),1,target_file);
        //}
        // ---------------- end ZIP DATA -----------------------



        if(buffer_size >= blocks_counter){
            fseek(file , blocks_counter , SEEK_CUR);
            blocks_counter = blocks_counter + buffer_size ;
        }



        // UNZIP
        //char *data_unzip = unzip_data(_tuples_array);
        //printf("-: [%s] LENGTH: [%lu]\n",data_unzip, strlen(data_unzip));


    } //fin while read file



    
    fclose(file);
    fclose(target_file);
    
    free(_tuples_array->tuple_list);
    free(_tuples_array);

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