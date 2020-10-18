#ifndef __MATRIX_H__

#define __MATRIX_H__

typedef struct
{
    unsigned int rows;
    unsigned int columns;
} matrix_size_t;

typedef struct
{
    matrix_size_t sizes;
    int *elements;
    int *rows;
    int *columns;
} sparse_matrix_t;

typedef struct
{
    matrix_size_t sizes;
    int **matrix;
} matrix_t;

int read_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                  matrix_t *matrix, matrix_t *row);

int read_uint(unsigned int *const integer);

int matrix_init(matrix_t *matrix, matrix_t *row, unsigned int rows, unsigned int columns);

int** allocate_matrix(int n, int m);

void free_matrix(int **data, int n);

#endif