#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

#include "io.h"
#include "timer.h"
#include "hash.h"
#include "trees.h"
#include "files.h"

extern int node_number;
extern bool word_in;
extern int hash_comparisons;
extern int comparisons;
extern int balance_comparisons;

int parse_args(const int argc, char **argv, char **filename)
{
    if (argc != ARGS_NUM)
        return ERR_ARGS_NUM;

    *filename = argv[1];

    return OK;
}

int open_file(FILE **file, const char *const filename, bool *const is_open)
{
    *file = fopen(filename, "r+");

    if (!*file)
        return ERR_OPEN_FILE;

    *is_open = true;
    return OK;
}

int read_string(char **string, FILE *file)
{
    *string = malloc(sizeof(char));

    if (!string)
        return ERR_MEMORY;

    int len = 0;
    int capacity = 1;

    char cur_ch;
    while ((cur_ch = getc(file)) != '\n' && cur_ch != EOF)
    {
        if (len >= capacity - 1)
        {
            char *tmp = realloc(*string, capacity * 2 * sizeof(char));

            if (!tmp)
            {
                free(*string);
                return ERR_MEMORY;
            }

            *string = tmp;
            capacity *= 2;
        }

        (*string)[len++] = cur_ch;
    }

    (*string)[len] = '\0';

    if (cur_ch == EOF)
        return END_OF_FILE;

    return OK;
}

void clear_stdin(void)
{
    char ch;
    do
    {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}            

int read_int(int *const integer)
{
    long long int llint;

    if (fscanf(stdin, "%lld", &llint) != 1)
        return ERR_NONINTEGER;

    if (llint < INT_MIN || llint > INT_MAX)
        return ERR_NONINTEGER;

    *integer = (int) llint;

    return OK;
}

int read_size(int *const size)
{
    int exit_code = OK;
    int integer;

    exit_code = read_int(&integer);
    clear_stdin();

    if (exit_code)
        return exit_code;

    if (integer <= 0)
        return ERR_NONSIZE;

    *size = integer;

    return OK;
}

int read_comp(int *const size)
{
    int exit_code = OK;
    int integer;

    exit_code = read_int(&integer);
    clear_stdin();

    if (exit_code)
        return exit_code;

    if (integer < 0)
        return ERR_NONSIZE;

    *size = integer;

    return OK;
}

int read_answer(bool *const answer)
{
    int exit_code = OK;
    int integer;

    exit_code = read_int(&integer);
    clear_stdin();

    if (exit_code)
        return exit_code;

    if (integer < 0 || integer > 1)
        return ERR_NONANSWER;

    *answer = (bool) integer;

    return OK;
}

void print_results(char *name, int64_t time, long unsigned int memory,
                   int comparisons)
{
    printf("%s\n", name);
    printf("Время добавления: %ld\n", time);
    printf("Количество сравнений: %d\n", comparisons);
    printf("Используемая память: %lu\n", memory);
}

int copy_word(char **new_word, char *word)
{
    int len = strlen(word);

    *new_word = malloc(sizeof(char) * len);

    if (!*new_word)
        return ERR_MEMORY;

    strncpy(*new_word, word, len + 1);

    return OK;
}

int add_while_not_in(node_t **tree, node_t **balanced_tree,
                     hash_table_t *table, FILE *file)
{
    comparisons = 0;
    hash_comparisons = 0;
    balance_comparisons = 0;
    puts("\nДобавить слово?");
    puts("да - 1");
    puts("нет - 0"); 
    bool answer;

    while (read_answer(&answer))
        puts("\nНесоответсвующие данные! Повторите попытку!");

    int exit_code = OK;
    while (!exit_code && answer)
    {
        answer = false;
        exit_code = add_word(tree, balanced_tree, table, file);

        if (!exit_code && word_in)
        {
            comparisons = 0;
            hash_comparisons = 0;
            balance_comparisons = 0;
            puts("\nДанное слово уже есть в деревьях и таблице!");
            puts("Добавить другое слово?");
            puts("да - 1");
            puts("нет - 0"); 
            while (read_answer(&answer))
                puts("\nНесоответсвующие данные! Повторите попытку!");
        }

        if (answer)
            word_in = false;
    }

    return exit_code;
}

int add_word(node_t **tree, node_t **balanced_tree,
             hash_table_t *table, FILE *file)
{
    int exit_code = OK;

    char *word, *word1, *word2;
    puts("\nВведите слово:");
    exit_code = read_string(&word, stdin);
    copy_word(&word1, word);
    copy_word(&word2, word);

    if (!exit_code)
    {
        int64_t start, finish;
        start = tick();
        exit_code = add_node_to_bintree(tree, word);
        finish = tick();

        if (!word_in)
        {
            print_results("\033[36m\nДОБАВЛЕНИЕ В ДДП\033[0m", finish - start,
                          node_number * (sizeof(node_t) + 1) + file_size(file),
                          comparisons);
            puts("Полученное дерево:");
            print_tree(*tree, 0);
        }
    }

    if (!word_in && !exit_code)
    {
        int64_t start, finish;
        start = tick();
        exit_code = add_node_to_balansed_tree(balanced_tree, word1);
        finish = tick();
        print_results("\033[36m\nДОБАВЛЕНИЕ В СБАЛАНСИРОВАННОЕ ДЕРЕВО\033[0m", finish - start,
                       node_number * (sizeof(node_t) + 1) + file_size(file),
                       balance_comparisons);
        puts("Полученное дерево:");
        print_tree(*balanced_tree, 0);
    }

    if (!word_in && !exit_code)
    {
        int64_t start, finish;
        start = tick();
        exit_code = add_word_to_hash_table(table, word2);
        finish = tick();
        print_results("\033[36m\nДОБАВЛЕНИЕ В ХЕШ-ТАБЛИЦУ\033[0m", finish - start,
                       node_number * (sizeof(word_list_t) + 1) + file_size(file) + \
                       table->table_size * sizeof(word_list_t *), hash_comparisons);
        puts("Полученная хеш-таблица:");
        print_table(table);
    }

    if (!word_in && !exit_code)
    {
        int64_t start, finish;
        start = tick();
        add_to_file(file, word2);
        finish = tick();
        fseek(file, 0, SEEK_SET);
        print_results("\033[36m\nДОБАВЛЕНИЕ В ФАЙЛ\033[0m", finish - start, file_size(file), node_number - 1);
    }
 
    return exit_code;   
}
