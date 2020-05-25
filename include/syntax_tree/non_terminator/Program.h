//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_PROGRAM_H
#define PASCAL_C_COMPILER_PROGRAM_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>

class Program {
public:
    Program() = default;
    Program(Id *id, IdentifierList *idList, ProgramBody *programBody):
            mProgramId(id), mIdList(idList), mProgramBody(programBody) {}

    std::string outputCodes() const;

    Id *mProgramId = nullptr;
    IdentifierList *mIdList = nullptr;
    ProgramBody *mProgramBody = nullptr;

};



class ProgramBody {
public:
    ProgramBody() = default;
    ProgramBody(ConstDeclarations *constDeclarations,
            VarDeclarations *varDeclarations, TypeDeclarations *typeDeclarations,
            SubProgramDeclarations *subProgramDeclarations, CompoundStatement *compoundStatement):
            mConstDeclarations(constDeclarations),
            mTypeDeclarations(typeDeclarations), mVarDeclarations(varDeclarations),
            mSubProgramDeclarations(subProgramDeclarations), mCompoundStatement(compoundStatement) {}


    std::string outputCodes() const;

    ConstDeclarations *mConstDeclarations = nullptr;
    TypeDeclarations *mTypeDeclarations = nullptr;
    VarDeclarations *mVarDeclarations = nullptr;
    SubProgramDeclarations *mSubProgramDeclarations = nullptr;
    CompoundStatement *mCompoundStatement = nullptr;
};

#endif //PASCAL_C_COMPILER_PROGRAM_H
