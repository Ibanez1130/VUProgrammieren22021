#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dynamic_stack_iue.h"

#define DEBUG

void push_stack(stack_t *stack, long element)
{
    if (stack == 0) {
        return;
    }
    if (stack->size == stack->capacity) {
        if (stack->capacity * 2 > MAX_CAPACITY) {
            #ifdef DEBUG
            fprintf(stderr, "Die maximale Größe des Stacks wurde erreicht.\n");
            #endif
            return;
        }
        long *tmp = realloc(stack->stack, stack->capacity * 2 * sizeof(long));
        if (tmp == 0) {
            #ifdef DEBUG
            fprintf(stderr, "Der Speicher konnte nicht realloziert werden.\n");
            #endif
            return;
        }
        stack->capacity *= 2;
        stack->stack = tmp;
    }
    stack->stack[stack->size] = element;
    stack->size++;
    return;
}

long pop_stack(stack_t *stack)
{
    if (stack == 0) {
        #ifdef DEBUG
        fprintf(stderr, "Der Stack ist nicht definiert!\n");
        #endif
        return 0;
    }
    if (stack->size == 0) {
        #ifdef DEBUG
        fprintf(stderr, "Der Stack ist leer.\n");
        #endif
        return 0;
    }
    long element = stack->stack[stack->size - 1];
    stack->size--;
    if (stack->capacity > 0 && stack->size > 0 && stack->capacity / stack->size > 2) {
        if (stack->capacity / 2 < MIN_CAPACITY) {
            #ifdef DEBUG
            fprintf(stderr, "Der Stack kann nicht verkleinert werden.\n");
            #endif
        } else {
            #ifdef DEBUG
            fprintf(stderr, "Der Stack ist nur noch zur Hälfte gefüllt und wird daher halbiert!\n");
            #endif
            long *tmp = realloc(stack->stack, stack->capacity / 2 * sizeof(long));
            if (tmp == 0) {
                #ifdef DEBUG
                fprintf(stderr, "Der Speicher konnte nicht realloziert werden.\n");
                #endif
                return 0;
            }
            stack->capacity /= 2;
            stack->stack = tmp;
        }
    }
    return element;
}

int main()
{
    stack_t stack;
    
    initialise_stack(&stack);

    long nums = MAX_CAPACITY + 5;  
    for(long i = 0; i < nums; i++)			// add a lot of elements
    {
        push_stack(&stack, i);
    }
    
    assert(stack.capacity == MAX_CAPACITY); 		// maximum was reached!
    delete_stack(&stack);				// free memory
    
    initialise_stack(&stack);
    
    push_stack(&stack, 42);				// add one element
    assert(42 == pop_stack(&stack) && stack.size == 0); // should be received

    for(long i = 0; i < 10; i++)			// add 10 elements
    {
        push_stack(&stack, i);
    }  
    for(long i = 9; i >= 0; i--)			// and pop them back
    {
        assert(pop_stack(&stack) == i);		
    }
    pop_stack(&stack);						
    delete_stack(&stack);
}
