/**
* @Author : Ticks
* @File   : list.c
* @Date   : 2022-02-02 下午4:05
* @Email  : 2938384958@qq.com
* @Des    : C语言双向链表，数据只存储int类型
**/

#include "list.h"

#ifndef _MC_LIST_TYPE
#define _MC_LIST_TYPE
// 链表长度类型
#define size_type int
// 链表数据域数据类型
#define data_type int
#endif

// 这里方便下文使用链表名称
#ifndef list_node
#define list_node    mc_list_node
#endif
#ifndef list
#define list    mc_list
#endif

// 这里定义链表操作的函数名
#ifndef _linked_list_func
#define _linked_list_func(name)      $_linked_list_func_##name##_$
#endif

#ifndef list_func_name
#define list_func_name(name)       _linked_list_func(name)
#endif


list_node*  list_func_name(new_node)(data_type data);
size_type list_func_name(size)(list* this);
bool list_func_name(insert)(list* this, size_type pos, data_type data);
bool list_func_name(push_front)(list* this, data_type data);
bool list_func_name(push_back)(list* this, data_type data);
bool list_func_name(erase)(list* this, size_type pos);
bool list_func_name(pop_front)(list* this);
bool list_func_name(pop_back)(list* this);
bool list_func_name(replace)(list* this, size_type pos, data_type data);
bool list_func_name(resize)(list* this, size_type count, data_type data);
bool list_func_name(push_all)(list* this, const list* other);
void list_func_name(clear)(list* this);
void list_func_name(sort)(list* this);
void list_func_name(unique)(list* this);
const list_node*  list_func_name(get_const)(list* this, size_type pos);
list_node* list_func_name(get)(list* this, size_type pos);

list_node*  list_func_name(get_node)(list* this, size_type pos);

// impl

/**
 * 创建新节点
 * @param data : 新节点数据
 * @return : 新节点
 */
list_node*  list_func_name(new_node)(data_type data)
{
    list_node* node = TO_CAST(list_node*, mc_zalloc(sizeof (list_node)));
    node->data = data;
    node->next = node->prev = NULL;
    return node;
}

/**
 * 获取链表长度
 * @param this :  链表
 * @return : 链表长度( 链表为空返回-1 )
 */
size_type list_func_name(size)(list* this)
{
    // this不能为空
    if (PTR_NOT_NULL(this)){
        return this->_count;
    }
    return TO_CAST(size_type, -1);
}

/**
 * 插入新节点
 * @param this : 链表
 * @param pos : 插入位置 (0 - size)
 * @param data : 新节点数据
 * @return : 是否插入成功
 */
bool list_func_name(insert)(list* this, size_type pos, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("insert on a nullptr pointer!");
        return false;
    }
    if (0 > pos || pos > this->_count){
        LOGE("insert pos over!");
        return false;
    }
    // 创建新节点
    list_node* new_node = list_func_name(new_node)(data);
    // 在头部插入
    if (pos == 0){
        new_node->next = this->_head->next;
        this->_head->next = new_node;
        new_node->prev = this->_head;
        // 最初尾节点指向头节点
        if (this->_last == this->_head){
            this->_last = new_node;
        }
    }else if (pos == this->_count){ // 尾部添加
        // 尾节点后继节点指向新节点
        this->_last->next = new_node;
        // 新节点前继节点指向尾节点
        new_node->prev = this->_head;
        // 当前节点成为尾节点
        this->_last = new_node;
    }else{
        // 获取要插入节点前一个节点
        list_node* prev_node = list_func_name(get_node)(this, pos - 1);
        // 节点为空说明获取失败
        if (PTR_NULL(prev_node)){
            LOGE("insert internal error!");
            mc_free(PTR_ADDRESS(new_node));
            return false;
        }
        // 新节点后继节点指向待插入位置节点
        new_node->next = prev_node->next;
        // 待插入位置节点前继节点指向新节点
        prev_node->next->prev = new_node;
        // 前节点后继节点指向新节点
        prev_node->next = new_node;
    }
    ++this->_count;
    return true;
}

/**
 * 添加新节点到头部
 * @param this : 链表
 * @param data : 新节点数据
 * @return : 是否添加成功
 */
bool list_func_name(push_front)(list* this, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("push_front on a nullptr pointer");
        return false;
    }
    // 相当于插入到第一个位置
    return list_func_name(insert)(this, 0, data);
}

/**
 * 添加节点到链表尾部
 * @param this : 链表
 * @param data : 新节点数据
 * @return : 是否添加成功
 */
