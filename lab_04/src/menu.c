#include <stdio.h>
#include <wchar.h>

#include "menu.h"
#include "my_functions.h"
#include "errors.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "free_areas.h"
#include "palindrome.h"

void print_menu(void)
{
    putws(L"\n          СТЕК\n\n");
    putws(L"1  - Добавить элемент в стек на массиве\n");
    putws(L"2  - Удалить элемент из стека на массиве\n");
    putws(L"3  - Вывести текущее состояние стека на массиве\n");
    putws(L"4  - Добавить элемент в стек на списке\n");
    putws(L"5  - Удалить элемент в стек на списке\n");
    putws(L"6  - Вывести текущее состояние стека на списке\n");
    putws(L"7  - Вывести адреса освобожденных областей\n");
    putws(L"8  - Проверить, является ли слово палиндромом\n");
    putws(L"0  - Выход\n");
    putws(L"");
    putws(L"P. S.");
    putws(L"1) ;");
    putws(L"2) ;");
    putws(L"3) ");
    putws(L"");
}

void print_error_message(const int code)
{
    if (ERR_WRONG_ACTION == code)
    {
        putws(L"\nВведенный код не соответствует ни одному действию.");
        putws(L"Попробуйте ещё раз.\n");
    }
    else if (ERR_READ_ACTION == code)
    {
        putws(L"\nНекорректный ввод кода действия.");
        putws(L"Попробуйте ещё раз.\n");
    }
    else if (ERR_NULL_POINTER == code)
        putws(L"\nВ одну из функций передан нулевой указатель.");

    else if (ERR_EMPTY_STACK == code)
        putws(L"\nСтек пуст!");

    else if (ERR_FULL_STACK == code)
        putws(L"\nПереполнение стека!");
}

int choose_action(short int *const action)
{
    putws(L"Выберете пункт меню: ");

    wchar_t str[MAX_MENU_ITEM_LEN + 2];

    if (read_wstr(str, MAX_MENU_ITEM_LEN + 3, stdin))
        return ERR_READ_ACTION;

    wchar_t *end_prt;
    long int long_str = wcstol(str, &end_prt, 10);

    if (*end_prt != L'\0')
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
                putws(L"\nЭлемент успешно добавлен!");

            break;
        }

        case 2:
        {
            wint_t el1;
            exit_code = as_pop(a_stack, &el1);

            if (!exit_code)
                fwprintf(stdout, L"\nЭлемент '%c' успешно удален!\n", el1);

            break;
        }

        case 3:
        {
            putws(L"\nТекущее состояние стека на массиве:");
            exit_code = as_print(a_stack);
            break;
        }

        case 4:
        {
            exit_code = ls_push(l_stack, 'a');

            if (!exit_code)
                putws(L"\nЭлемент успешно добавлен!");

            delete_area(ptrs, *l_stack);
            break;
        }

        case 5:
        {
            wint_t el2;

            add_area(ptrs, *l_stack);

            exit_code = ls_pop(l_stack, &el2);

            if (!exit_code)
                fwprintf(stdout, L"\nЭлемент '%c' успешно удален!\n", el2);

            break;
        }

        case 6:
        {
            putws(L"\nТекущее состояние стека на списке:");
            
            if (*l_stack)
                putws(L"\n    Адрес узла   Значение элемента");

            exit_code = ls_print(l_stack);
            break;
        }

        case 7:
        {
            if (print_free_areas(ptrs))
            {
                putws(L"\nПамять ещё не выделялась, или все освобожденные");
                putws(L"области были снова использованы!");
            }
            break;
        }

        case 8:
        {
            exit_code = check_word();
            break;
        }

        default:
            putws(L"\nСпасибо за использование программы!");
            putws(L"Автор:  МАСЛОВА МАРИНА");
            putws(L"Группа: ИУ7-33Б");
            exit(EXIT_SUCCESS);
            break;
    }

    return exit_code;
}