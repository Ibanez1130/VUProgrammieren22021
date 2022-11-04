#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "rehash_inc.h"

// #include "duma.h"

void hash_resize(hash_t *hash, long newsize)
{
    hash_t new_hash;
    hash_init(&new_hash, newsize);
    for (int i = 0; i < hash->hashsize; i++) {
        collision_list_t *element = hash->hasharray[i];
        while (element != 0) {
            hash_insert(&new_hash, &(element->data));
            element = element->next;
        }
    }
    hash_free(hash);
    *hash = new_hash;
	return;
}

int main()
{
    data_t *data = 0;
    long count, i;

    char *tmp = "Willkommen bei der Klausur zu Prog2";
    tmp = "A wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring";
    // Weitere Testfaelle
    //tmp="A wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring which I enjoy with my whole heart. I am alone, and feel the charm of existence in this spot, which was created for the bliss of souls like mine. I am so happy, my dear friend, so absorbed in the exquisite sense of mere tranquil existence, that I neglect my talents. I should be incapable of drawing a single stroke at the present moment; and yet I feel that I never was a greater artist than now. When, while the lovely";
    //tmp="A B C D E F G H I J K L";

    init_data(&data, &count, tmp);

    hash_t hash;
    hash_init(&hash, 5);
    for (i = 0; i < count; i++)
    {
        collision_list_t *el = hash_find(&hash, &data[i]);

        if (el)
            el->data.count++;
        else
            hash_insert(&hash, &data[i]);
    }
    hash_print(&hash);
    hash_resize(&hash, 13);
    hash_print(&hash);
    hash_free(&hash);

    free_data(&data);
}
