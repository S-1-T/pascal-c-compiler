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
        m_Id = id;
        m_Id_List = idList;
    }
    ProgramHead()
    {
        m_Id = nullptr;
        m_Id_List = nullptr;
    };

    Id *m_Id;
    IdList *m_Id_List;
};

class CompoundStatement
{
public:
    explicit CompoundStatement(StatementList *statementList)
    {
        m_Statement_List = statementList;
    }
    CompoundStatement()
    {
        m_Statement_List = nullptr;
    };

    StatementList *m_Statement_List;
};

class ConstDeclaration
{
public:
    ConstDeclaration() = default;
    ;

    explicit ConstDeclaration(vector<pair<Id *, ConstValue *>> Mv_Const)
    {
        mv_Const = std::move(Mv_Const);
    }

    vector<pair<Id *, ConstValue *>> mv_Const;
};

class VarDeclaration
{
public:
    VarDeclaration() = default;
    ;

    explicit VarDeclaration(vector<pair<IdList *, Type *>> Mv_Var)
    {
        mv_Var = std::move(Mv_Var);
    }

    vector<pair<IdList *, Type *>> mv_Var;
};

class SubProgramDeclaration
{
public:
    SubProgramDeclaration() = default;
    ;

    vector<Subprogram *> mv_Subprogram;
};

class Subprogram
{
public:
    Subprogram()
    {
        m_Subprogram_Head = nullptr;
        m_Subprogram_Body = nullptr;
    };

    SubprogramHead *m_Subprogram_Head;
    SubprogramBody *m_Subprogram_Body;
};

class SubprogramHead
{
public:
    SubprogramHead(Id *iD, FormalParameter *formalParameter, int SType)
    {
        m_ID = iD;
        m_Formal_Parameter = formalParameter;
        Simple_Type = SType;
    }
    SubprogramHead()
    {
        m_ID = nullptr;
        m_Formal_Parameter = nullptr;
        Simple_Type = 0;
    }

    Id *m_ID;
    FormalParameter *m_Formal_Parameter;
    int Simple_Type;
};

class SubprogramBody
{
public:
    SubprogramBody(ConstDeclarations *constDeclarations, VarDeclarations *varDeclarations,
                   CompoundStatement *compoundStatement)
    {
        m_Const_Declarations = constDeclarations;
        m_Var_Declarations = varDeclarations;
        m_Compound_Statement = compoundStatement;
    }
    SubprogramBody()
    {
        m_Const_Declarations = nullptr;
        m_Var_Declarations = nullptr;
        m_Compound_Statement = nullptr;
    }

    ConstDeclarations *m_Const_Declarations;
    VarDeclarations *m_Var_Declarations;
    CompoundStatement *m_Compound_Statement;
};

class FormalParameter
{
public:
    explicit FormalParameter(ParameterList *parameterList)
    {
        m_Parameter_List = parameterList;
    }
    FormalParameter()
    {
        m_Parameter_List = nullptr;
    }

    ParameterList *m_Parameter_List;
};

class VarParameter
{
public:
    explicit VarParameter(ValueParameter *valueParameter)
    {
        m_Value_Parameter = valueParameter;
    }
    VarParameter()
    {
        m_Value_Parameter = nullptr;
    }

    ValueParameter *m_Value_Parameter;
};

class ValueParameter
{
public:
    ValueParameter(IdList *idList, int SType)
    {
        m_Id_List = idList;
        Simple_Type = SType;
    }
    ValueParameter()
    {
        Simple_Type = 0;
        m_Id_List = nullptr;
    }

    int Simple_Type;
    IdList *m_Id_List;
};

class IdVarPart
{
public:
    explicit IdVarPart(ExpressionList *expressionList)
    {
        m_Expression_List = expressionList;
    }
    IdVarPart()
    {
        m_Expression_List = nullptr;
    }

    ExpressionList *m_Expression_List; //这个指针可以为NULL
};

class Program
{
public:
    Program(Id *Mp_Id, IdList *Mp_Id_List, ProgramBody *Mp_Program_Body)
    {
        mp_Id = Mp_Id;
        mp_Id_List = Mp_Id_List;
        mp_Program_Body = Mp_Program_Body;
    }
    Program()
    {
        mp_Id = nullptr;
        mp_Id_List = nullptr;
        mp_Program_Body = nullptr;
    }
    string outputCodes() const;

    bool errorDetect() const;

    Id *mp_Id;
    IdList *mp_Id_List;
    ProgramBody *mp_Program_Body;

    void outputTree() const;
};

