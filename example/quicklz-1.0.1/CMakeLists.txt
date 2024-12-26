cmake_minimum_required(VERSION 3.0)

project(quicklz)

add_library(${QUICKLZ_LIB} STATIC quicklz.c)

target_include_directories(${QUICKLZ_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
