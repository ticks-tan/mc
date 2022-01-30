/**
* @Author : Ticks
* @File   : mc_malloc.c
* @Date   : 2022-01-30 下午7:03
* @Email  : 2938384958@qq.com
* @Des    : 封装 malloc.h 方法，函数功能同标准库 malloc.h
**/

#include "mc_malloc.h"

#include <malloc.h>
#include <stdatomic.h>

// 原子地对 p 加一
#define atomic_inc(p) (p)++

// 全局静态变量，分别存储调用分配内存和释放内存的次数
static atomic_int s_alloc_count = (0);
static atomic_int s_free_count = (0);

// 获取调用内存分配的次数
long mc_malloc_count()
{
    return (long)(s_alloc_count);
}
// 获取调用内存释放的次数
long mc_free_count()
{
    return (long)(s_free_count);
}

void* mc_memset(void* ptr, int c, size_t size)
{
    if (NULL == ptr || size < 0) return NULL;
    char* tmp_str = (char*)ptr;
    while (size-- > 0){
        *tmp_str++ = c;
    }
    return ptr;
}

void* mc_malloc(size_t size)
{
    atomic_inc(s_alloc_count);
    void* ptr = malloc(size);
    if (!ptr){
        LOGE("malloc error -- is a null pointer");
        exit(-1);
    }
    return ptr;
}

void* mc_realloc(void** ptr, size_t old_size, size_t new_size)
{
    if (*ptr != NULL) atomic_inc(s_free_count);
    void* p = realloc(*ptr, new_size);
    *ptr = NULL;
    if (!p){
        LOGE("realloc error -- is a null pointer!");
        exit(-1);
    }
    atomic_inc(s_alloc_count);
    if (new_size > old_size){
        mc_memset((char *) p + old_size, 0, new_size - old_size);
    }
    return p;
}

void* mc_calloc(size_t nme_size, size_t size)
{
    atomic_inc(s_alloc_count);
    void* ptr = calloc(nme_size, size);
    if (!ptr){
        LOGE("calloc error -- is a null pointer");
        exit(-1);
    }
    return ptr;
}

void* mc_zalloc(size_t size)
{
    atomic_inc(s_alloc_count);
    void* ptr = malloc(size);
    if (!ptr){
        LOGE("zalloc error -- is a null pointer");
        exit(-1);
    }
    mc_memset(ptr, 0, size);
    return ptr;
}

void mc_free(void** ptr)
{
    if (*ptr != NULL){
        free(*ptr);
        atomic_inc(s_free_count);
    }
    *ptr = NULL;
}


