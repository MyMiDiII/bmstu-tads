#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "cars.h"
#include "read_cars.h"
#include "errors.h"
#include "my_string.h"

int check_and_assign_brand(const char *const read_brand, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_brand) > MAX_BRAND_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_BRAND;
    }
    else
    {
        strcpy((char *) &table->table[table->len - 1].brand, read_brand);
    }
    
    return CARS_OK;
}

int check_and_assign_country(const char *const read_country, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_country) > MAX_COUNTRY_LEN / 2)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_COUNTRY;
    }
    else
        strcpy((char *) &table->table[table->len - 1].country, read_country);

    return CARS_OK;
}

int check_and_assign_color(const char *const read_color, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_color) > MAX_COLOR_LEN / 2)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_COLOR;
    }
    else
        strcpy((char *) &table->table[table->len - 1].color, read_color);

    return CARS_OK;
}

int check_and_assign_price(const char *const read_price, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_price) > MAX_PRICE_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_PRICE;
    }
    else
    {
        char *end_prt;
        long int price = strtol(read_price, &end_prt, 10);

        if (*end_prt != '\0')
        {
            *err_row = table->len;
            return ERR_READ_PRICE;
        }
        else if (price < 0 || price > UINT_MAX)
        {
            *err_row = table->len;
            return ERR_WRONG_PRICE;
        }
        else
            table->table[table->len - 1].price = (unsigned int) price;
    }

    return CARS_OK;
}

int check_and_assign_condition(const char *const read_condition, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_condition) > MAX_CONDITION_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_CONDITION;
    }
    else if (!strcmp(read_condition, "new"))
        table->table[table->len - 1].condition = NEW;

    else if (!strcmp(read_condition, "used"))
        table->table[table->len - 1].condition = USED;

    else
    {
        *err_row = table->len;
        return ERR_WRONG_CONDITION;
    }

    return CARS_OK;
}

int check_and_assign_warranty(const char *const read_warranty, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_warranty) > MAX_WARRANTY_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_WARRANTY;
    }
    else if (USED == table->table[table->len - 1].condition && strcmp(read_warranty, "-"))
    {
        *err_row = table->len;
        return ERR_USED_WARRANTY;
    }
    else if (USED != table->table[table->len - 1].condition)
    {
        char *end_prt;
        long int warranty = strtol(read_warranty, &end_prt, 10);

        if (*end_prt != '\0')
        {
            *err_row = table->len;
            return ERR_READ_WARRANTY;
        }
        else if (warranty < 0 || warranty > USHRT_MAX)
        {
            *err_row = table->len;
            return ERR_WRONG_WARRANTY;
        }
        else
            table->table[table->len - 1].more_info.new_car.warranty = (unsigned short int) warranty;
    }

    return CARS_OK;
}

int check_and_assign_year(const char *const read_year, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_year) > MAX_YEAR_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_YEAR;
    }
    else if (NEW == table->table[table->len - 1].condition && strcmp(read_year, "-"))
    {
        *err_row = table->len;
        return ERR_NEW_YEAR;
    }
    else if (NEW != table->table[table->len - 1].condition)
    {
        char *end_prt;
        long int year = strtol(read_year, &end_prt, 10);

        if (*end_prt != '\0')
        {
            *err_row = table->len;
            return ERR_READ_YEAR;
        }
        else if (year < 0 || year > USHRT_MAX)
        {
            *err_row = table->len;
            return ERR_WRONG_YEAR;
        }
        else
            table->table[table->len - 1].more_info.used_car.year = (unsigned short int) year;
    }

    return CARS_OK;
}

int check_and_assign_mileage(const char *const read_mileage, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_mileage) > MAX_MILEAGE_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_MILEAGE;
    }
    else if (NEW == table->table[table->len - 1].condition && strcmp(read_mileage, "-"))
    {
        *err_row = table->len;
        return ERR_NEW_MILEAGE;
    }
    else if (NEW != table->table[table->len - 1].condition)
    {
        char *end_prt;
        long int mileage = strtol(read_mileage, &end_prt, 10);

        if (*end_prt != '\0')
        {
            *err_row = table->len;
            return ERR_READ_MILEAGE;
        }
        else if (mileage < 0 || mileage > UINT_MAX)
        {
            *err_row = table->len;
            return ERR_WRONG_MILEAGE;
        }
        else
            table->table[table->len - 1].more_info.used_car.mileage = (unsigned int) mileage;
    }
    
    return CARS_OK;
}

