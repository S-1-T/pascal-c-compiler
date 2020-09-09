#include "syntax_tree.h"
#include <iostream>

using namespace std;

void Program::outputTree() const
{
    cout << "Program" << endl;
    if (mp_Id == nullptr)
        cout << "mp_Id is nullptr" << endl;
    else
        mp_Id->outputTree();
    if (mp_Id_List == nullptr)
        cout << "IdList is nullptr" << endl;
    else
        mp_Id_List->outputTree();
    if (mp_Program_Body == nullptr)
        cout << "mp_Program_Body is nullptr" << endl;
    else
        mp_Program_Body->outputTree();
}

void ProgramBody::outputTree() const
{
    cout << "ProgramBody" << endl;
    if (mp_Const_Declarations == nullptr)
        cout << "mp_Const_Declarations is nullptr" << endl;
    else
        mp_Const_Declarations->outputTree();
    if (mp_Var_Declarations == nullptr)
        cout << "mp_Var_Declarations is nullptr" << endl;
    else
        mp_Var_Declarations->outputTree();
    if (mp_SubProgram_Declarations == nullptr)
        cout << "mp_SubProgram_Declarations is nullptr" << endl;
    else
        mp_SubProgram_Declarations->outputTree();
    if (mp_Statement_List == nullptr)
        cout << "mp_Statement_List is nullptr" << endl;
    else
        mp_Statement_List->outputTree();
}

void ConstDeclarations::outputTree()
{
    cout << "ConstDeclarations" << endl;
    if (mv_Const.empty())
        cout << "mv_Const is nullptr" << endl;
    else
        for (auto &i : mv_Const)
        {
            i.first->outputTree();
            i.second->outputTree();
        }
}

void VarDeclarations::outputTree()
{
    cout << "VarDeclarations";
    if (mv_Var.empty())
        cout << "mv_Var is nullptr" << endl;
    else
        for (auto &i : mv_Var)
        {
            i.first->outputTree();
            i.second->outputTree();
        }
}

void SubProgramDeclarations::outputTree()
{
    cout << "SubProgramDeclarations" << endl;
    if (mv_Common.empty())
        cout << "mv_Common is nullptr" << endl;
    else
        for (auto &i : mv_Common)
        {
            i->outputTree();
        }
}

void StatementList::outputTree()
{
    cout << "StatementList" << endl;
    if (mv_Statement.empty())
        cout << "mv_Statement is nullptr" << endl;
    for (auto &i : mv_Statement)
    {
        i->outputTree();
    }
}

void Procedure::outputTree()
{
    cout << "Procedure" << endl;
    cout << "m_lineo = " << m_lineno << endl;
    if (mp_Id == nullptr)
    {
        cout << "mp_Id is nullptr" << endl;
    }
    else
    {
        mp_Id->outputTree();
    }
    if (mp_Parameter_List == nullptr)
    {
        cout << "mp_Parameter_List is nullptr" << endl;
    }
    else
    {
        mp_Parameter_List->outputTree();
    }
    if (mp_Const_Declarations == nullptr)
    {
        cout << "mp_Const_Declarations is nullptr" << endl;
    }
    else
    {
        mp_Const_Declarations->outputTree();
    }
    if (mp_Var_Declarations == nullptr)
    {
        cout << "mp_Var_Declarations is nullptr" << endl;
    }
    else
    {
        mp_Var_Declarations->outputTree();
    }
    if (mp_Statement_List == nullptr)
    {
        cout << "mp_Statement_List is nullptr" << endl;
    }
    else
    {
        mp_Statement_List->outputTree();
    }
}

void Function::outputTree()
{
    cout << "Function" << endl;
    cout << "m_returnType = " << m_returnType << endl;
    cout << "m_lineo = " << m_lineno << endl;
    if (mp_Id == nullptr)
    {
        cout << "mp_Id is nullptr" << endl;
    }
    else
    {
        mp_Id->outputTree();
    }
    if (mp_Parameter_List == nullptr)
    {
        cout << "mp_Parameter_List is nullptr" << endl;
    }
    else
    {
        mp_Parameter_List->outputTree();
    }
    if (mp_Const_Declarations == nullptr)
    {
        cout << "mp_Const_Declarations is nullptr" << endl;
    }
    else
    {
        mp_Const_Declarations->outputTree();
    }
    if (mp_Var_Declarations == nullptr)
    {
        cout << "mp_Var_Declarations is nullptr" << endl;
    }
    else
    {
        mp_Var_Declarations->outputTree();
    }
    if (mp_Statement_List == nullptr)
    {
        cout << "mp_Statement_List is nullptr" << endl;
    }
    else
    {
        mp_Statement_List->outputTree();
    }
}

