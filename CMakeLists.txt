cmake_minimum_required(VERSION 3.21)
project(mc C)

set(CMAKE_C_STANDARD 11)

include_directories(lib)

add_executable(mc main.c
        lib/tools/mc_malloc.h   lib/tools/mc_malloc.c
        lib/tools/mc_log.h      lib/tools/mc_log.c
        lib/list/forward_list.h lib/list/forward_list.c
        lib/list/list.h         lib/list/list.c
        lib/queue/queue.h       lib/queue/queue.c
        lib/stack/stack.h       lib/stack/stack.c
        lib/map/map.h lib/map/map.c lib/set/set.h lib/set/set.c)
