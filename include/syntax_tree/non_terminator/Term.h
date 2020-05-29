//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_TERM_H
#define PASCAL_C_COMPILER_TERM_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>

class Term {
public:
    Term() = default;
    explicit Term(MulOp *mulOp): isMulOp(true), mMulOp(mulOp) {}
    explicit Term(Factor *factor): isMulOp(false), mFactor(factor) {}

    std::string outputCode() const;

    bool isMulOp = false;
    MulOp *mMulOp = nullptr;
    Factor *mFactor = nullptr;
};

#endif //PASCAL_C_COMPILER_TERM_H
