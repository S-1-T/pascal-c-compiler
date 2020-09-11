#pragma once

#ifndef PASCAL_C_COMPILER_SYNTAX_TREE_H
#define PASCAL_C_COMPILER_SYNTAX_TREE_H

#include "defines/const.h"

#include <utility>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Program;
class ProgramBody;
class ConstDeclarations;
class VarDeclarations;
class SubProgramDeclarations;
class StatementList;
class Common;
class Procedure;
class Function;
class Statement;
class ParameterList;
class Variable;
class ProcedureCall;
class FunctionCall;
class Expression;
class SimpleExpression;
class Term;
class Factor;
class Not;
class Uminus;
class Type;
class ConstValue;
class AssignOp;
class IfThenElse;
class For;
class Parameter;
class RelOp;
class AddOp;
class MulOp;
class Id;
class IdList;
class Period;
class ExpressionList;

// 以下类不生成代码，用于传递 AST 成分
class ProgramHead;
class CompoundStatement;
class ConstDeclaration;
class VarDeclaration;
class SubProgramDeclaration;
class Subprogram;
class SubprogramHead;
class SubprogramBody;
class FormalParameter;
class VarParameter;
class ValueParameter;
class IdVarPart;

class ProgramHead
{
public:
    ProgramHead(Id *id, IdList *idList)
    {
        mId = id;
        mIdList = idList;
    }
    ProgramHead()
    {
        mId = nullptr;
        mIdList = nullptr;
    };

    Id *mId;
    IdList *mIdList;
};

class CompoundStatement
{
public:
    explicit CompoundStatement(StatementList *statementList)
    {
        mStatementList = statementList;
    }
    CompoundStatement()
    {
        mStatementList = nullptr;
    };

    StatementList *mStatementList;
};

class ConstDeclaration
{
public:
    ConstDeclaration() = default;
    ;

    explicit ConstDeclaration(vector<pair<Id *, ConstValue *>> constVector)
    {
        mConstVector = std::move(constVector);
    }

    vector<pair<Id *, ConstValue *>> mConstVector;
};

class VarDeclaration
{
public:
    VarDeclaration() = default;
    ;

    explicit VarDeclaration(vector<pair<IdList *, Type *>> variableVector)
    {
        mVariableVector = std::move(variableVector);
    }

    vector<pair<IdList *, Type *>> mVariableVector;
};

class SubProgramDeclaration
{
public:
    SubProgramDeclaration() = default;

};

class Subprogram
{
public:
    Subprogram() = default;

    SubprogramHead *mSubprogramHead = nullptr;
    SubprogramBody *mSubprogramBody = nullptr;
};

class SubprogramHead
{
public:
    SubprogramHead(Id *id, FormalParameter *formalParameter, int SType)
    {
        mId = id;
        mFormalParameter = formalParameter;
        mSimpleType = SType;
    }
    SubprogramHead()
    {
        mId = nullptr;
        mFormalParameter = nullptr;
        mSimpleType = 0;
    }

    Id *mId;
    FormalParameter *mFormalParameter;
    int mSimpleType;
};

class SubprogramBody
{
public:
    SubprogramBody(ConstDeclarations *constDeclarations, VarDeclarations *varDeclarations,
                   CompoundStatement *compoundStatement)
    {
        mConstDeclarations = constDeclarations;
        mVarDeclarations = varDeclarations;
        mCompoundStatement = compoundStatement;
    }
    SubprogramBody()
    {
        mConstDeclarations = nullptr;
        mVarDeclarations = nullptr;
        mCompoundStatement = nullptr;
    }

    ConstDeclarations *mConstDeclarations;
    VarDeclarations *mVarDeclarations;
    CompoundStatement *mCompoundStatement;
};

class FormalParameter
{
public:
    explicit FormalParameter(ParameterList *parameterList)
    {
        mParameterList = parameterList;
    }
    FormalParameter()
    {
        mParameterList = nullptr;
    }

    ParameterList *mParameterList;
};

