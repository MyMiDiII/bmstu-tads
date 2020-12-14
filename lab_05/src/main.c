/**
 * @mainpage
 * *Вариант 11*\n\n
 * Реализация стека на массиве и списке. Палиндром.
 * **Автор:** Маслова Марина
 * **Группа:** ИУ7-33Б
 */

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "menu.h"
#include "errors.h"
#include "arr_queue.h"
#include "list_queue.h"
//#include "free_areas.h"

#define OK 0

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int exit_code = OK;
    arr_queue_t arr_queue = { .length = 0, .in = 0, .out = 0 };
    list_queue_t list_queue = { .in = NULL, .length = 0, .out = NULL };
    // free_areas_t ptrs = { .len = 0 };

    while (true)
    {
        // fwprintf(stdout, L"in = %p out = %p length = %d\n", list_queue.in, list_queue.out, list_queue.length);
        short int action;
        print_menu();
        exit_code = choose_action(&action);

        if (exit_code)
        {
            print_error_message(exit_code);
            continue;
        }

        exit_code = do_action(action, &arr_queue, &list_queue);

        if (exit_code)
        {
            print_error_message(exit_code);
            continue;
        }
    }

    return OK;
}
