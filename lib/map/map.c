/**
* @Author : Ticks
* @File   : skip_list.c
* @Date   : 2022-02-17 11:51
* @Email  : 2938384958@qq.com
* Des     : C语言简单map实现
**/
#include <math.h>
#include "map.h"
#ifndef _MC_MAP_TYPE
#define _MC_MAP_TYPE
#define data_type int
#define size_type int
#endif

#ifndef MC_MAP_DEF
#define MC_MAP_DEF
#define map        mc_map
#define map_node   mc_map_node
#endif

#ifndef _mc_map_func_name
#define _mc_map_func_name(name)     $_mc_map_func_##name##_$
#endif
#ifndef mc_map_func_name
#define mc_map_func_name(name)  _mc_map_func_name(name)
#endif

#define SKIP_P      0.25
#define MAX_SKIP_H  16

size_type   mc_map_func_name(random)();
size_type   mc_map_func_name(size)(map* this);
bool mc_map_func_name(insert)(map* this, data_type key, data_type value);
bool mc_map_func_name(erase)(map* this, data_type key);
map_node* mc_map_func_name(find)(map* this, data_type key);
void mc_map_func_name(clear)(map* this);
map_node* mc_map_func_name(new_node)(size_type level, size_type key, size_type value);


// 创建新节点
map_node* mc_map_func_name(new_node)(size_type level, size_type key, size_type value)
{
    map_node* node = TO_CAST(map_node*, mc_zalloc(sizeof(*node) + level * sizeof(map_node)));
    node->key = key;
    node->data = value;
    return node;
}

// 创建map
map* new_mc_map()
{
    int i = 0;
    map* m = TO_CAST(map*, mc_zalloc(sizeof(map)));
    m->_level = 1;
    m->_size = 0;
    m->_header = mc_map_func_name(new_node)(MAX_SKIP_H, 0, 0);
    for (i = 0; i < MAX_SKIP_H; ++i){
        m->_header->level[i].next = NULL;
    }

    m->size = mc_map_func_name(size);
    m->clear = mc_map_func_name(clear);
    m->insert = mc_map_func_name(insert);
    m->find = mc_map_func_name(find);
    m->erase = mc_map_func_name(erase);
    return m;
}

// 销毁map
void destroy_map(map* m)
{
    if (PTR_NULL(m)){
        LOGE("destroy the map on a nullptr pointer");
        return;
    }
    map_node* node = m->_header->level[0].next, *next;

    mc_free(PTR_ADDRESS(m->_header));
    while (node){
        next = node->level[0].next;
        mc_free(PTR_ADDRESS(node));
        node = next;
    }
    mc_free(PTR_ADDRESS(m));
}

// 返回需要在哪一层建立索引
size_type   mc_map_func_name(random)()
{
    int ret = 1;
    while ((random() & 0xFFFF) < (SKIP_P * 0xFFFF))
        ++ret;
    return (ret < MAX_SKIP_H) ? ret : MAX_SKIP_H;
}

size_type   mc_map_func_name(size)(map* this)
{
    if (PTR_NULL(this)){
        LOGE("map size on a nullptr pointer");
        return 0;
    }
    return this->_size;
}

bool mc_map_func_name(insert)(map* this, data_type key, data_type value)
{
    if (PTR_NULL(this)){
        LOGE("map insert on a nullptr pointer");
        return false;
    }
    map_node* pre_nodes[MAX_SKIP_H], *p;    // 要更新的前继节点列表
    size_type i, new_level;
    p = this->_header;
    for (i = this->_level - 1; i >= 0; --i){
        while (p->level[i].next && p->level[i].next->key < key){
            p = p->level[i].next;
        }
        // key相同，不用插入
        if (p->level[i].next && p->level[i].next->key == key){
            p->level[i].next->data = value;
            return true;
        }
        pre_nodes[i] = p;
    }
    new_level = mc_map_func_name(random)();
    if (new_level > this->_level){
        for (i = this->_level; i < new_level; ++i){
            pre_nodes[i] = this->_header;
        }
        this->_level = new_level;
    }
    p = mc_map_func_name(new_node)(new_level, key, value);
    for (i = 0; i < new_level; ++i){
        p->level[i].next = pre_nodes[i]->level[i].next;
        pre_nodes[i]->level[i].next = p;
    }
    ++this->_size;
    return true;
}

bool mc_map_func_name(erase)(map* this, data_type key)
{
    if (PTR_NULL(this)){
        LOGE("map erase on a nullptr pointer");
        return NULL;
    }
    map_node* p = this->_header, *pre_node[MAX_SKIP_H];
    int level = this->_level - 1, i;
    for (i = level; i >= 0; --i){
        while (p->level[i].next && p->level[i].next->key < key){
            p = p->level[i].next;
        }
        pre_node[i] = p;
    }
    p = p->level[0].next;
    if (p && p->key == key){
        for (i = 0; i < this->_level; ++i){
            if (pre_node[i]->level[i].next == p){
                pre_node[i]->level[i].next = p->level[i].next;
            }
        }
        for (i = level; i >= 1; --i){
            if (this->_header->level[i].next != NULL){
                break;
            }
            --this->_level;
        }
        --this->_size;
        mc_free(PTR_ADDRESS(p));
        return true;
    }
    return false;
}

map_node* mc_map_func_name(find)(map* this, data_type key)
{
    if (PTR_NULL(this)){
        LOGE("map find on a nullptr pointer");
        return NULL;
    }
    map_node* p = this->_header;
    int level = this->_level - 1, i;
    for (i = level; i >= 0; --i){
        while (p->level[i].next && p->level[i].next->key < key){
            p = p->level[i].next;
        }
        if (PTR_NULL(p->level[i].next) || p->level[i].next->key > key){
            continue;
        }
        return p->level[i].next;
    }
    return NULL;
}

void mc_map_func_name(clear)(map* this)
{
    if (PTR_NULL(this)){
        LOGE("map clear on a nullptr pointer");
        return;
    }
    map_node* p = this->_header->level[0].next, *next;
    size_type i;
    for (i = 0; i < this->_level; ++i){
        this->_header->level[i].next = NULL;
    }
    while (p){
        next = p->level[0].next;
        mc_free(PTR_ADDRESS(p));
        p = next;
    }
    this->_level = this->_size = 0;
}

#ifdef MC_MAP_DEF
#undef MC_MAP_DEF
#undef map
#undef map_node
#endif

#ifdef _MC_MAP_TYPE
#undef _MC_MAP_TYPE
#undef data_type
#undef size_type
#endif