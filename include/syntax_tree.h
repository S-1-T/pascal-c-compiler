#pragma once

#ifndef PASCAL_C_COMPILER_SYNTAX_TREE_H
#define PASCAL_C_COMPILER_SYNTAX_TREE_H

#include "const.h"

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
        m_ID = id;
        m_IDList = idList;
    }
    ProgramHead()
    {
        m_ID = nullptr;
        m_IDList = nullptr;
    };

    Id *m_ID;
    IdList *m_IDList;
};

class CompoundStatement
{
public:
    explicit CompoundStatement(StatementList *statementList)
    {
        m_StatementList = statementList;
    }
    CompoundStatement()
    {
        m_StatementList = nullptr;
    };

    StatementList *m_StatementList;
};

class ConstDeclaration
{
public:
    ConstDeclaration() = default;
    ;

    explicit ConstDeclaration(vector<pair<Id *, ConstValue *>> constVector)
    {
        m_ConstVector = std::move(constVector);
    }

    vector<pair<Id *, ConstValue *>> m_ConstVector;
};

class VarDeclaration
{
public:
    VarDeclaration() = default;
    ;

    explicit VarDeclaration(vector<pair<IdList *, Type *>> variableVector)
    {
        m_VariableVector = std::move(variableVector);
    }

    vector<pair<IdList *, Type *>> m_VariableVector;
};

class SubProgramDeclaration
{
public:
    SubProgramDeclaration() = default;
    ;

    vector<Subprogram *> m_subprogram;
};

class Subprogram
{
public:
    Subprogram()
    {
        m_SubprogramHead = nullptr;
        m_SubprogramBody = nullptr;
    };

    SubprogramHead *m_SubprogramHead;
    SubprogramBody *m_SubprogramBody;
};

class SubprogramHead
{
public:
    SubprogramHead(Id *id, FormalParameter *formalParameter, int SType)
    {
        m_ID = id;
        m_FormalParameter = formalParameter;
        m_SimpleType = SType;
    }
    SubprogramHead()
    {
        m_ID = nullptr;
        m_FormalParameter = nullptr;
        m_SimpleType = 0;
    }

    Id *m_ID;
    FormalParameter *m_FormalParameter;
    int m_SimpleType;
};

class SubprogramBody
{
public:
    SubprogramBody(ConstDeclarations *constDeclarations, VarDeclarations *varDeclarations,
                   CompoundStatement *compoundStatement)
    {
        m_ConstDeclarations = constDeclarations;
        m_VarDeclarations = varDeclarations;
        m_CompoundStatement = compoundStatement;
    }
    SubprogramBody()
    {
        m_ConstDeclarations = nullptr;
        m_VarDeclarations = nullptr;
        m_CompoundStatement = nullptr;
    }

    ConstDeclarations *m_ConstDeclarations;
    VarDeclarations *m_VarDeclarations;
    CompoundStatement *m_CompoundStatement;
};

class FormalParameter
{
public:
    explicit FormalParameter(ParameterList *parameterList)
    {
        m_ParameterList = parameterList;
    }
    FormalParameter()
    {
        m_ParameterList = nullptr;
    }

    ParameterList *m_ParameterList;
};

class VarParameter
{
public:
    explicit VarParameter(ValueParameter *valueParameter)
    {
        m_ValueParameter = valueParameter;
    }
    VarParameter()
    {
        m_ValueParameter = nullptr;
    }

    ValueParameter *m_ValueParameter;
};

class ValueParameter
{
public:
    ValueParameter(IdList *idList, int SType)
    {
        m_IDList = idList;
        m_SimpleType = SType;
    }
    ValueParameter()
    {
        m_SimpleType = 0;
        m_IDList = nullptr;
    }

    int m_SimpleType;
    IdList *m_IDList;
};

class IdVarPart
{
public:
    explicit IdVarPart(ExpressionList *expressionList)
    {
        m_ExpressionList = expressionList;
    }
    IdVarPart()
    {
        m_ExpressionList = nullptr;
    }

    ExpressionList *m_ExpressionList; //这个指针可以为NULL
};

