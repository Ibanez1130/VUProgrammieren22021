#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tree_balance_inc.h"

long tree_size(tree_c *tree);
void tree2feld_runner(tree_c *tree, tree_c **feld, long *idx);

tree_c **tree2feld(tree_c *tree, long *psize)
{
    long idx = 0;
    tree_c **feld;
    *psize = tree_size(tree);
    feld = malloc(*psize * sizeof(tree_c *));
    if (feld == 0)
        exit(-1);
    tree2feld_runner(tree, feld, &idx);
    return feld;
}

void tree_insert(tree_c **ptree, data_c *data)
{
    tree_c *tree = *ptree;
    if (*ptree == 0)
    {
        tree_c *tmp = malloc(sizeof(tree_c));
        if (tmp == 0)
            exit(-1);
        tmp->left = tmp->right = 0;
        tmp->data = *data;
        *ptree = tmp;
        return;
    }

    if (strcmp(data->word, tree->data.word) < 0)
        tree_insert(&tree->left, data);
    else
        tree_insert(&tree->right, data);
}

long tree_size(tree_c *tree)
{
    long ct = 0;
    if (tree)
        ct = 1;
    if (tree->left) ct += tree_size(tree->left);
    if (tree->right) ct += tree_size(tree->right);
    return ct;
}

void tree2feld_runner(tree_c *tree, tree_c **feld, long *idx)
{
    if (!tree) return;
    tree2feld_runner(tree->left, feld, idx);
    feld[*idx] = tree;
    (*idx)++;
    tree2feld_runner(tree->right, feld, idx);
}

data_c *tree_search(tree_c **ptree, data_c *data)
{
    tree_c *tree = *ptree;

    if (!*ptree)
        return NULL;
    if (strcmp(data->word, tree->data.word) == 0)
        return &tree->data;

    if (strcmp(data->word, tree->data.word) < 0)
        return tree_search(&tree->left, data);
    else
        return tree_search(&tree->right, data);
}

void tree_print(tree_c **ptree)
{
    static long blanks = 0;
    if (!*ptree)
        return;

    blanks += 4;
    if ((*ptree)->right)
        tree_print(&(*ptree)->right);
    blanks -= 4;

    for (long i = 0; i < blanks; i++) printf(" ");
    printf("%s: %ld\n", (*ptree)->data.word, (*ptree)->data.count);

    blanks += 4;
    if ((*ptree)->left)
        tree_print(&(*ptree)->left);
    blanks -= 4;
}

void tree_free(tree_c **ptree)
{
    if (!*ptree)
        return;

    if ((*ptree)->left)
        tree_free(&(*ptree)->left);
    if ((*ptree)->right)
        tree_free(&(*ptree)->right);
    free(*ptree);
}

void init_data(data_c **pdata, long *count, char *tmp)
{
    data_c *data;
    char *p, *q, *a, *b;
    long n = 0, len;
    data = 0;
    p = tmp;

    while (*p)
    {
        if ((q = strchr(p, ' ')) || (q = strchr(p, '\0')))
        {
            len = q - p - 1;
            data = realloc(data, (n + 1) * sizeof(data_c));
            if (data == 0)
                exit(-1);
            a = p;
            b = data[n].word;
            while (a != q) *b++ = tolower(*a++);
            data[n].word[len + 1] = '\0';
            data[n].count = 1;
            n++;
            p = q;
            while (*p == ' ')
                p++;
            continue;
        }
    }
    data = realloc(data, (n + 1) * sizeof(data_c));
    if (data == 0)
        exit(-1);
    data[n].word[0] = '\0';
    data[n].count = 1;
    *pdata = data;

    *count = n;
}

void free_data(data_c **data)
{
    free(*data);
    *data = 0;
}
