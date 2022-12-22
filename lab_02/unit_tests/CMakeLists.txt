cmake_minimum_required(VERSION 3.21)
project(lab_07_1_3_checks C)

set(CMAKE_C_STANDARD 99)
include_directories(../inc)

add_executable(lab_07_1_3_checks
        check_main.c
        check_array.c
        check_file.c
        check_sort.c)