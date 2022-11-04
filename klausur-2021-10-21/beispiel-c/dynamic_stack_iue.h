#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#define MAX_CAPACITY 64
#define MIN_CAPACITY 4

typedef struct stack_s
{
    long *stack;
    long size; // Aktueller Fuellstand
    long capacity; // Gesamtkapazitaet
} stack_t;

void initialise_stack(stack_t *);
void delete_stack(stack_t *);
void push_stack(stack_t *, long);
long pop_stack(stack_t *);

#endif //DYNAMIC_STACK_H
