#include <stdio.h>

#include "read_cars.h"
#include "errors.h"

int delete_record(car_table_t *table)
{
    printf("Введите цену машин (тыс руб), которые вы хотите удалить: ");

    unsigned int price;
    size_t count = 0;

    int exit_code = read_delete_price(&price);

    if (exit_code)
        return exit_code;

    for (size_t i = 0; i < table->len; i++)
    {
        if (table->table[i].price == price)
        {
            for (size_t j = i; j < table->len - 1; j++)
                table->table[j] = table->table[j + 1];
            table->len--;
            count++;
        }
    }

    if (count == 0)
        return ERR_NO_CARS;

    return CARS_OK;
}