void Statement::outputTree() const
{
    cout << "Statement" << endl;
    cout << "m_stateType = " << m_stateType << endl;
    cout << "m_lineno = " << m_lineno << endl;
    if (mp_AssignOp == nullptr)
    {
        cout << "mp_AssignOp is nullptr" << endl;
    }
    else
    {
        mp_AssignOp->outputTree();
    }
    if (mp_Procedure_call == nullptr)
    {
        cout << "mp_Procedure_call is nullptr" << endl;
    }
    else
    {
        mp_Procedure_call->outputTree();
    }
    if (mp_Statement_List == nullptr)
    {
        cout << "mp_Statement_List is nullptr" << endl;
    }
    else
    {
        mp_Statement_List->outputTree();
    }
    if (mp_If_Then_Else == nullptr)
    {
        cout << "mp_If_Then_Else is nullptr" << endl;
    }
    else
    {
        mp_If_Then_Else->outputTree();
    }
    if (mp_For == nullptr)
    {
        cout << "mp_For is nullptr" << endl;
    }
    else
    {
        mp_For->outputTree();
    }
}

void ParameterList::outputTree()
{
    cout << "ParameterList" << endl;
    cout << "m_lineno = " << m_lineno << endl;
    if (mv_Patameter.empty())
    {
        cout << "mv_Patameter is nullptr" << endl;
    }
    else
    {
        for (auto &i : mv_Patameter)
        {
            i->outputTree();
        }
    }
}

void Variable::outputTree() const
{
    cout << "Variable" << endl;
    cout << "m_isArray = " << m_isArray << endl;
    cout << "m_lineno = " << m_lineno << endl;
    if (mp_Id == nullptr)
    {
        cout << "mp_Id is nullptr" << endl;
    }
    else
    {
        mp_Id->outputTree();
    }
    cout << "type = " << type << endl;
    if (mp_Expression_List == nullptr)
    {
        cout << "mp_Expression_List is nullptr" << endl;
    }
    else
    {
        mp_Expression_List->outputTree();
    }
}

void ProcedureCall::outputTree() const
{
    cout << "ProcedureCall" << endl;
    cout << "m_proCall_Tpye = " << m_proCall_Tpye << endl;
    cout << "m_expNum = " << m_expNum << endl;
    cout << "m_lineno = " << m_lineno << endl;
    if (mp_Id == nullptr)
    {
        cout << "mp_Id is nullptr" << endl;
    }
    else
    {
        mp_Id->outputTree();
    }
    if (mp_Expression_List == nullptr)
    {
        cout << "mp_Expression_List is nullptr" << endl;
    }
    else
    {
        mp_Expression_List->outputTree();
    }
}

void FunctionCall::outputTree() const
{
    cout << "FunctionCall" << endl;
    cout << "m_expNum = " << m_expNum << endl;
    cout << "m_lineno = " << m_lineno << endl;
    if (mp_Id == nullptr)
    {
        cout << "mp_Id is nullptr" << endl;
    }
    else
    {
        mp_Id->outputTree();
    }
    if (mp_Expression_List == nullptr)
    {
        cout << "mp_Expression_List is nullptr" << endl;
    }
    else
    {
        mp_Expression_List->outputTree();
    }
}

void Expression::outputTree() const
{
    cout << "Expression" << endl;
    cout << "m_lineno = " << m_lineno << endl;
    cout << "rangeVal = " << rangeVal << endl;
    cout << "rangeValid = " << rangeValid << endl;
    if (mp_Relop == nullptr)
    {
        cout << "mp_Relop is nullptr" << endl;
    }
    else
    {
        mp_Relop->outputTree();
    }
    if (mp_Simple_Expression == nullptr)
    {
        cout << "mp_Simple_Expression is nullptr" << endl;
    }
    else
    {
        mp_Simple_Expression->outputTree();
    }

    cout << "type = " << type << endl;
}

void SimpleExpression::outputTree() const
{
    cout << "SimpleExpression" << endl;
    cout << "type = " << type << endl;
    cout << "m_lineno = " << m_lineno << endl;
    cout << "rangeVal = " << rangeVal << endl;
    cout << "rangeValid = " << rangeValid << endl;

    if (mp_AddOp == nullptr)
    {
        cout << "mp_AddOp is nullptr" << endl;
    }
    else
    {
        mp_AddOp->outputTree();
    }
    if (mp_Term == nullptr)
    {
        cout << "mp_Simple_Expression is nullptr" << endl;
    }
    else
    {
        mp_Term->outputTree();
    }
}

