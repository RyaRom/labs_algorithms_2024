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
        src/collections/CircularLinkedList.h
        src/collections/List.c
        src/collections/List.h
        src/utils/Scanner.c
        src/utils/Scanner.h
        src/collections/AbstractList.c
        src/collections/AbstractList.h
        src/lab3.c
        src/collections/Stack.c
        src/collections/Stack.h
        src/collections/queue.c
        src/collections/queue.h)
