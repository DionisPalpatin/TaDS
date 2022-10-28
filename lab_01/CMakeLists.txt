cmake_minimum_required(VERSION 3.23)
project(app.exe C)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c99 -Werror -Wall -Wextra -pedantic -Wvla -Wfloat-conversion -Wfloat-equal")

include_directories(src inc)

add_executable(app.exe

        src/main.c
        src/input_output.c

        inc/input_output.h
        inc/constants.h
        inc/errors.h inc/structs.h)
