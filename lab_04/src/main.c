/**
 * @mainpage
 * *Вариант 11*\n\n
 * Реализация стека на массиве и списке. Палиндром.
 * **Автор:** Маслова Марина
 * **Группа:** ИУ7-33Б
 */

#include <stdio.h>
#include <stdbool.h>

#include "menu.h"
#include "errors.h"
#include "arr_stack.h"
#include "list_stack.h"

#define OK 0

int main(void)
{
    puts("СТЕК");

    int exit_code = OK;
    arr_stack_t arr_stack = { .length = 0 };
    list_stack_t *list_stack = NULL;

    while (true)
    {
        short int action;
        print_menu();
        exit_code = choose_action(&action);

        if (exit_code)
        {
            print_error_message(exit_code);
            continue;
        }

        exit_code = do_action(action, &arr_stack, &list_stack);
        printf("%p\n", (void *) list_stack);

        if (exit_code)
        {
            print_error_message(exit_code);
            continue;
        }
    }

    return OK;
}