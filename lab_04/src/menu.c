#include <stdio.h>

#include "menu.h"
#include "my_functions.h"
#include "errors.h"
#include "arr_stack.h"
#include "list_stack.h"

void print_menu(void)
{
    puts("");
    puts("          МЕНЮ");
    puts("");
    puts("1  - Добавить элемент в стек на массиве");
    puts("2  - Удалить элемент из стека на массиве");
    puts("3  - Вывести текущее состояние стека на массиве");
    puts("4  - Добавить элемент в стек на списке");
    puts("5  - Удалить элемент в стек на списке");
    puts("6  - Вывести текущее состояние стека на списке");
    puts("7  - Проверить, является ли слово палиндромом");
    puts("0  - Выход");
    puts("");
    puts("P. S.");
    puts("1) ;");
    puts("2) ;");
    puts("3) ");
    puts("");
}

void print_error_message(const int code)
{
    if (ERR_WRONG_ACTION == code)
    {
        puts("\nВведенный код не соответствует ни одному действию.");
        puts("Попробуйте ещё раз.\n");
    }
    else if (ERR_READ_ACTION == code)
    {
        puts("\nНекорректный ввод кода действия.");
        puts("Попробуйте ещё раз.\n");
    }
    else if (ERR_NULL_POINTER == code)
        puts("\nВ одну из функций передан нулевой указатель.");

    else if (ERR_EMPTY_STACK == code)
        puts("\nПустой стек");

    else if (ERR_FULL_STACK == code)
        puts("\nПереполнение стека!");
}

int choose_action(short int *const action)
{
    puts("Выберете пункт меню: ");

    char str[MAX_MENU_ITEM_LEN + 2];

    if (read_str(str, MAX_MENU_ITEM_LEN + 3, stdin))
        return ERR_READ_ACTION;

    char *end_prt;
    long int long_str = strtol(str, &end_prt, 10);

    if (*end_prt != '\0')
        return ERR_WRONG_ACTION;
    
    if (long_str < 0 || long_str > 7)
        return ERR_WRONG_ACTION;

    *action = (short int) long_str;

    return READ_OK;
}

int do_action(const short int action,
              arr_stack_t *a_stack,
              list_stack_t **l_stack)
{
    int exit_code = OK;

    switch (action)
    {
        case 1:
            puts("Добавление элемента массива ;)");
            exit_code = as_push(a_stack, 'a'); 
            break;

        case 2:
            puts("Удаление элемента массива ;)");
            char el1;
            exit_code = as_pop(a_stack, &el1);
            break;

        case 3:
            puts("Вывод массива ;)");
            exit_code = as_print(a_stack);
            break;

        case 4:
            puts("Ввод элемента списка ;)");
            exit_code = ls_push(l_stack, 'a');
            break;

        case 5:
            puts("Удаление элемента списка ;)");
            char el2;
            exit_code = ls_pop(l_stack, &el2);
            break;

        case 6:
            puts("Вывод элемента списка ;)");
            exit_code = ls_print(*l_stack);
            break;

        case 7:
            puts("Любое слово палиндром в кольце по модулю 1 ;)");
            break;

        default:
            puts("\nСпасибо за использование программы!");
            puts("Автор:  МАСЛОВА МАРИНА");
            puts("Группа: ИУ7-33Б");
            exit(EXIT_SUCCESS);
            break;
    }

    return exit_code;
}