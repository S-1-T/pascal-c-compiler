//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_PERIODS_H
#define PASCAL_C_COMPILER_PERIODS_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>
#include <vector>

typedef std::vector<Period> PeriodList;

class Periods {
public:
    Periods() = default;
    explicit Periods(PeriodList periodList) { mPeriodList = std::move(periodList); }

    std::string outputCode();

    PeriodList mPeriodList;
};

class Period {
public:
    Period() = default;
    Period(ConstVariable *v1, ConstVariable *v2): first(v1), second(v2) {}

    std::string outputCodes();

    ConstVariable *first = nullptr;
    ConstVariable *second = nullptr;
};


#endif //PASCAL_C_COMPILER_PERIODS_H
