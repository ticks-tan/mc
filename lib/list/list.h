/**
* @Author : Ticks
* @File   : list.h
* @Date   : 2022-02-02 下午4:05
* @Email  : 2938384958@qq.com
* @Des    : C语言双向链表，数据只存储int类型
**/

#ifndef MC_LIST_H
#define MC_LIST_H

#include "tools/mc_malloc.h"

// 定义类型
#ifndef _MC_LIST_TYPE
#define _MC_LIST_TYPE
// 数据类型
#define data_type   int
// 长度类型
#define size_type   int
#endif

// 双向链表结构体别名
typedef struct mc_list mc_list;
// 链表节点别名
typedef struct mc_list_node mc_list_node;


#ifndef list
#define list        mc_list
#define list_node   mc_list_node
#endif

// 链表节点结构体
struct list_node
{
    data_type   data;       // 数据域
    list_node*  next;       // 指向下一个节点
    list_node*  prev;       // 指向上一个节点
};

// 链表结构体
struct list
{
    size_type _count;       // 链表节点数量
    list_node* _head;       // 链表头节点
    list_node* _last;
    // 方法定义--函数指针

    // 获取链表节点数量
    size_type (*size)(list* this);
    // 插入新元素到链表指定下标
    bool (*insert)(list* this, size_type pos, data_type data);
    // 插入新元素到链表头部
    bool (*push_front)(list* this, data_type data);
    // 插入新元素到链表尾部
    bool (*push_back)(list* this, data_type data);
    // 移除指定下标节点
    bool (*erase)(list* this, size_type pos);
    // 移除第一个节点
    bool (*pop_front)(list* this);
    // 移除第最后节点
    bool (*pop_back)(list* this);
    // 修改指定下标节点数据
    bool (*replace)(list* this, size_type pos, data_type data);
    // 更改可容纳元素大小
    bool (*resize)(list* this, size_type count, data_type data);
    // 添加另一个链表元素到当前链表尾部
    bool (*push_all)(list* this, const list* other);
    // 清空链表
    void (*clear)(list* this);
    // 排序元素
    void (*sort)(list* this);
    // 删除连续重复元素
    void (*unique)(list* this);
    // 获取指定下标节点(获取的节点不可修改)
    const list_node* const (*get_const)(list* this, size_type pos);
    // 获取指定下标节点，可改变
    list_node*  (*get)(list* this, size_type pos);
};

// 创建链表
list*   new_mc_list();
// 销毁链表
bool    destroy_mc_list(list* l);


// 取消定义 list
#ifdef list
#undef list
#endif
// 取消定义list_node
#ifdef list_node
#undef list_node
#endif

// 取消定义数据类型
#ifdef _MC_LIST_TYPE
#undef _MC_LIST_TYPE
#undef data_type
#undef size_type
#endif


#endif //MC_LIST_H
