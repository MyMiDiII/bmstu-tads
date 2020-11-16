#include <stdio.h>

#include "menu.h"
#include "my_functions.h"
#include "errors.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "free_areas.h"
#include "palindrome.h"

void print_menu(void)
{
    puts("");
    puts("          СТЕК");
    puts("");
    puts("1  - Добавить элемент в стек на массиве");
    puts("2  - Удалить элемент из стека на массиве");
    puts("3  - Вывести текущее состояние стека на массиве");
    puts("4  - Добавить элемент в стек на списке");
    puts("5  - Удалить элемент в стек на списке");
    puts("6  - Вывести текущее состояние стека на списке");
    puts("7  - Вывести адреса освобожденных областей");
    puts("8  - Проверить, является ли слово палиндромом");
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
        puts("\nСтек пуст!");

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
    
    if (long_str < 0 || long_str > 8)
        return ERR_WRONG_ACTION;

    *action = (short int) long_str;

    return READ_OK;
}

int do_action(const short int action, arr_stack_t *a_stack,
              list_stack_t **l_stack, free_areas_t *ptrs)
{
    int exit_code = OK;

    switch (action)
    {
        case 1:
        {
            exit_code = as_push(a_stack, 'a'); 
            
            if (!exit_code)
                puts("\nЭлемент успешно добавлен!");

            break;
        }

        case 2:
        {
            char el1;
            exit_code = as_pop(a_stack, &el1);

            if (!exit_code)
                printf("\nЭлемент '%c' успешно удален!\n", el1);

            break;
        }

        case 3:
        {
            puts("\nТекущее состояние стека на массиве:");
            exit_code = as_print(a_stack);
            break;
        }

        case 4:
        {
            exit_code = ls_push(l_stack, 'a');

            if (!exit_code)
                puts("\nЭлемент успешно добавлен!");

            delete_area(ptrs, *l_stack);
            break;
        }

        case 5:
        {
            char el2;

            add_area(ptrs, *l_stack);

            exit_code = ls_pop(l_stack, &el2);

            if (!exit_code)
                printf("\nЭлемент '%c' успешно удален!\n", el2);

            break;
        }

        case 6:
        {
            puts("\nТекущее состояние стека на списке:");
            
            if (*l_stack)
                puts("\n    Адрес узла   Значение элемента");

            exit_code = ls_print(l_stack);
            break;
        }

        case 7:
        {
            if (print_free_areas(ptrs))
            {
                puts("\nПамять ещё не выделялась, или все освобожденные");
                puts("области были снова использованы!");
            }
            break;
        }

        case 8:
        {
            // exit_code = check_word();
            break;
        }

        default:
            puts("\nСпасибо за использование программы!");
            puts("Автор:  МАСЛОВА МАРИНА");
            puts("Группа: ИУ7-33Б");
            exit(EXIT_SUCCESS);
            break;
    }

    return exit_code;
}