class Program
{
public:
    Program(Id *Mp_Id, IdList *Mp_Id_List, ProgramBody *Mp_Program_Body)
    {
        m_PID = Mp_Id;
        m_PIDList = Mp_Id_List;
        m_PProgramBody = Mp_Program_Body;
    }
    Program()
    {
        m_PID = nullptr;
        m_PIDList = nullptr;
        m_PProgramBody = nullptr;
    }
    string outputCodes() const;

    bool errorDetect() const;

    Id *m_PID;
    IdList *m_PIDList;
    ProgramBody *m_PProgramBody;

    void outputTree() const;
};

class ProgramBody
{
public:
    ProgramBody(ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations,
                SubProgramDeclarations *Mp_SubProgram_Declarations, CompoundStatement *Mp_Compound_Statements)
    {
        m_PConstDeclarations = Mp_Const_Declarations;
        m_PVarDeclarations = Mp_Var_Declarations;
        m_PSubProgramDeclarations = Mp_SubProgram_Declarations;
        m_PStatementList = Mp_Compound_Statements->m_StatementList;
    }
    ProgramBody()
    {
        m_PConstDeclarations = nullptr;
        m_PVarDeclarations = nullptr;
        m_PSubProgramDeclarations = nullptr;
        m_PStatementList = nullptr;
    }

    string outputCodes() const;

    pair<bool, string> createSymbolSheet() const;

    bool errorDetect() const;

    ConstDeclarations *m_PConstDeclarations;
    VarDeclarations *m_PVarDeclarations;
    SubProgramDeclarations *m_PSubProgramDeclarations;
    StatementList *m_PStatementList;

    void outputTree() const;
};

class ConstDeclarations
{
public:
    explicit ConstDeclarations(vector<pair<Id *, ConstValue *>> constVector)
    {
        m_ConstVector = std::move(constVector);
    }
    ConstDeclarations() = default;
    ;

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    vector<pair<Id *, ConstValue *>> m_ConstVector;

    void outputTree();
};

class VarDeclarations
{
public:
    VarDeclarations() = default;
    ;

    explicit VarDeclarations(vector<pair<IdList *, Type *>> variableVector)
    {
        m_VariableVector = std::move(variableVector);
    }

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    vector<pair<IdList *, Type *>> m_VariableVector;

    void outputTree();
};

class SubProgramDeclarations
{
public:
    SubProgramDeclarations() = default;
    ;

    explicit SubProgramDeclarations(vector<Common *> Mv_Common)
    {
        m_CommonVector = std::move(Mv_Common);
    }

    bool errorDetect(const string &symbolSheetName);

    bool definitionErrorDetect();

    string outputCodes();

    vector<Common *> m_CommonVector;

    void outputTree();
};

class StatementList
{
public:
    StatementList() = default;
    ;

    explicit StatementList(vector<Statement *> Mv_Statement)
    {
        m_StatementVector = std::move(Mv_Statement);
    }

    string outputCodes(const string &name = "");

    bool errorDetect(const string &);

    vector<Statement *> m_StatementVector;

    void outputTree();
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

    virtual ConstDeclarations *getConstDeclarations() = 0;

    virtual VarDeclarations *getVarDeclarations() = 0;

    virtual int getLineno() = 0;

    virtual void outputTree() = 0;
};

// 过程
class Procedure : public Common
{
public:
    Procedure(int lineno, Id *Mp_Id, ParameterList *Mp_Parameter_List, ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations, StatementList *Mp_Statement_List);
    Procedure()
    {
        m_Lineno = 0;
        m_PID = nullptr;
        m_PParameterList = nullptr;
        m_PConstDeclarations = nullptr;
        m_PVarDeclarations = nullptr;
        m_PStatementList = nullptr;
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
        return m_PID;
    }

    ParameterList *getParamList() override
    {
        return m_PParameterList;
    }

    ConstDeclarations *getConstDeclarations() override
    {
        return m_PConstDeclarations;
    }

    VarDeclarations *getVarDeclarations() override
    {
        return m_PVarDeclarations;
    }

