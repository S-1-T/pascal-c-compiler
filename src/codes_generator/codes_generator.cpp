
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
    if (mTypeDeclarations)
        output += mTypeDeclarations->outputCodes() + "\n";
    if (mVarDeclarations)
        output += mVarDeclarations->outputCodes() + "\n";
    if (mSubProgramDeclarations)
        output += mSubProgramDeclarations->outputCodes();
    output += "int main() {\n";
    if (mCompoundStatement)
        output += mCompoundStatement->outputCodes();
    output += "return 0;\n}\n";
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
        Type t(id->mType);
        output += t.outputCodes() + " ";
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

string TypeDeclarations::outputCodes() const {
    string output;
    if (mTypeDeclaration)
        output = mTypeDeclaration->outputCodes();
    return output;

}

string TypeDeclaration::outputCodes() {
    string output;
    for (auto typeDeclaration: mTypeDeclarationList) {
        output += "typedef ";
        Id *id = typeDeclaration.first;
        Type *type = typeDeclaration.second;
        output += type->outputCodes() + " " + id->outputCodes();
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
    if (mVarDeclaration)
        return mVarDeclaration->outputCodes();
    else
        return string();
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
    if (mSubProgramBody && mSubProgramHead)
        return mSubProgramHead->outputCodes() + mSubProgramBody->outputCodes();
    else
        return string();
}

string SubProgramHead::outputCodes() const {
    string output;
    Type returnType(mReturnType);
    if (mId && mFormalParameter)
        output = returnType.outputCodes() + mId->outputCodes() +
            mFormalParameter->outputCodes() + " ";
    return output;
}

string SubProgramBody::outputCodes() const {
    string output = "{\n";
    if (mConstDeclarations)
        output += mConstDeclarations->outputCodes();
    if (mVarDeclarations)
        output += mVarDeclarations->outputCodes();
    if (mCompoundStatement)
        output += mCompoundStatement->outputCodes();
    output += "}\n\n";
    return output;
}

string FormalParameter::outputCodes() const {
    if (mParameterLists)
        return "( " + mParameterLists->outputCodes() + ") ";
    else
        return "() ";
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
    if (mValueParameter)
        return mValueParameter->outputCodes();
    else
        return string();
}

string ValueParameter::outputCodes() const {
    string output;
    if (mIdentifierList) {
        auto idList = mIdentifierList->mIdList;
        for (auto id = idList.begin(); id != idList.end(); id++) {
            output += Type(mType).outputCodes() + " " + (*id)->outputCodes();
            if (id != idList.end() - 1)
                output += ", ";
        }
    }
    return output;
}

string CompoundStatement::outputCodes() const {
    string output;
    if (mStatementList)
        output = mStatementList->outputCodes();
    return output;
}

string StatementList::outputCodes() {
    string output;
    for (auto statement: mStatements) {
        output += statement->outputCodes();
    }
    return output;
}

string Statement::outputCodes() const {
    string output;
    switch (mStatementType) {
        case ASSIGN:
            output = mAssignOp->outputCodes();
            break;
        case CALL_PROC:
            output = mCallProcedureStatement->outputCodes();
            break;
        case IF_THEN_ELSE:
            output = mIfThenElseStatement->outputCodes();
            break;
        case FOR:
            output = mForStatement->outputCodes();
            break;
        default:
            break;
    }
    return output;
}



