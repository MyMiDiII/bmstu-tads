/**
 * @file big_nums.h
 * @brief Содежит функции для работы с длинными числами
 */

#ifndef __BIG_NUMS_H__

#define __BIG_NUMS_H__

#define MAX_INT_LEN 30
#define MAX_DOUBLE_LEN 30

#define READ_OK 0
#define MULTIPLY_OK 0
#define ERR_WRONG_CHAR -1
#define ERR_EMPTY_MANTISSA -3
#define ERR_READ_ORDER -4
#define ERR_WRONG_LEN -5
#define ERR_READ_INT_STR -6
#define ERR_TOO_BIG_ORDER -7

#define INT_INPUT 1

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

/**
 * @brief read_mantissa()
 * 
 * Считывает мантиссу длинного вещественного числа.
 * 
 * @param [out] number Указатель на длинное вещественное число
 * @return Код ошибки (целое число)
 */
int read_mantissa(big_double *const number);

/**
 * @brief read_int_str()
 * 
 * Считывает строку для последующего преобразования в int.
 * 
 * @param [in] max_int_len Максимальное количество цифр в числе
 * @param [out] read_str Указатель на считанную строку
 * @return Код ошибки
 */
int read_int_str(char *const read_str, const int max_int_len);

/**
 * @brief read_order()
 * 
 * Считывает порядок длинного вещественного числа.
 * 
 * @param [out] order Указатель на порядок вещественного числа
 * @return Код ошибки
 */
int read_order(int *const order);

/**
 * @brief normalize_number()
 * 
 * Преобразовывает длинное вещественное число к нормализованному виду
 * 
 * @param [in, out] Указатель на длинное вещчественное число
 */
void normalize_number(big_double *const number);

/**
 * @brief read_big_double()
 * 
 * Считывает длинное вещественное число.
 * 
 * @param [out] number Указатель на длинное вещественное число
 * @return Код ошибки
 */
int read_big_double(big_double *const number);

/**
 * @brief read_big_int()
 * 
 * Считывает длинное целое число
 * 
 * @param [out] number Указатель на длинное целое число
 * @return Код ошибки
 */
int read_big_int(big_int *const number);

/**
 * @brief print_big_double()
 * 
 * Выводит нормализованное вещественное число на экран
 * 
 * @param [in] number Указатель на длинное вещественное число
 */
void print_big_double(const big_double *const number); 

/**
 * @brief mulriply_big_numbers()
 * 
 * Осуществляет умножение длинного вещественного и длинного целого чисел
 * 
 * @param [in] int_num Указатель на длинное целое число 
 * @param [in] double_num Указатель на длинное вещественное число
 * @param [out] result_num Указатель на результат (длинное вещественное число)
 * @return Код ошибки
 */
int multiply_big_numbers(const big_int *const int_num,
                         const big_double *const double_int,
                         big_double *const result_num);

/**
 * @brief round_num()
 * 
 * Округляет вещественное число при выходе за разряды мантиссы
 * 
 * @param [in] last Последняя вышедшая за разряды цифра
 * @param [out] number Указатель на округленное вещественное число
 */
void round_num(big_double *const number, char last);

#endif
