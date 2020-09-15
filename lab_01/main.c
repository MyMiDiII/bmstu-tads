// TODO
// 1. КОММЕНТАРИИ
// 2. Уточнить обработку ошибок
// 3. Вывести информацию о том, что делает программа
// 4. Чтение больших чисел
// 5. Поиск произведения
// 6. Вывод числа в нормализованном виде
//
// ???
// 1. Как покороче записать вид ввода?
// 2. Нужно ли приводить в нормализованный вид введенные числа?


#include <stdio.h>

#include "big_nums.h"

#define OK 0
#define ERR_READ -1

int main(void)
{
    int exit_code;
    //big_int int_num;
    big_double double_num;

    puts("Поиск произведения длинного вещественного");
    puts("числа на длинное целое число.");
    puts("");
    puts("Формат ввода целого числа: ±n, длина(n) ≤ 30, знак + необязателен.");
    puts("");
    puts("Формат ввода вещественного числа: ±n.m E ±K, длина(n+m) ≤ 30,");
    puts("длина(k) ≤ 5, знак + и пробелы необязательны.");

    printf("Введите вещественный множитель: ");
    exit_code = read_big_double(&double_num);

    if (exit_code)
    {
        puts("Ошибка чтения вещественного множителя.");
        return ERR_READ;
    }

    /*printf("Введите целый множитель: ");
    exit_code = read_big_int(&int_num);

    if (exit_code)
    {
        puts("Ошибка чтения целого множителя.");
        return ERR_READ;
    }

    exit_code = multiply_big_numbers(&int_num, &double_num, &result_num);

    if (exit_code)
    {
        puts("Ошибка при умножении чисел.");
        return ERR_MULTIPLY;
    }

    exit_code = print_big_double(&result_num);

    if (exit_code)
    {
        puts("Ошибка при выводе результата.");
        return ERR_PRINT;
    }*/

    return OK;
}
