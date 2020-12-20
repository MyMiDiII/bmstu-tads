#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "hash.h"
#include "err.h"
#include "io.h"

typedef unsigned long long int ullint;

#define POLYNOMIAL 61

extern int hash_comparisons;
extern int all_hash_comp;

int hash_table_init(hash_table_t *table, const int table_size)
{
    table->table_size = table_size;
    table->arr = malloc(sizeof(word_list_t *) * table_size);

    if (!table->arr)
        return ERR_MEMORY;

    for (int i = 0; i < table_size; i++)
        table->arr[i] = NULL;

    return OK;
}

int hash_function(const char *word, const int table_size)
{
    ullint result = 0;
    ullint coef = 1;

    while (*word)
    {
        result += *word * coef;
        coef *= POLYNOMIAL;
        word++;
    }

    return result % table_size;
}

int push(word_list_t **list, char *word)
{
    word_list_t *elem = malloc(sizeof(word_list_t));

    if (!elem)
        return ERR_MEMORY;

    elem->word = word;
    elem->next = NULL;

    if (!*list)
        *list = elem;
    else
    {
        word_list_t *tmp = *list;

        while (tmp->next)
        {
            all_hash_comp++;
            hash_comparisons++;
            if (!strcmp(tmp->word, word))
            {
                free(elem);
                return OK;
            }
            tmp = tmp->next;
        }

        tmp->next = elem;
    }

    return OK;
}

int add_word_to_hash_table(hash_table_t *result, char *word)
{
    int index = hash_function(word, result->table_size);

    int exit_code = push(&result->arr[index], word);

    return exit_code;
}

int create_hash_table(FILE *file, hash_table_t *result)
{
    int exit_code = OK;
    char *word;

    while (!exit_code && !read_string(&word, file))
        exit_code = add_word_to_hash_table(result, word); 

    if (!feof(file))
        return ERR_MEMORY;

    fseek(file, 0L, SEEK_SET);
    return OK;
}

int is_prime(unsigned int num)
{
    if (num <= 1)
        return 0;
    if (num % 2 == 0 && num > 2)
        return 0;
    for (int i = 3; i < floor(sqrt(num)); i += 2)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

unsigned int next_prime(int n)
{
    unsigned int prime = n + 1;
    while (!is_prime(prime))
    {
        prime++;
    }

    return prime;
}

int restructuring(FILE *file, hash_table_t *table)
{
    int new_size = next_prime(table->table_size);

    if (new_size < table->table_size)
        return ERR_TOO_BIG_SIZE;

    free_table(table);

    int exit_code = hash_table_init(table, new_size);

    if (!exit_code)
        exit_code = create_hash_table(file, table);

    return exit_code;


    return OK;
}

void print_list(const int index, word_list_t *list)
{
    for (word_list_t *cur = list; cur; cur = cur->next)
        printf("│ %6d │ %28s │\n", index, cur->word);
}

void print_table(hash_table_t *table)
{
    if (!table->table_size)
        puts("Хеш-таблица пуста!");

    puts("┌────────┬──────────────────────────────┐");
    puts("│  Ключ  │           Слово              │");
    puts("├────────┼──────────────────────────────┤");

    for (int i = 0; i < table->table_size; i++)
        print_list(i, table->arr[i]);

    puts("└────────┴──────────────────────────────┘");
}

void free_list(word_list_t **head)
{
    if (!head)
        return;

    for (word_list_t *cur = *head; cur; )
    {
        word_list_t *next = cur->next;
        free(cur);
        cur = next;
    }

    *head = NULL;
}

void free_table(hash_table_t *table)
{
    for (int i = 0; i < table->table_size; i++)
    {
        free_list(&table->arr[i]);
    }

    free(table->arr);
}
