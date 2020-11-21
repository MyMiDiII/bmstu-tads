#include <stdio.h>
#include <wchar.h>

#include "menu.h"
#include "my_functions.h"
#include "errors.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "free_areas.h"
#include "palindrome.h"
#include "read_symbols.h"
#include "num_pops.h"

void print_menu(void)
{
    putws(L"\n          СТЕК\n\n");
    putws(L"1  - Добавить элементы в стек на массиве\n");
    putws(L"2  - Удалить элементы из стека на массиве\n");
    putws(L"3  - Вывести текущее состояние стека на массиве\n");
    putws(L"4  - Добавить элементы в стек на списке\n");
    putws(L"5  - Удалить элементы из стека на списке\n");
    putws(L"6  - Вывести текущее состояние стека на списке\n");
    putws(L"7  - Вывести адреса освобожденных областей\n");
    putws(L"8  - Проверить, является ли слово палиндромом\n");
    putws(L"0  - Выход\n\n");
}

void print_error_message(const int code)
{
    if (ERR_WRONG_ACTION == code)
    {
        putws(L"\nВведенный код не соответствует ни одному действию.\n");
        putws(L"Попробуйте ещё раз.\n");
    }
    else if (ERR_READ_ACTION == code)
    {
        putws(L"\nНекорректный ввод кода действия.\n");
        putws(L"Попробуйте ещё раз.\n");
    }
    else if (ERR_NULL_POINTER == code)
        putws(L"\nВ одну из функций передан нулевой указатель.\n");

    else if (ERR_EMPTY_STACK == code)
        putws(L"\nСтек пуст!\n");

    else if (ERR_FULL_STACK == code)
        putws(L"\nПереполнение стека!\n");

    else if (ERR_NONINTEGER == code)
        putws(L"\nВведенные данные нецелочисленные!\n");

    else if (ERR_INVALID_NUM == code)
        putws(L"\nВведенное количество выходит за допустимый диапазон!\n");
}

int choose_action(short int *const action)
{
    putws(L"Выберете пункт меню: \n");

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
            putws(L"\nСчитываются все символы до символа перехода строки!\n");
            putws(L"Введите символы для добавления:\n");

            exit_code = as_read_symbols(a_stack);
            
            break;
        }

        case 2:
        {
            if (!a_stack->length)
                exit_code = ERR_EMPTY_STACK;
            else
            {
                int num;
                putws(L"\nВведите количество удаляемых элементов:\n");
                exit_code = read_int(&num);
                wclear_stdin();

                if (!exit_code && (num <= 0 || num > a_stack->length))
                    exit_code = ERR_INVALID_NUM;

                if (!exit_code)
                    exit_code = as_num_pop(a_stack, num);
            }

            break;
        }

        case 3:
        {
            putws(L"\nТекущее состояние стека на массиве:\n");

            exit_code = as_print(a_stack);

            break;
        }

        case 4:
        {
            putws(L"\n\nСчитываются все символы до символа перехода строки!\n");
            putws(L"Введите символы для добавления:\n");

            exit_code = ls_read_symbols(l_stack, ptrs);

            break;
        }

        case 5:
        {
            if (!*l_stack)
                exit_code = ERR_EMPTY_STACK;
            else
            {
                int num;
                putws(L"\nВведите количество удаляемых элементов:\n");
                exit_code = read_int(&num);
                wclear_stdin();

                if (!exit_code && (num <= 0 ||
                    (*l_stack && num > (*l_stack)->index + 1)))
                    exit_code = ERR_INVALID_NUM;

                if (!exit_code)
                    exit_code = ls_num_pop(l_stack, num, ptrs);
            }
            break;
        }

        case 6:
        {
            putws(L"\nТекущее состояние стека на списке:\n");
            
            if (*l_stack)
                putws(L"\n    Адрес узла   Значение элемента\n");

            exit_code = ls_print(l_stack);
            break;
        }

        case 7:
        {
            if (print_free_areas(ptrs))
            {
                putws(L"\nПамять ещё не выделялась, или все освобожденные\n");
                putws(L"области были снова использованы!\n");
            }
            break;
        }

        case 8:
        {
            exit_code = check_word();
            break;
        }

        default:
        {
            wint_t el;
            while (*l_stack)
                ls_pop(l_stack, &el);

            putws(L"\nСпасибо за использование программы!\n");
            putws(L"Автор:  МАСЛОВА МАРИНА\n");
            putws(L"Группа: ИУ7-33Б\n");
            exit(EXIT_SUCCESS);
            break;
        }
    }

    return exit_code;
}