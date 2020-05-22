//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_SUBPROGRAM_H
#define PASCAL_C_COMPILER_SUBPROGRAM_H

#include "syntax_tree/syntax_tree_nodes.h"
#include "symbol_sheet/symbol_sheet.h"

#include <string>
#include <vector>

typedef std::vector<SubProgramDeclaration *> SubProgramList;

class SubProgramDeclarations {
public:
    SubProgramDeclarations() = default;
    explicit SubProgramDeclarations(SubProgramList subProgramList) {
        mSubProgramList = std::move(subProgramList);
    }

    std::string outputCodes();

    SubProgramList mSubProgramList;

};

class SubProgramDeclaration {
public:
    SubProgramDeclaration() = default;
    SubProgramDeclaration(SubProgramHead *subProgramHead, SubProgramBody *subProgramBody):
            mSubProgramHead(subProgramHead), mSubProgramBody(subProgramBody) {}

    std::string outputCodes();

    SubProgramHead *mSubProgramHead = nullptr;
    SubProgramBody *mSubProgramBody = nullptr;

};

class SubProgramHead {
public:
    SubProgramHead() = default;
    SubProgramHead(Symbol::TYPE type, FormalParameter *formalParameter):
            mProgramType(type), mFormalParameter(formalParameter) {}
    SubProgramHead(Symbol::TYPE type, FormalParameter *formalParameter, Symbol::TYPE returnType):
            mProgramType(type), mFormalParameter(formalParameter), mReturnType(returnType) {}

    std::string outputCodes();

    Symbol::TYPE mProgramType = Symbol::VOID;
    Id *mId = nullptr;
    FormalParameter *mFormalParameter = nullptr;
    Symbol::TYPE mReturnType = Symbol::VOID;
};

class SubProgramBody {
public:
    SubProgramBody() = default;
    SubProgramBody(ConstDeclarations *constDeclarations, VarDeclarations *varDeclarations,
                   CompoundStatement *compoundStatement):
            mConstDeclarations(constDeclarations), mVarDeclarations(varDeclarations), mCompoundStatement(compoundStatement) {}


    std::string outputCodes();

    ConstDeclarations *mConstDeclarations = nullptr;
    VarDeclarations *mVarDeclarations = nullptr;
    CompoundStatement *mCompoundStatement = nullptr;
};


#endif //PASCAL_C_COMPILER_SUBPROGRAM_H
