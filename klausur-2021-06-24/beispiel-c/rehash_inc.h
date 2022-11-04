#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char word[255];
    long count;
} data_t;

struct collision_list_s
{
    data_t data;
    struct collision_list_s *next;
};
typedef struct collision_list_s collision_list_t;

typedef struct
{
    collision_list_t **hasharray;
    long hashsize;
} hash_t;

void hash_init(hash_t *hash, long size);
void hash_free(hash_t *hash);
void hash_print(hash_t *hash);
void hash_insert(hash_t *hash, data_t *data);
collision_list_t *hash_find(hash_t *hash, data_t *data);
void init_data(data_t **pdata, long *count, char *tmp);
void free_data(data_t **data);
