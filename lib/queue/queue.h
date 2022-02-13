/**
* @Author : Ticks
* @File   : queue.h
* @Date   : 2022-02-13 21:16
* @Email  : 2938384958@qq.com
* @Des    : C语言队列实现
**/
#ifndef MC_QUEUE_H
#define MC_QUEUE_H

#include "../tools/mc_malloc.h"

// 定义类型，方便修改
#ifndef _MC_QUEUE_TYPE
#define _MC_QUEUE_TYPE
#define size_type int
#define data_type int
#endif

// 队列类型别名
typedef struct mc_queue mc_queue;

#ifndef queue
#define queue mc_queue
#endif


// 队列结构体
struct queue
{
    // 存放队列数据
    data_type* _data;
    // 指向队列头部
    size_type _head;
    // 指向队列尾部
    size_type _tail;
    // 队列最多可存储成员数量
    size_type _alloc_size;

    // 定义队列相关操作
    // 获取队列长度
    size_type (*size)(queue* this);
    // 判断队列是否为空
    bool (*empty)(queue* this);
    // 获取队列头部元素
    data_type (*front)(queue* this);
    // 获取队列尾部元素
    data_type (*back)(queue* this);
    // 入队操作
    bool (*push)(queue* this, data_type data);
    // 出队操作
    bool (*pop)(queue* this);
    // 清空队列
    void (*clear)(queue* this);
};

// 创建队列
queue* new_mc_queue();
// 销毁队列
void destroy_mc_queue(queue* q);


#ifdef queue
#undef queue
#endif

// 取消临时定义的类型
#ifdef _MC_QUEUE_TYPE
#undef _MC_QUEUE_TYPE
#undef size_type
#undef data_type
#endif

#endif //MC_QUEUE_H
