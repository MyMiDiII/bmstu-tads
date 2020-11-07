/**
 * \file
 * \brief Заголовочный файл с функциями для работы меню.
 */

#ifndef __MENU_H__

#define __MENU_H__

#include "matrix.h"

#define MAX_MENU_ITEM_LEN 2

/**
 * Печатает текст меню
 */
void print_menu(void);

/**
 * Считывает номер действия из меню
 * \param action Указатель на считываемое действие
 * \return Код ошибки
 */
int choose_action(short int *const action);

/**
 * Печатает сообщение об ошибке
 * \param code Код ошибки
 */
void print_error_message(const int code);

/**
 * Вызывает функцию соответствующую выбранному действию
 * \param action Выбранное действие
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param sparse_row Указатель на разреженную вектор-строку
 * \param matrix Указатель на матрицу в стандартном виде
 * \param row Указатель на вектор-строку в стандартном виде
 * \return Код ошибки
 */
int do_action(const short int action,
              sparse_matrix_t *sparse_matrix,
              sparse_matrix_t *sparse_row,
              matrix_t *matrix,
              matrix_t *row);

#endif