class ProgramBody
{
public:
    ProgramBody(ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations,
                SubProgramDeclarations *Mp_SubProgram_Declarations, CompoundStatement *Mp_Compound_Statements)
    {
        mp_Const_Declarations = Mp_Const_Declarations;
        mp_Var_Declarations = Mp_Var_Declarations;
        mp_SubProgram_Declarations = Mp_SubProgram_Declarations;
        mp_Statement_List = Mp_Compound_Statements->m_Statement_List;
    }
    ProgramBody()
    {
        mp_Const_Declarations = nullptr;
        mp_Var_Declarations = nullptr;
        mp_SubProgram_Declarations = nullptr;
        mp_Statement_List = nullptr;
    }

    string outputCodes() const;

    pair<bool, string> createSymbolSheet() const;

    bool errorDetect() const;

    ConstDeclarations *mp_Const_Declarations;
    VarDeclarations *mp_Var_Declarations;
    SubProgramDeclarations *mp_SubProgram_Declarations;
    StatementList *mp_Statement_List;

    void outputTree() const;
};

class ConstDeclarations
{
public:
    explicit ConstDeclarations(vector<pair<Id *, ConstValue *>> Mv_Const)
    {
        mv_Const = std::move(Mv_Const);
    }
    ConstDeclarations() = default;
    ;

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    vector<pair<Id *, ConstValue *>> mv_Const;

    void outputTree();
};

class VarDeclarations
{
public:
    VarDeclarations() = default;
    ;

    explicit VarDeclarations(vector<pair<IdList *, Type *>> Mv_Var)
    {
        mv_Var = std::move(Mv_Var);
    }

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    vector<pair<IdList *, Type *>> mv_Var;

    void outputTree();
};

class SubProgramDeclarations
{
public:
    SubProgramDeclarations() = default;
    ;

    explicit SubProgramDeclarations(vector<Common *> Mv_Common)
    {
        mv_Common = std::move(Mv_Common);
    }

    bool errorDetect(const string &symbolSheetName);

    bool definitionErrorDetect();

    string outputCodes();

    vector<Common *> mv_Common;

    void outputTree();
};

class StatementList
{
public:
    StatementList() = default;
    ;

    explicit StatementList(vector<Statement *> Mv_Statement)
    {
        mv_Statement = std::move(Mv_Statement);
    }

    string outputCodes(const string &name = "");

    bool errorDetect(const string &);

    vector<Statement *> mv_Statement;

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
        m_lineno = 0;
        mp_Id = nullptr;
        mp_Parameter_List = nullptr;
        mp_Const_Declarations = nullptr;
        mp_Var_Declarations = nullptr;
        mp_Statement_List = nullptr;
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
        return mp_Id;
    }

    ParameterList *getParamList() override
    {
        return mp_Parameter_List;
    }

    ConstDeclarations *getConstDeclarations() override
    {
        return mp_Const_Declarations;
    }

    VarDeclarations *getVarDeclarations() override
    {
        return mp_Var_Declarations;
    }

    int getLineno() override
    {
        return m_lineno;
    }

    int m_lineno;

    Id *mp_Id;
    ParameterList *mp_Parameter_List;
    ConstDeclarations *mp_Const_Declarations;
    VarDeclarations *mp_Var_Declarations;
    StatementList *mp_Statement_List;

    void outputTree() override;
};

// 函数
class Function : public Common
{
public:
    Function(int returnType, int lineno, Id *Mp_Id, ParameterList *Mp_Parameter_List, ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations, StatementList *Mp_Statement_List);
    Function()
    {
        m_returnType = 0;
        m_lineno = 0;
        mp_Id = nullptr;
        mp_Parameter_List = nullptr;
        mp_Const_Declarations = nullptr;
        mp_Var_Declarations = nullptr;
        mp_Statement_List = nullptr;
    }
    string outputCodes() override;

    int checkReturnType() override
    {
        return m_returnType;
    }

    int getCommonType() override
    {
        return SUBPROGRAM_FUNCTION;
    }

    pair<bool, string> createSymbolSheet() override;

    bool errorDetect() override;

    Id *getFuncId() override
    {
        return mp_Id;
    }

    ParameterList *getParamList() override
    {
        return mp_Parameter_List;
    }

    ConstDeclarations *getConstDeclarations() override
    {
        return mp_Const_Declarations;
    }

    VarDeclarations *getVarDeclarations() override
    {
        return mp_Var_Declarations;
    }

    int getLineno() override
    {
        return m_lineno;
    }

    int m_returnType;
    int m_lineno;

