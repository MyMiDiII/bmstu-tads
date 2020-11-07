/**
 * \file
 * \brief Заголовочный файл с типами и функциями
 * для работы с матрицами (стандартными и разреженными)
 */

#ifndef __MATRIX_H__

#define __MATRIX_H__

#include "my_functions.h"

/**
 * Структура для хранения размеров матрицы
 */
typedef struct
{
    uint rows; /**< Количество строк */
    uint columns; /**< Количество столбцов */
    uint nonzeros; /**< Количество ненулевых элементов */
} matrix_size_t;

/**
 * Структура матрицы в разреженном виде
 */
typedef struct
{
    matrix_size_t sizes; /**< Размеры матрицы */
    int *elements; /**< Указатель на массив элементов матрицы */
    uint *rows; /**< Указатель на массив строк, соответсвующих элементам*/
    uint *columns; /**< Указатель на массив номеров элементов, с которых начинается столбец */
} sparse_matrix_t;

/**
 * Структура матрицы в стандарном виде
 */
typedef struct
{
    matrix_size_t sizes; /**< Размеры матрицы */
    int **matrix; /**<  Матрица */
} matrix_t;

/**
 * Вызывает функции считывание матрицы и веткора строки
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param sparse_row Указатель на разреженную вектор-строку
 * \param matrix Указатель на матрицу в стандартном виде
 * \param row Указатель на вектор-строку в стандартном виде
 * \return Код ошибки
 */
int read_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                  matrix_t *matrix, matrix_t *row);

/**
 * Считывет матрицу
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param matrix Указатель на матрицу в стандартном виде
 * \param rows_num Указатель на количество строк
 * \param columns_num Указатель на количество столбцов
 * \return Код ошибки
 */
int read_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix,
                uint *const rows_num, uint *const columns_num);

/**
 * Очищает память, выделенную под матрицу в стандартном виде
 * \param matrix Указатель на матрицу в стандартном виде
 */
void free_matrix_t(matrix_t *matrix);

/**
 * Очищает память, выделенную под разреженную матрицу
 * \param sparse_matrix Указатель на разреженную матрицу
 */
void free_sparse_t(sparse_matrix_t *sparse_matrix);

/**
 * Считывает вектор-строку
 * \param sparse_row Указатель на разреженную вектор-строку
 * \param row Указатель на вектор-строку в стандартном виде
 * \param columns_num Количество столбцов матрицы
 * \return Код ошибки
 */
int read_row(matrix_t *row, sparse_matrix_t *sparse_row, const uint columns_num);

/**
 * Выделяет память и инициализирует нулями матрицу в стандарном виде
 * \param matrix Указатель на матрицу в стандартном виде
 * \param rows Количество строк
 * \param columns Количество столбцов
 * \param nonzeros_num Количество ненулевых элементов
 * \return Код ошибки
 */
int matrix_init(matrix_t *matrix, uint rows, uint columns, uint nonzeros_num);


int** allocate_matrix(uint n, uint m);

void free_matrix(int **data, uint n);

/**
 * Выделяет память под разреженную матрицу
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param rows Количество строк
 * \param columns Количество столбцов
 * \param nonzero_num Количество ненулевых элементов
 * \return Код ошибки
 */
int sparse_matrix_init(sparse_matrix_t *matrix,
                       uint rows, uint columns, uint nonzero_num);

/**
 * Считывает элементы матрицы
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param matrix Указатель на матрицу в стандартном виде
 * \param nonzeros Количество ненулевый элементов 
 * \return Код ошибки
 */
int read_matrix_elements(sparse_matrix_t *sparse_matrix, matrix_t *matrix,
                         const uint nonzeros);

/**
 * Считывает элементы веткора-строки
 * \param sparse_row Указатель на разреженную вектор-строку
 * \param row Указатель на вектор-строку в стандартном виде
 * \param nonzeros Количество ненулевых элементов
 * \return Код ошибки
 */
int read_row_elements(sparse_matrix_t *sparse_row, matrix_t *row,
                         const uint nonzeros);

/**
 * Создает разреженную матрицу по матрице в стандартном виде
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param matrix Указатель на матрицу в стандартном виде
 */
void create_sparse_by_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix);

/**
 * Создает матрицу в стандартном виде по разреженной матрице 
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param matrix Указатель на матрицу в стандартном виде
 */
void create_matrix_by_sparse(sparse_matrix_t *sparse_matrix, matrix_t *matrix);


int user_print(matrix_t *matrix, matrix_t *row,
               sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row);

/**
 * Печатает матрицу в стандарном виде
 * \param matrix Указатель на матрицу в стандартном виде
 * \return Код ошибки
 */
int print_matrix(matrix_t *matrix);

/**
 * Печатает матрицу в разреженном виде
 * \param matrix Указатель на матрицу в стандартном виде
 * \return Код ошибки
 */
int print_sparse(sparse_matrix_t *matrix);

/**
 * Считывает параметры генерируемых матриц и вызывает функцию генерации
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param sparse_row Указатель на разреженную вектор-строку
 * \param matrix Указатель на матрицу в стандартном виде
 * \param row Указатель на вектор-строку в стандартном виде
 * \return Код ошибки
 */
int generate_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                  matrix_t *matrix, matrix_t *row);

/**
 * Генерирует матрицы по их параметрам
 * \param sparse_matrix Указатель на разреженную матрицу
 * \param matrix Указатель на матрицу в стандартном виде
 * \return Код ошибки
 */
void generate_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix);

#endif