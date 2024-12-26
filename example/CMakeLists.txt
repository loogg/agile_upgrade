cmake_minimum_required(VERSION 3.0)

project(example)

set(LIB_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(EXEC_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(FASTLZ_LIB fastlz)
set(QUICKLZ_LIB quicklz)
set(CRYPT_LIB crypt)
set(UPGRADE_LIB upgrade)

option(AGILE_UPGRADE_ENABLE_VERSION_COMPARE "Enable version compare" ON)
option(AGILE_UPGRADE_ENABLE_LOG "Enable log" ON)

option(AGILE_UPGRADE_ENABLE_AES "Enable AES support" ON)

if(AGILE_UPGRADE_ENABLE_AES)
    set(AGILE_UPGRADE_AES_IV "0123456789ABCDEF" CACHE STRING "AES IV")
    set(AGILE_UPGRADE_AES_KEY "0123456789ABCDEF0123456789ABCDEF" CACHE STRING "AES Key")
    mark_as_advanced(CLEAR AGILE_UPGRADE_AES_IV AGILE_UPGRADE_AES_KEY)
else()
    mark_as_advanced(FORCE AGILE_UPGRADE_AES_IV AGILE_UPGRADE_AES_KEY)
endif()

option(AGILE_UPGRADE_ENABLE_FASTLZ "Enable fastlz" ON)
option(AGILE_UPGRADE_ENABLE_QUICKLZ "Enable quicklz" ON)

configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/common.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/include/common.h"
  )

set(LIBRARY_OUTPUT_PATH ${LIB_PATH})

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

file (COPY tools/app.rbl DESTINATION ${EXEC_PATH})

if (AGILE_UPGRADE_ENABLE_AES)
    add_subdirectory(tinycrypt-1.1.0)
    set(EXTRA_LIBS ${EXTRA_LIBS} ${CRYPT_LIB})
endif()

if (AGILE_UPGRADE_ENABLE_FASTLZ)
    add_subdirectory(fastlz-1.0.1)
    set(EXTRA_LIBS ${EXTRA_LIBS} ${FASTLZ_LIB})
endif()

if (AGILE_UPGRADE_ENABLE_QUICKLZ)
    add_subdirectory(quicklz-1.0.1)
    set(EXTRA_LIBS ${EXTRA_LIBS} ${QUICKLZ_LIB})
endif()

link_directories(${LIB_PATH})
link_libraries(${EXTRA_LIBS})
file (GLOB UPGRADE_SRCS ../src/*.c ../adapter/*.c)
add_library(${UPGRADE_LIB} STATIC ${UPGRADE_SRCS})
target_include_directories(${UPGRADE_LIB} PRIVATE ../inc inc)
set(EXTRA_LIBS ${EXTRA_LIBS} ${UPGRADE_LIB})

set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH})
link_libraries(${EXTRA_LIBS})
file (GLOB SRCS src/*.c)
add_executable(demo ${SRCS})
target_include_directories(demo PRIVATE ../inc)

enable_testing()

add_test (test_usage ${EXEC_PATH}/demo)
set_tests_properties (test_usage
  PROPERTIES PASS_REGULAR_EXPRESSION "Usage: .*")

add_test (test_run ${EXEC_PATH}/demo ${EXEC_PATH}/app.rbl ${EXEC_PATH}/app.bin)
