//
// Created by RinChanNOW! on 2020/5/20.
//

#include "syntax_tree.h"

#include <string>

class Program {
public:
    Program() = default;
    Program(Id *id, IdentifierList *idList, ProgramBody *programBody):
    mProgramId(id), mIdList(idList), mProgramBody(programBody) {}

    std::string outputCodes();

    Id *mProgramId = nullptr;
    IdentifierList *mIdList = nullptr;
    ProgramBody *mProgramBody = nullptr;

};