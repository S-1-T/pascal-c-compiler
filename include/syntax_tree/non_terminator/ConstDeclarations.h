//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_CONSTDECLARATIONS_H
#define PASCAL_C_COMPILER_CONSTDECLARATIONS_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>
#include <vector>


typedef std::vector<std::pair<Id *, ConstVariable *> > ConstVariableList;

class ConstDeclarations {
public:
    ConstDeclarations() = default;
    explicit ConstDeclarations(ConstDeclaration *constDeclaration): mConstDeclaration(constDeclaration) {}

    std::string outputCodes();

    ConstDeclaration *mConstDeclaration = nullptr;
};

class ConstDeclaration {
public:
    ConstDeclaration() = default;
    explicit ConstDeclaration(ConstVariableList constVariables) { mConstVariables = std::move(constVariables); }

    std::string outputCodes();

    ConstVariableList mConstVariables;
};



#endif //PASCAL_C_COMPILER_CONSTDECLARATIONS_H
