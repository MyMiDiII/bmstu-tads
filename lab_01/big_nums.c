#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "big_nums.h"

#define MAX_ORDER_LEN 6


int read_mantissa(big_double *const number)
{
    char ch;
    _Bool begin = true;
    _Bool point_flag = false;
    _Bool zeros_delete_flag = true;
    short int current_point_place = 0;
    number->sign = '+';
    number->len_num = 0;
    number->order = 0;

    while ((ch = getchar()) != 'e' && ch != 'E' && ch != '\n' && ch != EOF)
    {
        if (ch == ' ')
            continue;

        if (!begin && zeros_delete_flag && '0' == ch)
            continue;

        if (begin)
        {
            if ('-' == ch || '+' == ch)
            {
                number->sign = ch;
                begin = false;
                continue;
            }

            else if ((ch < '0' || ch > '9') && ch != '.')
                return ERR_WRONG_CHAR;

            begin = false; 
        }
        
        if (point_flag)
            current_point_place++;

        if (ch == '.')
        {
            if (point_flag)
                return ERR_WRONG_CHAR;
            point_flag = true;
            zeros_delete_flag = false;
        }

        else if (ch < '0' || ch > '9')
            return ERR_WRONG_CHAR;

        else
        {
            if (number->len_num >= MAX_DOUBLE_LEN)
                return ERR_WRONG_LEN;
            number->num[number->len_num] = ch;
            number->len_num++;
            zeros_delete_flag = false;
        }
    }

    number->point_place = number->len_num - current_point_place;

    if (0 == number->len_num)
    {
        number->num[0] = '0';
        number->len_num++;
    }

    if (!number->len_num && !point_flag)
        return ERR_EMPTY_MANTISSA;

    if (ch != 'e' && ch != 'E')
        return INT_INPUT;

    return READ_OK;
}


int read_int_str(char *const read_str, const int max_int_len)
{
    char ch;
    short int count = 0;
    _Bool zeros_flag = true;

    while ((ch = getchar()) != '\n' && ch != EOF && count < max_int_len + 1)
    {
        if (ch == ' ')
            continue;

        if ('0' == ch && count > 1 && zeros_flag)
            continue;

        if (ch < '0' || ch > '9')
        {
            if (count != 0 || (0 == count && ch != '-' && ch != '+'))
                return ERR_READ_INT_STR;
        }

        if (0 == count && ch != '-' && ch != '+')
            read_str[count++] = '+';

        if (ch != '0' && zeros_flag)
        {
            zeros_flag = false;
            
            if (count > 1)
                count--;
        }
        read_str[count++] = ch;
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


void normalize_number(big_double *const number)
{
    short int back_zeros = 0;

    number->order += number->point_place;
    number->point_place = 0;

    if (1 == number->len_num && '0' == number->num[0])
    {
        number->order = 0;
        return;
    }

    short int count;

    for (count = 0; count < number->len_num && '0' == number->num[count]; count++);

    for (short int i = count; i < number->len_num; i++)
        number->num[i - count] = number->num[i];

    number->order -= count;
    number->len_num -= count;

    for (count = 0; count < number->len_num; count++)
    {
        if ('0' == number->num[count])
            back_zeros++;
        else
            back_zeros = 0;
    }

    number->len_num -= back_zeros;

    if (0 == number->len_num)
    {
        number->num[0] = '0';
        number->len_num++;
        number->order = 0;
    }
}


int read_big_double(big_double *const number)
{
    short int exit_code = READ_OK;

    exit_code = read_mantissa(number);

    if (!exit_code)
        exit_code = read_order(&number->order);

    if (INT_INPUT == exit_code)
        exit_code = READ_OK;

    if (!exit_code)
        normalize_number(number);

    return exit_code; 
}

int read_big_int(big_int *const number)
{
    short int len = read_int_str(number->num, MAX_INT_LEN + 1);

    if (len < 0)
        return len;

    number->len_num = len;

    return READ_OK;
}


void print_big_double(const big_double *const number)
{
    printf("%c0.", number->sign);
    for (int i = number->point_place; i < number->len_num; i++)
    {
        printf("%c", number->num[i]);
    }

    printf(" E %+d\n", number->order);
}


void round_num(big_double *const number, char last)
{
    short int transfer = 0;
    short int i = number->len_num - 1;

    while (i >= 0 && (last >= '5' || transfer))
    {
        last = '\0';
        if (number->num[i] == '9')
        {
            number->num[i] = '0';
            transfer = 1;
        }
        else
        {
            number->num[i]++;
            transfer = 0;
        }

        i--;
    }

    if (transfer)
    {
        for (short int j = MAX_DOUBLE_LEN - 1; j > 0; j--)
            number->num[j] = number->num[j - 1];

        number->order++;
    }
}


int multiply_big_numbers(const big_int *const int_num,
    const big_double *const double_num, big_double *const result_num)
{
    short int first_len = int_num->len_num - 1;
    short int second_len = double_num->len_num;
    short int max_result_len = first_len + second_len;

    result_num->len_num = max_result_len > MAX_DOUBLE_LEN ? MAX_DOUBLE_LEN : max_result_len;
    result_num->point_place = 0;
    result_num->order = first_len + double_num->order;

    if (int_num->num[0] == double_num->sign)
        result_num->sign = '+';
    else
        result_num->sign = '-';

    short int transfer = 0;
    short int shift = 0;
    char last = '\0';

    for (short int i = 0; i < max_result_len; i++)
    {
        short int index;
        if (i >= MAX_DOUBLE_LEN)
            index = 0;
        else
            index = result_num->len_num - i - 1;
        
        short int current_sum = 0;

        for (short int k = 0; k < second_len; k++)
        {
            short int second_digit = double_num->num[second_len - k - 1] - '0';
            
            short int first_digit;

            if (i - k >= 0 && i - k < first_len)
                first_digit = int_num->num[first_len - i + k] - '0';
            else
                first_digit = 0;

            current_sum += first_digit * second_digit;
        }
        current_sum += transfer;

        transfer = current_sum / 10;

        if (i >= MAX_DOUBLE_LEN && current_sum)
        {
            shift++;
            last = result_num->num[MAX_DOUBLE_LEN - 1];

            for (short int j = MAX_DOUBLE_LEN - 1; j > 0; j--)
                result_num->num[j] = result_num->num[j - 1];
        }
        
        result_num->num[index] = current_sum % 10 + '0';
    }

    if (last != '\0')
        round_num(result_num, last);
    normalize_number(result_num);

    if (result_num->order > 99999 || result_num->order < -99999)
        return ERR_TOO_BIG_ORDER;

    return MULTIPLY_OK;
}