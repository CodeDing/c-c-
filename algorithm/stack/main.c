#include "stack.h"
#include <stdio.h>

int main(void)
{
    stack s;
    int x, y, z;
    s = create_stack(10);    
    push(1,s);
    push(2,s);
    push(3,s);
    x = top_and_pop(s);
    y = top_and_pop(s);
    z = top_and_pop(s);
    printf("%d\n%d\n%d\n", x, y, z);
    dispose_stack(s);
    return 0;
}
