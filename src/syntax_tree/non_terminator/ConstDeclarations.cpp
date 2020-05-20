//
// Created by RinChanNOW! on 2020/5/20.
//

#include "syntax_tree.h"

#include <string>
#include <vector>

typedef std::vector<std::pair<Id *, ConstVariable *> > ConstVariableList;

class ConstDeclarations {
public:
    ConstDeclarations() = default;
    explicit ConstDeclarations(ConstDeclaration *constDeclaration): mConstDeclaration(constDeclaration) {}

    std::string outputCodes();

    ConstDeclaration *mConstDeclaration = nullptr;
};

class ConstDeclaration {
public:
    ConstDeclaration() = default;
    explicit ConstDeclaration(ConstVariableList constVariables) { mConstVariables = std::move(constVariables); }

    std::string outputCodes();

    ConstVariableList mConstVariables;
};

