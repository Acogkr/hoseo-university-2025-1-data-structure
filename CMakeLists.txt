cmake_minimum_required(VERSION 3.10)
project(2025_1_ C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE C_FILES "${CMAKE_SOURCE_DIR}/*.c")

foreach(SRC ${C_FILES})
    get_filename_component(EXEC_NAME ${SRC} NAME_WE)
    add_executable(${EXEC_NAME} ${SRC})
endforeach()