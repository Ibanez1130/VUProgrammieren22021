#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char word[255];
    long count;
} data_c;

struct tree_s
{
    data_c data;
    struct tree_s *left, *right;
};
typedef struct tree_s tree_c;

long tree_size(tree_c *tree);
tree_c **tree2feld(tree_c *tree, long *size);
void tree_insert(tree_c **ptree, data_c *data);
data_c *tree_search(tree_c **ptree, data_c *data);
void tree_print(tree_c **ptree);
void tree_free(tree_c **ptree);
void init_data(data_c **pdata, long *count, char *tmp);
void free_data(data_c **data);

