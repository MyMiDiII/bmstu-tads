#ifndef __MENU_H__

#define __MENU_H__

#define OK_ACTION 0
#define ERR_WRONG_ACTION -1
#define ERR_READ_ACTION -2

void print_menu_error(const int code);

void print_menu(void);

int choose_action(short int *const action);

int do_action(const short int action);

#endif