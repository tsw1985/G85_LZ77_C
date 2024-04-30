struct int_array{
    int size;
    int *array_pointer;

};
int_array *index_of(char *wordToSearch , char *letter);
int exists_char_on_string(char *string_to_search, char *letter);
void remove_tail_rare_symbols(char word[]);
char *_p_remove_tail_rare_symbols(char *word);