#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "io.h"
#include "err.h"
#include "trees.h"
#include "hash.h"

int node_number = 0;
bool word_in = false;
int comparisons = 0;
int balance_comparisons = 0;
int hash_comparisons = 0;

int all_comp = 0;
int all_balance_comp = 0;
int all_hash_comp = 0;

int main(int argc, char **argv)
{
    int exit_code = OK;
    char *filename;
    FILE *file;
    bool is_open = false;
    node_t *binary_tree = NULL;
    node_t *balanced_tree = NULL;
    hash_table_t table;
    int table_size;
    int max_comparisons_num;

    exit_code = parse_args(argc, argv, &filename);

    if (!exit_code)
        exit_code = open_file(&file, filename, &is_open);

    if (!exit_code)
        exit_code = create_binary_tree(file, &binary_tree);

    if (!exit_code)
    {
        puts("\033[36m\nДДП\033[0m");
        print_tree(binary_tree, 0);

        if (node_number)
        {
            puts("\nСреднее количество сравнений при поиске ДДП:");
            printf("%d", (all_comp + node_number - 1) / node_number);
        }
    }

    if (!exit_code)
        exit_code = create_balanced_tree(file, &balanced_tree);

    if (!exit_code)
    {
        puts("\033[36m\nСБАЛАНСИРОВАННОЕ ДЕРЕВО\033[0m");
        print_tree(balanced_tree, 0);

        if (node_number)
        {
            puts("\nСреднее количество сравнений при поиске в сбалансированном дереве:");
            printf("%d", (all_balance_comp + node_number - 1) / node_number);
        }
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
    {
        exit_code = ERR_NONSIZE;
        while (exit_code)
        {
            puts("\nВведите максимальное среднее количество сравнений:");
            exit_code = read_comp(&max_comparisons_num);
            if (exit_code)
                puts("Неверные данные! Повторите попытку!");
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

        if (node_number)
        {
            puts("\nСреднее количество сравнений при поиске в хеш-таблице:");
            printf("%d\n", (all_hash_comp + node_number - 1) / node_number);
        }
    }

    if (!exit_code && node_number && (all_hash_comp + node_number - 1) / node_number > max_comparisons_num)
    {
        puts("Превышено максимальное среднее количество сравнений!");
        puts("Произодится реструктуризация!");

        while (!exit_code && (all_hash_comp + node_number - 1) / node_number > max_comparisons_num)
        {
            all_hash_comp = 0;

            exit_code = restructuring(file, &table);
        }

        puts("\033[36m\nРЕСТРУКТУРИРОВАННАЯ ХЕШ-ТАБЛИЦА\033[0m");
        print_table(&table);

        if (node_number)
        {
            puts("\nСреднее количество сравнений при поиске в хеш-таблице:");
            printf("%d\n", (all_hash_comp + node_number - 1) / node_number);
        }
    }

    if (!exit_code)
        exit_code = add_while_not_in(&binary_tree, &balanced_tree, &table, file);
        
    if (is_open && fclose(file) == EOF)
        exit_code = ERR_CLOSE_FILE;

    free_tree(binary_tree);
    free_table(&table);

    print_err(exit_code);
    return exit_code;
}
