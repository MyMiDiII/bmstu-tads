/**
 * @mainpage
 * *Вариант 11*\n\n
 * Программа производит вычисление произведения длинного вещественного и длинного целого чисел\n\n
 * **Автор:** Маслова Марина\n
 * **Группа:** ИУ7-33Б
 */

#include <stdio.h>

#include "big_nums.h"
#include "errors.h"

#define OK 0
#define ERR_READ -1

int main(void)
{
    int exit_code;
    big_int int_num;
    big_double double_num, result_num;

    puts("ПОИСК ПРОИЗВЕДЕНИЯ ДЛИННОГО ВЕЩЕСТВЕННОГО");
    puts("ЧИСЛА НА ДЛИННОЕ ЦЕЛОЕ ЧИСЛО.");
    puts("");
    puts("Пробелы, лидирующие и конечные нули при вводе игнорируются.");
    puts("");
    puts("Пустой ввод корректен и является вводом нуля");
    puts("");
    puts("Формат ввода вещественного числа: ±n.m E ±K, длина(n+m) ≤ 30,");
    puts("длина(k) ≤ 5, знак + необязателен.");
    puts("");
    puts("Формат ввода целого числа: ±n, длина(n) ≤ 30, знак + необязателен.");
    puts("");

    printf("Введите вещественный множитель: ");
    exit_code = read_big_double(&double_num);

    if (exit_code)
    {
        print_error(exit_code);
        return ERR_READ;
    }

    printf("Введите целый множитель: ");
    exit_code = read_big_int(&int_num);

    if (exit_code)
    {
        print_error(exit_code);
        return ERR_READ;
    }

    exit_code = multiply_big_numbers(&int_num, &double_num, &result_num);

    if (exit_code)
    {
        print_error(exit_code);
        return ERR_TOO_BIG_ORDER;
    }

    printf("Результат умножения двух чисел: ");
    print_big_double(&result_num);

    return OK;
}
