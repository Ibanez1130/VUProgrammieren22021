#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char word[255];
    long count;
} data_t;

typedef struct
{
    data_t *data;
    long nextfree, size;
} heap_t;

int bigger(char *str1, char *str2);
void heap_init(heap_t *heap, long size);
void heap_free(heap_t *heap);
void heap_print(heap_t *heap);
void heap_up(heap_t *heap, long i);
long heap_insert(heap_t *heap, data_t *data);
void init_data(data_t **pdata, long *count, char *tmp);
void free_data(data_t **data);

