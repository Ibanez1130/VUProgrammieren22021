#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "list_count_inc.h"

void list_count(list_t **plist)
{
    list_t *element = *plist;
    while (element != 0) {
        list_t *search_element = *plist;
        while (search_element != 0) {
            if (strcmp(search_element->data.word, element->data.word) == 0) {
                if (element != search_element) {
                    element->data.count++;
                    search_element->prev->next = search_element->next;
                    if (search_element->next != 0) {
                        search_element->next->prev = search_element->prev;   
                    }
                    free(search_element);
                }
            }
            search_element = search_element->next;
        }
        element = element->next;
    }
    return;
}

int main()
{
    data_t *data = 0, item;
    long i, count, stat;
    list_t *list = NULL;

    // char *tmp = "Programmieren ist prima ; es ist deshalb prima , weil es einfach prima ist .";
    char *tmp = "The wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring which I enjoy with my whole heart. I am alone, and feel the charm of existence in this spot, which was created for the bliss of souls like mine.";
    // Ein weiterer Testfall
    // tmp="The wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring which I enjoy with my whole heart. I am alone, and feel the charm of existence in this spot, which was created for the bliss of souls like mine.";

    init_data(&data, &count, tmp);

    for (i=0; i<count; i++)
    {
        item=data[i];
        item.count=1;
        stat = list_push(&list, &item);
        if (stat == -1)
            break;
    }

    // we should have: .:1 ist:1 prima:1 einfach:1 es:1 weil:1 ,:1 prima:1 deshalb:1 ist:1 es:1 ;:1 prima:1 ist:1 Programmieren:1
    // we should have: mine.:1 like:1 souls:1 of:1 bliss:1 the:1 for:1 created:1 was:1 which:1 spot,:1 this:1 in:1 existence:1
    list_print(&list);

    list_count(&list);

    // we should have: .:1 ist:3 prima:3 einfach:1 es:" weil:1 ,:! deshalb:1 ; Programmieren:1
    // we should have: mine.:1 like:2 souls:1 of:4 bliss:1 the:3 for:1 created:1 was:1 which:2 spot,:1 this:1 in:1 existence:1
    list_print(&list);

    list_free(&list);

    free_data(&data);
}
