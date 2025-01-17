#ifndef __LIST_STACK_H__

#define __LIST_STACK_H__

#include <wchar.h>

#define MAX_LIST_LEN 10

typedef struct list_stack_t list_stack_t;

struct list_stack_t
{
    wint_t data;
    int index;
    list_stack_t *prev;
};

int ls_pop(list_stack_t **stack, wint_t *const element);

int ls_push(list_stack_t **stack, const wint_t element);

int ls_print(list_stack_t **stack);

#endif