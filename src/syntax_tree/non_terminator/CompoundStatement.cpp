//
// Created by RinChanNOW! on 2020/5/20.
//

#include "syntax_tree.h"

#include <string>

class CompoundStatement {
    CompoundStatement() = default;
    explicit CompoundStatement(StatementList *statementList): mStatementList(statementList) {}

    std::string outputCodes();

    StatementList *mStatementList = nullptr;
};