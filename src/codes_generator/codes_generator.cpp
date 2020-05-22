
#include "syntax_tree/syntax_tree_includes.h"

#include <string>

std::string Program::outputCodes() {
    std::string output = "#include <stdio.h>\n\n";
    output += mProgramBody->outputCodes();
    return output;
}

std::string ProgramBody::outputCodes() {
    std::string output = "";
    if (mConstDeclarations)
        output += mConstDeclarations->outputCodes();
    if (mVarDeclarations)
        output += mVarDeclarations->outputCodes();
    if (mSubProgramDeclarations)
        output += mSubProgramDeclarations->outputCodes();
    if (mCompoundStatement)
        output += mCompoundStatement->outputCodes();
    return output;
}

std::string IdentifierList::outputCodes() {
    std::string output = "";
    IdList::iterator iter;
    for (iter = mIdList.begin(); iter != mIdList.end() - 1; iter++) {
        output += (*iter)->mName + ", ";
    }
    output += (*iter)->mName;
}

std::string ConstDeclarations::outputCodes() {
    if (mConstDeclaration)
        return mConstDeclaration->outputCodes();
    else
        return std::string();
}

std::string ConstDeclaration::outputCodes() {
    std::string output = "";
    for (auto iter = mConstVariables.begin(); iter != mConstVariables.end(); iter++) {
        output += "const ";
        Id *id = (*iter).first;
        ConstVariable *constVariable = (*iter).second;
        switch (id->mType) {
            case Symbol::INT:
                output += "int ";
                break;
            case Symbol::REAL:
                output += "float ";
                break;
            case Symbol::CHAR:
                output += "char ";
                break;
            case Symbol::BOOLEAN:
                output += "bool ";
                break;
            default:
                break;
        }
        output += id->mName + " = ";
        if (constVariable->isNegative)
            output += "-";
        switch (constVariable->mType) {
            case Symbol::ID:
                output += constVariable->mId->mName;
                break;
            case Symbol::INT:
                output += std::to_string(constVariable->mValue.intValue);
                break;
            case Symbol::REAL:
                output += std::to_string(constVariable->mValue.realValue);
                break;
            case Symbol::CHAR:
                output += "'" + std::string(1, constVariable->mValue.charValue) + "'";
                break;
            case Symbol::BOOLEAN:
                if (constVariable->mValue.boolValue)
                    output += "true";
                else
                    output += "false";
                break;
            default:
                break;
        }
        output += ";\n";
    }
    return output;
}

