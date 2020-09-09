#include "syntax_tree.h"
#include <iostream>

using namespace std;

void Program::outputTree() const
{
    cout << "Program" << endl;
    if (m_PID == nullptr)
        cout << "m_PID is nullptr" << endl;
    else
        m_PID->outputTree();
    if (m_PIDList == nullptr)
        cout << "IdList is nullptr" << endl;
    else
        m_PIDList->outputTree();
    if (m_PProgramBody == nullptr)
        cout << "m_PProgramBody is nullptr" << endl;
    else
        m_PProgramBody->outputTree();
}

void ProgramBody::outputTree() const
{
    cout << "ProgramBody" << endl;
    if (m_PConstDeclarations == nullptr)
        cout << "m_PConstDeclarations is nullptr" << endl;
    else
        m_PConstDeclarations->outputTree();
    if (m_PVarDeclarations == nullptr)
        cout << "m_PVarDeclarations is nullptr" << endl;
    else
        m_PVarDeclarations->outputTree();
    if (m_PSubProgramDeclarations == nullptr)
        cout << "m_PSubProgramDeclarations is nullptr" << endl;
    else
        m_PSubProgramDeclarations->outputTree();
    if (m_PStatementList == nullptr)
        cout << "m_PStatementList is nullptr" << endl;
    else
        m_PStatementList->outputTree();
}

void ConstDeclarations::outputTree()
{
    cout << "ConstDeclarations" << endl;
    if (m_ConstVector.empty())
        cout << "m_ConstVector is nullptr" << endl;
    else
        for (auto &i : m_ConstVector)
        {
            i.first->outputTree();
            i.second->outputTree();
        }
}

void VarDeclarations::outputTree()
{
    cout << "VarDeclarations";
    if (m_VariableVector.empty())
        cout << "m_VariableVector is nullptr" << endl;
    else
        for (auto &i : m_VariableVector)
        {
            i.first->outputTree();
            i.second->outputTree();
        }
}

void SubProgramDeclarations::outputTree()
{
    cout << "SubProgramDeclarations" << endl;
    if (m_CommonVector.empty())
        cout << "m_CommonVector is nullptr" << endl;
    else
        for (auto &i : m_CommonVector)
        {
            i->outputTree();
        }
}

void StatementList::outputTree()
{
    cout << "StatementList" << endl;
    if (m_StatementVector.empty())
        cout << "m_StatementVector is nullptr" << endl;
    for (auto &i : m_StatementVector)
    {
        i->outputTree();
    }
}

void Procedure::outputTree()
{
    cout << "Procedure" << endl;
    cout << "m_lineo = " << m_Lineno << endl;
    if (m_PID == nullptr)
    {
        cout << "m_PID is nullptr" << endl;
    }
    else
    {
        m_PID->outputTree();
    }
    if (m_PParameterList == nullptr)
    {
        cout << "m_PParameterList is nullptr" << endl;
    }
    else
    {
        m_PParameterList->outputTree();
    }
    if (m_PConstDeclarations == nullptr)
    {
        cout << "m_PConstDeclarations is nullptr" << endl;
    }
    else
    {
        m_PConstDeclarations->outputTree();
    }
    if (m_PVarDeclarations == nullptr)
    {
        cout << "m_PVarDeclarations is nullptr" << endl;
    }
    else
    {
        m_PVarDeclarations->outputTree();
    }
    if (m_PStatementList == nullptr)
    {
        cout << "m_PStatementList is nullptr" << endl;
    }
    else
    {
        m_PStatementList->outputTree();
    }
}

void Function::outputTree()
{
    cout << "Function" << endl;
    cout << "m_ReturnType = " << m_ReturnType << endl;
    cout << "m_lineo = " << m_Lineno << endl;
    if (m_PID == nullptr)
    {
        cout << "m_PID is nullptr" << endl;
    }
    else
    {
        m_PID->outputTree();
    }
    if (m_PParameterList == nullptr)
    {
        cout << "m_PParameterList is nullptr" << endl;
    }
    else
    {
        m_PParameterList->outputTree();
    }
    if (m_PConstDeclarations == nullptr)
    {
        cout << "m_PConstDeclarations is nullptr" << endl;
    }
    else
    {
        m_PConstDeclarations->outputTree();
    }
    if (m_PVarDeclarations == nullptr)
    {
        cout << "m_PVarDeclarations is nullptr" << endl;
    }
    else
    {
        m_PVarDeclarations->outputTree();
    }
    if (m_PStatementList == nullptr)
    {
        cout << "m_PStatementList is nullptr" << endl;
    }
    else
    {
        m_PStatementList->outputTree();
    }
}