class VarParameter
{
public:
    explicit VarParameter(ValueParameter *valueParameter)
    {
        mValueParameter = valueParameter;
    }
    VarParameter()
    {
        mValueParameter = nullptr;
    }

    ValueParameter *mValueParameter;
};

class ValueParameter
{
public:
    ValueParameter(IdList *idList, int SType)
    {
        mIdList = idList;
        mSimpleType = SType;
    }
    ValueParameter()
    {
        mSimpleType = 0;
        mIdList = nullptr;
    }

    int mSimpleType;
    IdList *mIdList;
};

class IdVarPart
{
public:
    explicit IdVarPart(ExpressionList *expressionList)
    {
        mExpressionList = expressionList;
    }
    IdVarPart()
    {
        mExpressionList = nullptr;
    }

    ExpressionList *mExpressionList; //这个指针可以为NULL
};

class Program
{
public:
    Program(Id *Mp_Id, IdList *Mp_Id_List, ProgramBody *Mp_ProgramBody)
    {
        mId = Mp_Id;
        mIdList = Mp_Id_List;
        mProgramBody = Mp_ProgramBody;
    }
    Program()
    {
        mId = nullptr;
        mIdList = nullptr;
        mProgramBody = nullptr;
    }
    string outputCodes() const;

    bool errorDetect() const;

    Id *mId;
    IdList *mIdList;
    ProgramBody *mProgramBody;


};

class ProgramBody
{
public:
    ProgramBody(ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations,
                SubProgramDeclarations *Mp_SubProgramDeclarations, CompoundStatement *Mp_Compound_Statements)
    {
        mConstDeclarations = Mp_Const_Declarations;
        mVarDeclarations = Mp_Var_Declarations;
        mSubProgramDeclarations = Mp_SubProgramDeclarations;
        mStatementList = Mp_Compound_Statements->mStatementList;
    }
    ProgramBody()
    {
        mConstDeclarations = nullptr;
        mVarDeclarations = nullptr;
        mSubProgramDeclarations = nullptr;
        mStatementList = nullptr;
    }

    string outputCodes() const;

    pair<bool, string> createSymbolSheet() const;

    bool errorDetect() const;

    ConstDeclarations *mConstDeclarations;
    VarDeclarations *mVarDeclarations;
    SubProgramDeclarations *mSubProgramDeclarations;
    StatementList *mStatementList;


};

class ConstDeclarations
{
public:
    explicit ConstDeclarations(vector<pair<Id *, ConstValue *>> constVector)
    {
        mConstVector = std::move(constVector);
    }
    ConstDeclarations() = default;
    ;

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    vector<pair<Id *, ConstValue *>> mConstVector;


};

class VarDeclarations
{
public:
    VarDeclarations() = default;
    ;

    explicit VarDeclarations(vector<pair<IdList *, Type *>> variableVector)
    {
        mVariableVector = std::move(variableVector);
    }

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    vector<pair<IdList *, Type *>> mVariableVector;


};

class SubProgramDeclarations
{
public:
    SubProgramDeclarations() = default;
    ;

    explicit SubProgramDeclarations(vector<Common *> Mv_Common)
    {
        mCommonVector = std::move(Mv_Common);
    }

    bool errorDetect(const string &symbolSheetName);

    bool definitionErrorDetect();

    string outputCodes();

    vector<Common *> mCommonVector;


};

class StatementList
{
public:
    StatementList() = default;
    ;

    explicit StatementList(vector<Statement *> Mv_Statement)
    {
        mStatementVector = std::move(Mv_Statement);
    }

    string outputCodes(const string &name = "");

    bool errorDetect(const string &);

    vector<Statement *> mStatementVector;


};

// 函数和过程类的基类
class Common
{
public:
    virtual string outputCodes() = 0;

    virtual int checkReturnType() = 0;

    virtual int getCommonType()
    {
        return -1;
    }

    virtual pair<bool, string> createSymbolSheet() = 0;

    virtual bool errorDetect() = 0;

    virtual Id *getFuncId() = 0;

    virtual ParameterList *getParamList() = 0;

//    virtual ConstDeclarations *getConstDeclarations() = 0;

//    virtual VarDeclarations *getVarDeclarations() = 0;

