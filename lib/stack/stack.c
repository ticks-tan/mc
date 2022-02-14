/**
* @Author : Ticks
* @File   : stack.c
* @Date   : 2022-02-14 18:53
* @Email  : 2938384958@qq.com
* Des     : C语言栈实现(数组实现)
**/

#include "stack.h"

#ifndef _MC_STACK_TYPE
#define _MC_STACK_TYPE
#define size_type   int
#define data_type   int
#endif

typedef struct mc_stack mc_stack;
#ifndef stack
#define stack mc_stack
#endif

#ifndef _stack_func_name
#define _stack_func_name(name)   $_mc_stack_func_##name##_$
#endif

#ifndef stack_func_name
#define stack_func_name(name)   _stack_func_name(name)
#endif


size_type stack_func_name(size)(stack* this);
bool stack_func_name(empty)(stack* this);
data_type stack_func_name(top)(stack* this);
bool stack_func_name(push)(stack* this, data_type data);
bool stack_func_name(pop)(stack* this);
void stack_func_name(clear)(stack* this);

// impl

/**
 * 获取栈元素个数
 * @param this : 栈
 * @return : 栈元素个数
 */
size_type stack_func_name(size)(stack* this)
{
    if (PTR_NULL(this)){
        LOGE("stack size on a nullptr pointer!");
        return -1;
    }
    return this->_pos;
}

/**
 * 判断栈是否为空
 * @param this : 栈
 * @return : 是否为空栈
 */
bool stack_func_name(empty)(stack* this)
{
    if (PTR_NULL(this)){
        LOGE("stack empty on a nullptr pointer!");
        return true;
    }
    return (this->_pos > 0) ? false : true;
}

/**
 * 获取栈顶元素
 * @param this : 栈
 * @return : 栈顶元素
 */
data_type stack_func_name(top)(stack* this)
{
    if (PTR_NULL(this)) {
        LOGE("stack top on a nullptr pointer!");
        exit(-1);
    }
   if (stack_func_name(empty)(this) == false){
        return this->_data[this->_pos - 1];
    }
   LOGE("stack top on a empty stack!");
   exit(-1);
}

/**
 * 元素入栈
 * @param this : 栈
 * @param data : 入栈元素
 * @return : 是否入栈成功
 */
bool stack_func_name(push)(stack* this, data_type data)
{
    if (PTR_NULL(this)) {
        LOGE("stack push on a nullptr pointer!");
        return false;
    }
    if (this->_pos >= this->_alloc_size){
        // 内存不足
        data_type* old_data = this->_data;
        if (PTR_NULL(this->_data)){
            this->_alloc_size = 2;
        }else{
            this->_alloc_size += TO_CAST(size_type, this->_alloc_size / 2);
        }
        this->_data = mc_zalloc(sizeof(data_type) * this->_alloc_size);
        size_type i = 0;
        for (; i < this->_pos; ++i){
            this->_data[i] = old_data[i];
        }
        mc_free(PTR_ADDRESS(old_data));
    }
    this->_data[this->_pos++] = data;
    return true;
}

/**
 * 出栈
 * @param this : 栈
 * @return : 是否出栈成功
 */
bool stack_func_name(pop)(stack* this)
{
    if (PTR_NULL(this)) {
        LOGE("stack pop on a nullptr pointer!");
        return false;
    }
    if (stack_func_name(empty)(this) == true){
        LOGE("stack pop on a empty stack!");
        return false;
    }
    --this->_pos;
    return true;
}

/**
 * 清空栈元素
 * @param this : 栈
 */
void stack_func_name(clear)(stack* this)
{
    if (PTR_NULL(this)) {
        LOGE("stack clear on a nullptr pointer!");
    }
    this->_pos = 0;
}

// 创建一个新栈
stack* new_mc_stack()
{
    stack* s = TO_CAST(stack*, mc_zalloc(sizeof(stack)));
    s->_data = NULL;
    s->_pos = s->_alloc_size = 0;

    s->size = stack_func_name(size);
    s->empty = stack_func_name(empty);
    s->top = stack_func_name(top);
    s->push = stack_func_name(push);
    s->pop = stack_func_name(pop);

    return s;
}

// 销毁创建的栈
void destroy_mc_stack(stack* s)
{
    if (PTR_NULL(s)){
        return;
    }
    mc_free(PTR_ADDRESS(s->_data));
    s->_pos = s->_alloc_size = 0;
    mc_free(PTR_ADDRESS(s));
}

#ifdef _stack_func_name
#undef _stack_func_name
#endif

#ifdef stack_func_name
#undef stack_func_name
#endif

#ifdef stack
#undef stack
#endif

#ifdef _MC_STACK_TYPE
#undef _MC_STACK_TYPE
#undef size_type
#undef data_type
#endif