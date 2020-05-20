//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"
#include "symbol_sheet.h"

#include <string>

class Factor {
public:
    enum FactorType { ERR, CONST_VAR, VAR, FUNC_CALL, EXPR, NOT };

    Factor() = default;
    // 这里需要只能接受非负
    explicit Factor(ConstVariable *constVariable): mFactorType(CONST_VAR), mConstValue(constVariable) {}
    explicit Factor(Variable *variable): mFactorType(VAR), mVariable(variable) {}
    explicit Factor(ExpressionList *expressionList): mFactorType(FUNC_CALL), mExpressionList(expressionList) {}
    explicit Factor(Expression *expression): mFactorType(EXPR), mExpression(expression) {}
    explicit Factor(Not *n): mFactorType(NOT), mNot(n) {}

    std::string outputCodes();

    FactorType mFactorType = ERR;
    Id *mId = nullptr;
    ConstVariable *mConstValue = nullptr;
    Variable *mVariable = nullptr;
    ExpressionList *mExpressionList = nullptr;
    Expression *mExpression = nullptr;
    Not *mNot = nullptr;
};
