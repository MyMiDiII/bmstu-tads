#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "big_nums.h"

#define MAX_ORDER_LEN 6

int char_into_int(char ch)
{
    if (ch < '0' || ch > '9')
        return EOF;

    return ch - '0';
}

int read_mantissa(big_double *const number)
{
    char ch;
    _Bool begin = true;
    _Bool point_flag = false;
    _Bool zeros_delete_flag = true;
    short int current_point_place = 0;
    short int zeros_count = 0;
    number->len_num = 0;
    number->order = 0;

    while ((ch = getchar()) != 'e' && ch != 'E' && ch != '\n' && ch != EOF)
    {
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // !! убирать нули в начале и конце !!
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        if (ch == ' ')
            continue;

        if (begin)
        {
            if ('-' == ch || '+' == ch)
            {
                number->sign = ch;
                continue;
            }

            else if ((ch < '0' || ch > '9') && ch != '.')
                return ERR_WRONG_CHAR;

            else
                number->sign = '+';

            begin = false; 
        }
        
        if (point_flag)
            current_point_place++;

        if (ch == '.')
            point_flag = true;

        else if (ch < '0' || ch > '9')
            return ERR_WRONG_CHAR;

        else
        {
            if (number->len_num >= MAX_DOUBLE_LEN)
                return ERR_WRONG_LEN;
            number->num[number->len_num] = ch;
            number->len_num++;
        }
    }

    if (ch != 'e' && ch != 'E')
        return ERR_INPUT;

    if (!number->len_num && !point_flag)
        return ERR_EMPTY_MANTISSA;

    if (zeros_delete_flag)
        number->len_num -= zeros_count;

    number->point_place = number->len_num - current_point_place;

    if (0 == number->len_num)
    {
        number->num[0] = '0';
        number->len_num++;
    }

    return READ_OK;
}

int read_int_str(char *const read_str, const int max_int_len)
{
    char ch;
    short int count = 0;

    while ((ch = getchar()) != '\n' && ch != EOF && count < max_int_len + 1)
    {
        if (ch == ' ')
            continue;

        if (ch < '0' || ch > '9')
            if (count != 0 || (0 == count && ch != '-' && ch != '+'))
                return ERR_READ_INT_STR;

        if (0 == count && ch != '-' && ch != '+')
            read_str[count++] = '+';

        read_str[count] = ch;
        count++;
    }

    if (count > max_int_len)
        return ERR_READ_INT_STR;

    read_str[count] = '\0';

    return count;
}

int read_order(int *const order)
{
    char read_order[MAX_ORDER_LEN + 1];

    if (read_int_str(read_order, MAX_ORDER_LEN) < 0)
        return ERR_READ_ORDER;

    char *end_ptr;

    *order = strtol(read_order, &end_ptr, 10);

    if (end_ptr == read_order || *end_ptr != '\0')
        return ERR_READ_ORDER;

    return READ_OK;
}

int read_big_double(big_double *const number)
{
    short int exit_code = READ_OK;

    exit_code = read_mantissa(number);

    if (!exit_code)
        exit_code = read_order(&number->order);

    number->order += number->point_place;
    number->point_place = 0;

    if (1 == number->len_num && '0' == number->num[0])
        number->order = 0;

    return exit_code; 
}

int read_big_int(big_int *const number)
{
    short int len = read_int_str(number->num, MAX_INT_LEN + 1);

    if (len < 0)
        return ERR_READ_INT_STR;

    number->len_num = len;

    return READ_OK;
}

int print_big_double(const big_double *const number)
{
    printf("%c0.", number->sign);
    for (int i = number->point_place; i < number->len_num; i++)
    {
        printf("%c", number->num[i]);
    }

    printf(" E %+d\n", number->order);
}

int multyply_big_numbers(const big_int *const int_num,
    const big_double *const double_num, const big_double *const result_num)
{

}