//
// Created by RinChanNOW! on 2020/5/19.
//
#include "symbol_sheet/symbol_sheet.h"

#include <iostream>
#include <utility>

SymbolSheet::SymbolSheet(Symbol::Name sheetName) {
    mSheetName = std::move(sheetName);
    addReservedSymbol();
}

bool SymbolSheet::lookUp(const Symbol::Name& symbolName) {
    return mSheet.find(symbolName) != mSheet.end();
}

Symbol::TYPE SymbolSheet::getType(const Symbol::Name& symbolName) {
    return mSheet[symbolName].type;
}

Symbol::TYPE SymbolSheet::getReturnType(const Symbol::Name& symbolName) {
    return mSheet[symbolName].returnType;
}

int SymbolSheet::getArgumentsNum(const Symbol::Name& symbolName) {
    return mSheet[symbolName].argumentsNum;
}

Symbol::ArgumentsTypes SymbolSheet::getArgumentsTypes(const Symbol::Name& symbolName) {
    return mSheet[symbolName].argumentsTypes;
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



