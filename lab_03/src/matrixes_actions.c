#include <time.h>

#include "matrixes_actions.h"
#include "errors.h"

int multiply_row_and_matrix(matrix_t *row, matrix_t *matrix)
{
    if (!row->matrix || !matrix->matrix)
        return ERR_NO_MATRIX;

    int exit_code = MATRIX_OK;
    matrix_t result = { .matrix = NULL, .sizes.rows = 0,
                        .sizes.columns = 0, .sizes.nonzeros = 0};
    sparse_matrix_t sparse_result;

    if (row->sizes.rows != 1)
        return ERR_NONROW;

    if (row->sizes.columns != matrix->sizes.rows)
        return ERR_WRONG_MATRIXES_SIZES;

    exit_code = matrix_init(&result, 1, matrix->sizes.columns, matrix->sizes.rows);

    if (exit_code)
        return exit_code;

    exit_code = sparse_matrix_init(&sparse_result, 1, matrix->sizes.rows,
                                   matrix->sizes.rows);

    if (exit_code)
    {
        free_matrix_t(&result);
        return exit_code;
    }

    clock_t start, finish;

    start = clock();
    for (uint i = 0; i < row->sizes.columns; i++)
    {
        result.matrix[0][i] = 0;

        for (uint j = 0; j < row->sizes.columns; j++)
            result.matrix[0][i] += row->matrix[0][j] * matrix->matrix[j][i];
    }
    finish = clock();

    clock_t time = finish - start;
    printf("\nВремя работы (в тактах): %ld\n\n", time);

    create_sparse_by_matrix(&result, &sparse_result);

    exit_code = choice_print(&result, &sparse_result);

    free_matrix_t(&result);
    free_sparse_t(&sparse_result);
    
    return exit_code;
}

int sparse_multiply_row_and_matrix(sparse_matrix_t *row, sparse_matrix_t *matrix)
{
    if (!row->elements || !matrix->elements)
        return ERR_NO_MATRIX;

    int exit_code = MATRIX_OK;
    sparse_matrix_t sparse_result = { .elements = NULL, .rows = NULL, .columns = NULL,
                                      .sizes.columns = 0, .sizes.rows = 0,
                                      .sizes.nonzeros = 0};
    matrix_t result = { .matrix = NULL, .sizes.rows = 0,
                        .sizes.columns = 0, .sizes.nonzeros = 0};

    if (row->sizes.rows != 1)
        return ERR_NONROW;

    if (row->sizes.columns != matrix->sizes.rows)
        return ERR_WRONG_MATRIXES_SIZES;

    exit_code = sparse_matrix_init(&sparse_result, 1, matrix->sizes.columns,
                                   matrix->sizes.columns);
     
    if (exit_code)
        return exit_code;

    uint nonzeros_num = 0;

    clock_t start, finish;

    start = clock();
    for (uint begin = 0; begin < matrix->sizes.columns; )
    {
        if (matrix->columns[begin] != -1)
        {
            // el -- element
            int sum = 0;
            uint end = begin + 1;
            uint begin_el_index = matrix->columns[begin];
            uint end_el_index;

            while (end < matrix->sizes.columns && matrix->columns[end] == -1)
                end++;

            if (end == matrix->sizes.columns)
                end_el_index = matrix->sizes.nonzeros;
            else
                end_el_index = matrix->columns[end]; 

            for (uint i = begin_el_index; i < end_el_index; i++)
            {
                int el = matrix->elements[i];
                uint el_row = matrix->rows[i];
                int row_el_index = row->columns[el_row];

                if (row_el_index != -1)
                    sum += el * row->elements[row_el_index];

            }
            
            if (sum != 0)
            {
                sparse_result.elements[nonzeros_num] = sum;
                sparse_result.rows[nonzeros_num] = 0;
                sparse_result.columns[begin] = nonzeros_num;
                nonzeros_num++;
            }

            begin = end;
        }
        else
            begin++;
    }
    finish = clock();

    clock_t time = finish - start;
    printf("\nВремя работы (в тактах): %ld\n\n", time);

    sparse_result.sizes.nonzeros = nonzeros_num;

    exit_code = matrix_init(&result, 1, matrix->sizes.columns, nonzeros_num);

    if (exit_code)
    {
        free_sparse_t(&sparse_result);
        return exit_code;
    }

    create_matrix_by_sparse(&sparse_result, &result);

    exit_code = choice_print(&result, &sparse_result);

    free_matrix_t(&result);
    free_sparse_t(&sparse_result);

    return exit_code;
}

int choice_print(matrix_t *matrix, sparse_matrix_t *sparse_matrix)
{
    int exit_code = MATRIX_OK;
    uint choice;

    puts("Выберете формат вывода результирующией матрицы:");
    puts("    0 - стандартный;");
    puts("    1 - разреженный.");

    exit_code = read_uint(&choice);
    clear_stdin();

    if (exit_code || (choice != 0 && choice != 1))
        return ERR_PRINT_FLAG_READ;

    puts("\nРезультат умножения вектора-строки на матрицу:\n");

    if (choice)
        exit_code = print_sparse(sparse_matrix);
    else
        exit_code = print_matrix(matrix);

    return exit_code;
}