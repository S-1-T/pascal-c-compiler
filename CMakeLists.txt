cmake_minimum_required(VERSION 3.16)
project(pascal_c_compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(pascal_c_compiler
        src/codes_generator/codes_generator.cpp src/symbol_sheet/symbol_sheet.cpp include/syntax_tree.h include/symbol_sheet.h src/syntax_tree/non_terminator/Program.cpp src/syntax_tree/non_terminator/ProgramBody.cpp src/syntax_tree/non_terminator/CompoundStatement.cpp src/syntax_tree/non_terminator/ConstDeclarations.cpp src/syntax_tree/non_terminator/ConstVariable.cpp src/syntax_tree/non_terminator/VarDeclarations.cpp src/syntax_tree/non_terminator/SubProgramDeclarations.cpp src/syntax_tree/non_terminator/Parameters.cpp)