void Statement::outputTree() const
{
    cout << "Statement" << endl;
    cout << "m_stateType = " << m_stateType << endl;
    cout << "m_Lineno = " << m_Lineno << endl;
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
    if (m_PStatementList == nullptr)
    {
        cout << "m_PStatementList is nullptr" << endl;
    }
    else
    {
        m_PStatementList->outputTree();
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
    cout << "m_Lineno = " << m_Lineno << endl;
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
    cout << "m_Lineno = " << m_Lineno << endl;
    if (m_PID == nullptr)
    {
        cout << "m_PID is nullptr" << endl;
    }
    else
    {
        m_PID->outputTree();
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
    cout << "m_Lineno = " << m_Lineno << endl;
    if (m_PID == nullptr)
    {
        cout << "m_PID is nullptr" << endl;
    }
    else
    {
        m_PID->outputTree();
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
    cout << "m_Lineno = " << m_Lineno << endl;
    if (m_PID == nullptr)
    {
        cout << "m_PID is nullptr" << endl;
    }
    else
    {
        m_PID->outputTree();
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
    cout << "m_Lineno = " << m_Lineno << endl;
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
    cout << "m_Lineno = " << m_Lineno << endl;
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
    if (m_PTerm == nullptr)
    {
        cout << "mp_Simple_Expression is nullptr" << endl;
    }
    else
    {
        m_PTerm->outputTree();
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

    if (m_ExpressionVector.empty())
        cout << "m_ExpressionVector is empty" << endl;
    else
        for (auto mExpression : m_ExpressionVector)
            mExpression->outputTree();

    if (m_TypeVector.empty())
        cout << "m_TypeVector is empty" << endl;
    else
        for (auto mType : m_TypeVector)
            cout << mType << endl;

    if (m_VarDefineVector.empty())
        cout << "m_VarDefineVector is empty" << endl;
    else
        for (auto mVarDefine : m_VarDefineVector)
            cout << mVarDefine << endl;
}

void Period::outputTree()
{
    cout << "Period" << endl;

    if (m_DimsVector.empty())
        cout << "m_DimsVector is empty" << endl;
    else
        for (auto mdims : m_DimsVector)
            cout << mdims.first << " " << mdims.second << endl;
}

void IdList::outputTree()
{
    cout << "IdList" << endl;
    cout << "m_Lineno is " << m_Lineno << endl;

    if (m_IDVector.empty())
        cout << "m_IDVector is empty" << endl;
    else
        for (auto mId : m_IDVector)
            mId->outputTree();
}

void Id::outputTree() const
{
    cout << "Id" << endl;
    cout << "m_Name is " << m_Name << endl;
    cout << "m_IDType is " << m_IDType << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    cout << "m_IsVal is " << m_IsVal << endl;
}

void MulOp::outputTree() const
{
    cout << "MulOp" << endl;
    cout << "m_mulopType is " << m_mulopType << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    cout << "type is " << type << endl;
    if (m_PTerm == nullptr)
        cout << "m_PTerm is nullptr" << endl;
    else
        m_PTerm->outputTree();
    if (m_PFactor == nullptr)
        cout << "m_PFactor is nullptr" << endl;
    else
        m_PFactor->outputTree();
}

void AddOp::outputTree() const
{
    cout << "AddOp" << endl;
    cout << "m_addopType is " << m_addopType << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    cout << "type is " << type << endl;
    if (mp_Simple_Expression == nullptr)
        cout << "mp_Simple_Expression is nullptr" << endl;
    else
        mp_Simple_Expression->outputTree();
    if (m_PTerm == nullptr)
        cout << "m_PTerm is nullptr" << endl;
    else
        m_PTerm->outputTree();
}

void RelOp::outputTree() const
{
    cout << "RelOp" << endl;
    cout << "m_relopType is " << m_relopType << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
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
    cout << "m_IsVal is " << m_IsVal << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    cout << "m_Type is " << m_Type << endl;
    if (m_PIDList == nullptr)
        cout << "m_PIDList is nullptr" << endl;
    else
        m_PIDList->outputTree();
}

void For::outputTree() const
{
    cout << "For" << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    if (m_PID == nullptr)
        cout << "m_PID is nullptr" << endl;
    else
        m_PID->outputTree();
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
    cout << "m_Lineno is " << m_Lineno << endl;
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
    cout << "m_Lineno is " << m_Lineno << endl;
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
    cout << "m_Lineno is " << m_Lineno << endl;
    cout << "m_isId is " << m_isId << endl;
    cout << "m_postNeg is " << m_postNeg << endl;
    cout << "m_valueType is " << m_valueType << endl;
    cout << "m_int is " << m_int << endl;
    cout << "m_real is " << m_real << endl;
    cout << "m_char is " << m_char << endl;
    cout << "m_bool is " << m_bool << endl;
    if (m_PID == nullptr)
        cout << "m_PID is nullptr" << endl;
    else
        m_PID->outputTree();
}

void Type::outputTree() const
{
    cout << "Type" << endl;
    cout << "m_SimpleType is " << m_SimpleType << endl;
    cout << "m_isArray is " << m_isArray << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    if (mp_Period == nullptr)
        cout << "mp_Period is nullptr" << endl;
    else
        mp_Period->outputTree();
}

void Uminus::outputTree() const
{
    cout << "Uminus" << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    cout << "rangeVal is " << rangeVal << endl;
    cout << "type is " << type << endl;
    cout << "rangeValid is " << rangeValid << endl;
    cout << "m_unimusType is " << m_unimusType << endl;
    if (m_PFactor == nullptr)
        cout << "m_PFactor is nullptr" << endl;
    else
        m_PFactor->outputTree();
}

void Not::outputTree() const
{
    cout << "Not" << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
    if (m_PFactor == nullptr)
        cout << "m_PFactor is nullptr" << endl;
    else
        m_PFactor->outputTree();
}

void Factor::outputTree() const
{
    cout << "Factor" << endl;
    cout << "m_Lineno is " << m_Lineno << endl;
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
    cout << "m_Lineno is " << m_Lineno << endl;
    cout << "rangeVal is " << rangeVal << endl;
    cout << "type is " << type << endl;
    cout << "rangeValid is " << rangeValid << endl;
    if (mp_MulOp == nullptr)
        cout << "mp_MulOp is nullptr" << endl;
    else
        mp_MulOp->outputTree();
    if (m_PFactor == nullptr)
        cout << "m_PFactor is nullptr" << endl;
    else
        m_PFactor->outputTree();
}

Procedure::Procedure(int lineno, Id *Mp_Id, ParameterList *Mp_Parameter_List,
                     ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations,
                     StatementList *Mp_Statement_List)
{
    m_Lineno = lineno;
    m_PID = Mp_Id;
    m_PParameterList = Mp_Parameter_List;
    m_PConstDeclarations = Mp_Const_Declarations;
    m_PVarDeclarations = Mp_Var_Declarations;
    m_PStatementList = Mp_Statement_List;
}

Function::Function(int returnType, int lineno, Id *Mp_Id, ParameterList *Mp_Parameter_List,
                   ConstDeclarations *Mp_Const_Declarations, VarDeclarations *Mp_Var_Declarations,
                   StatementList *Mp_Statement_List)
{
    m_ReturnType = returnType;
    m_Lineno = lineno;
    m_PID = Mp_Id;
    m_PParameterList = Mp_Parameter_List;
    m_PConstDeclarations = Mp_Const_Declarations;
    m_PVarDeclarations = Mp_Var_Declarations;
    m_PStatementList = Mp_Statement_List;
}
