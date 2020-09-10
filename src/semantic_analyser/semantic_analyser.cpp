#include "syntax_tree.h"
#include "symbol_sheet.h"

#include <iostream>
#include <map>
#include <cassert>
#include <utility>
#include <set>

extern map<SymbolSheetName, SymbolSheet> SymbolSheetList;

// 语义分析，以 DFS 的方式由根结点出发进#Line 错误检测
bool Program::errorDetect() const
{
    bool flag = true;
    if (this->mProgramBody)
        flag = mProgramBody->errorDetect();
    return flag;
}

bool ProgramBody::errorDetect() const
{
    bool flag = true;
    if (mSubProgramDeclarations)
    {
        flag = mSubProgramDeclarations->definitionErrorDetect();
    }
    if (mStatementList)
    {
        flag = mStatementList->errorDetect("0") && flag;
    }
    return flag;
}

bool ConstDeclarations::errorDetect(const string &symbolSheetName)
{
    set<string> idSet;
    bool flag = true;
    for (auto const_symbol : mConstVector)
    {
        if (symbolSheetName != "0" && const_symbol.first->mName == symbolSheetName)
        {
            // 同名检查
            cout << "子程序\"" << symbolSheetName << "\"声明的常量\"" << const_symbol.first->mName
                 << "\"存在与子程序名重复的错误" << endl;
            flag = false;
            break;
        }
        auto result = idSet.insert(const_symbol.first->mName);
        if (!result.second)
        { // 重复声明检查
            if (symbolSheetName == "0")
            {
                cout << "全局常量声明中存在重复声明错误" << endl;
            }
            else
            {
                cout << "子程序\"" << symbolSheetName << "\"常量声明中存在重复声明错误";
            }
            flag = false;
            break;
        }
    }
    return flag;
}

