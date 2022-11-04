#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "ring_read_inc.h"

#include "duma.h"

long ring_read (ring_t *ring, data_t *data) {
    if (ring->fill <= 0) {
        return -1;
    }
    {
        // Auslesen des aktuellen Elements
        data_t *read_element = &(ring->buffer[ring->rd]);
        strcpy(data->word, read_element->word);
        ring->rd = (ring->rd + 1) % ring->size;
        ring->fill--;
    }
    return 0;
}

int main()
{
#if 0 // Simple tests
    ring_t ring;
    data_t dat;
    long status;

    data_t tmp[] = {{"Hallo"}, {"Welt"}};

    ring_init(&ring, 10);

    ring_write(&ring, &tmp[0]);
    ring_write(&ring, &tmp[1]);
    ring_print(&ring);

    status = ring_read(&ring, &dat);
    if (status == 0) printf("read: %s\n", dat.word);
    ring_print(&ring);

    status = ring_read(&ring, &dat);
    if (status == 0) printf("read: %s\n", dat.word);
    ring_print(&ring);

    status = ring_read(&ring, &dat);
    if (status == 0) printf("read: %s\n", dat.word);
    ring_print(&ring);

    ring_free(&ring);

#else // Additional tests

    ring_t ring;
    data_t *data, *p, dat;
    char *tmp = "Willkommen bei der Klausur zu Prog2. Hier kommen noch ein paar weitere Worte";
    long count = 0, i, status;

    init_data(&data, &count, tmp);
    ring_init(&ring, 10);

    printf("\n");
    p = data;
    printf("Write elements.\n");
    while (p->word[0])
    {
        printf("write: %s\n", p->word);
        status = ring_write(&ring, p);
        if (status != 0)
        {
            fprintf(stderr, "Can only write up to %ld elements\n", ring.size);
            break;
        }
        p++;
    }
    ring_print(&ring);

    printf("\n");
    printf("Read 6 elements.\n");
    i = 0;
    while ((i < 6) && ((status = ring_read(&ring, &dat)) == 0))
    {
        printf("read: %s\n", dat.word);
        i++;
    }
    ring_print(&ring);

    printf("\n");
    printf("Write elements.\n");
    while (p->word[0])
    {
        printf("write: %s\n", p->word);
        status = ring_write(&ring, p);
        if (status != 0)
        {
            fprintf(stderr, "Can only write up to %ld elements\n", ring.size);
            break;
        }
        p++;
    }
    ring_print(&ring);

    printf("\n");
    i = 0;
    while (((status = ring_read(&ring, &dat)) == 0) && i < 50)
    {
        printf("read: %s\n", dat.word);
        i++;
    }
    ring_print(&ring);
    free_data(&data);

    ring_free(&ring);
#endif // Additional tests
}
