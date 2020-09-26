#include <stdio.h>

#include "errors.h"
#include "big_nums.h"

void print_error(const int code)
{
    if (ERR_WRONG_CHAR == code)
        puts("При вводе использован некорректный символ.");
    else if (ERR_EMPTY_MANTISSA == code)
        puts("Перед экспонентой необходмо ввести мантиссу.");
    else if (ERR_READ_ORDER == code)
        puts("Ошибка при чтении порядка.");
    else if (ERR_WRONG_LEN == code)
        puts("Превышено максимальное количество символов.");
    else if (ERR_READ_INT_STR == code)
        puts("При вводе использован некорректный символ.");
    else if (ERR_TOO_BIG_ORDER == code)
        puts("Переполнение порядка при выполнении умножения");
}