    int getLineno() override
    {
        return m_Lineno;
    }

    int m_Lineno;

    Id *m_PID;
    ParameterList *m_PParameterList;
    ConstDeclarations *m_PConstDeclarations;
    VarDeclarations *m_PVarDeclarations;
    StatementList *m_PStatementList;

    void outputTree() override;
};

// 函数
class Function : public Common
{
public:
    Function(int returnType, int lineno, Id *Mp_Id, ParameterList *Mp_Parameter_List, ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations, StatementList *Mp_Statement_List);
    Function()
    {
        m_ReturnType = 0;
        m_Lineno = 0;
        m_PID = nullptr;
        m_PParameterList = nullptr;
        m_PConstDeclarations = nullptr;
        m_PVarDeclarations = nullptr;
        m_PStatementList = nullptr;
    }
    string outputCodes() override;

    int checkReturnType() override
    {
        return m_ReturnType;
    }

    int getCommonType() override
    {
        return SUBPROGRAM_FUNCTION;
    }

    pair<bool, string> createSymbolSheet() override;

    bool errorDetect() override;

    Id *getFuncId() override
    {
        return m_PID;
    }

    ParameterList *getParamList() override
    {
        return m_PParameterList;
    }

    ConstDeclarations *getConstDeclarations() override
    {
        return m_PConstDeclarations;
    }

    VarDeclarations *getVarDeclarations() override
    {
        return m_PVarDeclarations;
    }

    int getLineno() override
    {
        return m_Lineno;
    }

    int m_ReturnType;
    int m_Lineno;

    Id *m_PID;
    ParameterList *m_PParameterList;
    ConstDeclarations *m_PConstDeclarations;
    VarDeclarations *m_PVarDeclarations;
    StatementList *m_PStatementList;

    void outputTree() override;
};

class Statement
{
public:
    Statement()
    {
        mp_AssignOp = nullptr;
        mp_Procedure_call = nullptr;
        m_PStatementList = nullptr;
        mp_If_Then_Else = nullptr;
        mp_For = nullptr;
        m_stateType = 0;
        m_Lineno = 0;
    };

    string outputCodes(const string &name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_stateType;
    int m_Lineno;

    AssignOp *mp_AssignOp;
    ProcedureCall *mp_Procedure_call;
    StatementList *m_PStatementList;
    IfThenElse *mp_If_Then_Else;
    For *mp_For;

    void outputTree() const;
};

class ParameterList
{
public:
    ParameterList()
    {
        m_Lineno = 0;
    };
    ParameterList(int lineno, vector<Parameter *> Mv_Patameter)
    {
        m_Lineno = lineno;
        mv_Patameter = std::move(Mv_Patameter);
    }

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    int m_Lineno;

    vector<Parameter *> mv_Patameter;

    void outputTree();
};

//    define the variable type
class Variable
{
public:
    Variable()
    {
        m_isArray = false;
        m_Lineno = 0;
        m_PID = nullptr;
        mp_Expression_List = nullptr;
        type = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() { return type; }

    bool m_isArray;
    int m_Lineno;

    Id *m_PID;
    int type;
    ExpressionList *mp_Expression_List;

    void outputTree() const;
};

//    belong to statement
class ProcedureCall
{
public:
    ProcedureCall()
    {
        m_proCall_Tpye = 0;
        m_expNum = 0;
        m_Lineno = 0;
        m_PID = nullptr;
        mp_Expression_List = nullptr;
    };
    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int m_proCall_Tpye;

    int m_expNum;
    int m_Lineno;

    Id *m_PID;
    ExpressionList *mp_Expression_List;