    Id *mp_Id;
    ParameterList *mp_Parameter_List;
    ConstDeclarations *mp_Const_Declarations;
    VarDeclarations *mp_Var_Declarations;
    StatementList *mp_Statement_List;

    void outputTree() override;
};

class Statement
{
public:
    Statement()
    {
        mp_AssignOp = nullptr;
        mp_Procedure_call = nullptr;
        mp_Statement_List = nullptr;
        mp_If_Then_Else = nullptr;
        mp_For = nullptr;
        m_stateType = 0;
        m_lineno = 0;
    };

    string outputCodes(const string &name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_stateType;
    int m_lineno;

    AssignOp *mp_AssignOp;
    ProcedureCall *mp_Procedure_call;
    StatementList *mp_Statement_List;
    IfThenElse *mp_If_Then_Else;
    For *mp_For;

    void outputTree() const;
};

class ParameterList
{
public:
    ParameterList()
    {
        m_lineno = 0;
    };
    ParameterList(int lineno, vector<Parameter *> Mv_Patameter)
    {
        m_lineno = lineno;
        mv_Patameter = std::move(Mv_Patameter);
    }

    bool errorDetect(const string &symbolSheetName);

    string outputCodes();

    int m_lineno;

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
        m_lineno = 0;
        mp_Id = nullptr;
        mp_Expression_List = nullptr;
        type = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() { return type; }

    bool m_isArray;
    int m_lineno;

    Id *mp_Id;
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
        m_lineno = 0;
        mp_Id = nullptr;
        mp_Expression_List = nullptr;
    };
    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int m_proCall_Tpye;

    int m_expNum;
    int m_lineno;

    Id *mp_Id;
    ExpressionList *mp_Expression_List;

    void outputTree() const;
};

class FunctionCall
{
public:
    FunctionCall()
    {
        mp_Id = nullptr;
        mp_Expression_List = nullptr;
        m_expNum = 0;
        m_lineno = 0;
    };
    FunctionCall(int expNum, int lineno, Id *Mp_Id, ExpressionList *Mp_Expression_List)
    {
        m_expNum = expNum;
        m_lineno = lineno;
        mp_Id = Mp_Id;
        mp_Expression_List = Mp_Expression_List;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_expNum;
    int m_lineno;

    Id *mp_Id;
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
        m_lineno = 0;
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

    int m_lineno;
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
        m_lineno = lineno;
        mp_AddOp = Mp_Addop;
        mp_Term = Mp_Term;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
    }
    SimpleExpression()
    {
        mp_AddOp = nullptr;
        mp_Term = nullptr;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
        m_lineno = 0;
    }

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    void setType(int _type) { type = _type; };

    int getType() { return type; };

    int getRangeVal() { return rangeVal; }

    bool getRangeValid() { return rangeValid; }

    int m_lineno;
    int type;
    int rangeVal;
    bool rangeValid;

    AddOp *mp_AddOp;
    Term *mp_Term;

    void outputTree() const;
};

class Term
{
public:
    Term(int lineno, MulOp *Mp_Mulop, Factor *Mp_Factor)
    {
        m_lineno = lineno;
        mp_MulOp = Mp_Mulop;
        mp_Factor = Mp_Factor;
        rangeValid = false;
        rangeVal = 0;
        type = 0;
    }
    Term()
    {
        mp_MulOp = nullptr;
        mp_Factor = nullptr;
        m_lineno = 0;
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

    int m_lineno;
    int type;
    int rangeVal;
    bool rangeValid;
    MulOp *mp_MulOp;
    Factor *mp_Factor;

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
        m_lineno = 0;
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
    int m_lineno;
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
        mp_Factor = nullptr;
        m_lineno = 0;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_lineno;

    Factor *mp_Factor;

    void outputTree() const;
};

class Uminus
{
public:
    Uminus()
    {
        rangeVal = 0;
        rangeValid = 0;
        m_lineno = 0;
        m_unimusType = 0;
        type = 0;
        mp_Factor = nullptr;
    };

    string outputCodes() const;

    bool errorDetect(const string &symbolSheetName);

    int getType() { return type; };

    void setType(int _type) { type = _type; }

    int getRangeVal() { return rangeVal; }

    bool getRangeValid() { return rangeValid; }

    int rangeVal;
    bool rangeValid;
    int m_lineno;
    int m_unimusType;
    int type;
    Factor *mp_Factor;

    void outputTree() const;
};

class Type
{
public:
    Type()
    {
        m_simpleType = 0;
        m_isArray = 0;
        m_lineno = 0;
        mp_Period = nullptr;
    };

    string outputCodes() const;

    string codeGetPeriod() const;

