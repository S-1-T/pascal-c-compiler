//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"

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