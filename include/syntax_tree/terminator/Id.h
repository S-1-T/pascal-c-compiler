//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_ID_H
#define PASCAL_C_COMPILER_ID_H

#include "symbol_sheet/symbol_sheet.h"

#include <string>

class Id {
public:
    Id() = default;

    std::string outputCodes();

    bool isVarInProc = false;   // 引用调用
    Symbol::TYPE mType = Symbol::VOID;
    Symbol::Name mName;

};

#endif //PASCAL_C_COMPILER_ID_H
