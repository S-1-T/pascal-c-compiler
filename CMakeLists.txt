cmake_minimum_required(VERSION 3.16)
project(pascal_c_compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(pascal_c_compiler
        include/symbol_sheet.h
        src/code_generator/genertor.cpp src/symbol_sheet/symbol_sheet.cpp)
