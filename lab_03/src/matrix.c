#include <stdio.h>
#include <limits.h>

#include "matrix.h"
#include "errors.h"
#include "my_read_functions.h"

int read_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                  matrix_t *matrix, matrix_t *row)
{
    int exit_code = MATRIX_OK;
    uint rows_num = 0, columns_num = 0;

    exit_code = read_matrix(matrix, sparse_matrix, &rows_num, &columns_num);
    
    if (exit_code)
        return exit_code;

    exit_code = read_row(row, sparse_row, rows_num, columns_num);

    return exit_code;

}

int read_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix,
                uint *const rows_num, uint *const columns_num)
{
    int exit_code = MATRIX_OK;
    uint nonzero_num = 0;

    free_matrix(matrix->matrix, matrix->sizes.rows);

    puts("Введите количество строк матрицы: ");

    exit_code = read_uint(rows_num);
    clear_stdin();

    if (exit_code || !rows_num)
        return exit_code;

    puts("Введите количество столбцов матрицы: ");

    exit_code = read_uint(columns_num);
    clear_stdin();

    if (exit_code || !columns_num)
        return exit_code;

    printf("Введите количество ненулевых элементов матрицы (max_num = %d):\n",
            *rows_num * *columns_num);

    read_uint(&nonzero_num);
    clear_stdin();

    if (exit_code)
        return exit_code;

    if (nonzero_num > *rows_num * *columns_num)
        return ERR_TOO_MUCH_NONZERO;

    exit_code = matrix_init(matrix, *rows_num, *columns_num, nonzero_num);

    if (exit_code)
        return exit_code;

    exit_code = sparse_matrix_init(sparse_matrix, *rows_num, *columns_num, nonzero_num);

    if (exit_code)
        return exit_code;

    if (nonzero_num)
    {
        printf("Введите %d элемент(а/ов) матрицы в формате \"строка столбец значение\""
               "(без ковычек):\n", nonzero_num);

        exit_code = read_matrix_elements(sparse_matrix, matrix, nonzero_num);
        clear_stdin();
    }

    if (exit_code)
        return exit_code;

    puts("");
    print_matrix(matrix);
    puts("");
    print_sparse(sparse_matrix);
    puts("");

    return exit_code;
}

int read_row(matrix_t *row, sparse_matrix_t *sparse_row,
             const uint rows_num, const uint columns_num)
{
    int exit_code = MATRIX_OK;
    uint nonzero_num = 0;

    printf("Введите количество ненулевых элементов вектора-строки (max_num = %d):\n",
            rows_num);

    read_uint(&nonzero_num);
    clear_stdin();

    if (exit_code)
        return exit_code;

    if (nonzero_num > rows_num)
        return ERR_TOO_MUCH_NONZERO;

    exit_code = matrix_init(row, 1, columns_num, nonzero_num);

    if (exit_code)
        return exit_code;

    exit_code = sparse_matrix_init(sparse_row, 1, columns_num, nonzero_num);
    
    if (exit_code)
        return exit_code;

    if (nonzero_num)
    {
        printf("Введите %d элемент(а/ов) вектора-строки в формате \"столбец значение\""
               "(без ковычек):\n", nonzero_num);

        exit_code = read_row_elements(sparse_row, row, nonzero_num);
    }

    puts("");
    print_matrix(row);
    puts("");
    print_sparse(sparse_row);
    puts("");

    return exit_code;

}

int matrix_init(matrix_t *matrix, uint rows, uint columns, uint nonzero_num)
{
    matrix->sizes.rows = rows;
    matrix->sizes.columns = columns;
    matrix->sizes.nonzeros = nonzero_num;

    matrix->matrix = allocate_matrix(rows, columns);

    if (matrix->matrix == NULL)
        return ERR_MEMORY_ALLOCATION;

    return MATRIX_OK;
}

