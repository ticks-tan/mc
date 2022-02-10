/**
* @Author : Ticks
* @File   : mc_malloc.h
* @Date   : 2022-01-30 下午6:57
* @Email  : 2938384958@qq.com
* @Des    : 封装 malloc.h 方法，函数功能同标准库 malloc.h
**/

#ifndef MC_MC_MALLOC_H
#define MC_MC_MALLOC_H

#include <stdlib.h>
#include "mc_log.h"

typedef unsigned int bool;
#define true 1
#define false 0

// 获取指针地址
#define PTR_ADDRESS(a)      (void**)(&(a))
// 指针是否为空
#define PTR_NULL(p)         (NULL == (p))
// 指针是否不为空
#define PTR_NOT_NULL(p)     (NULL != (p))
// 类型转换
#define TO_CAST(to_type, type)  ((to_type)(type))

// 错误输出
// #define LOGE(type) fprintf(stderr,"error in file: %s - %d line at %s ==> %s\n", __FILE__, __LINE__, __TIME__, type)
// 查看内存分配情况
#define Me_MemCheck() fprintf(stdout, "malloc count : %ld, free count : %ld\n", me_malloc_count(), me_free_count())

// 内存分配与释放次数
long mc_malloc_count();
long mc_free_count();

/**
 * 内存初始化
 * @param ptr   : 指针
 * @param c     : 初始化字符
 * @param size  : 内存大小(字节)
 * @return
 */
void* mc_memset(void* ptr, int c, size_t size);

/**
 * 分配内存,不会对内存初始化
 * @param size  : 要分配的内存大小
 * @return      : 成功返回对应内存，失败程序退出,同时有错误日志输出
 */
void* mc_malloc(size_t size);
void* mc_calloc(size_t nme_size, size_t size);

/**
 * 分配内存并自动初始化
 * @param size  : 要分配的内存大小
 * @return      : 成功返回对应内存，失败程序退出,同时有错误日志输出
 */
void* mc_zalloc(size_t size);

/**
 * 重新分配内存
 * @param ptr       : 要重新分配内存的地址
 * @param old_size  : 原来地址存储数据大小
 * @param new_size  : 新分配内存大小
 * @return          : 成功返回新分配内存地址，失败退出程序，同时输出日志
 */
void* mc_realloc(void** ptr, size_t old_size, size_t new_size);

/**
 * 释放内存
 * @param ptr   : 要释放的内存地址
 */
void mc_free(void** ptr);

#endif //MC_MC_MALLOC_H
