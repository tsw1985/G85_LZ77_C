#include <stdio.h>
#include <stdlib.h>
#include <../header/main.h>
#include <../header/compresor_struct.h>


//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main()
{
    print_head_info();
    char *compress_text = "ABRA_CADABRA_PATA_DE_CABRA";
    printf("A COMPRIMIR: %s\n",compress_text);


    return 0;
}

void print_head_info(){
    printf("********************************************\n");
    printf("Bienvenido al compresor Descompresor G85\n");
    printf("Uso para comprimir : g85 file.g85 -c\n");
    printf("Uso para descomprimir : g85 file.g85 -d\n");
    printf("********************************************\n");
}