void ExpressionList::outputTree()
{
    cout << "ExpressionList" << endl;

    if (rangeVal.empty())
        cout << "rangeVal is empty" << endl;
    else
        for (auto rangeValmun : rangeVal)
            cout << rangeValmun << endl;

    if (rangeVal.empty())
        cout << "rangeVal is empty" << endl;
    else
        for (auto rangeValmun : rangeVal)
            cout << rangeValmun << endl;

    if (mv_Expression.empty())
        cout << "mv_Expression is empty" << endl;
    else
        for (auto mExpression : mv_Expression)
            mExpression->outputTree();

    if (mv_Type.empty())
        cout << "mv_Type is empty" << endl;
    else
        for (auto mType : mv_Type)
            cout << mType << endl;

    if (mv_VarDefine.empty())
        cout << "mv_VarDefine is empty" << endl;
    else
        for (auto mVarDefine : mv_VarDefine)
            cout << mVarDefine << endl;
}

void Period::outputTree()
{
    cout << "Period" << endl;

    if (mv_dims.empty())
        cout << "mv_dims is empty" << endl;
    else
        for (auto mdims : mv_dims)
            cout << mdims.first << " " << mdims.second << endl;
}

void IdList::outputTree()
{
    cout << "IdList" << endl;
    cout << "m_lineno is " << m_lineno << endl;

    if (mv_Id.empty())
        cout << "mv_Id is empty" << endl;
    else
        for (auto mId : mv_Id)
            mId->outputTree();
}

void Id::outputTree() const
{
    cout << "Id" << endl;
    cout << "m_name is " << m_name << endl;
    cout << "m_idType is " << m_idType << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "m_isVal is " << m_isVal << endl;
}

void MulOp::outputTree() const
{
    cout << "MulOp" << endl;
    cout << "m_mulopType is " << m_mulopType << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "type is " << type << endl;
    if (mp_Term == nullptr)
        cout << "mp_Term is nullptr" << endl;
    else
        mp_Term->outputTree();
    if (mp_Factor == nullptr)
        cout << "mp_Factor is nullptr" << endl;
    else
        mp_Factor->outputTree();
}

void AddOp::outputTree() const
{
    cout << "AddOp" << endl;
    cout << "m_addopType is " << m_addopType << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "type is " << type << endl;
    if (mp_Simple_Expression == nullptr)
        cout << "mp_Simple_Expression is nullptr" << endl;
    else
        mp_Simple_Expression->outputTree();
    if (mp_Term == nullptr)
        cout << "mp_Term is nullptr" << endl;
    else
        mp_Term->outputTree();
}

void RelOp::outputTree() const
{
    cout << "RelOp" << endl;
    cout << "m_relopType is " << m_relopType << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "type is " << type << endl;
    if (mp_Simple_Expression_1 == nullptr)
        cout << "mp_Simple_Expression_1 is nullptr" << endl;
    else
        mp_Simple_Expression_1->outputTree();
    if (mp_Simple_Expression_2 == nullptr)
        cout << "mp_Simple_Expression_2 is nullptr" << endl;
    else
        mp_Simple_Expression_2->outputTree();
}

void Parameter::outputTree() const
{
    cout << "Parameter" << endl;
    cout << "m_isVal is " << m_isVal << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "m_Type is " << m_Type << endl;
    if (mp_Id_List == nullptr)
        cout << "mp_Id_List is nullptr" << endl;
    else
        mp_Id_List->outputTree();
}

void For::outputTree() const
{
    cout << "For" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    if (mp_Id == nullptr)
        cout << "mp_Id is nullptr" << endl;
    else
        mp_Id->outputTree();
    if (mp_Expression_1 == nullptr)
        cout << "mp_Expression_1 is nullptr" << endl;
    else
        mp_Expression_1->outputTree();
    if (mp_Expression_2 == nullptr)
        cout << "mp_Expression_2 is nullptr" << endl;
    else
        mp_Expression_2->outputTree();
    if (mp_Statement == nullptr)
        cout << "mp_Statement is nullptr" << endl;
    else
        mp_Statement->outputTree();
}

void IfThenElse::outputTree() const
{
    cout << "IfThenElse" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    if (mp_Expression == nullptr)
        cout << "mp_Expression is nullptr" << endl;
    else
        mp_Expression->outputTree();
    if (mp_Statement_1 == nullptr)
        cout << "mp_Statement_1 is nullptr" << endl;
    else
        mp_Statement_1->outputTree();
    if (mp_Statement_2 == nullptr)
        cout << "mp_Statement_2 is nullptr" << endl;
    else
        mp_Statement_2->outputTree();
}

