#ifndef __MATRIXES_ACTIONS_H__

#define __MATRIXES_ACTIONS_H__

#include "matrix.h"

int multiply_row_and_matrix(matrix_t *row, matrix_t *matrix);

int sparse_multiply_row_and_matrix(sparse_matrix_t *row, sparse_matrix_t *matrix);

#endif