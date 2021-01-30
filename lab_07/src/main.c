#include <stdio.h>
#include <stdbool.h>

#include "menu.h"
#include "graph.h"

#define OK 0

int main(void)
{
    int exit_code = OK;
    graph_t graph = { .graph = NULL, .nodes = 0 }; 

    while (true)
    {
        short int action;
        print_menu();
        exit_code = choose_action(&action);

        if (exit_code)
        {
            print_error_message(exit_code);
            continue;
        }

        exit_code = do_action(action, &graph);

        if (exit_code)
        {
            print_error_message(exit_code);
            continue;
        }
    }

    return OK;
}
