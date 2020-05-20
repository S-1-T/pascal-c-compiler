cmake_minimum_required(VERSION 3.16)
project(pascal_c_compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(pascal_c_compiler
        src/codes_generator/codes_generator.cpp src/symbol_sheet/symbol_sheet.cpp include/syntax_tree.h include/symbol_sheet.h src/syntax_tree/non_terminator/Program.cpp src/syntax_tree/non_terminator/Statements.cpp src/syntax_tree/non_terminator/ConstDeclarations.cpp src/syntax_tree/non_terminator/ConstVariable.cpp src/syntax_tree/non_terminator/VarDeclarations.cpp src/syntax_tree/non_terminator/SubProgram.cpp src/syntax_tree/non_terminator/Parameters.cpp src/syntax_tree/non_terminator/IdentifierList.cpp src/syntax_tree/non_terminator/Type.cpp src/syntax_tree/non_terminator/Periods.cpp src/syntax_tree/non_terminator/Expression.cpp src/syntax_tree/non_terminator/Variable.cpp src/syntax_tree/non_terminator/Term.cpp src/syntax_tree/non_terminator/Factor.cpp src/syntax_tree/terminator/Id.cpp src/syntax_tree/terminator/Not.cpp src/syntax_tree/terminator/ControlStatements.cpp src/syntax_tree/terminator/Operators.cpp)
