//
// Created by RinChanNOW! on 2020/5/20.
//

#include "syntax_tree.h"

#include <string>

class ProgramBody {
public:
    ProgramBody() = default;
    ProgramBody(ConstDeclarations *constDeclarations, VarDeclarations *varDeclarations,
            SubProgramDeclarations *subProgramDeclarations, CompoundStatement *compoundStatement):
    mConstDeclarations(constDeclarations), mVarDeclarations(varDeclarations),
    mSubProgramDeclarations(subProgramDeclarations), mCompoundStatement(compoundStatement) {}


    std::string outputCodes();

    ConstDeclarations *mConstDeclarations = nullptr;
//    TypeDeclarations *mTypeDeclarations = nullptr;
    VarDeclarations *mVarDeclarations = nullptr;
    SubProgramDeclarations *mSubProgramDeclarations = nullptr;
    CompoundStatement *mCompoundStatement = nullptr;
};
