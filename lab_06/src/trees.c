#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trees.h"
#include "io.h"
#include "err.h"

#define MAX(a, b) ((a < b) ? b : a)

extern int node_number;
extern bool word_in;
extern int comparisons;
extern int balance_comparisons;

int create_binary_tree(FILE *file, node_t **result)
{
    int exit_code = OK;
    char *word;

    while (!exit_code && !read_string(&word, file))
        exit_code = add_node_to_bintree(result, word); 

    if (!feof(file))
    {
        //free_tree();
        return ERR_MEMORY;
    }

    fseek(file, 0L, SEEK_SET);
    return OK;
}

void print_tree(node_t *root, int place)
{
    int add_space = 15;

    if (root)
    {
        place += add_space;

        print_tree(root->right, place);
        puts("");

        for (int i = add_space; i < place; i++)
            printf(" ");

        printf("{ %d %s }\n", root->height, root->value);

        print_tree(root->left, place);
    }
}

int height(node_t *root)
{
    return root ? root->height : -1;
}

void renew_height(node_t *node)
{
	node->height = MAX(height(node->left), height(node->right)) + 1;
}

void node_init(node_t *node, const int height, node_t *left, node_t *right, char *word)
{
    node->height = height;
    node->left = left;
    node->right = right;
    node->value = word;
}

int add_node(node_t **result, char *word)
{
    *result = malloc(sizeof(node_t));

    if (!*result)
        return ERR_MEMORY;

    node_init(*result, 0, NULL, NULL, word);

    return OK;
}

int add_node_to_bintree(node_t **result, char *word)
{
    int exit_code = OK;

    if (!*result)
    {
        exit_code = add_node(result, word);
        node_number++;
        return exit_code;   
    }

    int compare_result = strcmp(word, (*result)->value);
    comparisons++;
    
    if (compare_result < 0)
        exit_code = add_node_to_bintree(&(*result)->left, word);
    else if (compare_result > 0)
        exit_code = add_node_to_bintree(&(*result)->right, word);
    else
        word_in = true;

    renew_height(*result);

    return exit_code;
}
 
int copy_tree(node_t *from, node_t **to)
{
    if (!from)
    {
        *to = NULL;
        return OK;
    }

    int exit_code = OK;

    exit_code = add_node(to, from->value);

    if (!exit_code)
       (*to)->height = from->height;

    if (!exit_code)
        exit_code = copy_tree(from->left, &(*to)->left);

    if (!exit_code)
        exit_code = copy_tree(from->right, &(*to)->right);

    return exit_code;
}

node_t *rotate_right(node_t *node) 
{
	node_t *tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	renew_height(node);
	renew_height(tmp);
	return tmp;
}

node_t *rotate_left(node_t *node) 
{
	node_t *tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	renew_height(node);
	renew_height(tmp);
	return tmp;
}

int balance_factor(node_t *node)
{
	return height(node->right) - height(node->left);
}

node_t *balance_node(node_t* node)
{
	renew_height(node);

	if (balance_factor(node) >= 2)
	{
		if (balance_factor(node->right) < 0)
			node->right = rotate_right(node->right);
		return rotate_left(node);
	}

	if (balance_factor(node) <= -2)
	{
		if (balance_factor(node->left) > 0)
			node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	renew_height(node);
	return node;
}

void balance_tree(node_t **tree)
{
    if (!*tree)
        return;
    
    *tree = balance_node(*tree);
    balance_tree(&(*tree)->left);
    balance_tree(&(*tree)->right);
    //*tree = balance_node(*tree);
} 

int create_balanced_tree(node_t *tree, node_t **balanced_tree)
{
    int exit_code = OK;
    exit_code = copy_tree(tree, balanced_tree);

    balance_tree(balanced_tree);

    return exit_code;
}

int add_node_to_balansed_tree(node_t **tree, char *word)
{
    int exit_code = OK;

    if (!*tree)
    {
        exit_code = add_node(tree, word);
        return exit_code;   
    }

    int compare_result = strcmp(word, (*tree)->value);
    balance_comparisons++;
    
    if (compare_result < 0)
        exit_code = add_node_to_balansed_tree(&(*tree)->left, word);
    else if (compare_result > 0)
        exit_code = add_node_to_balansed_tree(&(*tree)->right, word);

    if (!exit_code)
        balance_tree(tree);

    return exit_code;
}
