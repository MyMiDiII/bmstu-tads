#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"
#include "err.h"
#include "io.h"

typedef long long int llint;

#define POLYNOMIAL 61

extern int hash_comparisons;

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
    llint result = 0; 
    llint coef = 1;

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

    word_list_t tmp = { .word = NULL, .next = *list };
    word_list_t *cur = &tmp;
    
    for (; cur && cur->next; cur = cur->next)
    {
        hash_comparisons++;
        if (cur->word && !strcmp(word, cur->word))
        {
            free(elem);
            return OK;
        }

    }
    
    if (cur->word && !strcmp(word, cur->word))
    {
        free(elem);
        return OK;
    }

    elem->word = word;
    elem->next = cur->next;
    cur->next = elem;
    *list = (!*list) ? elem : *list;    

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
    {
        //free_tree();
        return ERR_MEMORY;
    }

    fseek(file, 0L, SEEK_SET);
    return OK;
}

void print_list(const int index, word_list_t *list)
{
    for (word_list_t *cur = list; cur; cur = cur->next)
        printf("│ %4d │ %28s │\n", index, cur->word);
}

void print_table(hash_table_t *table)
{
    if (!table->table_size)
        puts("Хеш-таблица пуста!");

    puts("┌──────┬──────────────────────────────┐");
    puts("│ Ключ │           Слово              │");
    puts("├──────┼──────────────────────────────┤");

    for (int i = 0; i < table->table_size; i++)
        print_list(i, table->arr[i]);

    puts("└──────┴──────────────────────────────┘");
}
