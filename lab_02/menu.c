#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "cars.h"
#include "my_string.h"
#include "read_cars.h"
#include "print_cars.h"

void print_menu_error(const int code)
{
    if (ERR_WRONG_ACTION == code)
    {
        puts("Введенный код не соответствует ни одному действию.");
        puts("Попробуйте ещё раз.");
    }
    else if (ERR_READ_ACTION == code)
    {
        puts("Некорректный ввод кода действия.");
        puts("Попробуйте ещё раз.");
    }
}

void print_menu(void)
{
    puts("");
    puts("          МЕНЮ");
    puts("");
    puts("1  - Загрузить таблицу машин из файла");
    puts("2  - Просмотреть таблицу");
    puts("3  - Добавить информацию о новой машине в конец таблицы");
    puts("4  - Удалить машины из списка по цене");
    puts("5  - Просмотреть отсортированную по цене таблицу ключей");
    puts("6  - Вывести упорядоченную по цене таблицу");
    puts("7  - Вывести таблицу в упорядоченном по цене виде по упорядоченной таблице ключей");
    puts("8  - Сравнить эффективность работы программы способами 6 и 7");
    puts("9  - Сравнить время работы сортировок (быстрой и пузырьком)");
    puts("10 - Вывести цены не новых машин указанной марки");
    puts("     с одним предыдущим собственником, отстутсвием ремонта");
    puts("     в указанном диапазоне цен");
    puts("0  - Выход");
    puts("");
}

int choose_action(short int *const action)
{
    puts("Выберете пункт меню: ");

    char str[MAX_MENU_ITEM_LEN + 2];

    if (read_str(str, MAX_MENU_ITEM_LEN + 3, stdin))
        return ERR_READ_ACTION;

    char *end_prt;
    long int long_str = strtol(str, &end_prt, 10);
    
    if (long_str < 0 || long_str > 10)
        return ERR_WRONG_ACTION;

    *action = (short int) long_str;

    return READ_OK;
}

int do_action(const short int action, car_table_t *table)
{
    int exit_code = OK_ACTION;

    switch (action)
    {
        case 1:
            exit_code = upload_from_file(table);
            printf("%s\n", exit_code ? "Ошибка при чтении файла!" : "Данные успешно загружены!");            
            break;

        case 2:
            print_cars(table);
            break;

        case 3:
            read_record(table);
            break;

        case 4:
            if (table->len == 0)
                puts("\nВ таблице нет данных!");
            else
                delete_record(table);
            break;

        case 5:
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        case 6:
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        case 7:
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        case 8:
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        case 9:
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        case 10:
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        default:
            puts("Пока!");
            break;
    }

    return exit_code;
}