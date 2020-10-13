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

#endif