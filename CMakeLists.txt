cmake_minimum_required(VERSION 3.16)
project(pascal-c-compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

aux_source_directory(src src_dir)
aux_source_directory(src/codes_generator codes_generator_dir)
aux_source_directory(src/debug debug_dir)
aux_source_directory(src/semantic_analyser semantic_analyser_dir)

SET(compiler ${src_dir})
SET(codes_generator ${codes_generator_dir})
SET(debug ${debug_dir})
SET(semantic_analyser ${semantic_analyser_dir} include/semantic_analyser/symbol_sheet.h src/semantic_analyser/symbol_sheet.cpp)

add_executable(pascal_c_compiler
        ${compiler}
        ${codes_generator}
        ${debug}
        ${semantic_analyser} include/defines/const.h include/defines/types.h)
