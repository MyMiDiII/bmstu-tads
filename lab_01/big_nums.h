#ifndef __BIG_NUMS_H__

#define __BIG_NUMS_H__

#define MAX_INT_LEN 30
#define MAX_DOUBLE_LEN 30

#define READ_OK 0
#define ERR_WRONG_CHAR -1
#define ERR_INPUT -2
#define ERR_EMPTY_MANTISSA -3
#define ERR_READ_ORDER -4
#define ERR_WRONG_LEN -5
#define ERR_READ_INT_STR -6

typedef struct
{
    char num[MAX_INT_LEN + 1];
    short int len_num;
} big_int;

typedef struct
{
    char sign;
    char num[MAX_DOUBLE_LEN];
    short int len_num;
    short int point_place;
    int order;
} big_double;

int read_big_double(big_double *const number);

int read_big_int(big_int *const number);

int multiply_big_numbers(const big_int *const int_num,
                         const big_double *const double_int,
                         big_double *const result);

int print_big_double(const big_double *const number); 

#endif
