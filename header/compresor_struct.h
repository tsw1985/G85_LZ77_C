//Struct tuple
typedef struct tuple
{
    unsigned short go_back_positions;
    char get_number_chars;
    char next_char;   
} tuple;

//list of tuples
typedef struct 
{
    tuple *tuple_list;
    int size;
    int capacity;
} tuple_array;


typedef struct decompressed_bytes {
    char* buf;
    int   capacity;
    int   len;
} decompressed_bytes;


typedef struct
{
    int length;
    char *pointer_data_unziped;
     
} data_unziped_struct;

const int search_buf    = 1024;
const int lookahead_buf = 100; // limited to 255