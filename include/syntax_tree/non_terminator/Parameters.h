//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_PARAMETERS_H
#define PASCAL_C_COMPILER_PARAMETERS_H

#include "syntax_tree/syntax_tree_nodes.h"
#include "symbol_sheet/symbol_sheet.h"

#include <string>
#include <vector>

typedef std::vector<Parameter *> ParameterList;

class FormalParameter {
public:
    FormalParameter() = default;
    explicit FormalParameter(ParameterLists *parameterLists): mParameterLists(parameterLists) {}

    std::string outputCodes();

    ParameterLists *mParameterLists = nullptr;
};

class ParameterLists {
public:
    ParameterLists() = default;
    explicit ParameterLists(ParameterList parameterList) {
        mParameterList = std::move(parameterList);
    }

    std::string outputCodes();

    ParameterList mParameterList;
};

class Parameter {
public:
    Parameter() = default;
    explicit Parameter(VarParameter *varParameter): isVar(true), mVarParameter(varParameter) {}
    explicit Parameter(ValueParameter *valueParameter): isVar(false), mValueParameter(valueParameter) {}

    std::string outputCodes();

    bool isVar = false;
    VarParameter *mVarParameter = nullptr;
    ValueParameter *mValueParameter = nullptr;
};

class VarParameter {
public:
    VarParameter() = default;
    explicit VarParameter(ValueParameter *valueParameter): mValueParameter(valueParameter) {}

    std::string outputCodes();

    ValueParameter *mValueParameter;
};

class ValueParameter {
public:
    ValueParameter() = default;
    ValueParameter(Symbol::TYPE type, IdentifierList *identifierList):
            mReturnType(type), mIdentifierList(identifierList) {}

    std::string outputCodes();

    IdentifierList *mIdentifierList;
    Symbol::TYPE mReturnType = Symbol::VOID;
};





#endif //PASCAL_C_COMPILER_PARAMETERS_H
