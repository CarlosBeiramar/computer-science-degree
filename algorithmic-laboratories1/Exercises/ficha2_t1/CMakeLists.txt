cmake_minimum_required(VERSION 3.13)
project(ficha2_t1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ficha2_t1
        4blocos.c
        funções.h
        main.c
        menu.c
        NIB.c)
