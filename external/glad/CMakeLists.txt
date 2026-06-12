cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(glad VERSION 4.0.0 LANGUAGES C)

add_library(glad STATIC include/glad/glad.h include/KHR/khrplatform.h src/glad.c)

target_include_directories(glad PUBLIC include/)
