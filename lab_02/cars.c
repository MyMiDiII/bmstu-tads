#include <stdio.h>
#include <stdlib.h>

#include "cars.h"
#include "errors.h"

int upload_from_file(car_table_t *table)
{
    char *file_name = NULL;
    size_t len = 0;
    char ch;
    int read;

    // ! после нормального считывания пункта меню убрать
    scanf("%c", &ch);
    puts("Введите имя файла (с путем при нахождении файла в другой директории):");

    if ((read = getline(&file_name, &len, stdin)) != -1)
    {
        if ('\n' == file_name[read - 1])
            file_name[read - 1] = '\0';

        // for (int i = 0; i < read - 1; i++)
        //    printf("%c", file_name[i]);

        FILE *file = fopen(file_name, "r");
        free(file_name);
        
        if (file)
        {
            // считать данные из файла

            if (fclose(file) == EOF)
                puts("Произошла неведомая хрень!");
        }
        else
            return ERR_OPEN_FILE;
    }
    else
        return ERR_READ_FILE_NAME;
}