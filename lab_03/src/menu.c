#include <stdio.h>

#include "menu.h"
#include "my_functions.h"
#include "errors.h"
#include "matrix.h"
#include "matrixes_actions.h"

void print_menu(void)
{
    puts("");
    puts("          МЕНЮ");
    puts("");
    puts("1  - Ввести вектор-строку и матрицу вручную");
    puts("2  - Сгенерировать вектор-строку и матрицу по проценту заполненности");
    puts("3  - Вывести исходную матрицу и вектор-строку");
    puts("4  - Перемножить матрицы алгоритмом обработки разреженных матриц");
    puts("5  - Перемножить матрицы стандартным алгоритмом обработки матриц");
    puts("0  - Выход");
    puts("");
    puts("P. S. Затраченное время и пямять указываются при выполнении умножения (пункты 3 и 4)");
    puts("");
}

void print_error_message(const int code)
{
    if (ERR_WRONG_ACTION == code)
    {
        puts("\nВведенный код не соответствует ни одному действию.");
        puts("Попробуйте ещё раз.\n");
    }
    else if (ERR_READ_ACTION == code)
    {
        puts("\nНекорректный ввод кода действия.");
        puts("Попробуйте ещё раз.\n");
    }
    else if (ERR_TOO_MUCH_NONZERO == code)
        puts("\nКоличество ненулевых элементов больше количества элементов в матрице!");

    else if (ERR_NONINTEGER == code)
        puts("\nОшибка при чтении числа!");

    else if (ERR_NONUINTEGER == code)
        puts("\nВведенное значение выходит за допустимый диапазон значений!");

    else if (ERR_NO_MATRIX == code)
        puts("\nСначала введите или сгенерируйте матрицы!");

    else if (ERR_PRINT_FLAG_READ== code)
        puts("\nТакого значения нет в списке!");
}

int choose_action(short int *const action)
{
    puts("Выберете пункт меню: ");

    char str[MAX_MENU_ITEM_LEN + 2];

    if (read_str(str, MAX_MENU_ITEM_LEN + 3, stdin))
        return ERR_READ_ACTION;

    char *end_prt;
    long int long_str = strtol(str, &end_prt, 10);

    if (*end_prt != '\0')
        return ERR_WRONG_ACTION;
    
    if (long_str < 0 || long_str > 5)
        return ERR_WRONG_ACTION;

    *action = (short int) long_str;

    return READ_OK;
}

int do_action(const short int action,
              sparse_matrix_t *sparse_matrix,
              sparse_matrix_t *sparse_row,
              matrix_t *matrix,
              matrix_t *row)
{
    int exit_code = MATRIX_OK;

    switch (action)
    {
        case 1:
            exit_code = read_matrixes(sparse_matrix, sparse_row, matrix, row);
            break;

        case 2:
            exit_code = generate_matrixes(sparse_matrix, sparse_row, matrix, row);
            break;

        case 3:
            exit_code = user_print(matrix, row, sparse_matrix, sparse_row);
            break;

        case 4:
            exit_code = sparse_multiply_row_and_matrix(sparse_row, sparse_matrix);
            break;

        case 5:
            exit_code = multiply_row_and_matrix(row, matrix);
            break;

        default:
            puts("\nСпасибо за использование программы!");
            puts("Автор:  МАСЛОВА МАРИНА");
            puts("Группа: ИУ7-33Б");
            exit(EXIT_SUCCESS);
            break;
    }

    return exit_code;
}