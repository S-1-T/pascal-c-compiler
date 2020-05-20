//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"

#include <string>

class Type {
public:
    Type() = default;
    explicit Type(Periods *periods): isStandardType(false), mPeriods(periods) {}

    std::string outputCodes();

    bool isStandardType = true;
    Periods *mPeriods = nullptr;
};
