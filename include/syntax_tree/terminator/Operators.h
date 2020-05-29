//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_OPERATORS_H
#define PASCAL_C_COMPILER_OPERATORS_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>

class AssignOp {
public:
    AssignOp() = default;
    AssignOp(Variable *variable, Expression *expression): mVariable(variable), mExpression(expression) {}

    std::string outputCodes() const;

    Variable *mVariable = nullptr;
    Expression *mExpression = nullptr;
};

class RelOp {
public:
    enum RelType { ERR, EQ, GT, LT, GE, LE };

    RelOp() = default;
    RelOp(SimpleExpression *s1, RelType relType, SimpleExpression *s2):
            mSimpleExpression1(s1), mRelType(relType), mSimpleExpression2(s2) {}

    std::string outputCodes() const;

    RelType mRelType = ERR;
    SimpleExpression *mSimpleExpression1 = nullptr;
    SimpleExpression *mSimpleExpression2 = nullptr;
};

class AddOp {
public:
    enum AddType { ERR, PLUS, SUB, OR };

    AddOp() = default;
    AddOp(SimpleExpression *simpleExpression, AddType addType, Term *term):
            mSimpleExpression(simpleExpression), mAddType(addType), mTerm(term) {}

    std::string outputCodes() const;

    AddType mAddType = ERR;
    SimpleExpression *mSimpleExpression = nullptr;
    Term *mTerm = nullptr;
};

class MulOp {
public:
    enum MulType { ERR, MUL, DIV, MOD, AND };

    MulOp() = default;
    MulOp(Term *term, MulType mulType, Factor *factor):
            mTerm(term), mMulType(mulType), mFactor(factor) {}

    std::string outputCodes() const;

    MulType mMulType = ERR;
    Term *mTerm = nullptr;
    Factor* mFactor = nullptr;
};

#endif //PASCAL_C_COMPILER_OPERATORS_H
