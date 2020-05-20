//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"

#include <string>

class IfThenElseStatement {
public:
    IfThenElseStatement() = default;
    IfThenElseStatement(Expression *expression, Statement *statement):
    hasElse(false), mCondition(expression), mStatement1(statement) {}

    IfThenElseStatement(Expression *expression, Statement *s1, Statement *s2):
    hasElse(true), mCondition(expression), mStatement1(s1), mStatement2(s2) {}

    std::string outputCodes();

    bool hasElse = false;
    Expression *mCondition = nullptr;
    Statement *mStatement1 = nullptr;
    Statement *mStatement2 = nullptr;
};

class ForStatement {
public:
    ForStatement() = default;
    ForStatement(Id *id, Expression *e1, bool updown, Expression *e2, Statement *statement):
    mId(id), mInitial(e1), isUp(updown), mCondition(e2), mForLoopBody(statement) {}

    std::string outputCodes();

    bool isUp = true;
    Id *mId = nullptr;
    Expression *mInitial = nullptr;
    Expression *mCondition = nullptr;
    Statement *mForLoopBody = nullptr;

};