void AssignOp::outputTree() const
{
    cout << "AssignOp" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    if (mp_Variable == nullptr)
        cout << "mp_Variable is nullptr" << endl;
    else
        mp_Variable->outputTree();
    if (mp_Expression == nullptr)
        cout << "mp_Expression is nullptr" << endl;
    else
        mp_Expression->outputTree();
}

void ConstValue::outputTree() const
{
    cout << "ConstValue" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "m_isId is " << m_isId << endl;
    cout << "m_postNeg is " << m_postNeg << endl;
    cout << "m_valueType is " << m_valueType << endl;
    cout << "m_int is " << m_int << endl;
    cout << "m_real is " << m_real << endl;
    cout << "m_char is " << m_char << endl;
    cout << "m_bool is " << m_bool << endl;
    if (mp_Id == nullptr)
        cout << "mp_Id is nullptr" << endl;
    else
        mp_Id->outputTree();
}

void Type::outputTree() const
{
    cout << "Type" << endl;
    cout << "m_simpleType is " << m_simpleType << endl;
    cout << "m_isArray is " << m_isArray << endl;
    cout << "m_lineno is " << m_lineno << endl;
    if (mp_Period == nullptr)
        cout << "mp_Period is nullptr" << endl;
    else
        mp_Period->outputTree();
}

void Uminus::outputTree() const
{
    cout << "Uminus" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "rangeVal is " << rangeVal << endl;
    cout << "type is " << type << endl;
    cout << "rangeValid is " << rangeValid << endl;
    cout << "m_unimusType is " << m_unimusType << endl;
    if (mp_Factor == nullptr)
        cout << "mp_Factor is nullptr" << endl;
    else
        mp_Factor->outputTree();
}

void Not::outputTree() const
{
    cout << "Not" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    if (mp_Factor == nullptr)
        cout << "mp_Factor is nullptr" << endl;
    else
        mp_Factor->outputTree();
}

void Factor::outputTree() const
{
    cout << "Factor" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "rangeVal is " << rangeVal << endl;
    cout << "type is " << type << endl;
    cout << "rangeValid is " << rangeValid << endl;
    cout << "m_factorType is " << m_factorType << endl;
    cout << "m_int is " << m_int << endl;
    cout << "m_real is " << m_real << endl;
    cout << "m_char is " << m_char << endl;
    cout << "m_bool is " << m_bool << endl;
    if (mp_Variable == nullptr)
        cout << "mp_Variable is nullptr" << endl;
    else
        mp_Variable->outputTree();
    if (mp_Function_Call == nullptr)
        cout << "mp_Function_Call is nullptr" << endl;
    else
        mp_Function_Call->outputTree();
    if (mp_Expression == nullptr)
        cout << "mp_Expression is nullptr" << endl;
    else
        mp_Expression->outputTree();
    if (mp_Not == nullptr)
        cout << "mp_Not is nullptr" << endl;
    else
        mp_Not->outputTree();
    if (mp_Uminus == nullptr)
        cout << "mp_Uminus is nullptr" << endl;
    else
        mp_Uminus->outputTree();
}

void Term::outputTree() const
{
    cout << "Term" << endl;
    cout << "m_lineno is " << m_lineno << endl;
    cout << "rangeVal is " << rangeVal << endl;
    cout << "type is " << type << endl;
    cout << "rangeValid is " << rangeValid << endl;
    if (mp_MulOp == nullptr)
        cout << "mp_MulOp is nullptr" << endl;
    else
        mp_MulOp->outputTree();
    if (mp_Factor == nullptr)
        cout << "mp_Factor is nullptr" << endl;
    else
        mp_Factor->outputTree();
}

Procedure::Procedure(int lineno, Id *Mp_Id, ParameterList *Mp_Parameter_List,
                     ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations,
                     StatementList *Mp_Statement_List)
{
    m_lineno = lineno;
    mp_Id = Mp_Id;
    mp_Parameter_List = Mp_Parameter_List;
    mp_Const_Declarations = Mp_Const_Declarations;
    mp_Var_Declarations = Mp_Var_Declarations;
    mp_Statement_List = Mp_Statement_List;
}

Function::Function(int returnType, int lineno, Id *Mp_Id, ParameterList *Mp_Parameter_List,
                   ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations,
                   StatementList *Mp_Statement_List)
{
    m_returnType = returnType;
    m_lineno = lineno;
    mp_Id = Mp_Id;
    mp_Parameter_List = Mp_Parameter_List;
    mp_Const_Declarations = Mp_Const_Declarations;
    mp_Var_Declarations = Mp_Var_Declarations;
    mp_Statement_List = Mp_Statement_List;
}
