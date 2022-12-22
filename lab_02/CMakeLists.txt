cmake_minimum_required(VERSION 3.23)
project(lab_02 C)

set(CMAKE_C_STANDARD 99)
include_directories(inc src)

SET(CFLAGS "-Wall -Werror -Wextra -O0 -g3 -pedantic")
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${CFlAGS}")

add_executable(app.exe
        inc/data_types.h
        inc/constants.h
        src/load_data.c
        inc/load_data.h
        src/table.c
        inc/table.h
        src/sort.c
        inc/sort.h
        src/measurements.c
        inc/measurements.h
        src/io.c
        inc/io.h
        src/read.c
        inc/read.h
        src/menu.c
        inc/menu.h
        src/main.c)
