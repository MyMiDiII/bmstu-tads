#include "files.h"

void add_to_file(FILE *file, char *string)
{
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s\n", string);
}

size_t file_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}
