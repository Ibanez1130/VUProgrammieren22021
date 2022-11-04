#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char word[255];
} data_t;

struct list_s
{
    data_t data;
    struct list_s *next, *prev;
};
typedef struct list_s list_t;

long list_push(list_t **plist, data_t *pdata);
void list_print(list_t **plist);
void list_free(list_t **plist);
void init_data(data_t **pdata, long *count, char *tmp);
void free_data(data_t **data);
