//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_EXPRESSION_H
#define PASCAL_C_COMPILER_EXPRESSION_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>
#include <vector>

typedef std::vector<Expression *> Expressions;

class ExpressionList {
public:
    ExpressionList() = default;
    explicit ExpressionList(Expressions expressions) { mExpressions = std::move(expressions); }

    std::string outputCodes();

    Expressions mExpressions;
};

class Expression {
public:
    Expression() = default;
    explicit Expression(SimpleExpression *simpleExpression): isRelOp(false), mSimpleExpression(simpleExpression) {}
    explicit Expression(RelOp *relOp): isRelOp(true), mRelOp(relOp) {}

    std::string outputCodes();

    bool isRelOp = false;
    SimpleExpression *mSimpleExpression = nullptr;
    RelOp *mRelOp = nullptr;
};

class SimpleExpression {
public:
    SimpleExpression() = default;
    SimpleExpression(bool sign, Term *term): isSigned(sign), isAddOp(false), mTerm(term) {}
    SimpleExpression(bool sign, AddOp *addOp): isSigned(sign), isAddOp(true), mAddOp(addOp) {}

    std::string outputCodes();

    bool isSigned = false;
    bool isAddOp = false;
    Term *mTerm = nullptr;
    AddOp *mAddOp = nullptr;
};

#endif //PASCAL_C_COMPILER_EXPRESSION_H
