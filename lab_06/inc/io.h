#ifndef __IO_H__

#define __IO_H__

#include <stdbool.h>
#include <stdio.h>
#include "err.h"
#include "trees.h"
#include "hash.h"

#define ARGS_NUM 2

int parse_args(const int argc, char **argv, char **filename);

int open_file(FILE **file, const char *const filename, bool *const is_open);

int read_string(char **string, FILE *file);

int read_int(int *const integer);

int read_size(int *const size);

int read_comp(int *const size);

int read_answer(bool *const integer);

int add_word(node_t **tree, node_t **balanced_tree,
             hash_table_t *table, FILE *file);

int add_while_not_in(node_t **tree, node_t **balanced_tree,
                     hash_table_t *table, FILE *file);

#endif
