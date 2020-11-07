/**
 * \file
 * \brief Заголовочный файл с функциями умножения матриц
 * в любой из форматов (стандартный/разреженный)
 */

#ifndef __MATRIXES_ACTIONS_H__

#define __MATRIXES_ACTIONS_H__

#include "matrix.h"

/**
 * Умножает вектор-строку на матрицу по стандартном алгоритму
 * \param matrix Указатель на матрицу в стандартном виде
 * \param row Указатель на вектор-строку в стандартном виде
 * \return Код ошибки
 */
int multiply_row_and_matrix(matrix_t *row, matrix_t *matrix);

/**
 * Умножает вектор-строку на матрицу в разреженном виде
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param sparse_row Указатель на разреженную вектор-строку
 * \return Код ошибки
 */
int sparse_multiply_row_and_matrix(sparse_matrix_t *row, sparse_matrix_t *matrix);

/**
 * Выбор формата печати матрицы
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param matrix Указатель на матрицу в стандартном виде
 * \return Код ошибки
 */
int choice_print(matrix_t *matrix, sparse_matrix_t *sparse_matrix);

#endif