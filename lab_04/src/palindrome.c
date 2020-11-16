#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>

#include "palindrome.h"
#include "my_functions.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "errors.h"

void read_word(arr_stack_t *a_word, list_stack_t **l_word)
{
    wint_t wc = L'1';
    putws(L"Enter text. Include a dot (.) in a sentence to exit:\n");
    do {
        putws(L"here\n");
        wc=getwchar();
        putwchar(wc);
        putws(L"her\n");
    } while (wc != L'.');
    /*wint_t cur_ch;
    while ((cur_ch = getwchar()) != L'\n' && cur_ch != WEOF)
    {
        as_push(a_word, cur_ch);
        ls_push(l_word, cur_ch);
    }*/
}

int check_word(void)
{
    int exit_code = OK;
    arr_stack_t a_word = { .length = 0};
    list_stack_t *l_word = NULL;

    read_word(&a_word, &l_word);
    ls_print(&l_word);
    as_print(&a_word);

    /*if (!exit_code)
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
        printf("Строка %s палнидромом!\n", l_flag ?
               "является" : "не является");
        puts("Время");
    }*/

    return exit_code;
}