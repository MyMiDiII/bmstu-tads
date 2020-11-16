/**
 * \file
 * \brief Заголовочый файл с часто используемыми
 * константами, типами, функциями.
 */

#ifndef __MY_FUNCTIONS_H__

#define __MY_FUNCTIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#define READ_OK 0
#define ERR_FGETS -1
#define ERR_STR_READ -2

typedef unsigned int uint;

size_t my_strlen(const char *const str);

int read_wstr(wchar_t *const str, const int max_len, FILE *stream);

int read_str(char *const str, const int max_len, FILE *stream);

/**
 * Очищает поток ввода
 */
void clear_stdin(void);

/**
 * Очищает поток ввода
 */
void wclear_stdin(void);

/**
 *Считывает число типа uint.
 * \param integer Указатель на считываемое число
 * \return Код ошибки 
 */
int read_uint(uint *const integer);

/**
 * Округляет число по математическим правилам.
 * Приводит его к беззнаковому типу.
 * Если число отрицательное, округляет его модуль.
 * \param number Округляемое число
 * \return Округленное число в беззнаковом целом типе
*/
uint my_round(double number);

int putws(const wchar_t *ws);

#endif
