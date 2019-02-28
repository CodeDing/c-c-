#ifndef _stack_h
#define _stack_h

struct stack_record;
typedef struct stack_record *stack;
typedef int element_type;

int is_empty(stack s);
int is_full(stack s);
stack create_stack(int max_elements);
void dispose_stack(stack s);
void make_empty(stack s);
void push(element_type x, stack s);
element_type top(stack s);
void pop(stack s);
element_type top_and_pop(stack s);

#endif