    virtual int getLineno() = 0;


};

// 过程
class Procedure : public Common
{
public:
    Procedure(int lineno, Id *id, ParameterList *parameterList, ConstDeclarations *constDeclarations, VarDeclarations *varDeclarations, StatementList *statementList) {
        mLineno = lineno;
        mId = id;
        mParameterList = parameterList;
        mConstDeclarations = constDeclarations;
        mVarDeclarations = varDeclarations;
        mStatementList = statementList;
    }
    Procedure()
    {
        mLineno = 0;
        mId = nullptr;
        mParameterList = nullptr;
        mConstDeclarations = nullptr;
        mVarDeclarations = nullptr;
        mStatementList = nullptr;
    }
    string outputCodes() override;

    int checkReturnType() override
    {
        return -1; // return VOID
    }

    int getCommonType() override
    {
        return SUBPROGRAM_PROCEDURE;
    }

    pair<bool, string> createSymbolSheet() override;

    bool errorDetect() override;

    Id *getFuncId() override
    {
        return mId;
    }

    ParameterList *getParamList() override
    {
        return mParameterList;
    }

//    ConstDeclarations *getConstDeclarations() override
//    {
//        return mConstDeclarations;
//    }
//
//    VarDeclarations *getVarDeclarations() override
//    {
//        return mVarDeclarations;
//    }

    int getLineno() override
    {
        return mLineno;
    }

    int mLineno;

    Id *mId;
    ParameterList *mParameterList;
    ConstDeclarations *mConstDeclarations;
    VarDeclarations *mVarDeclarations;
    StatementList *mStatementList;

};

// 函数
class Function : public Common
{
public:
    Function(int returnType, int lineno, Id *id, ParameterList *parameterList, ConstDeclarations *constDeclarations, VarDeclarations *varDeclarations, StatementList *statementList) {
        mReturnType = returnType;
        mLineno = lineno;
        mId = id;
        mParameterList = parameterList;
        mConstDeclarations = constDeclarations;
        mVarDeclarations = varDeclarations;
        mStatementList = statementList;
    }
    Function()
    {
        mReturnType = 0;
        mLineno = 0;
        mId = nullptr;
        mParameterList = nullptr;
        mConstDeclarations = nullptr;
        mVarDeclarations = nullptr;
        mStatementList = nullptr;
    }
    string outputCodes() override;

    int checkReturnType() override
    {
        return mReturnType;
    }

    int getCommonType() override
    {
        return SUBPROGRAM_FUNCTION;
    }

    pair<bool, string> createSymbolSheet() override;

    bool errorDetect() override;

    Id *getFuncId() override
    {
        return mId;
    }

    ParameterList *getParamList() override
    {
        return mParameterList;
    }

//    ConstDeclarations *getConstDeclarations() override
//    {
//        return mConstDeclarations;
//    }
//
//    VarDeclarations *getVarDeclarations() override
//    {
//        return mVarDeclarations;
//    }

    int getLineno() override
    {
        return mLineno;
    }

    int mReturnType;
    int mLineno;

    Id *mId;
    ParameterList *mParameterList;
    ConstDeclarations *mConstDeclarations;
    VarDeclarations *mVarDeclarations;
    StatementList *mStatementList;

};

class Statement
{
public:
    Statement()
    {
        mAssignOp = nullptr;
        mProcedure_call = nullptr;
        mStatementList = nullptr;
        mIfThenElse = nullptr;
        mFor = nullptr;
        mStateType = 0;
        mLineno = 0;
    };

    string outputCodes(const string &name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int mStateType;
    int mLineno;

    AssignOp *mAssignOp;
    ProcedureCall *mProcedure_call;
    StatementList *mStatementList;
    IfThenElse *mIfThenElse;
    For *mFor;


};

class ParameterList
{
public:
    ParameterList()
    {
        mLineno = 0;
    };
    ParameterList(int lineno, vector<Parameter *> parameters)
    {
        mLineno = lineno;
        mParameters = std::move(parameters);
    }

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    int mLineno;

