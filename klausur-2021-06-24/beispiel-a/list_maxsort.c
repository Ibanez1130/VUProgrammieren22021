#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "list_maxsort_inc.h"

void list_sort(list_t **plist)
{
    list_t *sorted_element = 0;
    list_t *first = 0;
    while (*plist != 0) {
        list_t *element = *plist;
        list_t *biggest = *plist;
        while (element != 0) {
            if (strcmp(element->data.word, biggest->data.word) > 0) {
                biggest = element;
            }
            element = element->next;
        }
        if (biggest->prev != 0) {
            biggest->prev->next = biggest->next;
        } else {
            *plist = biggest->next;
        }
        if (biggest->next != 0) {
            biggest->next->prev = biggest->prev;
        }
        {
            if (first == 0) {
                first = biggest;
            }
            if (sorted_element == 0) {
                sorted_element = biggest;
            } else {
                sorted_element->next = biggest;
                biggest->prev = sorted_element;
                sorted_element = sorted_element->next;
            }
        }
    }
    *plist = first;
    return;
}

int main()
{
    data_t *data = 0, *p;
    long count, stat;

    char *tmp = "A wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring.";
    // Ein weiterer Testfall
    //tmp="A wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring which I enjoy with my whole heart. I am alone, and feel the charm of existence in this spot, which was created for the bliss of souls like mine. I am so happy, my dear friend, so absorbed in the exquisite sense of mere tranquil existence, that I neglect my talents. I should be incapable of drawing a single stroke at the present moment; and yet I feel that I never was a greater artist than now. When, while the lovely";

    init_data(&data, &count, tmp);

    list_t *list = NULL;
    p = data;
    while (p->word[0])
    {
        stat = list_push(&list, p);
        if (stat == -1)
            break;
        p++;
    }
    list_print(&list);

    list_sort(&list);
    list_print(&list);

    list_free(&list);

    free_data(&data);
}
