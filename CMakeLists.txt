cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(philosophers
        main.c
        philosophers.h utils.c utils.h)
