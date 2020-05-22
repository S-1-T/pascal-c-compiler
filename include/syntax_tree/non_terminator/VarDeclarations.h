//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_VARDECLARATIONS_H
#define PASCAL_C_COMPILER_VARDECLARATIONS_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>
#include <vector>

typedef std::vector<std::pair<IdentifierList *, Type *> > VariableList;

class VarDeclarations {
public:
    VarDeclarations() = default;
    explicit VarDeclarations(VarDeclaration *varDeclaration): mVarDeclaration(varDeclaration) {}

    std::string outputCodes();

    VarDeclaration *mVarDeclaration = nullptr;
};

class VarDeclaration {
public:
    VarDeclaration() = default;
    explicit VarDeclaration(VariableList variableList) { mVariableList = std::move(variableList); }

    std::string outputCodes();

    VariableList mVariableList;

};

#endif //PASCAL_C_COMPILER_VARDECLARATIONS_H
