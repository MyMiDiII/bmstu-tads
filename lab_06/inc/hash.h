#ifndef __HASH_H__

#define __HASH_H__

#include <stdio.h>

typedef struct word_list word_list_t;

struct word_list
{
    char *word;
    word_list_t *next;
};

typedef struct hash_table
{
    word_list_t **arr;
    int table_size;
} hash_table_t;

int hash_table_init(hash_table_t *table, const int table_size);

int hash_functon(const char *const word, const int table_size);

int create_hash_table(FILE *file, hash_table_t *result);

void print_table(hash_table_t *table);

int add_word_to_hash_table(hash_table_t *result, char *word);

#endif
