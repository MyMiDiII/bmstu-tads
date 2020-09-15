#ifndef __BIG_NUMS_H__

#define __BIG_NUMS_H__

#define MAX_INT_LEN 30
#define MAX_DOUBLE_LEN 30

#define READ_OK 0
#define ERR_WRONG_CHAR -1
#define ERR_INPUT -2

typedef struct
{
    char sign;
    short int num[MAX_INT_LEN];
    short int len_num;
} big_int;

typedef struct
{
    char sign;
    short int num[MAX_DOUBLE_LEN];
    short int len_num;
    int order;
    short int point_place;
} big_double;

int read_big_double(big_double *const number);

int read_big_int(big_int *const number);

int multiply_big_numbers(const big_int *const int_num,
                         const big_double *const double_int,
                         big_double *const result);

int print_big_double(const big_double *const number); 

#endif
