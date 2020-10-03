/**
 * @mainpage
 * *Вариант 11*\n\n
 * Сортировка и поиск в таблице со списком машин
 * **Автор:** Маслова Марина
 * **Группа:** ИУ7-33Б
 */

#include <stdio.h>
#include <stdbool.h>

#include "menu.h"

#define OK 0

int main(void)
{
    int exit_code = OK;
    puts("ПРОГРАММА ОБРАБОТКИ СПИСКА МАШИН");

    while (true)
    {
        short int action;
        print_menu();
        exit_code = choose_action(&action);

        if (exit_code)
        {
            print_menu_error(exit_code);
            return exit_code;
        }

        if (!action)
        {
            puts("Спасибо за использование программы!");
            break;
        }

        exit_code = do_action(action);

        if (exit_code)
        {
            print_menu_error(exit_code);
            return exit_code;
        }
    }

    return exit_code;
}