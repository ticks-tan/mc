#include <stdio.h>

#include "list/single_list.h"

int main() {
    single_list* list = new_single_list();
    int i = 0;
    for (; i < 10; ++i){
        list->push_back(list, i);
    }
    printf("list->size = %d\n", list->size(list));
    destroy_single_list(list);
    return 0;
}
