cmake_minimum_required(VERSION 3.21)
project(mc C)

set(CMAKE_C_STANDARD 11)

include_directories(lib)

add_executable(mc main.c
        lib/tools/mc_malloc.h   lib/tools/mc_malloc.c
        lib/tools/mc_log.h      lib/tools/mc_log.c
        lib/list/single_list.h  lib/list/single_list.c)
