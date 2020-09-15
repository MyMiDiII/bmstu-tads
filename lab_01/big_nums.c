#include <stdio.h>
#include <stdbool.h>

#include "big_nums.h"

int char_into_int(char ch)
{
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
            number->num[number->len_num] = char_into_int(ch);
            number->len_num++;
        }
    }

    if (ch != 'e' && ch != 'E')
        return ERR_INPUT;

    number->point_place = number->len_num - current_point_place;

    return READ_OK;
}

int read_big_double(big_double *const number)
{
    short int exit_code = READ_OK;

    exit_code = read_mantissa(number);

    return exit_code; 
}
