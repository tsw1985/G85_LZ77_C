//Struct tuple
typedef struct
{
    int go_back_positions;
    int get_number_chars;
    char next_char;   
} tuple;

//list of tuples
typedef struct 
{
    tuple *tuple_list;
    long size;
} tuple_array;

typedef struct
{
    int length;
    char *pointer_data_unziped;
     
} data_unziped_struct;

typedef struct
{
    int length;
    char *pointer_data_ziped;
     
} data_ziped_struct;

//Struct to save zip data on file
#pragma pack(push, 1)
typedef struct
{
    char go_back_get_chars;
    char next_char;   
} tuple_ziped;
#pragma pack(pop)