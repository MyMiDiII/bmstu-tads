#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "errors.h"
#include "my_functions.h"

#define MAX_PRINT_SIZE 30

int read_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                  matrix_t *matrix, matrix_t *row)
{
    int exit_code = MATRIX_OK;
    uint rows_num = 0, columns_num = 0;

    exit_code = read_matrix(matrix, sparse_matrix, &rows_num, &columns_num);
    
    if (exit_code)
        return exit_code;

    exit_code = read_row(row, sparse_row, rows_num);

    return exit_code;
}

int read_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix,
                uint *const rows_num, uint *const columns_num)
{
    int exit_code = MATRIX_OK;
    uint nonzero_num = 0;

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

    exit_code = read_uint(&nonzero_num);
    clear_stdin();

    if (exit_code)
        return exit_code;

    if (nonzero_num > *rows_num * *columns_num)
        return ERR_TOO_MUCH_NONZERO;

    free_matrix_t(matrix);
    free_sparse_t(sparse_matrix);

    exit_code = matrix_init(matrix, *rows_num, *columns_num, nonzero_num);

    if (exit_code)
        return exit_code;

    exit_code = sparse_matrix_init(sparse_matrix, *rows_num, *columns_num, nonzero_num);

    if (exit_code)
    {
        free_matrix(matrix->matrix, matrix->sizes.rows);
        return exit_code;
    }

    if (nonzero_num)
    {
        printf("Введите %d элемент(а/ов) матрицы в формате \"строка столбец значение\""
               "(без ковычек):\n", nonzero_num);

        exit_code = read_matrix_elements(sparse_matrix, matrix, nonzero_num);
        clear_stdin();
    }

    if (exit_code)
    {
        free_matrix_t(matrix);
        free_sparse_t(sparse_matrix);
    }

    return exit_code;
}

void free_matrix_t(matrix_t *matrix)
{
    free_matrix(matrix->matrix, matrix->sizes.rows);
    matrix->matrix = NULL;
    matrix->sizes.rows = 0;
    matrix->sizes.columns = 0;
    matrix->sizes.nonzeros = 0;
}

void free_sparse_t(sparse_matrix_t *sparse_matrix)
{
    free(sparse_matrix->elements);
    free(sparse_matrix->rows);
    free(sparse_matrix->columns);
    sparse_matrix->elements = NULL;
    sparse_matrix->rows = NULL;
    sparse_matrix->columns = NULL;
    sparse_matrix->sizes.columns = 0;
    sparse_matrix->sizes.rows = 0;
    sparse_matrix->sizes.nonzeros = 0; 
}

int read_row(matrix_t *row, sparse_matrix_t *sparse_row, const uint columns_num)
{
    int exit_code = MATRIX_OK;
    uint nonzero_num = 0;

    printf("Введите количество ненулевых элементов вектора-строки (max_num = %d):\n",
            columns_num);

    read_uint(&nonzero_num);
    clear_stdin();

    if (exit_code)
        return exit_code;

    if (nonzero_num > columns_num)
        return ERR_TOO_MUCH_NONZERO;
    
    free_matrix_t(row);
    free_sparse_t(sparse_row);

    exit_code = matrix_init(row, 1, columns_num, nonzero_num);

    if (exit_code)
        return exit_code;
        
    exit_code = sparse_matrix_init(sparse_row, 1, columns_num, nonzero_num);
    
    if (exit_code)
    {
        free_matrix_t(row);
        return exit_code;
    }

    if (nonzero_num)
    {
        printf("Введите %d элемент(а/ов) вектора-строки в формате \"столбец значение\""
               "(без ковычек):\n", nonzero_num);

        exit_code = read_row_elements(sparse_row, row, nonzero_num);
        clear_stdin();
    }

    if (exit_code)
    {
        free_matrix_t(row);
        free_sparse_t(sparse_row);
    }

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
        uint row;
        uint column;
        int num;

        exit_code = read_uint(&row);

        if (exit_code || row >= sparse_matrix->sizes.rows
            || row >= matrix->sizes.rows)
            return ERR_WRONG_ELEMENT_PARAMETERS;

        exit_code = read_uint(&column);
        
        if (exit_code || column >= sparse_matrix->sizes.columns
            || column >= matrix->sizes.columns)
            return ERR_WRONG_ELEMENT_PARAMETERS;

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
        uint column;
        int num;

        exit_code = read_uint(&column);

        if (exit_code || column >= sparse_row->sizes.columns
            || column >= row->sizes.columns)
            return ERR_WRONG_ELEMENT_PARAMETERS;
        
        if (scanf("%d", &num) != 1)
            return ERR_NONINTEGER;

        row->matrix[0][column] = num;
    }

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

    sparse_matrix->sizes.nonzeros = count;
    sparse_matrix->sizes.rows = matrix->sizes.rows;
    sparse_matrix->sizes.columns = matrix->sizes.columns;
}