bool list_func_name(push_back)(list* this, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("push_back on a nullptr pointer");
        return false;
    }
    // 相当于插入到尾部
    return list_func_name(insert)(this, this->_count, data);
}

/**
 * 移除指定下标节点
 * @param this : 链表
 * @param pos : 待移除下标 ( 0 - size -1 )
 * @return : 是否移除成功
 */
bool list_func_name(erase)(list* this, size_type pos)
{
    if (PTR_NULL(this)){
        LOGE("erase on a nullptr pointer");
        return false;
    }
    if (0 > pos || pos >= this->_count){
        LOGE("erase pos over!");
        return false;
    }
    if (pos == this->_count - 1){
        // 移除最后节点
        list_node* del_node = this->_last;
        // 尾节点变为前一个节点
        this->_last = this->_last->prev;
        // 前一个节点后继节点变为NULL
        this->_last->next = NULL;
        // 释放节点内存
        mc_free(PTR_ADDRESS(del_node));
    }else if (pos == 0){
        // 待删除节点
        list_node* del_node = this->_head->next;
        // 前一个节点后继节点指向待删除节点后一个节点
        this->_head->next = del_node->next;
        // 后一个节点前继节点指向待删除节点前一个节点
        del_node->next->prev = this->_head;
        // 释放节点内存
        mc_free(PTR_ADDRESS(del_node));
    }else {
        // 找到指定下标前一个节点
        list_node *prev_node = list_func_name(get_node)(this, pos - 1);
        if (PTR_NULL(prev_node)) {
            LOGE("erase internal error!");
            return false;
        }
        list_node *del_node = prev_node->next;
        prev_node->next = del_node->next;
        del_node->next->prev = prev_node;
    }
    --this->_count;
    return true;
}

/**
 * 移除第一个节点
 * @param this : 链表
 * @return : 是否移除成功
 */
bool list_func_name(pop_front)(list* this)
{
    if (PTR_NULL(this)){
        LOGE("pop_front on a nullptr pointer!");
        return false;
    }
    // 相当于移除下标为 0 的节点
    return list_func_name(erase)(this, 0);
}

/**
 * 移除最后一个节点
 * @param this : 链表
 * @return : 是否移除成功
 */
bool list_func_name(pop_back)(list* this)
{
    if (PTR_NULL(this)){
        LOGE("pop_back on a nullptr pointer!");
        return false;
    }
    // 相当于移除下标为 size - 1 的节点
    return list_func_name(erase)(this, this->_count - 1);
}

/**
 * 更改指定下标节点数据
 * @param this : 链表
 * @param pos : 下标
 * @param data : 新数据
 * @return
 */
bool list_func_name(replace)(list* this, size_type pos, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("replace on a nullptr pointer!");
        return false;
    }
    // pos不能越界
    if (0 > pos || pos >= this->_count){
        LOGE("replace pos over!");
        return false;
    }
    list_node* p = list_func_name(get_node)(this, pos);
    if (PTR_NULL(p)){
        LOGE("replace internal error!");
        return false;
    }
    p->data = data;
    return true;
}

/**
 * 更改链表存储节点数量，比原来小删除多余节点，比原来大添加新节点到尾部
 * @param this : 链表
 * @param count : 新数量
 * @param data : 如果 count > size，新节点的默认数据
 * @return : 是否更改成功
 */
bool list_func_name(resize)(list* this, size_type count, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("resize on a nullptr pointer!");
        return false;
    }
    if (count > this->_count){
        // 大于当前链表元素数量
        count -= this->_count;
        size_type i = 0;

        // 添加新元素
        for (; i < count; ++i){
            list_node* node = list_func_name(new_node)(data);
            this->_last->next = node;
            node->prev = this->_last;
            this->_last = node;
        }
        // 更新节点数量
        this->_count += count;
    }else if (count < this->_count){
        // 小于当前链表元素数量，先找到 下标为 (count-1)的元素，然后清空后面的节点

        size_type i = 0;
        list_node* p = list_func_name(get_node)(this, count - 1);
        if (PTR_NULL(p)){
            goto INTERNAL_ERROR;
        }
        // 更新节点数量
        this->_count = count;
        // 获取后一个节点
        list_node* del_node = p->next;
        p->next = NULL;
        // 更新尾节点
        this->_last = p;
        // 循环删除后面的所有节点
        while (PTR_NOT_NULL(del_node)){
            p = del_node->next;
            mc_free(PTR_ADDRESS(del_node));
            del_node = p;
        }
    }
    return true;
    // 内部错误
    INTERNAL_ERROR:
    LOGE("resize internal error!");
    return false;
}

