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
    short int current_point_place = 0;

    while ((ch = getchar()) != 'e' && ch != 'E' && ch != '\n' && ch != EOF)
    {
        // ? как хранить ноль
        // ! убирать нули в начале и конце

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
            number->num[number->len_num] = char_into_int(ch);
            number->len_num++;
        }
    }

    if (ch != 'e' && ch != 'E')
        return ERR_INPUT;

    if (!number->len_num && !point_flag)
        return ERR_EMPTY_MANTISSA;

    number->point_place = number->len_num - current_point_place;

    return READ_OK;
}

int read_order(int *const order)
{
    char ch;
    short int count = 0;
    char read_order[MAX_ORDER_LEN + 1];

    while ((ch = getchar()) != '\n' && ch != EOF && count < MAX_ORDER_LEN + 1)
    {
        if (ch == ' ')
            continue;

        if (0 == count && ch != '-' && ch != '+')
            read_order[count++] = '+';
        read_order[count] = ch;
        count++;
    }

    if (count > MAX_ORDER_LEN)
        return ERR_READ_ORDER;

    read_order[count] = '\0';

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

    // printf("%d\n", exit_code);

    if (!exit_code)
        exit_code = read_order(&number->order);

    // printf("%d\n", exit_code);
/*
    if (!exit_code)
    {
        for (int i = 0; i < number->len_num; i++)
        {
            if (i == number->point_place)
            {
                printf(".%d", number->num[i]);
            }
            else
            {
                printf("%d", number->num[i]);
            }
        }

        printf("e%d\n", number->order);
    }*/

    return exit_code; 
}
