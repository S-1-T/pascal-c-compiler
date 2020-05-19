//
// Created by RinChanNOW! on 2020/5/19.
//
#include "symbol_sheet.h"

#include <iostream>

SymbolSheet::SymbolSheet(Symbol::Name sheetName) {
    mSheetName = sheetName;
    addReservedSymbol();
}

bool SymbolSheet::lookUp(Symbol::Name symbolName) {
    return false;
}

Symbol::TYPE SymbolSheet::getType(Symbol::Name symbolName) {
    return Symbol::VOID;
}

Symbol::TYPE SymbolSheet::getReturnType(Symbol::Name) {
    return Symbol::VOID;
}

int SymbolSheet::getArgumentsNum(Symbol::Name symbolName) {
    return 0;
}

Symbol::ArgumentsTypes SymbolSheet::getArgumentsTypes(Symbol::Name symbolName) {
    return Symbol::ArgumentsTypes();
}

Symbol::Name SymbolSheet::getSheetName() {
    return mSheetName;
}

bool SymbolSheet::addReservedSymbol() {
    bool flag = true;
    for (auto keyword: Symbol::keywords) {
        Symbol::Property property;
        property.type = Symbol::RESERVED;
        property.value.realValue = 0;
        if (mSheet.insert(Symbol::SheetItem(keyword, property)).second)
            continue;
        else {
            std::cout << "Error occurs when adding reserved symbol \""
            << keyword
            << "\" into the symbol sheet \"" << mSheetName << "\"\n";
            flag = false;
            break;
        }
    }
    for (auto func: Symbol::lib_functions) {
        Symbol::Property property;
        property.type = Symbol::LIB_FUNC;
        property.value.realValue = 0;
        if (mSheet.insert(Symbol::SheetItem(func, property)).second)
            continue;
        else {
            std::cout << "Error occurs when adding library function \""
                      << func
                      << "\" into the symbol sheet \"" << mSheetName << "\"\n";
            flag = false;
            break;
        }
    }
    return flag;
}



