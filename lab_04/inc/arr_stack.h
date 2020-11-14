#ifndef __ARR_STACK_H__

#define __ARR_STACK_H__

#define MAX_ARR_LEN 10

typedef struct
{
    char array[MAX_ARR_LEN];
    int length;
} arr_stack_t;

int as_pop(arr_stack_t *stack, char *const element);

int as_push(arr_stack_t *stack, const char element);

int as_print(arr_stack_t *stack);

#endif