#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "tree_balance_inc.h"


void balance_insert(tree_c **ptree, tree_c **feld, long a, long b)
{
    long pivot = (a + b) / 2;
    printf("pivot: %li | a: %li | b: %li\n", pivot, a, b);
    printf("%s\n", feld[pivot]->data.word);
    // Schöner gestalten -> Abfrage, ob wir weiter machen noch bevor wir Rekursion aufrufen!
    // RICHTIG AUF DATA ZUGREIFEN!!!
    if (a < 0 || b < 0) {
        return;
    } else if (a == b) {
        tree_insert(ptree, &(feld[pivot]->data));
    } else {
        tree_insert(ptree, &(feld[pivot]->data));
        balance_insert(ptree, feld, a, pivot - 1);
        balance_insert(ptree, feld, pivot + 1, b);
    }
	return;
}

void tree_balance(tree_c **ptree)
{
    if (*ptree == 0) {
        return;
    }
    tree_c *new_tree = 0;
    long tree_size = 0;
    tree_c **sorted_array = tree2feld(*ptree, &tree_size);
    balance_insert(&new_tree, sorted_array, 0, tree_size - 1);
    free(*ptree);
    *ptree = new_tree;
	return;
}

int main()
{
    data_c *data = 0;
    long count, i;
    tree_c *tree = NULL;
    data_c *ptr;

    char *tmp = "Willkommen bei der Klausur zu Prog2";
    // Weitere Testfaelle
    //tmp="A wonderful serenity has taken possession of my entire soul, like these sweet mornings of spring which I enjoy with my whole heart. I am alone, and feel the charm of existence in this spot, which was created for the bliss of souls like mine. I am so happy, my dear friend, so absorbed in the exquisite sense of mere tranquil existence, that I neglect my talents. I should be incapable of drawing a single stroke at the present moment; and yet I feel that I never was a greater artist than now. When, while the lovely";
    tmp = "A B C D E F G H I J K L";

    init_data(&data, &count, tmp);

    for (i = 0; i < count; i++)
    {
        if ((ptr = tree_search(&tree, &data[i])))
            ptr->count++;
        else
            tree_insert(&tree, &data[i]);
    }
    printf("\n");
    tree_print(&tree);

    tree_balance(&tree);

    printf("\n");
    tree_print(&tree);
    tree_free(&tree);

    free_data(&data);
}
