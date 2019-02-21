cmake_minimum_required(VERSION 3.10)
project(wf C)

set(CMAKE_C_STANDARD 99)

add_executable(wf main.c reader.c reader.c word.c word.h dict.c)