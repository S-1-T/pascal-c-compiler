//
// Created by RinChanNOW! on 2020/5/20.
//
#include "syntax_tree.h"

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

