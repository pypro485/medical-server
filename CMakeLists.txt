cmake_minimum_required(VERSION 4.3)
project(medical_server C)

set(CMAKE_C_STANDARD 17)

add_executable(medical_server main.c
        sockets.c
        sockets.h
        sockets.h)
