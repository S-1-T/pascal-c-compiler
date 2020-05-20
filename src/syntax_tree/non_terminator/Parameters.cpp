//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"
#include "symbol_sheet.h"

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
    Parameter(bool var, VarParameter *varParameter):
    isVar(var), mVarParameter(varParameter) {}
    Parameter(bool var, ValueParameter *valueParameter):
    isVar(var), mValueParameter(valueParameter) {}

    std::string outputCodes();

    bool isVar = false;
    VarParameter *mVarParameter = nullptr;
    ValueParameter *mValueParameter = nullptr;
};

class VarParameter {
public:
    VarParameter() = default;
    VarParameter(ValueParameter *valueParameter): mValueParameter(valueParameter) {}

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