    int checkSimpleType()
    {
        return m_simpleType;
    }

    bool checkIsArray()
    {
        return m_isArray;
    }

    int getLineno()
    {
        return m_lineno;
    }

    vector<pair<int, int>> getPeriod() const;

    int m_simpleType;
    bool m_isArray;
    int m_lineno;

    Period *mp_Period;

    void outputTree() const;
};

class ConstValue
{
public:
    ConstValue()
    {
        mp_Id = nullptr;
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

    int m_lineno;
    bool m_isId;
    Id *mp_Id;

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

    int m_lineno;

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

    int m_lineno;

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
        mp_Id = nullptr;
        mp_Expression_1 = nullptr;
        mp_Expression_2 = nullptr;
        mp_Statement = nullptr;
    };
    For(Id *_mp_Id, Expression *_mp_Expression_1, Expression *_mp_Expression_2, Statement *_mp_Statment)
    {
        mp_Id = _mp_Id;
        mp_Expression_1 = _mp_Expression_1;
        mp_Expression_2 = _mp_Expression_2;
        mp_Statement = _mp_Statment;
    }

    string outputCodes(string name = "") const;

    bool errorDetect(const string &symbolSheetName) const;

    int m_lineno;

    Id *mp_Id;
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
        m_isVal = isVal;
        m_lineno = lineno;
        mp_Id_List = Mp_Id_List;
    }
    Parameter()
    {
        mp_Id_List = nullptr;
    }

    string outputCodes();

    bool isVal()
    {
        return m_isVal;
    }

    vector<Id *> getIds() const;

    int getLineno()
    {
        return m_lineno;
    }

    int getType()
    {
        return m_Type;
    }

    IdList *getIdList()
    {
        return mp_Id_List;
    }

    // define whether the parameter is variable element
    bool m_isVal;
    int m_lineno;
    int m_Type;

    IdList *mp_Id_List;

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
        m_lineno = lineno;
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
    int m_lineno;
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
        mp_Term = nullptr;
    };
    AddOp(int addopType, int lineno, SimpleExpression *Mp_Simple_Expression, Term *Mp_Term)
    {
        m_addopType = addopType;
        m_lineno = lineno;
        mp_Simple_Expression = Mp_Simple_Expression;
        mp_Term = Mp_Term;
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
    int m_lineno;
    int type;
    SimpleExpression *mp_Simple_Expression;
    Term *mp_Term;

    void outputTree() const;
};

class MulOp
{
public:
    MulOp()
    {
        mp_Term = nullptr;
        mp_Factor = nullptr;
    };
    MulOp(int mulopType, int lineno, Term *Mp_Term, Factor *Mp_Factor)
    {
        m_mulopType = mulopType;
        m_lineno = lineno;
        mp_Term = Mp_Term;
        mp_Factor = Mp_Factor;
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
    int m_lineno;
    int type;

    Term *mp_Term;
    Factor *mp_Factor;

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
        return m_idType;
    };

    string getName()
    {
        return m_name;
    }

    bool isVal()
    {
        return m_isVal;
    }

    string m_name;
    int m_idType;
    int m_lineno;

    bool m_isVal;

    void outputTree() const;
};

class IdList
{
public:
    IdList()
    {
        m_lineno = 0;
    };

    string outputCodes();

    vector<Id *> getIds()
    {
        return mv_Id;
    }

    int getIdNum()
    {
        return (int)mv_Id.size();
    }

    int m_lineno;

    vector<Id *> mv_Id;

    void outputTree();
};

class Period
{
public:
    Period() = default;
    ;

    Period(vector<pair<int, int>> Mv_dims)
    {
        mv_dims = Mv_dims;
    }

    string outputCodes();

    vector<pair<int, int>> getRange()
    {
        return mv_dims;
    }
    vector<pair<int, int>> mv_dims;

    void outputTree();
};

class ExpressionList
{
public:
    ExpressionList() = default;
    ;

    ExpressionList(vector<Expression *> Mv_Expression, vector<int> MType)
    {
        mv_Expression = std::move(Mv_Expression);
        mv_Type = std::move(MType);
    }

    string outputCodes(bool isScanf = false);

    bool errorDetect(const string &symbolSheetName);

    vector<Expression *> getExpressions()
    {
        return mv_Expression;
    }

    vector<int> getTypes()
    {
        return mv_Type;
    }

    vector<int> rangeVal;
    vector<bool> rangeValid;
    vector<Expression *> mv_Expression;

    vector<int> mv_Type;

    vector<bool> mv_VarDefine;

    void outputTree();
};

#endif
