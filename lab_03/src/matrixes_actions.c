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

    exit_code = matrix_init(&result, 1, matrix->sizes.columns, 0);
    exit_code = sparse_matrix_init(&sparse_result, 1, matrix->sizes.rows, 0);

    if (exit_code)
        return exit_code;

    for (uint i = 0; i < row->sizes.columns; i++)
    {
        result.matrix[0][i] = 0;

        for (uint j = 0; j < row->sizes.columns; j++)
        {
            result.matrix[0][i] += row->matrix[0][j] * matrix->matrix[j][i];
            // printf("%d %d %d\n", row->matrix[0][j], matrix->matrix[j][i], result.matrix[0][i]);
        }
    }

    // puts("OK");
    create_sparse_by_matrix(&result, &sparse_result);
    // puts("OK");

    uint choice;

    puts("Выберете формат вывода результирующией матрицы:");
    puts("    0 - стандартный;");
    puts("    1 - разреженный.");

    exit_code = read_uint(&choice);
    clear_stdin();

    if (exit_code || (choice != 0 && choice != 1))
        return ERR_PRINT_FLAG_READ;

    puts("\nРезультат умножения вектора-строки на матрицу:\n");

    // puts("OK");
    if (choice)
        exit_code = print_sparse(&sparse_result);
    else
        exit_code = print_matrix(&result);
    // puts("OK");
    
    return exit_code;
}