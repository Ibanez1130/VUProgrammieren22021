#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "list_maxsort_inc.h"

long list_push(list_t **plist, data_t *pdata)
{
    list_t *list = *plist;
    list_t *tmp = malloc(sizeof(list_t));
    if (tmp == 0)
        return -1;
    tmp->data = *pdata;
    tmp->next = list;
    tmp->prev = 0;
    if (list) (list)->prev = tmp;
    *plist = tmp;
    return 0;
}

void list_print(list_t **plist)
{
    list_t *p = *plist;

    printf("\n");
    while (p)
    {
        printf("%s\n", p->data.word);
        p = p->next;
    }
}

void list_free(list_t **plist)
{
    list_t *q, *p = *plist;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    *plist = 0;
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
