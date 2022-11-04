#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "list_count_inc.h"

// #include "duma.h"

void list_count(list_t **plist)
{
    list_t *element_i = *plist;
    while (element_i != 0) {
        list_t *element_j = *plist;
        while (element_j != 0) {
            if (element_i != element_j && strcmp(element_i->data.word, element_j->data.word) == 0) {
                element_i->data.count++;
                {
                    element_j->prev->next = element_j->next;
                    if (element_j->next != 0) {
                        element_j->next->prev = element_j->prev;
                    }
                    free(element_j);
                }
            }
            element_j = element_j->next;
        }
        element_i = element_i->next;
    }
	return;
}

int main()
{
    data_t *data = 0, item;
    long i, count, stat;
    list_t *list = NULL;

    char *tmp = "Willkommen bei der Klausur zu Prog2";
    // Ein weiterer Testfall
    tmp="The wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring which I enjoy with my whole heart. I am alone, and feel the charm of existence in this spot, which was created for the bliss of souls like mine.";

    init_data(&data, &count, tmp);

    for (i=0; i<count; i++)
    {
        item=data[i];
	item.count=1;
        stat = list_push(&list, &item);
        if (stat == -1)
            break;
    }

    // we should have: mine.:1 like:1 souls:1 of:1 bliss:1 the:1 for:1 created:1 was:1 which:1 spot,:1 this:1 in:1 existence:1
    list_print(&list);

    list_count(&list);

    // we should have: mine.:1 like:2 souls:1 of:4 bliss:1 the:3 for:1 created:1 was:1 which:2 spot,:1 this:1 in:1 existence:1
    list_print(&list);

    list_free(&list);

    free_data(&data);
}
