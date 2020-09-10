cmake_minimum_required(VERSION 3.16)
project(pascal-c-compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

aux_source_directory(src DIR_SRCS)
aux_source_directory(src/codes_generator codes_generator_dir)
aux_source_directory(src/semantic_analyser semantic_analyser_dir)

SET(compiler ${DIR_SRCS})
SET(codes_generator ${codes_generator_dir})
SET(semantic_analyser ${semantic_analyser_dir})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

add_compile_options(-Wno-deprecated)

add_executable(pascal_c_compiler
        ${compiler}
        ${codes_generator}
        ${semantic_analyser})
