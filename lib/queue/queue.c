/**
* @Author : Ticks
* @File   : queue.c
* @Date   : 2022-02-13 21:34
* @Email  : 2938384958@qq.com
* Des     :   C语言队列实现
**/

#include "queue.h"

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

#ifndef _queue_func_name
#define _queue_func_name(name)   $_mc_queue_func_##name##_$
#endif

#ifndef queue_func_name
#define queue_func_name(name)   _queue_func_name(name)
#endif


size_type queue_func_name(size)(queue* this);
bool queue_func_name(empty)(queue* this);
data_type queue_func_name(front)(queue* this);
data_type queue_func_name(back)(queue* this);
bool queue_func_name(push)(queue* this, data_type data);
bool queue_func_name(pop)(queue* this);
void queue_func_name(clear)(queue* this);


// impl

size_type queue_func_name(size)(queue* this)
{
    if (PTR_NULL(this)){
        LOGE("queue size on a nullptr pointer!");
        return -1;
    }
    return this->_tail - this->_head;
}

bool queue_func_name(empty)(queue* this)
{
    if (PTR_NULL(this)){
        LOGE("queue empty on a nullptr pointer!");
        return true;
    }
    return (this->_head == this->_tail) ? 1 : 0;
}

data_type queue_func_name(front)(queue* this)
{
    if (PTR_NULL(this)){
        LOGE("queue front on a nullptr pointer!");
        exit(-1);
    }
    if (!queue_func_name(empty)(this)){
        return this->_data[this->_head];
    }
    LOGE("queue front on a empty queue!");
    exit(-1);
}

data_type queue_func_name(back)(queue* this)
{
    if (PTR_NULL(this)){
        LOGE("queue back on a nullptr pointer!");
        exit(-1);
    }
    if (!queue_func_name(empty)(this)){
        return this->_data[this->_tail - 1];
    }
    LOGE("queue front on a empty queue!");
    exit(-1);
}

bool queue_func_name(push)(queue* this, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("queue push on a nullptr pointer!");
        return false;
    }
    if (this->_tail < this->_alloc_size){
        this->_data[this->_tail++] = data;
    }else{
        if (this->_head > 0){
            size_type size = this->_tail - this->_head;
            size_type free_size = this->_head, i = 0;
            for (; i < size; ++i){
                this->_data[i] = this->_data[i + free_size];
            }
            this->_head = 0; this->_tail = size;
        }else{
            data_type* old_data = this->_data;
            if (this->_data != NULL) {
                this->_alloc_size += this->_alloc_size / 2;
            }else{
                this->_alloc_size = 2;
            }
            this->_data = mc_zalloc(sizeof(data_type) * this->_alloc_size);
            size_type i = 0;
            for (; (this->_head + i) < this->_tail; ++i){
                this->_data[i] = old_data[this->_head + i];
            }
            this->_head = 0; this->_tail = i;
            mc_free(PTR_ADDRESS(old_data));
        }
        this->_data[this->_tail++] = data;
    }
    return true;
}

bool queue_func_name(pop)(queue* this)
{
    if (PTR_NULL(this)){
        LOGE("queue pop on a nullptr pointer!");
        return false;
    }
    if (queue_func_name(empty)(this)){
        LOGE("queue is a empty queue!");
        return false;
    }
    ++this->_head;
    return true;
}

void queue_func_name(clear)(queue* this)
{
    if (PTR_NULL(this)){
        LOGE("queue clear on a nullptr pointer!");
    }
    this->_head = this->_tail = 0;
}

// 创建队列
queue* new_mc_queue()
{
    queue* q = TO_CAST(queue*, mc_zalloc(sizeof(queue)));
    q->_tail = q->_head = 0;
    q->_alloc_size = 0;
    q->_data = NULL;

    q->size     =   queue_func_name(size);
    q->clear    =   queue_func_name(clear);
    q->empty    =   queue_func_name(empty);
    q->front    =   queue_func_name(front);
    q->back     =   queue_func_name(back);
    q->push     =   queue_func_name(push);
    q->pop      =   queue_func_name(pop);

    return q;
}

// 销毁队列
void destroy_mc_queue(queue* q)
{
    if (PTR_NULL(q)){
        return;
    }
    mc_free(PTR_ADDRESS(q->_data));
    q->_tail = q->_head = 0;
    q->_alloc_size = 0;
    mc_free(PTR_ADDRESS(q));
}


#ifdef queue
#undef queue
#endif

// 取消临时定义的类型
#ifdef _MC_QUEUE_TYPE
#undef _MC_QUEUE_TYPE
#undef size_type
#undef data_type
#endif

#ifdef _queue_func_name
#undef _queue_func_name
#endif

#ifdef queue_func_name
#undef queue_func_name
#endif