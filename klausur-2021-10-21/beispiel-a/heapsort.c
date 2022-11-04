#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "heapsort_inc.h"

void heap_down(heap_t *heap, long i)
{
    if (heap == 0) {
        return;
    }
    long smallest = i;
    long left = 2 * i;
    long right = 2 * i + 1;
    if (left >= heap->nextfree || right >= heap->nextfree) {
        return;
    }
    if (bigger(heap->data[smallest].word, heap->data[left].word) || bigger(heap->data[smallest].word, heap->data[right].word)) {
        if (bigger(heap->data[left].word, heap->data[right].word)) {
            smallest = right;
        }
        if (bigger(heap->data[right].word, heap->data[left].word)) {
            smallest = left;
        }
    }
    if (smallest != i) {
        data_t tmp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = tmp;
        heap_down(heap, smallest);
    }
}

void heap_sort(heap_t *heap, data_t *sorted)
{
    if (heap == 0 || sorted == 0) {
        return;
    }
    {
        for (int i = 0; heap->nextfree > 1; i++) {
            sorted[i] = heap->data[1];
            heap->data[1] = heap->data[heap->nextfree - 1];
            heap->nextfree--;
            heap_down(heap, 1);
        }
    }
    return;
}

int main()
{
    data_t *data = 0, *sorted;
    long count, i;

    char *tmp = "Willkommen bei der Klausur zu Prog2";
    // Ein weiterer Testfall, soll natuerlich auch funktionieren
    //tmp="a wonderful serenity has taken possession of my entire soul like these sweet mornings spring which I enjoy with whole heart am alone and feel the charm existence in this spot was created for bliss souls mine so happy dear friend absorbed exquisite sense mere tranquil that neglect talents should be incapable drawing single stroke at present moment yet never greater artist than now When while lovely";

    init_data(&data, &count, tmp);

    heap_t heap;
    heap_init(&heap, 100);

    for (i = 0; i < count; i++)
    {
        heap_insert(&heap, &data[i]);
    }
    heap_print(&heap);

    sorted = calloc(count,sizeof(data_t));
    if (sorted == 0)
        exit(-1);
    heap_sort(&heap, sorted);
    heap_print(&heap);
    for (i = 0; i < count; i++)
    {
        printf("%s\n", sorted[i].word);
    }
    heap_free(&heap);
    if (sorted)
        free(sorted);

    free_data(&data);
}
