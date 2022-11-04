#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "rehash_inc.h"

unsigned long hash_func(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void hash_init(hash_t *hash, long size)
{
    hash->hasharray = calloc(size, sizeof(collision_list_t *));
    if (hash->hasharray == 0)
        exit(-1);
    hash->hashsize = size;
}
void hash_free(hash_t *hash)
{
    collision_list_t *el;
    long i;
    for (i = 0; i < hash->hashsize; i++)
    {
        el = hash->hasharray[i];
        while (el)
        {
            hash->hasharray[i] = el->next;
            free(el);
            el = hash->hasharray[i];
        }
    }
    free(hash->hasharray);
    hash->hasharray = 0;
    hash->hashsize = 0;
}

void hash_print(hash_t *hash)
{
    long i;
    collision_list_t *el;
    printf("\n");
    for (i = 0; i < hash->hashsize; i++)
    {
        if (hash->hasharray[i] == 0)
            continue;
        printf("%ld: ", i);
        el = hash->hasharray[i];
        while (el)
        {
            printf("%s: %ld  ", el->data.word, el->data.count);
            el = el->next;
        }
        printf("\n");
    }
}

void hash_insert(hash_t *hash, data_t *data)
{
    unsigned long idx = hash_func(data->word) % hash->hashsize;
    collision_list_t *el;

    el = hash->hasharray[idx];
    while (el)
    {
        if (strcmp(el->data.word, data->word) == 0)
            break;
        el = el->next;
    }
    if (el)
    {
        el->data = *data;
        return;
    }

    el = malloc(sizeof(collision_list_t));
    if (el == 0)
        exit(-1);

    el->data = *data;
    el->next = hash->hasharray[idx];
    hash->hasharray[idx] = el;
}
collision_list_t *hash_find(hash_t *hash, data_t *data)
{
    unsigned long idx = hash_func(data->word) % hash->hashsize;
    collision_list_t *el;

    el = hash->hasharray[idx];
    while (el)
    {
        if (strcmp(el->data.word, data->word) == 0)
            return el;
        el = el->next;
    }
    return el;
}

void init_data(data_t **pdata, long *count, char *tmp)
{
    data_t *data;
    char *p, *q, *a, *b;
    long n = 0, len;
    data = 0;
    p = tmp;

    while (*p)
    {
        if ((q = strchr(p, ' ')) || (q = strchr(p, '\0')))
        {
            len = q - p - 1;
            data = realloc(data, (n + 1) * sizeof(data_t));
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
    data = realloc(data, (n + 1) * sizeof(data_t));
    if (data == 0)
        exit(-1);
    data[n].word[0] = '\0';
    data[n].count = 1;
    *pdata = data;

    *count = n;
}

void free_data(data_t **data)
{
    free(*data);
    *data = 0;
}
