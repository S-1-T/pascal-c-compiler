//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_CONSTVARIABLE_H
#define PASCAL_C_COMPILER_CONSTVARIABLE_H

#include "syntax_tree/syntax_tree_nodes.h"
#include "symbol_sheet/symbol_sheet.h"

#include <string>

class ConstVariable {
public:
    ConstVariable() = default;
    explicit ConstVariable(Id *id): mType(Symbol::ID), mId(id) {}
    explicit ConstVariable(float num): mType(Symbol::REAL) { mValue.realValue = num; }
    explicit ConstVariable(char letter): mType(Symbol::CHAR) {mValue.charValue = letter; }

    std::string outputCodes();

    Id *mId = nullptr;
    Symbol::TYPE mType = Symbol::VOID;
    Symbol::Value mValue{0};
    bool isNegative = false;
//    bool isId = false;

    int mLineNo = 0;
};


#endif //PASCAL_C_COMPILER_CONSTVARIABLE_H
