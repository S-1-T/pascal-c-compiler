//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"

#include <string>
#include <vector>

typedef std::vector<IdVarPart *> IdVarPartList;

class Variable {
public:
    Variable() = default;
    Variable(Id *id, IdVarParts *idVarParts): mId(id), mIdVarParts(idVarParts) {}

    std::string outputCodes();

    Id *mId = nullptr;
    IdVarParts * mIdVarParts = nullptr;
};

class IdVarParts {
public:
    IdVarParts() = default;
    explicit IdVarParts(IdVarPartList idVarPartList) { mIdVarPartList = std::move(idVarPartList) }

    std::string outputCodes();

    IdVarPartList mIdVarPartList;

};

class IdVarPart {
public:
    IdVarPart() = default;
    explicit IdVarPart(ExpressionList *expressionList): mExpressionList(expressionList) {}

    std::string outputCodes();

    ExpressionList *mExpressionList = nullptr;
};