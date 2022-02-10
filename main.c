#include <stdio.h>

#include "list/forward_list.h"
#include "list/list.h"

int main() {
    mc_list* list = new_mc_list();
    for (int i = 0; i < 10; ++i){
        list->push_back(list, i);
    }

    printf("list's size = %d\n", list->size(list));
    destroy_mc_list(list);
    return 0;
}
