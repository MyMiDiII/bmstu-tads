#include <stdio.h>

#include "err.h"

void print_err(const int code)
{
    switch (code)
    {
        case (ERR_ARGS_NUM):
            puts("\033[31mНеверное количество аргументов! (./app.exe filename)\033[0m");
            break;
        case (ERR_OPEN_FILE):
            puts("\033[31mНе удалось открыть файл!\033[0m");
            break;
        case (ERR_CLOSE_FILE):
            puts("\033[31mНе удалось закрыть файл!\033[0m");
            break;
        case (ERR_MEMORY):
            puts("\033[31mОшибка выделения памяти!\033[0m");
            break;
        case (ERR_TOO_BIG_SIZE):
            puts("\033[31mПревышен максимальный размер таблицы!\033[0m");
            break;
        default:
            puts("\033[32m\nСпасибо за использование программы!\033[0m");
            puts("Автор: Маслова Марина");
            puts("Группа: ИУ7-33Б");
            break;
    }
}
