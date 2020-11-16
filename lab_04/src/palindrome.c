#include <stdio.h>
#include <stdbool.h>

#include "palindrome.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "errors.h"

/*
int check_word(void)
{
    int exit_code = OK;
    arr_stack_t a_word = { .length = 0};
    list_stack_t *l_word = NULL;

    exit_code = read_word(&a_word, &l_word);

    if (!exit_code)
    {
        bool a_flag, l_flag;

        puts("СТЕК НА МАССИВЕ\n");
        //time
        a_flag = a_is_palindrome(a_word);
        //time
        printf("Строка %s палнидромом!\n", a_flag ?
               "является" : "не является");
        puts("Время\n");
        
        puts("СТЕК НА СПИСКЕ\n");
        //time
        l_flag = l_is_palindrome(l_word);
        //time
        printf("Строка %s палнидромом!\n", a_flag ?
               "является" : "не является");
        puts("Время");
    }

    return exit_code;
}*/