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

    std::string outputCodes() const;
    ConstVariable operator-(ConstVariable &c) const {
        ConstVariable result;
        if (mType == c.mType) {
            switch (mType) {
                case Symbol::INT:
                    result.mValue.intValue = mValue.intValue - c.mValue.intValue;
                    result.mType = Symbol::INT;
                    break;
                case Symbol::CHAR:
                    result.mValue.intValue = (int)(mValue.charValue - c.mValue.charValue);
                    result.mType = Symbol::CHAR;
                    break;
                default:
                    break;
            }
        }
        return result;
    }

    Id *mId = nullptr;
    Symbol::TYPE mType = Symbol::VOID;
    Symbol::Value mValue{0};
    bool isNegative = false;
//    bool isId = false;

    int mLineNo = 0;
};


#endif //PASCAL_C_COMPILER_CONSTVARIABLE_H