int check_and_assign_repairs_num(const char *const read_repairs_num, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_repairs_num) > MAX_REPAIRS_NUM_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_REPAIRS_NUM;
    }
    else if (NEW == table->table[table->len - 1].condition && strcmp(read_repairs_num, "-"))
    {
        *err_row = table->len;
        return ERR_NEW_REPAIRS_NUM;
    }
    else if (NEW != table->table[table->len - 1].condition)
    {
        char *end_prt;
        long int repairs_num = strtol(read_repairs_num, &end_prt, 10);

        if (*end_prt != '\0')
        {
            *err_row = table->len;
            return ERR_READ_REPAIRS_NUM;
        }
        else if (repairs_num < 0 || repairs_num > USHRT_MAX)
        {
            *err_row = table->len;
            return ERR_WRONG_REPAIRS_NUM;
        }
        else
            table->table[table->len - 1].more_info.used_car.repairs_num =
                 (unsigned short int) repairs_num;
    }

    return CARS_OK;
}

int check_and_assign_owners_num(const char *const read_owners_num, car_table_t *table, int *const err_row)
{
    if (my_strlen(read_owners_num) > MAX_OWNERS_NUM_LEN)
    {
        *err_row = table->len;
        return ERR_TOO_LONG_OWNERS_NUM;
    }
    else if (NEW == table->table[table->len - 1].condition && strcmp(read_owners_num, "-"))
    {
        *err_row = table->len;
        return ERR_NEW_OWNERS_NUM;
    }
    else if (NEW != table->table[table->len - 1].condition)
    {
        char *end_prt;
        long int owners_num = strtol(read_owners_num, &end_prt, 10);

        if (*end_prt != '\0')
        {
            *err_row = table->len;
            return ERR_READ_OWNERS_NUM;
        }
        else if (owners_num < 0 || owners_num > USHRT_MAX)
        {
            *err_row = table->len;
            return ERR_WRONG_OWNERS_NUM;
        }
        else
            table->table[table->len - 1].more_info.used_car.owners_num =
                (unsigned short int) owners_num;
    }
     return CARS_OK;
}

int read_csv_file(FILE *const file, car_table_t *table, int *const err_row)
{
    char str[MAX_TABLE_STR_LEN + 2];
    table->len = -1;
    int exit_code = CARS_OK;

    while (fgets(str, MAX_TABLE_STR_LEN + 3, file))
    {
        table->len++;
        size_t len = table->len;

        if (0 == len)
            continue;

        if (my_strlen(str) > MAX_TABLE_STR_LEN + 2)
        {
            *err_row = len;
            return ERR_TOO_LONG_STR;
        }

        char *field_prt = strtok(str, ",");

        exit_code = check_and_assign_brand(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_country(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_color(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_price(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_condition(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_warranty(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_year(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_mileage(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",");

        exit_code = check_and_assign_repairs_num(field_prt, table, err_row);

        if (exit_code)
            return exit_code;

        field_prt = strtok(NULL, ",\n");

        exit_code = check_and_assign_owners_num(field_prt, table, err_row);

        if (exit_code)
            return exit_code;
    }

    return exit_code;
}

int upload_from_file(car_table_t *table)
{
    table->len = 0;
    int exit_code = CARS_OK;
    char *file_name = NULL;
    size_t len = 0;
    char ch;
    int read;

    // ! после нормального считывания пункта меню убрать
    scanf("%c", &ch);
    puts("Введите имя файла (с путем при нахождении файла в другой директории):");

    if ((read = getline(&file_name, &len, stdin)) != -1)
    {
        if ('\n' == file_name[read - 1])
            file_name[read - 1] = '\0';

        // for (int i = 0; i < read - 1; i++)
        //    printf("%c", file_name[i]);

        FILE *file = fopen(file_name, "r");
        free(file_name);
        
        if (file)
        {
            int err_row;
            exit_code = read_csv_file(file, table, &err_row);

            if (fclose(file) == EOF)
                return ERR_CLOSE_FILE;

            if (exit_code)
            {
                printf("%d\n", err_row);
                printf("%d\n", exit_code);
                return exit_code;
            }
        }
        else
            return ERR_OPEN_FILE;
    }
    else
        return ERR_READ_FILE_NAME;
}

int read_record(car_table_t *table)
{
    if (table->len >= MAX_TABLE_LEN)
    {
        puts("Достигнут максимальный размер таблицы.");
        puts("Удалите данные для возможности добавления записи!");
    }
    else
    {
        int exit_code = CARS_OK;
        printf("Марка: ");

        char *str = NULL;
        size_t len = 0;
        int err_row;
        char ch;

        scanf("%c", &ch);

        if (getline(&str, &len, stdin) != -1)
        {
            printf("%s", str);
            free(str);
            /*exit_code = check_and_assign_brand(str, table, &err_row);*/
        }

        if (exit_code)
            return exit_code;

        printf("Cтрана-произоводитель: ");

        printf("Цвет: ");

        printf("Цена: ");

        puts("Состояние: ");
        puts("N - новая");
        puts("U - б/у");

        printf("Гарантия: ");

        printf("Год выпуска: ");

        printf("Пробег: ");

        printf("Количество ремонтов: ");

        printf("Количество собственников: ");
    }

    return CARS_OK;
}
