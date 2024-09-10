cmake_minimum_required(VERSION 3.29)
project(Suai_labs_algorithms_2024 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(Suai_labs_algorithms_2024
        src/lab1.c
        src/lab2.c
        src/main.c
        src/collections/CircularLinkedList.c
        src/collections/CircularLinkedList.h)
