//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"
#include "symbol_sheet.h"

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
    bool isId = false;

    int mLineNo = 0;
};
