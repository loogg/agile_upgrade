cmake_minimum_required(VERSION 3.0)

project(tinycrypt)

file (GLOB SRCS "src/*.c")

add_library(${CRYPT_LIB} STATIC ${SRCS})

target_include_directories(${CRYPT_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
