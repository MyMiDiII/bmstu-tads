#ifndef __LIST_STACK_H__

#define __LIST_STACK_H__

#define MAX_LIST_LEN 10

typedef struct list_stack_t list_stack_t;

struct list_stack_t
{
    char data;
    int index;
    list_stack_t *prev;
};

int ls_pop(list_stack_t **stack, char *const element);

int ls_push(list_stack_t **stack, const char element);

int ls_print(list_stack_t *stack);

#endif