#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "heapsort_inc.h"

void heap_init(heap_t *heap, long size)
{
    heap->data = malloc((size + 1) * sizeof(data_t));
    if (heap->data == 0)
        exit(-1);
    heap->nextfree = 1;
    heap->size = size + 1;
}
void heap_free(heap_t *heap)
{
    free(heap->data);
    heap->data = 0;
    heap->nextfree = 0;
    heap->size = 0;
}

void heap_print(heap_t *heap)
{
    long i = 1, start = 1, end = 2;

    printf("\n");
    while (i < heap->nextfree)
    {
        for (i = start; (i < end) && (i < heap->nextfree) && (i < heap->size); i++)
        {
            printf("%s ", heap->data[i].word);
        }
        printf("\n");
        start *= 2;
        end *= 2;
    }
}

int bigger(char *str1, char *str2)
{
	if ((strlen(str1) > strlen(str2)) ||
	   ((strlen(str1) == strlen(str2)) &&
	    (strcmp(str1,str2)>0))
	   )
        {
		return 1;
	}
	else
	{
		return 0;
	}
}

void heap_up(heap_t *heap, long i)
{
    while (i > 1)
    {
        if (bigger(heap->data[i / 2].word,heap->data[i].word))
        {
            data_t h = heap->data[i / 2];
            heap->data[i / 2] = heap->data[i];
            heap->data[i] = h;
            i = i / 2;
        }
        else
            break;
    }
    return;
}

long heap_insert(heap_t *heap, data_t *data)
{
    if (heap->nextfree >= heap->size)
        return -1;
    heap->data[heap->nextfree] = *data;
    heap_up(heap, heap->nextfree);
    heap->nextfree++;

    return 0;
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
