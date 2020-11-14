#include <stdio.h>

#include "arr_stack.h"
#include "errors.h"

int as_pop(arr_stack_t *stack, char *const element)
{
    if (!stack->length)
        return ERR_EMPTY_STACK;

    stack->length--;
    *element = stack->array[stack->length];
    return OK;
}

int as_push(arr_stack_t *stack, const char element)
{
    if (stack->length == MAX_ARR_LEN)
        return ERR_FULL_STACK;

    stack->array[stack->length] = element;
    stack->length++;
    return OK;
}

int as_print(arr_stack_t *stack)
{
    if (!stack->length)
        return ERR_EMPTY_STACK;

    for (int i = stack->length - 1; i >= 0; i--)
        printf("%c\n", stack->array[i]);
        
    return OK;
}