//
// Created by RinChanNOW! on 2020/5/22.
//

#ifndef PASCAL_C_COMPILER_IDENTIFIERLIST_H
#define PASCAL_C_COMPILER_IDENTIFIERLIST_H

#include "syntax_tree/syntax_tree_nodes.h"

#include <string>
#include <vector>

typedef std::vector<Id *> IdList;

class IdentifierList {
public:
    IdentifierList() = default;
    explicit IdentifierList(IdList idList) { mIdList = std::move(idList); }

    std::string outputCodes();

    IdList mIdList;
};

#endif //PASCAL_C_COMPILER_IDENTIFIERLIST_H
