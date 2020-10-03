#include <stdio.h>

#include "menu.h"
#include "cars.h"

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
    puts("8  - Сравнить эффективность работы программы способами 5 и 6");
    puts("9  - Сравнить время работы сортировок (быстрой и пузырьком)");
    puts("10 - Вывести цены не новых машин указанной марки");
    puts("    с одним предыдущим собственником, отстутсвием ремонта");
    puts("    в указанном диапазоне цен");
    puts("0  - Выход");
    puts("");
}

int choose_action(short int *const action)
{
    puts("Выберете пункт меню: ");

    // ! поменять считывание, чтобы был возможен повторный ввод

    if (scanf("%hd", action) != 1)
        return ERR_READ_ACTION;
    
    else if (*action < 0 || *action > 9)
        return ERR_WRONG_ACTION;
    
    else
        return OK_ACTION;
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
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        case 3:
            puts("Поздравляю! Пункт меню выбран верно!");
            break;

        case 4:
            puts("Поздравляю! Пункт меню выбран верно!");
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