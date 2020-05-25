//
// Created by RinChanNOW! on 2020/5/25.
//

#ifndef PASCAL_C_COMPILER_TYPEDECLARATIONS_H
#define PASCAL_C_COMPILER_TYPEDECLARATIONS_H

#include <string>
#include <vector>

typedef std::vector<std::pair<Id *, Type *> > TypeDeclarationList;

class TypeDeclarations {
public:
    TypeDeclarations() = default;
    explicit TypeDeclarations(TypeDeclaration * typeDeclaration): mTypeDeclaration(typeDeclaration) {}

    std::string outputCodes() const;

    TypeDeclaration *mTypeDeclaration = nullptr;

};
class TypeDeclaration {
public:
    TypeDeclaration() = default;
    explicit TypeDeclaration(TypeDeclarationList typeDeclarationList) {
        mTypeDeclarationList = std::move(typeDeclarationList);
    }

    std::string outputCodes();

    TypeDeclarationList mTypeDeclarationList;

};

#endif //PASCAL_C_COMPILER_TYPEDECLARATIONS_H
