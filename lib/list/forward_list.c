/**
* @Author : Ticks
* @File   : single_list.c
* @Date   : 2022-01-30 下午8:07
* @Email  : 2938384958@qq.com
* @Des    : C语言单向链表，只实现存储int数据版本，其他版本类似
**/

#include "forward_list.h"

#ifndef _MC_FORWARD_LIST_TYPE
#define _MC_FORWARD_LIST_TYPE
// 链表长度类型
#define size_type int
// 链表数据域数据类型
#define data_type int
#endif

// 这里方便下文使用链表名称
#ifndef list_node
#define list_node    mc_forward_list_node
#endif
#ifndef list
#define list    mc_forward_list
#endif

// 这里定义链表操作的函数名
#ifndef _forward_linked_list_func
#define _forward_linked_list_func(name)      $_forward_linked_list_func_##name##_$
#endif

#ifndef list_func_name
#define list_func_name(name)       _forward_linked_list_func(name)
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
 * 创建新的链表节点
 * @param data  : 节点数据
 * @return      : 返回新的节点指针
 */
list_node*  list_func_name(new_node)(data_type data)
{
    // 调用内存分配函数，分配内存给node
    list_node* node = TO_CAST(list_node*, mc_zalloc(sizeof(list_node)));
    // 初始化node数据
    node->data = data;
    node->next = NULL;
    return node;
}

/**
 * 返回链表元素数量
 * @param this  : 链表
 * @return      : 链表元素数量
 */
size_type list_func_name(size)(list* this)
{
    // 需要对 this 判空
    if (PTR_NOT_NULL(this)){
        return this->_count;
    }
    return TO_CAST(size_type, -1);
}

/**
 * 插入新元素到链表指定下标
 * @param this  ： 链表
 * @param pos   : 下标
 * @param data  : 新数据
 * @return      : 操作是否成功
 */
bool list_func_name(insert)(list* this, size_type pos, data_type data)
{
    // 判断 this 是否为空
    if (PTR_NULL(this)){
        LOGE("insert on a nullptr pointer!");
        return false;
    }
    // 下标不能越界
    if (0 > pos || pos > this->_count){
        LOGE("insert pos over!");
        return false;
    }
    // 创建一个新节点，用于插入
    list_node* node = list_func_name(new_node)(data);
    if (pos == 0){
        // 相当于 push_front，在头部插入新节点
        // this->_head只用作节点，不存储数据，也就是 this->_head->next 为第一个正式节点
        // 先将新节点后继指针指向当前的第一个节点
        node->next = this->_head->next;
        // 然后将当前链表第一个节点赋值为新节点 node
        this->_head->next = node;
    }else{
        // 其他情况，也就是中间节点
        // 获取 下标为 pos 的前一个节点
        list_node* p = list_func_name(get_node)(this, pos - 1);
        // 判断是否为空节点
        if (PTR_NULL(p)){
            LOGE("insert internal error!");
            mc_free(PTR_ADDRESS(node));
            return false;
        }
        // 新节点指向要插入下标的节点
        node->next = p->next;
        // 要插入下标节点前一个节点后继指针指向新节点
        p->next = node;
    }
    ++this->_count;
    return true;
}

/**
 * 插入新元素到链表头部
 * @param this  : 链表
 * @return      : 操作是否成功
 * @date        : 新数据
 */
bool list_func_name(push_front)(list* this, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("push_front on a nullptr pointer!");
        return false;
    }
    // 插入到第一个位置
    return list_func_name(insert)(this, 0, data);
}

/**
 * 插入新元素到链表尾部
 * @param this  : 链表
 * @return      : 操作是否成功
 * @date        : 新数据
 */
bool list_func_name(push_back)(list* this, data_type data)
{
    if (PTR_NULL(this)){
        LOGE("push_back on a nullptr pointer!");
        return false;
    }
    // 插入到最后位置
    return list_func_name(insert)(this, this->_count, data);
}

/**
 * 移除指定下标节点
 * @param this  : 链表
 * @param pos   : 下表
 * @return      : 操作是否成功
 */
bool list_func_name(erase)(list* this, size_type pos)
{
    if (PTR_NULL(this)){
        LOGE("erase on a nullptr pointer!");
        return false;
    }
    // pos不能越界
    if (0 > pos || pos >= this->_count){
        LOGE("erase pos over!");
        return false;
    }
    list_node* p = list_func_name(get_node)(this, pos - 1);
    if (PTR_NULL(p)){
        LOGE("erase internal error!");
        return false;
    }
    list_node* del_node = p->next;
    p->next = del_node->next;
    mc_free(PTR_ADDRESS(del_node));
    --this->_count;
    return true;
}

