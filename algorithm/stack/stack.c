#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define  MIN_STACK_SIZE  5

struct stack_record {
    int capacity;
    int top_of_stack;
    element_type *array;
};

stack create_stack(int max_elements)
{
    stack s;
    if(max_elements < MIN_STACK_SIZE)
    {
        printf("Stack size is too small\n");
        exit(0);
    }

    s = malloc(sizeof(struct stack_record));
    if(s == NULL)
    {
        printf("Out of sapce\n");
        exit(1);
    }

    s->array = malloc(sizeof(element_type) * max_elements);
    if(s->array == NULL)
    {
        printf("Out of space\n");
        exit(1);
    }

    s->capacity = max_elements;
    make_empty(s);

    return s;
}

void dispose_stack(stack s)
{
    if(s != NULL)
    {
        free(s->array);
        free(s);
    }
}

int is_empty(stack s)
{
    return s->top_of_stack == -1;
}

int is_full(stack s)
{
    return s->capacity == s->top_of_stack + 1;
}

void make_empty(stack s)
{
    s->top_of_stack = -1;
}

void push(element_type x, stack s)
{
    if(is_full(s))
    {
        printf("Full stack!\n");
        exit(0);
    }
    else
        s->array[++s->top_of_stack] = x;
}

element_type top(stack s)
{
    if(!is_empty(s))
        return s->array[s->top_of_stack];
    else
    {
        printf("Empty stack\n");
        exit(0);
    }
    
    return 0;
}

void pop(stack s)
{
    if(is_empty( s))
    {
        printf("Empty stack\n");
        exit(0); 
    }
    else
        s->top_of_stack--;
}

element_type top_and_pop(stack s)
{
    if(!is_empty(s))
        return s->array[s->top_of_stack--];
    else
    {
        printf("Empty stack\n");
        exit(0);
    }
    return 0;
}
