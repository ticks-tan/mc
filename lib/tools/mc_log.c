/**
* @Author : Ticks
* @File   : mc_log.c
* @Date   : 2022-01-30 下午7:02
* @Email  : 2938384958@qq.com
* @Des    : 日志实现
**/

#include <stdarg.h>
#include "mc_log.h"

static int is_init_logger = 0;

#ifdef _WIN32
struct Win_Console_Handle
{
    HANDLE handle;
    WORD  attr;
};

struct Win_Console_Handle win_init_console_color();
void win_start_console_color(HANDLE handle, unsigned short color);
void win_finish_console_color(struct Win_Console_Handle handle);

#endif

void log_print(Log_Level level, const char* str, ...) {
#ifdef _WIN32
    struct Win_Console_Handle handle = win_init_console_color();
    if (handle.handle) {
        switch (level) {
			case Info:
				win_start_console_color(handle.handle, FOREGROUND_BLUE);
                break;
            case Debug:
                win_start_console_color(handle.handle, FOREGROUND_GREEN);
                break;
            case Warn:
                win_start_console_color(handle.handle, FOREGROUND_RED| FOREGROUND_GREEN);
                break;
            case Error:
                win_start_console_color(handle.handle, FOREGROUND_RED);
                break;
            default:
                break;
        }
    }
#endif
#ifdef __linux__
    switch (level) {
        case None:  _CONSOLE_COLOR_WHITE_START_     break;
        case Info:  _CONSOLE_COLOR_BLUE_START_      break;
        case Debug: _CONSOLE_COLOR_GREEN_START_     break;
        case Warn:  _CONSOLE_COLOR_YELL_START_      break;
        case Error: _CONSOLE_COLOR_RED_START_       break;
        default:    break;
    }
#endif
    va_list args;
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
#ifdef _WIN32
    if (handle.handle) {
        win_finish_console_color(handle);
    }
#endif

#ifdef __linux__
    _CONSOLE_COLOR_END
#endif

}

#ifdef _WIN32

struct Win_Console_Handle win_init_console_color()
{
    struct Win_Console_Handle h;
    h.handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(h.handle, &info);
    h.attr = info.wAttributes;
    return h;
}

void win_start_console_color(HANDLE handle ,unsigned short color)
{
    SetConsoleTextAttribute(handle, color);
}

void win_finish_console_color(struct Win_Console_Handle handle)
{
    SetConsoleTextAttribute(handle.handle, handle.attr);
}

#endif


File_Logger* get_default_logger()
{
    static File_Logger static_file_logger;
    if (0 == is_init_logger)
    {
        static_file_logger.fp = NULL;
        static_file_logger.level = Info;
        is_init_logger = 1;
    }
    return &static_file_logger;
}


// 打印日志到文件
void file_log_print(File_Logger* logger, Log_Level level, const char* str, ...)
{
    if (level >= logger->level)
    {
        if (NULL == logger->fp)
        {
            logger->fp = fopen("log.txt", "a+");
            if (NULL == logger->fp)
            {
                return;
            }
        }
        va_list args;
        va_start(args, str);
        vfprintf(logger->fp, str, args);
        va_end(args);
        fflush(logger->fp);
    }
}


// 设置默认日志记录器路径
int set_logger_path(File_Logger* logger, const char* path)
{
    if (NULL != path) {
        if (logger)
        {
            if (logger->fp)
            {
                fclose(logger->fp);
            }
            logger->fp = fopen(path, "a+");
            return (NULL != logger->fp) ? 1 : 0;
        }
    }
    return 0;
}
// 设置默认日志记录器过滤级别
int set_logger_level(File_Logger* logger, Log_Level level)
{
    if (logger)
    {
        logger->level = level;
        return 1;
    }
    return 0;
}