bool list_func_name(push_all)(list* this, const list* other)
{
    if (PTR_NULL(this) || PTR_NULL(other)){
        LOGE("push_all on a nullptr pointer!");
        return false;
    }

    // 循环将 other 链表中节点添加到 this 链表中
    // 记录添加的节点数量
    size_type count = 0;
    // 指向 other 链表节点的指针
    list_node* op = other->_head->next;
    while (PTR_NOT_NULL(op)){
        // 创建新节点并添加到 this 链表尾部
        list_node* node = list_func_name(new_node)(op->data);
        this->_last->next = node;
        node->prev = this->_last;
        this->_last = node;
        op = op->next;
        ++count;
    }
    // 更新 this 链表节点数量
    this->_count += count;
    return true;
}

void list_func_name(clear)(list* this)
{
    if (PTR_NULL(this)){
        LOGE("push_all on a nullptr pointer!");
        return;
    }
    list_node* del_node = this->_head->next, *p = NULL;
    while (PTR_NOT_NULL(del_node)){
        p = del_node->next;
        mc_free(PTR_ADDRESS(del_node));
        del_node = p;
    }
    this->_head->next = NULL;
    this->_count = 0;
}

void list_func_name(sort)(list* this)
{

}

void list_func_name(unique)(list* this)
{

}

const list_node*  list_func_name(get_const)(list* this, size_type pos)
{
    if (PTR_NULL(this)){
        LOGE("get_const on a nullptr pointer!");
        return NULL;
    }
    if (pos < 0 || pos >= this->_count){
        LOGE("get_const pos over!");
        return NULL;
    }
    list_node* node = list_func_name(get_node)(this, pos);
    if (node == NULL){
        LOGE("get_const internal error!");
    }
    return TO_CAST(const list_node*, node);
}

list_node* list_func_name(get)(list* this, size_type pos)
{
    if (PTR_NULL(this)){
        LOGE("get_const on a nullptr pointer!");
        return NULL;
    }
    if (pos < 0 || pos >= this->_count){
        LOGE("get_const pos over!");
        return NULL;
    }
    list_node* node = list_func_name(get_node)(this, pos);
    if (node == NULL){
        LOGE("get_const internal error!");
    }
    return node;
}

list_node*  list_func_name(get_node)(list* this, size_type pos)
{
    size_type i = 0;
    list_node* node = NULL;
    if (pos >= (this->_count / 2)){
        node = this->_last;
        for (i = this->_count - 1; PTR_NOT_NULL(node) && (i > pos); --i){
            node = node->prev;
        }
    }else{
        node = this->_head->next;
        for (i = 0; PTR_NOT_NULL(node) && (i < pos); ++i){
            node = node->next;
        }
    }
    return (i == pos) ? node : NULL;
}

// 创建链表
list*   new_mc_list()
{
    list* l = TO_CAST(list*, mc_zalloc(sizeof(list)));
    l->_count = 0;
    l->_head = list_func_name(new_node)((data_type)0);
    l->_last = l->_head;

    // 对函数指针赋值
    l->insert =     list_func_name(insert);
    l->push_back =  list_func_name(push_back);
    l->push_front = list_func_name(push_front);
    l->push_all =   list_func_name(push_all);
    l->erase =      list_func_name(erase);
    l->pop_back =   list_func_name(pop_back);
    l->pop_front =  list_func_name(pop_front);
    l->replace =    list_func_name(replace);
    l->resize =     list_func_name(resize);
    l->size =       list_func_name(size);
    l->clear =      list_func_name(clear);
    l->sort =       list_func_name(sort);
    l->unique =     list_func_name(unique);
    l->get_const =  list_func_name(get_const);
    l->get =        list_func_name(get);

    return l;
}

// 销毁链表
bool    destroy_mc_list(list* l)
{
    if (PTR_NULL(l)){
        LOGE("destroy_mc_list on a nullptr pointer!");
        return false;
    }
    l->clear(l);
    mc_free(PTR_ADDRESS(l->_head));
    mc_free(PTR_ADDRESS(l));
    return true;
}


#ifdef _MC_LIST_TYPE
#undef _MC_LIST_TYPE
// 链表长度类型
#undef size_type
// 链表数据域数据类型
#undef data_type
#endif

// 使用完，取消定义
#ifdef list
#undef list
#endif

#ifdef list_node
#undef list_node
#endif

#ifdef _linked_list_func
#undef _linked_list_func
#endif

#ifdef list_func_name
#undef list_func_name
#endif