#ifndef __MATRIX_H__

#define __MATRIX_H__

#include "my_read_functions.h"

typedef struct
{
    uint rows;
    uint columns;
    uint nonzeros;
} matrix_size_t;

typedef struct
{
    matrix_size_t sizes;
    int *elements;
    uint *rows;
    uint *columns;
} sparse_matrix_t;

typedef struct
{
    matrix_size_t sizes;
    int **matrix;
} matrix_t;

int read_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                  matrix_t *matrix, matrix_t *row);

int read_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix,
                uint *const rows_num, uint *const columns_num);

int read_row(matrix_t *row, sparse_matrix_t *sparse_row,
             const uint rows_num, const uint columns_num);

int matrix_init(matrix_t *matrix, uint rows, uint columns, uint nonzeros_num);

int** allocate_matrix(uint n, uint m);

void free_matrix(int **data, uint n);

int sparse_matrix_init(sparse_matrix_t *matrix,
                       uint rows, uint columns, uint nonzero_num);

int read_matrix_elements(sparse_matrix_t *sparse_matrix, matrix_t *matrix,
                         const uint nonzeros);

int read_row_elements(sparse_matrix_t *sparse_row, matrix_t *row,
                         const uint nonzeros);

void create_sparse_by_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix);

int user_print(matrix_t *matrix, matrix_t *row,
               sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row);

int print_matrix(matrix_t *matrix);

int print_sparse(sparse_matrix_t *matrix);

#endif