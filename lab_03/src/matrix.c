#include <stdio.h>
#include <limits.h>

#include "matrix.h"
#include "errors.h"
#include "my_string.h"

int read_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                  matrix_t *matrix, matrix_t *row)
{
    int exit_code = MATRIX_OK;
    unsigned int rows_num, columns_num;
    unsigned int nonzero_num;

    // очистить память

    puts("Введите количество строк матрицы: ");

    exit_code = read_uint(&rows_num);

    if (exit_code)
        return exit_code;

    puts("Введите количество столбцов матрицы: ");

    exit_code = read_uint(&columns_num);

    if (exit_code)
        return exit_code;

    exit_code = matrix_init(matrix, row, rows_num, columns_num);

    if (exit_code)
        return exit_code;

    /*puts("Введите количество ненулевых элементов матрицы: ");

    read_uint(&nonzero_num);

    if (exit_code)
        return exit_code;

    if (nonzero_num > rows_num * columns_num)
        return ERR_TOO_MUCH_NONZERO;

    exit_code = sparse_matrix_init(matrix, row, rows_num, columns_num, nonzero_num);*/

    // printf("Введите %d элемент(а/ов) в формате \"строка столбец значение\"\n"
        //    "(без ковычек, каждый элемент на новой строке):", nonzero_num);

    // exit_code = read_matrix_elements(sparse_matrix, matrix);

    // if (exit_code)
        // return exit_code;

    // printf("Введите количество ненулевых элементов вектора-строки (max_num = %d)", rows_num);

    // read_int(&nonzero_num);

    // if (exit_code)
        // return exit_code;

    // if (nonzero_num > rows_num)
        // return ERR_TOO_MUCH_NONZERO;

    // printf("Введите %d элемент(а/ов) в формате \"строка столбец значение\"\n"
        //    "(без ковычек, каждый элемент на новой строке):", nonzero_num);

    // exit_code = read_row_elements(sparse_matrix, matrix);

    return exit_code;
}

int read_uint(unsigned int *const uint)
{
    long long int llint;
    if (scanf("%lld", &llint) != 1)
    {
        clear_stdin();
        return ERR_NONINTEGER;
    }

    clear_stdin();

    if (llint < 1 || llint > UINT_MAX)
        return ERR_NONUINTEGER;

    return MATRIX_OK;
}

int matrix_init(matrix_t *matrix, matrix_t *row, unsigned int rows, unsigned int columns)
{
    matrix->sizes.rows = rows;
    matrix->sizes.columns = columns;

    matrix->matrix = allocate_matrix(rows, columns);

    if (matrix->matrix == NULL)
        return ERR_MEMORY_ALLOCATION;

    row->sizes.rows = 1;
    row->sizes.columns = columns;

    row->matrix = allocate_matrix(1, columns);

    if (row->matrix == NULL)
        return ERR_MEMORY_ALLOCATION;

    return MATRIX_OK;
}

int** allocate_matrix(int n, int m)
{
    int **data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        data[i] = calloc(m, sizeof(int));
        if (!data[i])
        {
            free_matrix(data, n);
            return NULL;
        }
    }
    return data;
}

void free_matrix(int **data, int n)
{
    for (int i = 0; i < n; i++)
       free(data[i]);

    free(data);
}