    void outputTree() const;
};

class FunctionCall
{
public:
    FunctionCall()
    {
        m_PID = nullptr;
        mp_Expression_List = nullptr;
        m_expNum = 0;
        m_Lineno = 0;
    };
    FunctionCall(int expNum, int lineno, Id *Mp_Id, ExpressionList *Mp_Expression_List)
    {
        m_expNum = expNum;
        m_Lineno = lineno;
        m_PID = Mp_Id;
        mp_Expression_List = Mp_Expression_List;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_expNum;
    int m_Lineno;

    Id *m_PID;
    ExpressionList *mp_Expression_List;

    void outputTree() const;
};

class Expression
{
public:
    Expression()
    {
        mp_Relop = nullptr;
        mp_Simple_Expression = nullptr;
        m_Lineno = 0;
        rangeVal = 0;
        rangeValid = false;
        type = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    void setType(int _type) { type = _type; };

    int getType() { return type; }

    int getRangeVal() { return rangeVal; };

    bool getRangeValid() { return rangeValid; }

    int m_Lineno;
    int rangeVal;
    bool rangeValid;

    RelOp *mp_Relop;
    SimpleExpression *mp_Simple_Expression;
    int type;

    void outputTree() const;
};

class SimpleExpression
{
public:
    SimpleExpression(int lineno, AddOp *Mp_Addop, Term *Mp_Term)
    {
        m_Lineno = lineno;
        mp_AddOp = Mp_Addop;
        m_PTerm = Mp_Term;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
    }
    SimpleExpression()
    {
        mp_AddOp = nullptr;
        m_PTerm = nullptr;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
        m_Lineno = 0;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    void setType(int _type) { type = _type; };

    int getType() { return type; };

    int getRangeVal() { return rangeVal; }

    bool getRangeValid() { return rangeValid; }

    int m_Lineno;
    int type;
    int rangeVal;
    bool rangeValid;

    AddOp *mp_AddOp;
    Term *m_PTerm;

    void outputTree() const;
};

class Term
{
public:
    Term(int lineno, MulOp *Mp_Mulop, Factor *Mp_Factor)
    {
        m_Lineno = lineno;
        mp_MulOp = Mp_Mulop;
        m_PFactor = Mp_Factor;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
    }
    Term()
    {
        mp_MulOp = nullptr;
        m_PFactor = nullptr;
        m_Lineno = 0;
        type = 0;
        rangeVal = 0;
        rangeValid = false;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    void setType(int _type) { type = _type; }

    int getType() { return type; };

    int getRangeVal() { return rangeVal; }

    bool getRangeValid() { return rangeValid; }

    int m_Lineno;
    int type;
    int rangeVal;
    bool rangeValid;
    MulOp *mp_MulOp;
    Factor *m_PFactor;

    void outputTree() const;
};

class Factor
{
public:
    Factor()
    {
        rangeVal = 0;
        rangeValid = false;
        m_int = 0;
        m_real = 0;
        m_char = 0;
        m_bool = false;
        m_factorType = 0;
        m_Lineno = 0;
        type = 0;

        mp_Variable = nullptr;
        mp_Function_Call = nullptr;
        mp_Expression = nullptr;
        mp_Not = nullptr;
        mp_Uminus = nullptr;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() { return type; } //返回数据类型，integer,char等等
    void setType(int _type) { type = _type; }

    int checkFactorType()
    {
        return m_factorType;
    }

    int getRangeVal() { return rangeVal; }

    bool getRangeValid() { return rangeValid; }

    int rangeVal;
    bool rangeValid;

    int m_int;
    float m_real;
    char m_char;
    bool m_bool;

    int m_factorType;
    int m_Lineno;
    int type;

    Variable *mp_Variable;
    FunctionCall *mp_Function_Call;
    Expression *mp_Expression;
    Not *mp_Not;
    Uminus *mp_Uminus;

    void outputTree() const;
};

class Not
{
public:
    Not()
    {
        m_PFactor = nullptr;
        m_Lineno = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_Lineno;

    Factor *m_PFactor;

    void outputTree() const;
};

class Uminus
{
public:
    Uminus()
    {
        rangeVal = 0;
        rangeValid = 0;
        m_Lineno = 0;
        m_unimusType = 0;
        type = 0;
        m_PFactor = nullptr;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() { return type; };

    void setType(int _type) { type = _type; }

    int getRangeVal() { return rangeVal; }

    bool getRangeValid() { return rangeValid; }

    int rangeVal;
    bool rangeValid;
    int m_Lineno;
    int m_unimusType;
    int type;
    Factor *m_PFactor;

    void outputTree() const;
};

class Type
{
public:
    Type()
    {
        m_SimpleType = 0;
        m_isArray = 0;
        m_Lineno = 0;
        mp_Period = nullptr;
    };