    vector<Parameter *> mParameters;


};

//    define the variable type
class Variable
{
public:
    Variable()
    {
        misArray = false;
        mLineno = 0;
        mId = nullptr;
        mExpressionList = nullptr;
        type = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() const { return type; }

    bool misArray;
    int mLineno;

    Id *mId;
    int type;
    ExpressionList *mExpressionList;


};

//    belong to statement
class ProcedureCall
{
public:
    ProcedureCall()
    {
        mProcedureCallType = 0;
        mExpressionsNum = 0;
        mLineno = 0;
        mId = nullptr;
        mExpressionList = nullptr;
    };
    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int mProcedureCallType;

    int mExpressionsNum;
    int mLineno;

    Id *mId;
    ExpressionList *mExpressionList;


};

class FunctionCall
{
public:
    FunctionCall()
    {
        mId = nullptr;
        mExpressionList = nullptr;
        mExpressionsNum = 0;
        mLineno = 0;
    };
    FunctionCall(int expNum, int lineno, Id *Mp_Id, ExpressionList *Mp_Expression_List)
    {
        mExpressionsNum = expNum;
        mLineno = lineno;
        mId = Mp_Id;
        mExpressionList = Mp_Expression_List;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName) const;

    int mExpressionsNum;
    int mLineno;

    Id *mId;
    ExpressionList *mExpressionList;


};

class Expression
{
public:
    Expression()
    {
        mRelOp = nullptr;
        mSimpleExpression = nullptr;
        mLineno = 0;
        rangeVal = 0;
        rangeValid = false;
        type = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    void setType(int _type) { type = _type; };

    int getType() const { return type; }

    int getRangeVal() const { return rangeVal; };

    bool getRangeValid() const { return rangeValid; }

    int mLineno;
    int rangeVal;
    bool rangeValid;

    RelOp *mRelOp;
    SimpleExpression *mSimpleExpression;
    int type;


};

class SimpleExpression
{
public:
    SimpleExpression(int lineno, AddOp *addOp, Term *Mp_Term)
    {
        mLineno = lineno;
        mAddOp = addOp;
        mTerm = Mp_Term;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
    }
    SimpleExpression()
    {
        mAddOp = nullptr;
        mTerm = nullptr;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
        mLineno = 0;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    void setType(int _type) { type = _type; };

    int getType() const { return type; };

    int getRangeVal() const { return rangeVal; }

    bool getRangeValid() const { return rangeValid; }

    int mLineno;
    int type;
    int rangeVal;
    bool rangeValid;

    AddOp *mAddOp;
    Term *mTerm;


};

class Term
{
public:
    Term(int lineno, MulOp *mulOp, Factor *Mp_Factor)
    {
        mLineno = lineno;
        mMulOp = mulOp;
        mFactor = Mp_Factor;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
    }
    Term()
    {
        mMulOp = nullptr;
        mFactor = nullptr;
        mLineno = 0;
        type = 0;
        rangeVal = 0;
        rangeValid = false;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    void setType(int _type) { type = _type; }

    int getType() const { return type; };

    int getRangeVal() const { return rangeVal; }

    bool getRangeValid() const { return rangeValid; }

    int mLineno;
    int type;
    int rangeVal;
    bool rangeValid;
    MulOp *mMulOp;
    Factor *mFactor;


};

class Factor
{
public:
    Factor()
    {
        rangeVal = 0;
        rangeValid = false;
        mInt = 0;
        mReal = 0;
        mChar = 0;
        mBool = false;
        mFactorType = 0;
        mLineno = 0;
        type = 0;

        mVariable = nullptr;
        mFunction_Call = nullptr;
        mExpression = nullptr;
        mNot = nullptr;
        mUminus = nullptr;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() const { return type; } //返回数据类型，integer,char等等
    void setType(int _type) { type = _type; }

    /*int checkFactorType()
    {
        return mFactorType;
    }
*/
    int getRangeVal() const { return rangeVal; }

    bool getRangeValid() const { return rangeValid; }

    int rangeVal;
    bool rangeValid;

    int mInt;
    float mReal;
    char mChar;
    bool mBool;

    int mFactorType;
    int mLineno;
    int type;

    Variable *mVariable;
    FunctionCall *mFunction_Call;
    Expression *mExpression;
    Not *mNot;
    Uminus *mUminus;


};

class Not
{
public:
    Not()
    {
        mFactor = nullptr;
        mLineno = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName) const;