/**
 * 移除第一个节点
 * @param this  : 链表
 * @return      : 操作是否成功
 */
bool list_func_name(pop_front)(list* this)
{
    if (PTR_NULL(this)){
        LOGE("pop_front on a nullptr pointer!");
        return false;
    }
    // 移除第一个元素
    return list_func_name(erase)(this, 0);
}

/**
 * 移除第最后节点
 * @param this  : 链表
 * @return      : 操作是否成功
 */
bool list_func_name(pop_back)(list* this)
{
    if (PTR_NULL(this)){
        LOGE("pop_back on a nullptr pointer!");
        return false;
    }
    // 移除最后一个元素
    return list_func_name(erase)(this, this->_count - 1);
}

/**
 * 修改指定下标节点数据
 * @param this      : 链表
 * @param pos       : 下标
 * @param data      : 新数据
 * @return          : 操作是否成功
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
 * 更改可容纳元素大小,如果 count 小于当前链表元素个数，则会删除多余节点
 * @param this      : 链表
 * @param pos       : 下标
 * @param data      : 如果 count 大于当前链表元素，则后添加的节点默认数据为 data
 * @return          : 操作是否成功
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
        list_node* p = list_func_name(get_node)(this, this->_count - 1);
        // 如果为空，说明提前结束循环，出现错误
        if (PTR_NULL(p)){
            goto INTERNAL_ERROR;
        }
        // 添加新元素
        for (; i < count; ++i){
            list_node* node = list_func_name(new_node)(data);
            p->next = node;
            p = node;
        }
        p = NULL;
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

/**
 * 添加另一个链表元素到当前链表尾部
 * @param this      : 链表
 * @param other     : 其他链表
 * @return          : 操作是否成功
 */
bool list_func_name(push_all)(list* this, const list* other)
{
    if (PTR_NULL(this) || PTR_NULL(other)){
        LOGE("push_all on a nullptr pointer!");
        return false;
    }
    // 获取 this 链表最后一个节点
    list_node* p = list_func_name(get_node)(this, this->_count - 1);
    if (PTR_NULL(p)){
        LOGE("push_all internal error!");
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
        p->next = node;
        p = node;
        op = op->next;
        ++count;
    }
    // 更新 this 链表节点数量
    this->_count += count;
    return true;
}

/**
 * 清空链表元素
 * @param this  : 链表
 */
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

/**
 * 排序链表元素
 * @param this  : 链表
 */
void list_func_name(sort)(list* this)
{

}

/**
 * 删除连续链表中重复元素
 * @param this  : 链表
 */
void list_func_name(unique)(list* this)
{

}

const list_node* list_func_name(get_const)(list* this, size_type pos)
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

/**
 * 获取指定下标节点
 * @param this  : 链表
 * @param pos   : 下标
 * @return      : 成功返回节点，失败返回NULL
 */
list_node*  list_func_name(get_node)(list* this, size_type pos)
{
    list_node* p = this->_head->next;
    size_type i = 0;
    for (; PTR_NOT_NULL(p) && i < pos; ++i){
        p = p->next;
    }
    return (i == pos)? p : NULL;
}


/**
 * 创建单向链表
 * @return  : 返回新的链表指针
 */
list*   new_mc_forward_list()
{
    list* l = TO_CAST(list*, mc_zalloc(sizeof(list)));
    l->_count = 0;
    l->_head = list_func_name(new_node)((data_type)0);

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

/**
 * 销毁链表
 * @param l : 链表
 * @return
 */
bool    destroy_mc_forward_list(list* l)
{
    if (PTR_NULL(l)){
        LOGE("destroy_mc_forward_list on a null pointer!");
        return false;
    }
    l->clear(l);
    mc_free(PTR_ADDRESS(l->_head));
    mc_free(PTR_ADDRESS(l));
    return true;
}

#ifdef _MC_FORWARD_LIST_TYPE
#undef _MC_FORWARD_LIST_TYPE
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

#ifdef _single_linked_list_func
#undef _single_linked_list_func
#endif

#ifdef list_func_name
#undef list_func_name
#endif