    string outputCodes() const;

    string codeGetPeriod() const;

    int checkSimpleType()
    {
        return m_SimpleType;
    }

    bool checkIsArray()
    {
        return m_isArray;
    }

    int getLineno()
    {
        return m_Lineno;
    }

    vector<pair<int, int>> getPeriod() const;

    int m_SimpleType;
    bool m_isArray;
    int m_Lineno;

    Period *mp_Period;

    void outputTree() const;
};

class ConstValue
{
public:
    ConstValue()
    {
        m_PID = nullptr;
    };

    string outputCodes() const;

    int func_checkValueType()
    {
        return m_valueType;
    }

    int m_postNeg;
    int m_valueType;

    int m_int;
    float m_real;
    char m_char;
    bool m_bool;

    int m_Lineno;
    bool m_isId;
    Id *m_PID;

    void outputTree() const;
};

class AssignOp
{
public:
    AssignOp()
    {
        mp_Variable = nullptr;
        mp_Expression = nullptr;
    };
    AssignOp(Variable *Mp_Variable, Expression *Mp_Expression)
    {
        mp_Variable = Mp_Variable;
        mp_Expression = Mp_Expression;
    }

    string outputCodes(const string &name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_Lineno;

    Variable *mp_Variable;
    Expression *mp_Expression;

    void outputTree() const;
};

class IfThenElse
{
public:
    IfThenElse()
    {
        mp_Expression = nullptr;
        mp_Statement_1 = nullptr;
        mp_Statement_2 = nullptr;
    };
    IfThenElse(Expression *_mp_Expression, Statement *_mp_Statement_1, Statement *_mp_Statement_2)
    {
        mp_Expression = _mp_Expression;
        mp_Statement_1 = _mp_Statement_1;
        mp_Statement_2 = _mp_Statement_2;
    }

    string outputCodes(const string &name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_Lineno;

    Expression *mp_Expression;
    Statement *mp_Statement_1;
    Statement *mp_Statement_2;

    void outputTree() const;
};

class For
{
public:
    For()
    {
        m_PID = nullptr;
        mp_Expression_1 = nullptr;
        mp_Expression_2 = nullptr;
        mp_Statement = nullptr;
    };
    For(Id *_mp_Id, Expression *_mp_Expression_1, Expression *_mp_Expression_2, Statement *_mp_Statment)
    {
        m_PID = _mp_Id;
        mp_Expression_1 = _mp_Expression_1;
        mp_Expression_2 = _mp_Expression_2;
        mp_Statement = _mp_Statment;
    }

    string outputCodes(string name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_Lineno;

    Id *m_PID;
    Expression *mp_Expression_1;
    Expression *mp_Expression_2;
    Statement *mp_Statement;

    void outputTree() const;
};

class Parameter
{
public:
    Parameter(bool isVal, int lineno, IdList *Mp_Id_List)
    {
        m_IsVal = isVal;
        m_Lineno = lineno;
        m_PIDList = Mp_Id_List;
    }
    Parameter()
    {
        m_PIDList = nullptr;
    }

    string outputCodes();

    bool isVal()
    {
        return m_IsVal;
    }

    vector<Id *> getIds() const;

    int getLineno()
    {
        return m_Lineno;
    }

    int getType()
    {
        return m_Type;
    }

    IdList *getIdList()
    {
        return m_PIDList;
    }

    // define whether the parameter is variable element
    bool m_IsVal;
    int m_Lineno;
    int m_Type;

    IdList *m_PIDList;

