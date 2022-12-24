cmake_minimum_required(VERSION 3.23)
project(lab_08 C)

set(CMAKE_C_STANDARD 99)
include_directories(inc src)

add_executable(
        app.exe

        src/main.c
        src/graph.c
        src/menu.c
        src/io.c
        src/measurements.c

        inc/io.h
        inc/menu.h
        inc/constants.h
        inc/graph.h
        inc/data_types.h
        inc/measurements.h
        )
