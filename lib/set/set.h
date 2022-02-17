/**
* @Author : Ticks
* @File   : set.h
* @Date   : 2022-02-17 16:17
* @Email  : 2938384958@qq.com
* Des     : 基于跳表实现简单set
**/
#ifndef MC_SET_H
#define MC_SET_H

#include "tools/mc_malloc.h"

#ifndef _MC_SET_TYPE
#define _MC_SET_TYPE
#define data_type int
#define size_type int
#endif

// 跳表
typedef struct mc_set mc_set;
// 跳表数据节点
typedef struct mc_set_node    mc_set_node;

#ifndef MC_SET_DEF
#define MC_SET_DEF
#define set        mc_set
#define set_node   mc_set_node
#endif

struct set_node
{
    data_type   key;    // 存储key
    struct{
        set_node* next; // 后继节点
    }level[];
};

struct set
{
    set_node*  _header;    // 索引 0 为底层链表，> 1 为索引
    size_type   _level;    // 索引高度
    size_type   _size;     // 数据节点个数
    // 定义操作

    // 获取长度
    size_type (*size)(set* this);
    // 插入节点
    bool (*insert)(set* this, data_type key);
    // 删除节点
    bool (*erase)(set* this, data_type key);
    // 查找数据
    set_node* (*find)(set* this, data_type key);
    // 清空map
    void (*clear)(set* this);
};

// 创建map
set* new_mc_map();
// 销毁map
void destroy_map(set* m);


#ifdef MC_SET_DEF
#undef MC_SET_DEF
#undef map
#undef map_node
#endif

#ifdef _MC_SET_TYPE
#undef _MC_SET_TYPE
#undef data_type
#undef size_type
#endif

#endif //MC_SET_H
