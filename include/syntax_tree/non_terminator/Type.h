//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_TYPE_H
#define PASCAL_C_COMPILER_TYPE_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>

class Type {
public:
    Type() = default;
    explicit Type(Periods *periods): isStandardType(false), mPeriods(periods) {}

    std::string outputCodes();

    bool isStandardType = true;
    Periods *mPeriods = nullptr;
};

#endif //PASCAL_C_COMPILER_TYPE_H
