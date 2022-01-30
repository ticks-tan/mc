/**
* @Author : Ticks
* @File   : mc_log.h
* @Date   : 2022-01-30 下午6:58
* @Email  : 2938384958@qq.com
* @Des    : 日志实现
**/

#ifndef MC_MC_LOG_H
#define MC_MC_LOG_H

#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
// 对应linux控制台前景颜色，也就是字体颜色

// 黑色
#define _CONSOLE_COLOR_BLACK_START_     printf("\033[30m");
// 红色
#define _CONSOLE_COLOR_RED_START_       printf("\033[31m");
// 绿色
#define _CONSOLE_COLOR_GREEN_START_     printf("\033[32m");
// 黄色
#define _CONSOLE_COLOR_YELL_START_      printf("\033[33m");
// 蓝色
#define _CONSOLE_COLOR_BLUE_START_      printf("\033[34m");
// 紫色
#define _CONSOLE_COLOR_PUR_START_       printf("\033[35m");
// 白色
#define _CONSOLE_COLOR_WHITE_START_     printf("\033[37m");

// 还原控制台颜色设置
#define _CONSOLE_COLOR_END              printf("\033[0m");
#endif

// 日志级别
typedef enum Log_Level
{
    None = 1,
    Info,
    Debug,
    Warn,
    Error,
}Log_Level;

// 日志记录器
typedef struct
{
    FILE* fp;
    Log_Level level;
}File_Logger;

// 获取默认的文件日志器
File_Logger* get_default_logger();
#define default_logger     get_default_logger()

// 设置日志记录器路径
int set_logger_path(File_Logger* logger, const char* path);
// 设置日志记录器过滤级别
int set_logger_level(File_Logger* logger, Log_Level level);

#define set_default_logger_path(path)       set_logger_path(default_logger, path)
#define set_default_logger_level(level)     set_logger_level(default_logger, level)

// 打印日志到控制台
void log_print(Log_Level level, const char* str, ...);
// 打印日志到文件
void file_log_print(File_Logger* logger, Log_Level level,  const char* str, ...);

// 更详细的日志输出，有对应文件名、函数、行数和时间
#define LOGI(str)   log_print(Info, "Info -> in function [%s] at [%s:%d] : %s \n", __func__, __FILE__, __LINE__ ,str)
#define LOGD(str)   log_print(Debug, "Debug -> in function [%s] at [%s:%d] : %s \n", __func__, __FILE__, __LINE__ , str)
#define LOGW(str)   log_print(Warn, "Warn -> in function [%s] at [%s:%d] : %s \n", __func__, __FILE__, __LINE__ , str)
#define LOGE(str)   log_print(Error, "Error -> in function [%s] at [%s:%d] : %s \n", __func__, __FILE__, __LINE__ , str)

// 更详细的文件日志记录，使用默认的日志记录器
#define FLOGI(str)  file_log_print(default_logger, Info, "Info -> in [%s] at [%s:%d] : %s  [%s %s]\n", __func__, __FILE__, __LINE__, str, __DATE__, __TIME__)
#define FLOGD(str)  file_log_print(default_logger, Debug, "Debug -> in [%s] at [%s:%d] : %s  [%s %s]\n", __func__, __FILE__, __LINE__, str, __DATE__, __TIME__)
#define FLOGW(str)  file_log_print(default_logger, Warn, "Warn -> in [%s] at [%s:%d] : %s  [%s %s]\n", __func__, __FILE__, __LINE__, str, __DATE__, __TIME__)
#define FLOGE(str)  file_log_print(default_logger, Error, "Error -> in [%s] at [%s:%d] : %s  [%s %s]\n", __func__, __FILE__, __LINE__, str, __DATE__, __TIME__)



#endif //MC_MC_LOG_H