bool VarDeclarations::errorDetect(const string &symbolSheetName)
{
    set<string> idSet;
    SymbolSheet sheet;
    bool flag = true;
    for (auto typeGroup : mVariableVector)
    {
        for (auto id : typeGroup.first->mIdVector)
        {
            string idName = id->mName;
            // 同名检查
            if (symbolSheetName != "0" && idName == symbolSheetName)
            {
                cout << "子程序\"" << symbolSheetName << "\"声明的变量\"" << idName
                     << "\"存在与子程序名相同的错误" << endl;
                flag = false;
                break;
            }
            auto result = idSet.insert(idName);
            if (!result.second)
            { // 重复声明检查
                if (symbolSheetName == "0")
                {
                    cout << "全局变量声明#Line 中存在重复声明错误" << endl;
                }
                else
                {
                    cout << "子程序\"" << symbolSheetName << "\"变量声明#Line 中存在重复声明错误";
                }
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool SubProgramDeclarations::errorDetect(const string &symbolSheetName)
{
    set<string> idSet;
    bool flag = true;
    for (auto subprogram : mCommonVector)
    {
        string idName = subprogram->getFuncId()->mName;
        auto result = idSet.insert(idName);
        if (!result.second)
        { // 重复声明检查
            cout << "子程序\"" << idName << "\"重复声明错误" << endl;
            flag = false;
            break;
        }
    }
    return flag;
}

bool SubProgramDeclarations::definitionErrorDetect()
{
    bool flag = true;
    for (auto subprogram : mCommonVector)
    {
        flag = subprogram->errorDetect() && flag;
    }
    return flag;
}

bool Procedure::errorDetect()
{
    string procedureName = mId->mName;
    SymbolSheet sheet = SymbolSheetList[procedureName];
    bool flag = true;
    if (mParameterList)
        flag = mParameterList->errorDetect(procedureName);
    if (mConstDeclarations)
        flag = flag && mConstDeclarations->errorDetect(procedureName);
    if (mVarDeclarations)
        flag = flag && mVarDeclarations->errorDetect(procedureName);
    if (mStatementList)
        flag = flag && mStatementList->errorDetect(procedureName);
    return flag;
}

bool Function::errorDetect()
{
    string functionName = mId->mName;
    SymbolSheet sheet = SymbolSheetList[functionName];
    bool flag = true;
    if (mParameterList)
        flag = mParameterList->errorDetect(functionName);
    if (mConstDeclarations)
        flag = flag && mConstDeclarations->errorDetect(functionName);
    if (mVarDeclarations)
        flag = flag && mVarDeclarations->errorDetect(functionName);
    if (mStatementList)
        flag = flag && mStatementList->errorDetect(functionName);
    return flag;
}

bool ParameterList::errorDetect(const string &symbolSheetName)
{
    set<string> idSet;
    bool flag = true;
    for (auto parameter : mParameters)
    {
        bool isValue = parameter->mIsVal;
        vector<Id *> parameterSymbols = parameter->getIds();
        for (auto id : parameterSymbols)
        {
            id->mIsVal = isValue;
            string idName = id->mName;
            if (idName == symbolSheetName)
            { // 同名检查
                cout << "子程序\"" << symbolSheetName << "\"声明的形式参数\"" << idName
                     << "\"存在与子程序名相同的错误" << endl;
                flag = false;
                break;
            }
            auto result = idSet.insert(idName);
            if (!result.second)
            { // 重复声明检查
                cout << "子程序\"" << symbolSheetName << "\"声明#Line 中形式参数\"" << idName
                     << "\"存在重复声明错误" << endl;
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool StatementList::errorDetect(const string &symbolSheetName)
{
    bool flag = true;
    for (auto &i : mStatementVector)
    {
        if (i)
        {
            bool flag1 = true;
            flag1 = i->errorDetect(symbolSheetName);
            flag = flag && flag1;
        }
    }
    return flag;
}

bool Statement::errorDetect(const string &symbolSheetName) const
{
    bool flag = true;
    if (mAssignOp) //检查赋值语句的错误
    {
        flag = mAssignOp->errorDetect(symbolSheetName);
    }
    else if (mProcedure_call)
    { //检查过程调用的错误
        flag = mProcedure_call->errorDetect(symbolSheetName);
    }
    else if (mStatementList)
    { //检查语句列表的错误
        flag = mStatementList->errorDetect(symbolSheetName);
    }
    else if (mIfThenElse)
    { //检查分支语句的错误
        flag = mIfThenElse->errorDetect(symbolSheetName);
    }
    else if (mFor)
    { //检查循环语句的错误
        flag = mFor->errorDetect(symbolSheetName);
    }
    else
    {
        cout << "null" << endl;
    }
    return flag;
}

bool AssignOp::errorDetect(const string &symbolSheetName) const
{
    bool flag = true;
    if (mVariable) //对赋值变量进#Line 检错
        flag = mVariable->errorDetect(symbolSheetName);
    if (mExpression) //对表达式进#Line 检错
        flag = flag && mExpression->errorDetect(symbolSheetName);
    int variableType = mVariable->getType();
    int expressiontype = mExpression->getType(); //判断类型是否能转化
    bool flag1 = (variableType == expressiontype ||
                  (variableType == TYPE_INTEGER && expressiontype == TYPE_REAL) ||
                  (expressiontype == TYPE_INTEGER && variableType == TYPE_REAL));
    if (!flag1)
    {
        std::cout << "#Line " << mLineno << ": 类型不能转化" << endl;
        flag = false;
    }
    if (flag1 && variableType == 5 && expressiontype == 5)
    { //特殊处理两个数组类型进#Line 赋值
        int leftArrayType = get_array_type(symbolSheetName, mVariable->mId->getName());
        int rightArrayType = -1;
        try
        {
            rightArrayType = get_array_type(symbolSheetName,
                                            mExpression->mSimpleExpression->mTerm->mFactor->mVariable->mId->getName());
            if (leftArrayType != rightArrayType)
            { //判断元素类型是否相同
                std::cout << "#Line " << mLineno << ": 数组类型不能转化" << endl;
                flag = false;
            } //判断数组大小是否相同
            int leftArrayRange = get_symbol_range(symbolSheetName, mVariable->mId->getName()).size();
            int rightArrayRange = get_symbol_range(symbolSheetName, mExpression->mSimpleExpression->mTerm->mFactor->mVariable->mId->getName()).size();

            if (leftArrayRange != rightArrayRange)
            {
                std::cout << "#Line " << mLineno << ": 数组长度不同" << endl;
                flag = false;
            }
        }
        catch (...)
        {
            flag = false;
            std::cout << "#Line " << mLineno << ":  AST 错误" << endl;
        }
    }
    if (!mVariable || !mExpression)
    { // AST 错误
        flag = false;
        std::cout << "#Line " << mLineno << ":  AST 错误" << endl;
    }
    return flag;
}

bool IfThenElse::errorDetect(const string &symbolSheetName) const
{
    bool flag = true;
    if (mExpression) //判断条件检错
        flag = mExpression->errorDetect(symbolSheetName);
    else
    {
        cout << "#Line " << mLineno << ":  AST 错误" << endl;
        flag = false;
    }
    if (mStatement_1) //then语句检错
        flag = mStatement_1->errorDetect(symbolSheetName) && flag;
    if (mStatement_1 && mStatement_2) //else语句检错
        flag = mStatement_2->errorDetect(symbolSheetName) && flag;
    else if (!mStatement_1 && mStatement_2)
    {
        cout << "#Line " << mLineno << ":  AST 错误" << endl;
        flag = false;
    }
    return flag;
}

bool For::errorDetect(const string &symbolSheetName) const
{
    if (mId && mExpression_1 && mExpression_2) //判断 AST 是否出错
    {                                                //循环变量是否声明
        if (lookup_symbol(symbolSheetName, mId->getName()))
        {
            mId->mIsVal = get_symbol_var_type(symbolSheetName, mId->getName());
            bool flag = true; //起始，终止表达式检错
            int type1 = get_symbol_type(symbolSheetName, mId->getName());
            flag = mExpression_1->errorDetect(symbolSheetName);
            flag = flag && mExpression_2->errorDetect(symbolSheetName);
            int type2 = mExpression_1->getType();
            int type3 = mExpression_2->getType();
            if (!((type1 == TYPE_INTEGER || type1 == TYPE_CHAR) && type1 == type2 && type1 == type3))
            {
                flag = false;
                std::cout << "#Line " << mLineno << ": 循环变量有问题" << endl;

            } //语句检错
            flag = flag && mStatement->errorDetect(symbolSheetName);
            return flag;
        }
        else
        {
            std::cout << "#Line " << mLineno << ": 未声明变量\"" << mId->getName() << "\"" << endl;
            return false;
        }
    }
    else
    {
        std::cout << "#Line " << mId->mLineno << " AST 出错" << endl;
        return false;
    }
}

bool Variable::errorDetect(const string &symbolSheetName)
{
    if (mId)
    {
        if (lookup_symbol(symbolSheetName, mId->getName()))
        {
            int symbolType = get_symbol_type(symbolSheetName, mId->getName());
            mId->mIsVal = get_symbol_var_type(symbolSheetName, mId->getName());
            bool flag = true;
            if (mExpressionList && symbolType != 5)
            { //判断是否是数组
                misArray = false;
                std::cout << "#Line " << mLineno << ": 变量非数组" << endl;
                flag = false;
            }
            else if (mExpressionList && //判断数组维数
                     mExpressionList->getExpressions().size() != get_symbol_range(symbolSheetName, mId->getName()).size())
            {
                misArray = true;
                std::cout << "#Line " << mLineno << ": 数组维数不对" << endl;
                flag = false;
            }
            else if (mExpressionList)
            { //检查数组是否越界
                flag = mExpressionList->errorDetect(symbolSheetName);
                this->type = get_array_type(symbolSheetName, mId->getName());
                vector<int> rangeVal = mExpressionList->rangeVal;
                vector<bool> rangeValid = mExpressionList->rangeValid;
                vector<pair<int, int>> rangeTemp = get_symbol_range(symbolSheetName, mId->getName());
                for (int i = 0; i < rangeTemp.size(); i++)
                {
                    if (rangeValid[i])
                    {
                        if (rangeVal[i] < rangeTemp[i].first || rangeVal[i] > rangeTemp[i].second)
                        {
                            std::cout << "#Line " << mLineno << ": 数组越界" << endl;
                            flag = false;
                        }
                    }
                }
            }
            else
            {
                this->type = symbolType;
                misArray = false;
            }
            return flag;
        }
        else
        {
            std::cout << "#Line " << mLineno << ": 未声明变量\"" << mId->getName() << "\"" << endl;
            return false;
        }
    }
    else
    {
        std::cout << "#Line " << mId->mLineno << " AST 出错" << endl;
        return false;
    }
}

bool FunctionCall::errorDetect(const string &symbolSheetName) const
{
    bool flag = lookup_func(mId->getName()); //判断是否为函数
    if (!flag)
    {
        std::cout << "#Line " << mLineno << ": 非函数" << endl;
        return false;
    }
    int nArgs = get_symbol_narg(symbolSheetName, mId->getName());
    if (nArgs)
    {
        if (nArgs == -1)
        {
            if (mExpressionList)
            {
                if (!mExpressionList->errorDetect(symbolSheetName))
                {
                    return false;
                }
                vector<bool> nargs_var_or_not(this->mExpressionList->mExpressionVector.size(), false);
                this->mExpressionList->mVarDefineVector = nargs_var_or_not;
            }
            return true;
        }
        else
        {
            if (mExpressionList)
            {
                if (!mExpressionList->errorDetect(symbolSheetName))
                {
                    return false;
                } //判断形参个数是否匹配
                if (nArgs != mExpressionList->getTypes().size())
                {
                    std::cout << "#Line " << mLineno << ": 实参形参数量不匹配" << endl;
                    return false;
                }
                vector<int> types = mExpressionList->getTypes();
                vector<int> argTypes = get_symbol_narg_type(symbolSheetName, mId->getName());
                for (int i = 0; i < types.size(); i++)
                {
                    if (types[i] != argTypes[i])
                    { //判断类型是否匹配
                        std::cout << "#Line " << mLineno << ": 第" << i + 1 << "个实参形参不匹配" << endl;
                        flag = false;
                    }
                }
                vector<bool> nArgsVarOrNot = get_symbol_nargs_var_or_not(symbolSheetName, mId->getName());
                this->mExpressionList->mVarDefineVector = nArgsVarOrNot;
            }
        }
    }
    return flag;
}

bool ProcedureCall::errorDetect(const string &symbolSheetName)
{
    // set mproCall_type
    if (mId->getName() == "read")
    {
        mProcedureCallType = PROCECALL_READ;
    }
    else if (mId->getName() == "readln")
    {
        mProcedureCallType = PROCECALL_READLN;
    }
    else if (mId->getName() == "write")
    {
        mProcedureCallType = PROCECALL_WRITE;
    }
    else if (mId->getName() == "writeln")
    {
        mProcedureCallType = PROCECALL_WRITELN;
    }
    else
    {
        mProcedureCallType = PROCECALL_NORMAL;
    }

    bool flag = lookup_procedure(mId->getName()) || lookup_func(mId->getName());
    if (!flag)
    {
        std::cout << "#Line " << mLineno << ": 非过程或者函数" << endl;
        return false;
    }
    int nArgs = get_symbol_narg(symbolSheetName, mId->getName());
    if (nArgs)
    { // builtins n == -1, normal procs n > 0
        if (nArgs == -1)
        {
            // if this proc is a builtin
            // nArgs == -1 -> the proc has variable length (or none) of parameters of any type,
            // used in the builtin procedures, which dont require type & num check
            if (mExpressionList)
            {
                if (!mExpressionList->errorDetect(symbolSheetName))
                {
                    return false;
                }
                // for builtins, the argument cannot be a variable type
                vector<bool> nargs_var_or_not(this->mExpressionList->mExpressionVector.size(), false);
                this->mExpressionList->mVarDefineVector = nargs_var_or_not;
            }
            return true;
        }
        else
        {
            if (mExpressionList)
            {
                if (!mExpressionList->errorDetect(symbolSheetName))
                {
                    return false;
                } //判断形参实参个数
                if (nArgs != mExpressionList->getTypes().size())
                {
                    std::cout << "#Line " << mLineno << ": 实参形参数量不匹配" << endl;
                    return false;
                }
                vector<int> types = mExpressionList->getTypes();
                vector<int> argTypes = get_symbol_narg_type(symbolSheetName, mId->getName());
                for (int i = 0; i < types.size(); i++)
                {
                    if (types[i] != argTypes[i])
                    { //判断形参实参类型
                        std::cout << "#Line " << mLineno << ": 第" << i + 1 << "个实参形参不匹配" << endl;
                        flag = false;
                    }
                }
                vector<bool> nargs_var_or_not = get_symbol_nargs_var_or_not(symbolSheetName, mId->getName());
                this->mExpressionList->mVarDefineVector = nargs_var_or_not;
            }
        }
    }
    return flag;
}

bool Expression::errorDetect(const string &symbolSheetName)
{
    if (mRelOp)
    { //运算符子树检错
        bool flag = mRelOp->errorDetect(symbolSheetName);
        this->setType(mRelOp->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    }
    else if (mSimpleExpression)
    { //对应的简单表达式检错
        bool flag = mSimpleExpression->errorDetect(symbolSheetName);
        setType(mSimpleExpression->getType());
        rangeVal = mSimpleExpression->getRangeVal();
        rangeValid = mSimpleExpression->getRangeValid();
        return flag;
    }
    else
    {
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << mLineno << " AST 出错" << endl;
        return false;
    }
}

bool ExpressionList::errorDetect(const string &symbolSheetName)
{
    bool flag = true;
    for (auto &i : mExpressionVector)
    {
        flag = i->errorDetect(symbolSheetName) && flag; //检测其中所有的表达式
        mTypeVector.push_back(i->getType());
        rangeVal.push_back(i->getRangeVal());
        rangeValid.push_back(i->getRangeValid());
    }
    return flag;
}

bool RelOp::errorDetect(const string &symbolSheetName)
{
    if (mSimple_Expression_1 && mSimple_Expression_2)
    {
        bool flag;
        int type1 = mSimple_Expression_1->getType();
        int type2 = mSimple_Expression_2->getType(); //判断运算符两边是否能进#Line 类型转换
        flag = (type1 == type2 ||
                (type1 == TYPE_INTEGER && type2 == TYPE_REAL) ||
                (type2 == TYPE_INTEGER && type1 == TYPE_REAL));
        if (!flag)
            std::cout << "#Line " << mLineno << "逻辑运算符两边操作数不匹配" << endl;
        setType(TYPE_BOOLEAN);
        return flag;
    }
    else
    {
        std::cout << "#Line " << mLineno << " AST 出错" << endl;
        return false;
    }
}

bool SimpleExpression::errorDetect(const string &symbolSheetName)
{
    if (mAddOp)
    { //判断运算符两边是否有错
        bool flag = mAddOp->errorDetect(symbolSheetName);
        setType(mAddOp->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    }
    else if (mTerm)
    { //判断Term是否有错
        bool flag = mTerm->errorDetect(symbolSheetName);
        setType(mTerm->getType());
        rangeVal = mTerm->getRangeVal();
        rangeValid = mTerm->getRangeValid();
        return flag;
    }
    else
    {
        setType(-1);
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << mLineno << " AST 出错" << endl;
        return false;
    }
}

bool AddOp::errorDetect(const string &symbolSheetName)
{
    bool flag1 = mSimpleExpression->errorDetect(symbolSheetName);
    bool flag2 = mTerm->errorDetect(symbolSheetName);
    bool flag3 = true;
    int type1 = mSimpleExpression->getType();
    int type2 = mTerm->getType(); //不同的运算符，两边有不同的要求
    if (mAddOpType == OP_ADD || mAddOpType == OP_SUB)
    {
        flag3 = ((type1 == TYPE_INTEGER || type1 == TYPE_REAL) && (type2 == TYPE_INTEGER || type2 == TYPE_REAL));
        //即使类型不对也会附一个正确类型，出错以后不会再继续执#Line 代码翻译
        if (!flag3)
            std::cout << "#Line " << mLineno << "加减号两边应该为integer 或者 real" << endl;
        if (type1 == TYPE_REAL || type2 == TYPE_REAL)
            setType(TYPE_REAL); //设置相应的类型
        else
            setType(TYPE_INTEGER);
    }
    else
    {
        flag3 = (type1 == type2 && type1 == TYPE_BOOLEAN);
        if (!flag3)
            std::cout << "#Line " << mLineno << "运算符两边应该为boolean类型" << endl;
        setType(TYPE_BOOLEAN);
    }
    return flag1 && flag2 && flag3;
}

bool Term::errorDetect(const string &symbolSheetName)
{
    if (mMulOp)
    {
        bool flag = mMulOp->errorDetect(symbolSheetName);
        setType(mMulOp->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    }
    else if (mFactor)
    {
        bool flag = mFactor->errorDetect(symbolSheetName);
        setType(mFactor->getType());
        rangeVal = mFactor->getRangeVal();
        rangeValid = mFactor->getRangeValid();
        return flag;
    }
    else
    { //均为空， AST 错误
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << mLineno << " AST 出错" << endl;
        return false;
    }
}

bool MulOp::errorDetect(const string &symbolSheetName)
{
    if (mTerm && mFactor)
    {
        bool flag1 = mTerm->errorDetect(symbolSheetName);
        bool flag2 = mFactor->errorDetect(symbolSheetName);
        int type1 = mTerm->getType();
        int type2 = mFactor->getType();
        int opType = this->checkMulOpType();
        bool flag3 = true; //两边必须为整型或者实型
        if (opType == OP_MULTIPLY || opType == OP_INT_DIV || opType == OP_REAL_DIV)
        {
            flag3 = ((type1 == TYPE_INTEGER || type1 == TYPE_REAL) && (type2 == TYPE_INTEGER || type2 == TYPE_REAL));
            if (type1 == TYPE_REAL || type2 == TYPE_REAL)
                setType(TYPE_REAL);
            else
                setType(TYPE_INTEGER);
        }
        else if (opType == OP_MOD)
        { //模运算两边必须为整型
            flag3 = (type1 == type2) && (type1 == TYPE_INTEGER);
            setType(TYPE_INTEGER);
        }
        else
        { //逻辑运算符两边必须为boolean 型
            flag3 = (type1 == type2 && type1 == TYPE_BOOLEAN);
            setType(TYPE_BOOLEAN);
        }
        if (!(flag1 && flag2 && flag3))
        {
            if (!flag3)
            {
                std::cout << "#Line " << mLineno << ": 运算符两边类型不匹配." << endl;
            }
            return false;
        }
        return true;
    }
    else
    {
        std::cout << "#Line " << mLineno << " AST 出错" << endl;
        return false;
    }
}

bool Factor::errorDetect(const string &symbolSheetName)
{
    bool flag = true; //按类型设置节点类型，并进#Line 相应的错误检测
    switch (mFactorType)
    {
    case FACTOR_VALUE_BOOL:
    {
        rangeVal = -1;
        rangeValid = false;
        setType(TYPE_BOOLEAN);
        break;
    }
    case FACTOR_VALUE_INT:
    {

        rangeVal = mInt;
        rangeValid = true;
        setType(TYPE_INTEGER);
        break;
    }
    case FACTOR_VALUE_CHAR:
    {
        rangeVal = -1;
        rangeValid = false;
        setType(TYPE_CHAR);
        break;
    }
    case FACTOR_VALUE_REAL:
    {
        rangeVal = -1;
        rangeValid = false;
        setType(TYPE_REAL);
        break;
    }
    case FACTOR_VAR:
    {
        rangeVal = -1;
        rangeValid = false;
        flag = mVariable->errorDetect(symbolSheetName);
        setType(mVariable->getType());
        break;
    }
    case FACTOR_FUNCCALL:
    {
        rangeVal = -1;
        rangeValid = false;
        flag = mFunction_Call->errorDetect(symbolSheetName);
        setType(get_func_return_type(mFunction_Call->mId->getName()));
        break;
    }
    case FACTOR_BRACKETS:
    {
        rangeVal = -1;
        rangeValid = false;
        flag = mExpression->errorDetect(symbolSheetName);
        setType(mExpression->getType());
        break;
    }
    case FACTOR_NOT:
    {
        rangeVal = -1;
        rangeValid = false;
        flag = mNot->errorDetect(symbolSheetName);
        setType(TYPE_BOOLEAN);
        break;
    }
    case FACTOR_UMINUS:
    {
        int typeTemp = mUminus->getType();
        flag = mUminus->errorDetect(symbolSheetName);
        setType(mUminus->getType());
        if (typeTemp != TYPE_INTEGER)
        {
            rangeVal = -1;
            rangeValid = false;
        }
        else
        {
            rangeVal = mUminus->getRangeVal();
            rangeValid = true;
        }
        break;
    }

    default:
    {
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << mLineno << " AST 出错" << endl;
        return false;
    }
    }
    return flag;
}

bool Not::errorDetect(const string &symbolSheetName) const
{
    if (mFactor)
    {
        bool flag = true;
        flag = mFactor->errorDetect(symbolSheetName);
        int typeTemp = mFactor->getType();
        if (typeTemp != TYPE_BOOLEAN)
        { //只有Boolean型能取反
            flag = false;
            std::cout << "#Line " << mLineno << ": 非boolean类型不能not" << endl;
        }
        return flag;
    }
    else
    {
        std::cout << "#Line " << mLineno << " AST 出错" << endl;
        return false;
    }
}

bool Uminus::errorDetect(const string &symbolSheetName)
{
    if (mFactor)
    {
        bool flag = mFactor->errorDetect(symbolSheetName);
        int typeTemp = mFactor->getType();
        if (typeTemp != TYPE_INTEGER && typeTemp != TYPE_REAL)
        {
            flag = false; //只有整型，实型能去算术取反
            std::cout << "#Line " << mLineno << ": 类型不匹配" << endl;
        }
        rangeVal = mFactor->getRangeVal();
        rangeVal = mUnimusType == 0 ? rangeVal : rangeValid;
        rangeValid = mFactor->getRangeValid();
        setType(typeTemp);
        return flag;
    }
    else
    {
        setType(TYPE_INTEGER);
        std::cout << "#Line " << mLineno << ":  AST 出错" << endl;
        return false;
    }
}

// 语义分析接口
bool semantic_analyse(Program *root)
{
    bool flag = true;
    //　创建全局符号表
    if (root->mProgramBody)
        flag = root->mProgramBody->createSymbolSheet().first;
    if (flag)
        assert(!SymbolSheetList.empty());
    // 为定义的函数、过程建立自符号表
    if (!root->mProgramBody->mSubProgramDeclarations->mCommonVector.empty())
    {
        for (auto subprogram : root->mProgramBody->mSubProgramDeclarations->mCommonVector)
        {
            flag = flag && subprogram->createSymbolSheet().first;
            if (!flag)
            {
                break;
            }
        }
    }
    if (flag)
        assert(SymbolSheetList.find("0") != SymbolSheetList.end());
    // 从 AST 根节点开始语义分析
    if (flag)
    {
        flag = root->errorDetect() && flag;
    }
    return flag;
}