    void outputTree() const;
};

class RelOp
{
public:
    RelOp()
    {
        mp_Simple_Expression_1 = nullptr;
        mp_Simple_Expression_2 = nullptr;
    };
    RelOp(int relopType, int lineno, SimpleExpression *Mp_Simple_Expression_1,
          SimpleExpression *Mp_Simple_Expression_2)
    {
        m_relopType = relopType;
        m_Lineno = lineno;
        mp_Simple_Expression_1 = Mp_Simple_Expression_1;
        mp_Simple_Expression_2 = Mp_Simple_Expression_2;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int checkRelOpType()
    {
        return m_relopType;
    }

    void setRelOpType(int _type) { m_relopType = _type; }

    void setType(int _type) { type = _type; } //设置或返回该表达式是什么类型；
    int getType() { return type; }

    int m_relopType;
    int m_Lineno;
    int type;

    SimpleExpression *mp_Simple_Expression_1;
    SimpleExpression *mp_Simple_Expression_2;

    void outputTree() const;
};

class AddOp
{
public:
    AddOp()
    {
        mp_Simple_Expression = nullptr;
        m_PTerm = nullptr;
    };
    AddOp(int addopType, int lineno, SimpleExpression *Mp_Simple_Expression, Term *Mp_Term)
    {
        m_addopType = addopType;
        m_Lineno = lineno;
        mp_Simple_Expression = Mp_Simple_Expression;
        m_PTerm = Mp_Term;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() { return type; }

    void setType(int _type) { type = _type; } //设置type的值

    int checkAddOpType()
    {
        return m_addopType;
    }

    void checkAddOpType(int _type)
    {
        m_addopType = _type;
    }

    int m_addopType;
    int m_Lineno;
    int type;
    SimpleExpression *mp_Simple_Expression;
    Term *m_PTerm;

    void outputTree() const;
};

class MulOp
{
public:
    MulOp()
    {
        m_PTerm = nullptr;
        m_PFactor = nullptr;
    };
    MulOp(int mulopType, int lineno, Term *Mp_Term, Factor *Mp_Factor)
    {
        m_mulopType = mulopType;
        m_Lineno = lineno;
        m_PTerm = Mp_Term;
        m_PFactor = Mp_Factor;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int checkMulOpType()
    {
        return m_mulopType;
    }

    void setType(int _type) { type = _type; }

    int getType() { return type; }

    int m_mulopType;
    int m_Lineno;
    int type;

    Term *m_PTerm;
    Factor *m_PFactor;

    void outputTree() const;
};

class Id
{
public:
    Id() = default;
    ;

    string outputCodes() const;

    int checkType()
    {
        return m_IDType;
    };

    string getName()
    {
        return m_Name;
    }

    bool isVal()
    {
        return m_IsVal;
    }

    string m_Name;
    int m_IDType;
    int m_Lineno;

    bool m_IsVal;

    void outputTree() const;
};

class IdList
{
public:
    IdList()
    {
        m_Lineno = 0;
    };

    string outputCodes();

    vector<Id *> getIds()
    {
        return m_IDVector;
    }

    int getIdNum()
    {
        return (int)m_IDVector.size();
    }

    int m_Lineno;

    vector<Id *> m_IDVector;

    void outputTree();
};

class Period
{
public:
    Period() = default;
    ;

    Period(vector<pair<int, int>> dimsVector)
    {
        m_DimsVector = dimsVector;
    }

    string outputCodes();

    vector<pair<int, int>> getRange()
    {
        return m_DimsVector;
    }
    vector<pair<int, int>> m_DimsVector;

    void outputTree();
};

class ExpressionList
{
public:
    ExpressionList() = default;
    ;

    ExpressionList(vector<Expression *> Mv_Expression, vector<int> MType)
    {
        m_ExpressionVector = std::move(Mv_Expression);
        m_TypeVector = std::move(MType);
    }

    string outputCodes(bool isScanf = false);

    bool errorDetect(const string &symbolSheetName);

    vector<Expression *> getExpressions()
    {
        return m_ExpressionVector;
    }

    vector<int> getTypes()
    {
        return m_TypeVector;
    }

    vector<int> rangeVal;
    vector<bool> rangeValid;
    vector<Expression *> m_ExpressionVector;

    vector<int> m_TypeVector;

    vector<bool> m_VarDefineVector;

    void outputTree();
};

#endif
