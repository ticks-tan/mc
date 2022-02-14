#include <stdio.h>

#include "stack/stack.h"

int main() {
    mc_stack* s = new_mc_stack();
    int i = 0;
    for (; i < 10; ++i){
        s->push(s, i);
    }
    printf("栈元素个数: %d\n", s->size(s));
    while (s->empty(s) == false){
        printf("stack : %d\n", s->top(s));
        s->pop(s);
    }
    printf("栈元素个数: %d\n", s->size(s));
    destroy_mc_stack(s);
    Mc_MemCheck();
    return 0;
}

