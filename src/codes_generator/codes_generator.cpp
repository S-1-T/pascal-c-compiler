
#include "syntax_tree/syntax_tree_includes.h"

#include <string>

using std::string;

string Id::outputCodes() {
    if (isVarInProc)
        return mName;
    else
        return "*" + mName;
}

string Program::outputCodes() const {
    string output = "#include <stdio.h>\n\n";
    output += mProgramBody->outputCodes();
    return output;
}

string ProgramBody::outputCodes() const {
    string output;
    if (mConstDeclarations)
        output += mConstDeclarations->outputCodes() + "\n";
    if (mVarDeclarations)
        output += mVarDeclarations->outputCodes() + "\n";
    if (mSubProgramDeclarations)
        output += mSubProgramDeclarations->outputCodes();
    if (mCompoundStatement)
        output += mCompoundStatement->outputCodes();
    return output;
}

string IdentifierList::outputCodes() {
    string output;
    IdList::iterator iter;
    for (iter = mIdList.begin(); iter != mIdList.end() - 1; iter++) {
        output += (*iter)->mName + ", ";
    }
    output += (*iter)->mName;
    return output;
}

string ConstDeclarations::outputCodes() const {
    if (mConstDeclaration)
        return mConstDeclaration->outputCodes();
    else
        return string();
}

string ConstDeclaration::outputCodes() {
    string output;
    for (auto & mConstVariable : mConstVariables) {
        output += "const ";
        Id *id = mConstVariable.first;
        ConstVariable *constVariable = mConstVariable.second;
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
                output += "'" + string(1, constVariable->mValue.charValue) + "'";
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

string Type::outputCodes() const {
    string output;
    switch (mType) {
        case Symbol::INT:
            output += "int";
            break;
        case Symbol::REAL:
            output += "float";
            break;
        case Symbol::CHAR:
            output += "char";
            break;
        case Symbol::BOOLEAN:
            output += "bool";
            break;
        case Symbol::VOID:
            output += "void";
            break;
        case Symbol::INT_ARRAY:
            output += "int*";
            break;
        case Symbol::REAL_ARRAY:
            output += "float*";
            break;
        case Symbol::BOOLEAN_ARRAY:
            output += "bool*";
            break;
        case Symbol::CHAR_ARRAY:
            output += "char*";
            break;
        default:
            break;
    }
    return output;
}

string Periods::outputCode() {
    string output;
    for (auto period: mPeriodList) {
        int diff = (*(period.second) - *(period.first)).mValue.intValue;
        output += "[" + std::to_string(diff) + "]";
    }
    return output;
}

string VarDeclarations::outputCodes() const {
    return mVarDeclaration->outputCodes();
}

string VarDeclaration::outputCodes() {
    string output;
    for (auto var: mVariableList) {
        output += var.second->outputCodes() +
                " " + var.first->outputCodes() + ";\n";
    }
    return output;
}

string SubProgramDeclarations::outputCodes() {
    string output;
    for (auto declaration: mSubProgramList) {
        output += declaration->outputCodes();
    }
    return output;
}

string SubProgramDeclaration::outputCodes() const {
    return mSubProgramHead->outputCodes() + mSubProgramBody->outputCodes();
}

string SubProgramHead::outputCodes() const {
    string output;
    Type returnType(mReturnType);
    output = returnType.outputCodes() + mId->outputCodes() +
            mFormalParameter->outputCodes() + " ";
    return output;
}

string SubProgramBody::outputCodes() const {
    string output = "{\n";
    output += mConstDeclarations->outputCodes() +
            mVarDeclarations->outputCodes() +
            mCompoundStatement->outputCodes();
    output += "}\n\n";
    return output;
}

string FormalParameter::outputCodes() const {
    return "( " + mParameterLists->outputCodes() + ")";
}

string ParameterLists::outputCodes() {
    string output;
    for (auto iter = mParameterList.begin(); iter != mParameterList.end(); iter++) {
        output += (*iter)->outputCodes();
        if (iter != mParameterList.end() - 1)
            output += ", ";
    }
    return output;
}

string Parameter::outputCodes() const {
    if (isVar)
        return mVarParameter->outputCodes();
    else
        return mValueParameter->outputCodes();
}

string VarParameter::outputCodes() const {
    return mValueParameter->outputCodes();
}

string ValueParameter::outputCodes() const {
    string output;
    auto idList = mIdentifierList->mIdList;
    for (auto id = idList.begin(); id != idList.end(); id++) {
        output += Type(mType).outputCodes() + " " + (*id)->outputCodes();
        if (id != idList.end() - 1)
            output += ", ";
    }
    return output;
}

string CompoundStatement::outputCodes() const {
    string output = "int main() {\n";
    output += mStatementList->outputCodes();
    output += "return 0;\n}\n";
    return output;
}

string StatementList::outputCodes() {
    string output;
    for (auto statement: mStatements) {
        output += statement->outputCodes();
    }
    return output;
}

