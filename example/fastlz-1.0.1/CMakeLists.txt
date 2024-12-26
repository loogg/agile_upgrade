cmake_minimum_required(VERSION 3.0)

project(fastlz)

add_library(${FASTLZ_LIB} STATIC fastlz.c)

target_include_directories(${FASTLZ_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
