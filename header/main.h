void print_head_info();
int start_zip_process(FILE* file , char* file_name);
int start_unzip_process(FILE* file , char* file_name);
FILE *print_file_info(char* file_name);
size_t file_size(FILE* file);
void* print_loading(void* arg);