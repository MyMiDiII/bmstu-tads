#include <stdio.h>
#include <wchar.h>
#include <time.h>

#include "num_pops.h"
#include "errors.h"

int as_num_pop(arr_stack_t *stack, const int num)
{
    clock_t start, finish, time = 0L;
    wint_t el1;
    int exit_code = OK;

    for (int i = 0; i < num && stack->length && !exit_code; i++)
    {
        start = clock();
        exit_code = as_pop(stack, &el1);
        finish = clock();
        time += finish - start;
        if (!exit_code)
            fwprintf(stdout, L"\nЭлемент '%lc' успешно удален!\n", el1);
    }

    if (!exit_code)
        fwprintf(stdout, L"\nВремя работы (в тактах): %ld\n", time);

    return exit_code;
}

int ls_num_pop(list_stack_t **stack, const int num, free_areas_t *ptrs)
{
    clock_t start, finish, time = 0L;
    wint_t el1;
    int exit_code = OK;

    for (int i = 0; i < num && *stack && !exit_code; i++)
    {
        add_area(ptrs, *stack);
        start = clock();
        exit_code = ls_pop(stack, &el1);
        finish = clock();
        time += finish - start;
        if (!exit_code)
            fwprintf(stdout, L"\nЭлемент '%lc' успешно удален!\n", el1);
    }

    if (!exit_code)
        fwprintf(stdout, L"\nВремя работы (в тактах): %ld\n", time);

    return exit_code;
}