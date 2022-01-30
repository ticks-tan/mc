/**
* @Author : Ticks
* @File   : single_list.h
* @Date   : 2022-01-30 下午6:40
* @Email  : 2938384958@qq.com
* @Des    : C语言单向链表，只实现存储int数据版本，其他版本类似
**/

#ifndef MC_SINGLE_LIST_H
#define MC_SINGLE_LIST_H

#include "tools/mc_malloc.h"

// 链表长度类型
typedef int size_type;
// 链表数据域数据类型
typedef int data_type;
// 单向链表结构体别名
typedef struct single_list   single_list;
// 单向链表节点结构体别名
typedef struct single_list_node   single_list_node;


// 这里方便下文使用链表名称
#ifndef list_node
#define list_node    single_list_node
#endif
#ifndef list
#define list    single_list
#endif

// 单向链表节点定义
struct list_node
{
    data_type data;     // 数据域
    list_node* next;    // 指针域
};

// 单向链表定义
struct list
{
    size_type   _count;         // 链表节点数量
    list_node*  _head;          // 链表节点

    // 下面定义一些链表操作(函数指针实现)

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
};

// 创建链表
list*   new_single_list();
// 销毁链表
bool    destroy_single_list(list* l);

// 使用完，取消定义
#ifdef list
#undef list
#endif

#ifdef list_node
#undef list_node
#endif

#endif //MC_SINGLE_LIST_H
