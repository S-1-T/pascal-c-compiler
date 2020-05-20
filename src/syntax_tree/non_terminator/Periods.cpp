//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"

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
