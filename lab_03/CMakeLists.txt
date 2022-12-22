cmake_minimum_required(VERSION 3.23)
project(lab_03 C)

set(CMAKE_C_STANDARD 99)
include_directories(inc src)

add_executable(app.exe
        src/io.c
        src/menu.c
        src/load_mtr.c
        src/matrix_sparse.c
        src/matrix_standard.c
        src/measurements.c

        inc/constants.h
        inc/io.h
        inc/menu.h
        inc/data_types.h
        inc/load_mtr.h
        inc/matrix_sparse.h
        inc/matrix_standard.h
        inc/measurements.h src/main.c)