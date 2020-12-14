#include <stdio.h>
#include <wchar.h>
#include <time.h>

#include "menu.h"
#include "my_functions.h"
#include "errors.h"
#include "arr_queue.h"
#include "list_queue.h"
#include "modeling.h"

void print_menu(void)
{
    putws(L"\n          ОЧЕРЕДЬ\n\n");
    putws(L"1  - Добавить элементы в очередь на массиве\n");
    putws(L"2  - Удалить элементы из очереди на массиве\n");
    putws(L"3  - Вывести адреса элементов очереди на массиве\n");
    putws(L"4  - Добавить элементы в очередь на списке\n");
    putws(L"5  - Удалить элементы из очереди на списке\n");
    putws(L"6  - Вывести адреса элементов очереди на списке\n");
    putws(L"7  - Запустить моделирование\n");
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

    else if (ERR_EMPTY_QUEUE == code)
        putws(L"\nОчередь пуста!\n");

    else if (ERR_FULL_QUEUE == code)
        putws(L"\nПереполнение очереди!\n");

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
    
    if (long_str < 0 || long_str > 7)
        return ERR_WRONG_ACTION;

    *action = (short int) long_str;

    return READ_OK;
}

int do_action(const short int action, arr_queue_t *a_queue,
              list_queue_t *l_queue)
{
    int exit_code = OK;

    switch (action)
    {
        case 1:
        {
            exit_code = aq_pushs(a_queue);
            break;
        }

        case 2:
        {
            exit_code = aq_pops(a_queue);
            break;
        }

        case 3:
        {
            putws(L"\nАдреса элементов очереди на массиве:\n");
            exit_code = aq_print(a_queue);
            break;
        }

        
        case 4:
        {
            exit_code = lq_pushs(l_queue);
            break;
        }

        case 5:
        {
            exit_code = lq_pops(l_queue);
            break;
        }

        case 6:
        {
            putws(L"\nАдреса элементов очереди на списке:\n");
            
            exit_code = lq_print(l_queue);
            break;
        }

        
        case 7:
        {
            modeling();
            break;
        }

        default:
        {
            lq_clear(l_queue);

            putws(L"\nСпасибо за использование программы!\n");
            putws(L"Автор:  МАСЛОВА МАРИНА\n");
            putws(L"Группа: ИУ7-33Б\n");
            exit(EXIT_SUCCESS);
            break;
        }
    }

    return exit_code;
}
