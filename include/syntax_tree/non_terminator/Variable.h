//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_VARIABLE_H
#define PASCAL_C_COMPILER_VARIABLE_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>
#include <vector>

typedef std::vector<IdVarPart *> IdVarPartList;

class Variable {
public:
    Variable() = default;
    Variable(Id *id, IdVarParts *idVarParts): mId(id), mIdVarParts(idVarParts) {}

    std::string outputCodes() const;

    Id *mId = nullptr;
    IdVarParts * mIdVarParts = nullptr;
};

class IdVarParts {
public:
    IdVarParts() = default;
    explicit IdVarParts(IdVarPartList idVarPartList) { mIdVarPartList = std::move(idVarPartList); }

    std::string outputCodes();

    IdVarPartList mIdVarPartList;

};

class IdVarPart {
public:
    IdVarPart() = default;
    explicit IdVarPart(ExpressionList *expressionList): mExpressionList(expressionList) {}

    std::string outputCodes() const;

    ExpressionList *mExpressionList = nullptr;
};

#endif //PASCAL_C_COMPILER_VARIABLE_H
