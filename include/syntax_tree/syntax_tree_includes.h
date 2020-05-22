//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_SYNTAX_TREE_INCLUDES_H
#define PASCAL_C_COMPILER_SYNTAX_TREE_INCLUDES_H

// 非终结符
#include "syntax_tree/non_terminator/ConstDeclarations.h"
#include "syntax_tree/non_terminator/ConstVariable.h"
#include "syntax_tree/non_terminator/Factor.h"
#include "syntax_tree/non_terminator/IdentifierList.h"
#include "syntax_tree/non_terminator/Parameters.h"
#include "syntax_tree/non_terminator/Periods.h"
#include "syntax_tree/non_terminator/Program.h"
#include "syntax_tree/non_terminator/Statements.h"
#include "syntax_tree/non_terminator/SubProgram.h"
#include "syntax_tree/non_terminator/Term.h"
#include "syntax_tree/non_terminator/Type.h"
#include "syntax_tree/non_terminator/VarDeclarations.h"
#include "syntax_tree/non_terminator/Variable.h"

// 终结符
#include "syntax_tree/terminator/ControlStatements.h"
#include "syntax_tree/terminator/Id.h"
#include "syntax_tree/terminator/Operators.h"

#endif //PASCAL_C_COMPILER_SYNTAX_TREE_INCLUDES_H
