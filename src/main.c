#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/gstring.h"

#define TRUE 1
#define FALSE 0 

//How to compile ? write "make clean ; make" . Later enter to /bin folder and play
int main()
{
    system("clear");
    printf("Bienvenido al juego del ahorcado. Tienes 5 oportunidades. Introduce una palabra: ");
    char word_to_play[200];
    char word_to_show[200];
    int total_chars = 0;

    scanf("%s",word_to_play);
    //remove_tail_rare_symbols(word_to_play);
    //remove_tail_rare_symbols(word_to_show);

    _p_remove_tail_rare_symbols(word_to_play);
    _p_remove_tail_rare_symbols(word_to_show);


    memset(word_to_show,'*',strlen(word_to_play));

    system("clear");
    total_chars = (int)strlen(word_to_show);
    printf("Tienes que averiguar %d letras\n", total_chars);

    
    int lifes = 5;
    int win = 0;
    int end_game = 0;
    int_array *matchs_list = NULL;

    

    while(end_game == 0)
    {
        system("clear");
        printf("%s\n",word_to_show);

        char letter[2];
        printf("Tienes %d oportunidades y vas por %d aciertos de %d. ¿letra?-> ",lifes,win,total_chars);
        scanf("%s",letter);
        //remove_tail_rare_symbols(letter);
        _p_remove_tail_rare_symbols(letter);

         if (exists_char_on_string(word_to_show,letter) == 0)
         {
             lifes--;
         }
         else
         {

            matchs_list = index_of(word_to_play,letter);
            if(matchs_list != NULL){
                
                int exists_match = 0;
                for(int index_match_list = 0 ; index_match_list < matchs_list->size ; index_match_list++){
                    int match = matchs_list->array_pointer[index_match_list];
                    if(match != -1){
                        exists_match = 1;
                        word_to_show[match] = letter[0];
                        win++;
                    }
                }

                if(exists_match == 0){
                    lifes--;
                }

                //check if user win
                char *check_hidden_chars = NULL; 
                check_hidden_chars = strchr(word_to_show , '*' );
                if(check_hidden_chars == NULL){
                    printf("%s\n",word_to_play);
                    printf("BIEN !! HAS GANADO!!\n");
                    end_game = 1;
                }

                if(lifes == 0){
                    printf("%s\n",word_to_play);
                    printf("PERDISTE :(\n");
                    end_game = 1;
                }
        }
    };
}
    free(matchs_list->array_pointer);
    return 0;
}