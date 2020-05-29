cmake_minimum_required(VERSION 3.16)
project(pascal_c_compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(pascal_c_compiler
        src/codes_generator/codes_generator.cpp
        src/symbol_sheet/symbol_sheet.cpp
        include/symbol_sheet/symbol_sheet.h
        include/syntax_tree/syntax_tree_nodes.h include/syntax_tree/non_terminator/ConstDeclarations.h include/syntax_tree/non_terminator/ConstVariable.h include/syntax_tree/non_terminator/Expression.h include/syntax_tree/non_terminator/Factor.h include/syntax_tree/non_terminator/IdentifierList.h include/syntax_tree/non_terminator/Parameters.h include/syntax_tree/non_terminator/Periods.h include/syntax_tree/non_terminator/Program.h include/syntax_tree/non_terminator/Statements.h include/syntax_tree/non_terminator/SubProgram.h include/syntax_tree/non_terminator/Term.h include/syntax_tree/non_terminator/Type.h include/syntax_tree/non_terminator/VarDeclarations.h include/syntax_tree/non_terminator/Variable.h include/syntax_tree/terminator/ControlStatements.h include/syntax_tree/terminator/Id.h include/syntax_tree/terminator/Operators.h include/syntax_tree/syntax_tree_includes.h include/syntax_tree/non_terminator/TypeDeclarations.h)
