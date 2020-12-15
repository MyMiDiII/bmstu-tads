#ifndef __TREES_H__

#define __TREES_H__

#include <stdio.h>

typedef struct node node_t;

struct node
{
    int height;
    node_t *left;
    node_t *right;
    char *value;
};

int create_binary_tree(FILE *file, node_t **result);

void node_init(node_t *node, const int height, node_t *left, node_t *right, char *word);

int add_node_to_bintree(node_t **result, char *word);

int find_and_add(node_t *root, char *word);

void print_tree(node_t *root, int place);

int create_balanced_tree(node_t *tree, node_t **balanced_tree);

int add_node_to_balansed_tree(node_t **tree, char *word);
#endif
