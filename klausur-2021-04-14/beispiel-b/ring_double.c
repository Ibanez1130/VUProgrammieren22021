#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "ring_double_inc.h"

long ring_double(ring_t *ring)
{
    if (ring == 0) {
        return 0;
    }
    data_t *new_buffer = realloc(ring->buffer, 2 * ring->size * sizeof(data_t));
    if (new_buffer == 0) {
        printf("Der Speicher konnte nicht neu alloziert werden!\n");
        return 0;
    } else {
        {
            if (ring->wr <= ring->rd) {
                for (int i = 0; i < ring->wr; i++) {
                    new_buffer[(ring->size + i) % (ring->size * 2)] = new_buffer[i];
                }
                ring->wr = (ring->rd + ring->fill) % (ring->size * 2);
            }
            ring->buffer = new_buffer;
            ring->size *= 2;
        }
    }
	return ring->size;
}

int main()
{
    ring_t ring;
    data_t *data, dat;
    char *tmp = "Willkommen bei der Klausur zu Prog2. Hier kommen noch ein paar weitere Worte zum Eintragen.";
    long count = 0, status;

    init_data(&data, &count, tmp);
    ring_init(&ring, 5);

    printf("\n");
    printf("Write elements.\n");

    status  = ring_write(&ring, &data[0]);
    status |= ring_write(&ring, &data[1]);
    status |= ring_write(&ring, &data[2]);
    status |= ring_write(&ring, &data[3]);
    status |= ring_write(&ring, &data[4]);
    if (status) printf("Error in write.\n");

    // Now we should print: willkommen bei der klausur zu
    ring_print(&ring);

    printf("\n");
    printf("Read elements.\n");
    status |= ring_read(&ring, &dat);
    status |= ring_read(&ring, &dat);
    status |= ring_read(&ring, &dat);
    if (status) printf("Error in read.\n");

    // Now we should print: klausur zu
    ring_print(&ring);

    printf("\nWrite elements.\n");
    status |= ring_write(&ring, &data[5]);
    status |= ring_write(&ring, &data[6]);
    status |= ring_write(&ring, &data[7]);
    if (status) printf("Error in write.\n");

    // Now we should print: klausur zu prog2. hier kommen
    ring_print(&ring);

    printf("\nWrite additional element.\n");
    status |= ring_write(&ring, &data[8]);
    if (status) printf("Error in write.\n");
    status=0;

    // Now we should print: klausur zu prog2. hier kommen
    printf("\nBefore resize:\n");
    ring_print(&ring);

    printf("\nDouble size\n");
    // RING DOUBLE
    ring_double(&ring);

    // Now we should also print: klausur zu prog2. hier kommen
    printf("\nAfter resize:\n");
    ring_print(&ring);

    printf("\nNow we add some elements:\n");
    status |= ring_write(&ring, &data[8]);
    status |= ring_write(&ring, &data[9]);
    status |= ring_write(&ring, &data[10]);
    if (status) printf("Error in write, but we should have double the size here.\n");

    // Now we have: klausur zu prog2. hier kommen noch ein paar
    ring_print(&ring);
    free_data(&data);

    ring_free(&ring);
}
