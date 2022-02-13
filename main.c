#include <stdio.h>

#include "queue//queue.h"

int main() {
    mc_queue* q = new_mc_queue();
    int i = 0;
    for (; i < 100; ++i){
        q->push(q, i);
    }
    while(!q->empty(q)){
        printf("queue : %d\n", q->front(q));
        q->pop(q);
    }
    destroy_mc_queue(q);
    Mc_MemCheck();
    return 0;
}

