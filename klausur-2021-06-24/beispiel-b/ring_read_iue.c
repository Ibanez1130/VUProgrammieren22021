#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "ring_read_inc.h"

void ring_init(ring_t *ring, long sz)
{
    ring->buffer = malloc(sizeof(data_t) * sz);
    if (ring->buffer == 0)
        exit(-1);
    ring->size = sz;
    ring->fill = 0;
    ring->rd = 0;
    ring->wr = 0;
}

long ring_write(ring_t *ring, data_t *data)
{
    if (ring->fill == ring->size)
        return -1;
    ring->buffer[ring->wr] = *data;
    ring->wr = (ring->wr + 1) % ring->size;
    ring->fill++;
    return 0;
}

void ring_print(ring_t *ring)
{
    long i, j;
    printf("\n");
    for (i = 0; i < ring->fill; i++)
    {
        j = (ring->rd + i) % ring->size;
        printf("print: %s\n", ring->buffer[j].word);
    }
}

void ring_free(ring_t *ring)
{
    free(ring->buffer);
    ring->buffer = 0;
    ring->size = ring->fill = ring->rd = ring->wr = 0;
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
    *pdata = data;

    *count = n;
}

void free_data(data_t **data)
{
    free(*data);
    *data = 0;
}
