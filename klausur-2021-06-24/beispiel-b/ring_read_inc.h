#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char word[255];
} data_t;

typedef struct
{
    data_t *buffer;
    long size, fill, rd, wr;
} ring_t;

void ring_init(ring_t *ring, long sz);
long ring_write(ring_t *ring, data_t *data);
void ring_print(ring_t *ring);
void ring_free(ring_t *ring);
void init_data(data_t **pdata, long *count, char *tmp);
void free_data(data_t **data);

