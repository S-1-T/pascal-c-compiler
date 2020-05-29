//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_TYPE_H
#define PASCAL_C_COMPILER_TYPE_H

#include "syntax_tree/syntax_tree_nodes.h"
#include "symbol_sheet/symbol_sheet.h"

#include <string>

class Type {
public:
    Type() = default;
    Type(Symbol::TYPE type, Periods *periods): mType(type), isStandardType(false), mPeriods(periods) {}
    explicit Type(Symbol::TYPE type): mType(type), isStandardType(true) {}

    std::string outputCodes() const;

    bool isStandardType = true;
    Symbol::TYPE mType;
    Periods *mPeriods = nullptr;
};

#endif //PASCAL_C_COMPILER_TYPE_H