void create_matrix_by_sparse(sparse_matrix_t *sparse_matrix, matrix_t *matrix)
{
    for (uint begin = 0; begin < sparse_matrix->sizes.columns; )
    {
        if (sparse_matrix->columns[begin] != -1)
        {
            // el -- element
            uint end = begin + 1;
            uint begin_el_index = sparse_matrix->columns[begin];
            uint end_el_index;

            while (end < sparse_matrix->sizes.columns &&
                   sparse_matrix->columns[end] == -1)
                end++;

            if (end == matrix->sizes.columns)
                end_el_index = sparse_matrix->sizes.nonzeros;
            else
                end_el_index = sparse_matrix->columns[end]; 

            for (uint i = begin_el_index; i < end_el_index; i++)
            {
                int el = sparse_matrix->elements[i];
                uint el_row = sparse_matrix->rows[i];

                matrix->matrix[el_row][begin] = el;
            }
            
            begin = end;
        }
        else
            begin++;
    }
}

int user_print(matrix_t *matrix, matrix_t *row,
               sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row)
{
    int exit_code = MATRIX_OK;
    uint choice;

    if (!matrix->matrix || !row->matrix)
        return ERR_NO_MATRIX;

    puts("Выберете формат вывода матриц:");
    puts("    0 - стандартный;");
    puts("    1 - разреженный.");

    exit_code = read_uint(&choice);
    clear_stdin();

    if (exit_code || (choice != 0 && choice != 1))
        return ERR_PRINT_FLAG_READ;

    if (choice)
    {
        puts("\nИсходная матрица:");
        exit_code = print_sparse(sparse_matrix);

        if (exit_code)
            return exit_code;

        puts("\nИсходный вектор-строка:");
        exit_code = print_sparse(sparse_row);

        if (exit_code)
            return exit_code;
    }
    else
    {
        puts("\nИсходная матрица:");
        exit_code = print_matrix(matrix);

        if (exit_code)
            return exit_code;

        puts("\nИсходный вектор-строка:");
        exit_code = print_matrix(row);

        if (exit_code)
            return exit_code;
    }

    return MATRIX_OK;
}

int print_matrix(matrix_t *matrix)
{
    int exit_code = MATRIX_OK;
    uint print_flag = 1;

    if (matrix->sizes.rows > MAX_PRINT_SIZE ||
        matrix->sizes.columns > MAX_PRINT_SIZE)
    {
        printf("\nОдна из размерностей выводимой матрицы больше %d!\n",
               MAX_PRINT_SIZE);
        puts("Вывести матрицу? (0 - нет, 1 - да)");

        exit_code = read_uint(&print_flag);
        clear_stdin();

        if (exit_code || (print_flag != 0 && print_flag != 1))
            return ERR_PRINT_FLAG_READ;
    }

    if (print_flag)
    {
        for (uint i = 0; i < matrix->sizes.rows; i++)
        {
            for (uint j = 0; j < matrix->sizes.columns; j++)
                printf("%6d ", matrix->matrix[i][j]);
            
            puts("");
        }
    }

    return MATRIX_OK;
}