int** allocate_matrix(uint n, uint m)
{
    int **data = calloc(n, sizeof(int*));

    if (!data)
        return NULL;

    for (uint i = 0; i < n; i++)
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

void free_matrix(int **data, uint n)
{
    for (uint i = 0; i < n; i++)
       free(data[i]);

    free(data);
}

int sparse_matrix_init(sparse_matrix_t *matrix, uint rows, uint columns, uint nonzero_num)
{
    matrix->sizes.rows = rows;
    matrix->sizes.columns = columns;
    matrix->sizes.nonzeros = nonzero_num;

    matrix->elements = calloc(nonzero_num, sizeof(int));

    if (!matrix->elements)
        return ERR_MEMORY_ALLOCATION;

    matrix->rows = calloc(nonzero_num, sizeof(int));

    if (!matrix->rows)
        return ERR_MEMORY_ALLOCATION;

    matrix->columns = malloc(columns * sizeof(int));

    if (!matrix->columns)
        return ERR_MEMORY_ALLOCATION;

    for (uint i = 0; i < columns; i++)
        matrix->columns[i] = -1;

    return MATRIX_OK;
}

int read_matrix_elements(sparse_matrix_t *sparse_matrix, matrix_t *matrix,
                         const uint nonzeros)
{
    int exit_code = MATRIX_OK;

    for (uint i = 0; i < nonzeros; i++)
    {
        puts("ye");
        uint row;
        uint column;
        int num;

        exit_code = read_uint(&row);
        
        if (exit_code || row > sparse_matrix->sizes.rows
            || row > matrix->sizes.rows)
            return exit_code;

        exit_code = read_uint(&column);
        
        if (exit_code || column > sparse_matrix->sizes.columns
            || row > matrix->sizes.columns)
            return exit_code;
        
        if (scanf("%d", &num) != 1)
            return ERR_NONINTEGER;

        matrix->matrix[row][column] = num;
    }

    create_sparse_by_matrix(matrix, sparse_matrix);

    return MATRIX_OK;
}

int read_row_elements(sparse_matrix_t *sparse_row, matrix_t *row,
                         const uint nonzeros)
{
    int exit_code = MATRIX_OK;

    for (uint i = 0; i < nonzeros; i++)
    {
        puts("ye");
        uint column;
        int num;

        exit_code = read_uint(&column);
        
        if (exit_code || column > sparse_row->sizes.columns
            || column > row->sizes.columns)
            return exit_code;
        
        if (scanf("%d", &num) != 1)
            return ERR_NONINTEGER;

        row->matrix[0][column] = num;
    }
    clear_stdin();

    create_sparse_by_matrix(row, sparse_row);

    return MATRIX_OK;

}

void create_sparse_by_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix)
{
    uint count = 0;

    for (uint j = 0; j < matrix->sizes.columns; j++)
    {
        for (uint i = 0; i < matrix->sizes.rows; i++)
        {
            int element = matrix->matrix[i][j];

            if (element)
            {
                sparse_matrix->elements[count] = element;
                sparse_matrix->rows[count] = i;

                if (sparse_matrix->columns[j] == -1)
                    sparse_matrix->columns[j] = count;
                
                count++;
            }
        }
    }
}

void print_matrix(matrix_t *matrix)
{
    for (uint i = 0; i < matrix->sizes.rows; i++)
    {
        for (uint j = 0; j < matrix->sizes.columns; j++)
            printf("%d ", matrix->matrix[i][j]);
        
        puts("");
    }
}

void print_sparse(sparse_matrix_t *matrix)
{
    for (uint i = 0; i < matrix->sizes.nonzeros; i++)
        printf("%d ", matrix->elements[i]);
    puts("");

    for (uint i = 0; i < matrix->sizes.nonzeros; i++)
        printf("%d ", matrix->rows[i]);
    puts("");

    for (uint i = 0; i < matrix->sizes.columns; i++)
        printf("%d ", matrix->columns[i]);
    puts("");
}