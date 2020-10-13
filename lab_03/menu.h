#ifndef __MENU_H__

#define __MENU_H__

#include "matrix.h"

#define MAX_MENU_ITEM_LEN 2

void print_menu(void);

int choose_action(short int *const action);

void print_error_message(const int code);

int do_action(const short int action,
              sparse_matrix_t *sparse_matrix,
              sparse_matrix_t *sparse_row,
              matrix_t *matrix,
              matrix_t *row);

#endif