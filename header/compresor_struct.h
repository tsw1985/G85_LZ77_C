//Struct tuple
typedef struct info_tuple
{
    int go_back_positions;
    int get_chars;
    char next_char;   
} struct_info_tuple;

//list of tuples
typedef struct info_tuple_array
{
    struct_info_tuple tuple_list;
    long size;
};

 