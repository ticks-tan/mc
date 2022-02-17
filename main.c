#include <stdio.h>

#include "list/forward_list.h"
#include "map/map.h"
#include <time.h>
#include <unistd.h>

int main()
{
    srand(TO_CAST(unsigned , time(NULL)));

    mc_forward_list* list = new_mc_forward_list();
    mc_map* map = new_mc_map();

    int nums[1000];
    int i, index = 0;
    for (i = 0; i < 1000; ++i){
        nums[i] = i + 1;
    }
    for (i = 0; i < 1000; ++i){
        list->push_back(list, nums[i]);
        map->insert(map, nums[i], nums[i]);
    }


    long start1 = clock();
    mc_forward_list_node* p1 = list->get(list, 0);
    while (PTR_NOT_NULL(p1)){
        if (p1->data == 900){
            break;
        }
        p1 = p1->next;
    }
    long end1 = clock();
    if (PTR_NOT_NULL(p1)){
        printf("find the list node: %d -> %ld\n", p1->data, (end1 - start1));
    }else{
        printf("not find the list node!\n");
    }

    long start2 = clock();
    mc_map_node* p2 = map->find(map, 900);
    long end2 = clock();
    if (PTR_NOT_NULL(p2)){
        printf("find the map node: %d -> %ld\n", p2->data, (end2 - start2));
    }else{
        printf("not find the map node!\n");
    }
    destroy_map(map);
    destroy_mc_forward_list(list);
    Mc_MemCheck();
    return 0;
}

