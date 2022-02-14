/**
* @Author : Ticks
* @File   : stack.h
* @Date   : 2022-02-14 11:49
* @Email  : 2938384958@qq.com
* Des     : C语言栈实现 -- 底层为数组，不是链表
**/
#ifndef MC_STACK_H
#define MC_STACK_H

#include "../tools/mc_malloc.h"

#ifndef _MC_STACK_TYPE
#define _MC_STACK_TYPE
#define size_type   int
#define data_type   int
#endif

typedef struct mc_stack mc_stack;
#ifndef stack
#define stack mc_stack
#endif

struct stack
{
    // 栈实际数据存储位置
    data_type*  _data;
    // 指向栈顶
    size_type   _pos;
    // 最大可存储元素数量
    size_type   _alloc_size;

    // 定义操作
    // 获取元素个数
    size_type (*size)(stack* this);
    // 判断栈是否为空
    bool (*empty)(stack* this);
    // 返回栈顶元素
    data_type (*top)(stack* this);
    // 入栈
    bool (*push)(stack* this, data_type data);
    // 出栈
    bool (*pop)(stack* this);
    // 清空链表
    void (*clear)(stack* this);
};

// 创建一个新栈
stack* new_mc_stack();
// 销毁创建的栈
void destroy_mc_stack(stack* s);

#ifdef stack
#undef stack
#endif

#ifdef _MC_STACK_TYPE
#undef _MC_STACK_TYPE
#undef size_type
#undef data_type
#endif

#endif //MC_STACK_H
