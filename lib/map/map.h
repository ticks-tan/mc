/**
* @Author : Ticks
* @File   : skip_list.h
* @Date   : 2022-02-17 11:50
* @Email  : 2938384958@qq.com
* Des     : C语言实现简单的map
**/
#ifndef MC_MAP_H
#define MC_MAP_H

#include "tools/mc_malloc.h"

#ifndef _MC_MAP_TYPE
#define _MC_MAP_TYPE
#define data_type int
#define size_type int
#endif

// 跳表
typedef struct mc_map mc_map;
// 跳表数据节点
typedef struct mc_map_node    mc_map_node;

#ifndef MC_MAP_DEF
#define MC_MAP_DEF
#define map        mc_map
#define map_node   mc_map_node
#endif

struct map_node
{
    data_type   key;    // 存储key
    data_type   data;   // 存储value
    struct{
        map_node* next; // 后继节点
    }level[];
};

struct map
{
    map_node*  _header;    // 索引 0 为底层链表，> 1 为索引
    size_type   _level;    // 索引高度
    size_type   _size;     // 数据节点个数
    // 定义操作

    // 获取长度
    size_type (*size)(map* this);
    // 插入节点
    bool (*insert)(map* this, data_type key, data_type value);
    // 删除节点
    bool (*erase)(map* this, data_type key);
    // 查找数据
    map_node* (*find)(map* this, data_type key);
    // 清空map
    void (*clear)(map* this);
};

// 创建map
map* new_mc_map();
// 销毁map
void destroy_map(map* m);


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

#endif //MC_MAP_H
