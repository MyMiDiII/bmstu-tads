#include <stdlib.h>
#include <string.h>

#include "files.h"
#include "io.h"

void add_to_file(FILE *file, char *string)
{
    int exit_code = OK;
    char *word;
    while (!read_string(&word, file))
    {
        read_string(&word, file);
        if (!strcmp(word, string))
            exit_code = 1;

        free(word);
    }

    if (!exit_code)
        fprintf(file, "%s\n", string);
}

size_t file_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}