    int mLineno;

    Factor *mFactor;


};

class Uminus
{
public:
    Uminus()
    {
        rangeVal = 0;
        rangeValid = false;
        mLineno = 0;
        mUnimusType = 0;
        type = 0;
        mFactor = nullptr;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() const { return type; };

    void setType(int _type) { type = _type; }

    int getRangeVal() const { return rangeVal; }

//    bool getRangeValid() { return rangeValid; }

    int rangeVal;
    bool rangeValid;
    int mLineno;
    int mUnimusType;
    int type;
    Factor *mFactor;


};

class Type
{
public:
    Type()
    {
        mSimpleType = 0;
        misArray = false;
        mLineno = 0;
        mPeriod = nullptr;
    };

    string outputCodes() const;

    string codeGetPeriod() const;

    int checkSimpleType() const
    {
        return mSimpleType;
    }

    bool checkIsArray() const
    {
        return misArray;
    }

    int getLineno() const
    {
        return mLineno;
    }

    vector<pair<int, int>> getPeriod() const;

    int mSimpleType;
    bool misArray;
    int mLineno;

    Period *mPeriod;


};

class ConstValue
{
public:
    ConstValue()
    {
        mId = nullptr;
    };

    string outputCodes() const;

    int checkValueType() const
    {
        return mValueType;
    }

    int mPolarity{};
    int mValueType{};

    int mInt{};
    float mReal{};
    char mChar{};
    bool mBool{};

    int mLineno{};
    bool misId{};
    Id *mId;


};

class AssignOp
{
public:
    AssignOp()
    {
        mVariable = nullptr;
        mExpression = nullptr;
    };
    AssignOp(Variable *Mp_Variable, Expression *Mp_Expression)
    {
        mVariable = Mp_Variable;
        mExpression = Mp_Expression;
    }

    string outputCodes(const string &name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int mLineno{};

    Variable *mVariable;
    Expression *mExpression;


};

class IfThenElse
{
public:
    IfThenElse()
    {
        mExpression = nullptr;
        mStatement_1 = nullptr;
        mStatement_2 = nullptr;
    };
    IfThenElse(Expression *_mExpression, Statement *_mStatement_1, Statement *_mStatement_2)
    {
        mExpression = _mExpression;
        mStatement_1 = _mStatement_1;
        mStatement_2 = _mStatement_2;
    }

    string outputCodes(const string &name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int mLineno{};

    Expression *mExpression;
    Statement *mStatement_1;
    Statement *mStatement_2;


};

class For
{
public:
    For()
    {
        mId = nullptr;
        mExpression_1 = nullptr;
        mExpression_2 = nullptr;
        mStatement = nullptr;
    };
    For(Id *_mId, Expression *expression_1, Expression *expression_2, Statement *statement)
    {
        mId = _mId;
        mExpression_1 = expression_1;
        mExpression_2 = expression_2;
        mStatement = statement;
    }

    string outputCodes(const string& name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int mLineno{};

    Id *mId;
    Expression *mExpression_1;
    Expression *mExpression_2;
    Statement *mStatement;


};

class Parameter
{
public:
    Parameter(bool isVal, int lineno, IdList *list)
    {
        mIsVal = isVal;
        mLineno = lineno;
        mIdList = list;
    }
    Parameter()
    {
        mIdList = nullptr;
    }

    string outputCodes() const;

//    bool isVal()
//    {
//        return mIsVal;
//    }

    vector<Id *> getIds() const;

    int getLineno() const { return mLineno;}

    int getType() const { return mType;}

    IdList *getIdList() const { return mIdList; }

    // define whether the parameter is variable element
    bool mIsVal{};
    int mLineno{};
    int mType{};

