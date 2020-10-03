#include <stdio.h>
#include <stdlib.h>

#include "cars.h"

int upload_from_file(car_table_t *table)
{
    char *file_name = NULL;
    size_t len = 0;
    char ch;

    // ! после нормального считывания пункта меню убрать
    scanf("%c", &ch);
    puts("Введите имя файла (с путем при нахождении файла в другой директории):");

    if ((getline(&file_name, &len, stdin)) != -1)
    {
        FILE *file = fopen(file_name, "r");
        
        if (!file)
        {
            puts("Файл открыт!");

            if (fclose(file) == EOF)
                puts("Произошла неведомая хрень!");
        }
        else
            puts("Сударь, Вы ошиблись!");


        free(file_name);
    }
    else
        // ! убрать Сударя
        puts("Ну Вы молодец, Сударь, ведь ничего не работает");
}