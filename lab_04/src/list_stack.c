#include <stdio.h>
#include <stdlib.h>

#include "list_stack.h"
#include "errors.h"

int ls_pop(list_stack_t **stack, char *const element)
{
    if (!stack)
        return ERR_NULL_POINTER;

    if (!*stack)
        return ERR_EMPTY_STACK;

    list_stack_t *prev = *stack;
    *stack = (*stack)->prev;

    *element = prev->data;
    free(prev);

    return OK;
}

int ls_push(list_stack_t **stack, const char element)
{
    if (!stack)
        return ERR_NULL_POINTER;
    
    if (*stack && (*stack)->index == MAX_LIST_LEN)
        return ERR_FULL_STACK;

    list_stack_t *node = malloc(sizeof(list_stack_t));
    node->data = element;
    node->index = (!*stack) ? 0 : (*stack)->index + 1;
    node->prev = *stack;
    *stack = node;

    return OK;
}

int ls_print(list_stack_t **stack)
{
    if (!*stack)
        return ERR_EMPTY_STACK;

    list_stack_t *node = NULL;
    while (*stack)
    {
        printf("%p  ", (void *) (*stack));
        printf("%18c\n", (*stack)->data);

        char el;
        ls_pop(stack, &el);
        ls_push(&node, el);
    }

    while (node)
    {
        char el;
        ls_pop(&node, &el);
        ls_push(stack, el);
    }

    return OK;
}
