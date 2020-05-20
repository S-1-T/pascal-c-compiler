//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"
#include "symbol_sheet.h"

#include <string>

class ConstVariable {
public:
    ConstVariable() = default;
    explicit ConstVariable(Symbol::TYPE type): mType(type) {}

    std::string outputCodes();

    Id *mId = nullptr;
    Symbol::TYPE mType = Symbol::VOID;
    Symbol::Value mValue{0};
    bool isNegative = false;
    bool isId = false;

    int mLineNo = 0;
};