    IdList *mIdList;


};

class RelOp
{
public:
    RelOp()
    {
        mSimple_Expression_1 = nullptr;
        mSimple_Expression_2 = nullptr;
    };
    RelOp(int relOpType, int lineno, SimpleExpression *Mp_Simple_Expression_1,
          SimpleExpression *Mp_Simple_Expression_2)
    {
        mRelOpType = relOpType;
        mLineno = lineno;
        mSimple_Expression_1 = Mp_Simple_Expression_1;
        mSimple_Expression_2 = Mp_Simple_Expression_2;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

//    int checkRelOpType()
//    {
//        return mRelOpType;
//    }

//    void setRelOpType(int _type) { mRelOpType = _type; }

    void setType(int _type) { type = _type; } //设置或返回该表达式是什么类型；
    int getType() const { return type; }

    int mRelOpType{};
    int mLineno{};
    int type{};

    SimpleExpression *mSimple_Expression_1;
    SimpleExpression *mSimple_Expression_2;


};

class AddOp
{
public:
    AddOp()
    {
        mSimpleExpression = nullptr;
        mTerm = nullptr;
    };
    AddOp(int addOpType, int lineno, SimpleExpression *Mp_Simple_Expression, Term *Mp_Term)
    {
        mAddOpType = addOpType;
        mLineno = lineno;
        mSimpleExpression = Mp_Simple_Expression;
        mTerm = Mp_Term;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() const { return type; }

    void setType(int _type) { type = _type; } //设置type的值

//    int checkAddOpType()
//    {
//        return mAddOpType;
//    }

//    void checkAddOpType(int _type)
//    {
//        mAddOpType = _type;
//    }

    int mAddOpType{};
    int mLineno{};
    int type{};
    SimpleExpression *mSimpleExpression;
    Term *mTerm;


};

class MulOp
{
public:
    MulOp()
    {
        mTerm = nullptr;
        mFactor = nullptr;
    };
    MulOp(int mulOpType, int lineno, Term *Mp_Term, Factor *Mp_Factor)
    {
        mMulOpType = mulOpType;
        mLineno = lineno;
        mTerm = Mp_Term;
        mFactor = Mp_Factor;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int checkMulOpType() const
    {
        return mMulOpType;
    }

    void setType(int _type) { type = _type; }

    int getType() const { return type; }

    int mMulOpType{};
    int mLineno{};
    int type{};

    Term *mTerm;
    Factor *mFactor;


};

class Id
{
public:
    Id() = default;
    ;

    string outputCodes() const;

//    int checkType()
//    {
//        return mIdType;
//    };

    string getName() const { return mName;}

//    bool isVal() { return mIsVal;}

    string mName;
    int mIdType{};
    int mLineno{};

    bool mIsVal{};


};

class IdList
{
public:
    IdList()
    {
        mLineno = 0;
    };

    string outputCodes();

    vector<Id *> getIds() const
    {
        return mIdVector;
    }

    int getIdNum() const
    {
        return (int)mIdVector.size();
    }

    int mLineno;

    vector<Id *> mIdVector;


};

class Period
{
public:
    Period() = default;
    ;

    explicit Period(vector<pair<int, int>> dimsVector)
    {
        mDimsVector = std::move(dimsVector);
    }

    string outputCodes();

    vector<pair<int, int>> getRange() const
    {
        return mDimsVector;
    }
    vector<pair<int, int>> mDimsVector;


};

class ExpressionList
{
public:
    ExpressionList() = default;
    ;

    ExpressionList(vector<Expression *> Mv_Expression, vector<int> MType)
    {
        mExpressionVector = std::move(Mv_Expression);
        mTypeVector = std::move(MType);
    }

    string outputCodes(bool isScanf = false);

    bool errorDetect(const string &symbolSheetName);

    vector<Expression *> getExpressions() const { return mExpressionVector;}

    vector<int> getTypes() const { return mTypeVector;}

    vector<int> rangeVal;
    vector<bool> rangeValid;
    vector<Expression *> mExpressionVector;

    vector<int> mTypeVector;

    vector<bool> mVarDefineVector;


};

#endif
