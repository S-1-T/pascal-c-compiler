//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_FACTOR_H
#define PASCAL_C_COMPILER_FACTOR_H

#include "syntax_tree/syntax_tree_nodes.h"
#include "symbol_sheet/symbol_sheet.h"

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
    explicit Factor(Factor *factor): mFactorType(NOT), mFactor(factor) {}

    std::string outputCodes();

    FactorType mFactorType = ERR;
    Id *mId = nullptr;
    ConstVariable *mConstValue = nullptr;
    Variable *mVariable = nullptr;
    ExpressionList *mExpressionList = nullptr;
    Expression *mExpression = nullptr;
    Factor *mFactor = nullptr;
};


#endif //PASCAL_C_COMPILER_FACTOR_H
