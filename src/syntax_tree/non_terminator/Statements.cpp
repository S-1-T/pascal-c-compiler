//
// Created by RinChanNOW! on 2020/5/20.
//

#include "syntax_tree.h"

#include <string>
#include <vector>

typedef std::vector<Statement *> Statements;


class CompoundStatement {
public:
    CompoundStatement() = default;
    explicit CompoundStatement(StatementList *statementList): mStatementList(statementList) {}

    std::string outputCodes();

    StatementList *mStatementList = nullptr;
};

class StatementList {
public:
    StatementList() = default;
    explicit StatementList(Statements statements) { mStatements = std::move(statements); }

    std::string outputCodes();

    Statements mStatements;
};



class Statement {
public:
    enum StatementType { ERR, ASSIGN, CALL_PROC, COMPOUND, IF_THEN_ELSE, FOR };

    Statement() = default;
    explicit Statement(AssignOp *assignOp): mStatementType(ASSIGN), mAssignOp(assignOp) {}

    explicit Statement(CallProcedureStatement *callProcedureStatement):
    mStatementType(CALL_PROC), mCallProcedureStatement(callProcedureStatement) {}

    explicit Statement(IfThenElseStatement *ifThenElseStatement):
    mStatementType(IF_THEN_ELSE), mIfThenElseStatement(ifThenElseStatement) {}

    explicit Statement(ForStatement *forStatement): mStatementType(FOR), mForStatement(forStatement) {}

    std::string outputCodes();

    StatementType mStatementType = ERR;
    AssignOp *mAssignOp = nullptr;
    CallProcedureStatement *mCallProcedureStatement = nullptr;
    IfThenElseStatement *mIfThenElseStatement = nullptr;
    ForStatement *mForStatement = nullptr;
};
