#include <stdio.h>
#include <stdbool.h>

#include "io.h"
#include "err.h"
#include "trees.h"
#include "hash.h"

int node_number = 0;
bool word_in = false;
int comparisons = 0;
int balance_comparisons = 0;
int hash_comparisons = 0;

int main(int argc, char **argv)
{
    int exit_code = OK;
    char *filename;
    FILE *file;
    bool is_open = false;
    // bool is_mem_bin = false;
    node_t *binary_tree = NULL;
    node_t *balanced_tree = NULL;
    hash_table_t table;
    int table_size;
    // bool answer = true;

    exit_code = parse_args(argc, argv, &filename);

    if (!exit_code)
        exit_code = open_file(&file, filename, &is_open);

    if (!exit_code)
        exit_code = create_binary_tree(file, &binary_tree);

    if (!exit_code)
    {
        puts("\033[36m\nДДП\033[0m");
        print_tree(binary_tree, 0);
    }

    if (!exit_code)
    {
        exit_code = create_balanced_tree(binary_tree, &balanced_tree);
    }

    if (!exit_code)
    {
        puts("\033[36m\nСБАЛАНСИРОВАННОЕ ДЕРЕВО\033[0m");
        print_tree(balanced_tree, 0);
    }

    if (!exit_code)
    {
        exit_code = ERR_NONSIZE;
        while (exit_code)
        {
            puts("\nВведите размер хеш-таблицы:");
            exit_code = read_size(&table_size);
            if (exit_code)
                puts("Неверный размер! Повторите попытку!");
        }
    }

    if (!exit_code)
        exit_code = hash_table_init(&table, table_size);

    if (!exit_code)
        exit_code = create_hash_table(file, &table);

    if (!exit_code)
    {
        puts("\033[36m\nХЕШ-ТАБЛИЦА\033[0m");
        print_table(&table);
    }

    if (!exit_code)
        exit_code = add_while_not_in(&binary_tree, &balanced_tree, &table, file);
        
    if (is_open && fclose(file) == EOF)
        exit_code = ERR_CLOSE_FILE;

    //if (is_mem_bin)
    //    free_tree(binary_tree);

    print_err(exit_code);
    return exit_code;
}
