#include "dynamic_stack_iue.h"
#include <stdio.h>
#include <stdlib.h>

void initialise_stack(stack_t *stack)
{
    stack->stack = malloc(MIN_CAPACITY * sizeof(long));
    stack->size = 0;
    stack->capacity = MIN_CAPACITY;
    if (stack->stack==NULL)
    {
	fprintf(stderr,"ERROR: Kein Speicher für den Stack!\n");
	stack->capacity = 0;
    }
}

void delete_stack(stack_t *stack)
{
    if(stack->stack) 
    {
        free(stack->stack);
        stack->stack = 0;
        stack->capacity = 0;
        stack->size = 0;
    } 
    else 
    {
        printf("ERROR: Stack schon leer!\n");
    }
}