int print_sparse(sparse_matrix_t *matrix)
{
    int exit_code = MATRIX_OK;
    uint print_flag = 1;

    if (matrix->sizes.rows > MAX_PRINT_SIZE ||
        matrix->sizes.columns > MAX_PRINT_SIZE ||
        matrix->sizes.nonzeros > MAX_PRINT_SIZE)
    {
        printf("\nОдна из размерностей выводимой матрицы больше %d!\n",
               MAX_PRINT_SIZE);
        puts("Вывести матрицу? (0 - нет, 1 - да)");

        exit_code = read_uint(&print_flag);
        clear_stdin();

        if (exit_code || (print_flag != 0 && print_flag != 1))
            return ERR_PRINT_FLAG_READ;
    }

    if (print_flag)
    {
        puts("\nЗначения элементов:");
        for (uint i = 0; i < matrix->sizes.nonzeros; i++)
            printf("%6d ", matrix->elements[i]);
        puts("");

        puts("\nНомера строк этих элементов:");
        for (uint i = 0; i < matrix->sizes.nonzeros; i++)
            printf("%6d ", matrix->rows[i]);
        puts("");

        puts("\nНомер элемента, с которого начинается k-ый столбец, "
             "где k - порядковый номер столбца:");
        for (uint i = 0; i < matrix->sizes.columns; i++)
            printf("%6d ", matrix->columns[i]);
        puts("");
    }

    puts("\n-1 в последнем массиве означает, что в столбце нет элементов");

    return MATRIX_OK;
}

int generate_matrixes(sparse_matrix_t *sparse_matrix, sparse_matrix_t *sparse_row,
                      matrix_t *matrix, matrix_t *row)
{
    puts("\nРазмеры вектора-строки задаются автоматически для возможности умножения.");
    puts("Процент заполенности такой же, как у матрицы (для оценки эффективности).\n");

    int exit_code = MATRIX_OK;
    uint percent = 0;
    uint rows_num, columns_num;

    puts("Введите количество строк матрицы: ");

    exit_code = read_uint(&rows_num);
    clear_stdin();

    if (exit_code || !rows_num)
        return exit_code;

    puts("Введите количество столбцов матрицы: ");

    exit_code = read_uint(&columns_num);
    clear_stdin();

    if (exit_code || !columns_num)
        return exit_code;

    puts("Введите процент заполненности матрицы: ");

    read_uint(&percent);
    clear_stdin();

    if (exit_code)
        return exit_code;

    uint non_zeros = my_round(((double) rows_num * columns_num * percent) / 100);

    if (!non_zeros)
        return ERR_EMPTY_MATRIX;

    free_matrix_t(matrix);
    free_matrix_t(row);
    free_sparse_t(sparse_matrix);
    free_sparse_t(sparse_row);

    exit_code = matrix_init(matrix, rows_num, columns_num, non_zeros);

    if (exit_code)
        return exit_code;

    exit_code = sparse_matrix_init(sparse_matrix, rows_num, columns_num, non_zeros);

    if (exit_code)
    {
        free_matrix_t(matrix);
        return exit_code;
    }

    generate_matrix(matrix, sparse_matrix);

    non_zeros = my_round(((double) rows_num * percent) / 100);

    if (!non_zeros)
    {
        free_matrix_t(matrix);
        free_sparse_t(sparse_matrix);
        return ERR_EMPTY_MATRIX;
    }

    exit_code = matrix_init(row, 1, rows_num, non_zeros);

    if (exit_code)
    {
        free_matrix_t(matrix);
        free_sparse_t(sparse_matrix);
        return exit_code;
    }

    exit_code = sparse_matrix_init(sparse_row, 1, rows_num, non_zeros);

    if (exit_code)
    {
        free_matrix_t(matrix);
        free_matrix_t(row);
        free_sparse_t(sparse_matrix);
        return exit_code;
    }
        
    generate_matrix(row, sparse_row);

    return exit_code;
}

void generate_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix)
{
    srand(time(NULL));

    for (uint i = 0; i < matrix->sizes.nonzeros; i++)
    {
        int el = -50 + rand() % 101;
        uint rows = matrix->sizes.rows;
        uint columns = matrix->sizes.columns;
        uint index = rand() % (rows * columns);

        matrix->matrix[index / columns][index % columns] = el;
    }

    create_sparse_by_matrix(matrix, sparse_matrix);
}