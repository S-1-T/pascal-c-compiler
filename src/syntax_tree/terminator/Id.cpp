//
// Created by RinChanNOW! on 2020/5/20.
//
#include "symbol_sheet.h"

#include <string>

class Id {
public:
    Id() = default;

    std::string outputCodes();

    Symbol::TYPE mType = Symbol::VOID;
    Symbol::Name mName;

};

