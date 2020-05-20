//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"

#include <string>

class Term {
public:
    Term() = default;
    explicit Term(MulOp *mulOp): isMulOp(true), mMulOp(mulOp) {}
    explicit Term(Factor *factor): isMulOp(false), mFactor(factor) {}

    std::string outputCode();

    bool isMulOp = false;
    MulOp *mMulOp = nullptr;
    Factor *mFactor = nullptr;
};