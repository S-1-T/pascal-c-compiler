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
    if (this->m_PProgramBody)
        flag = m_PProgramBody->errorDetect();
    return flag;
}

bool ProgramBody::errorDetect() const
{
    bool flag = true;
    if (m_PSubProgramDeclarations)
    {
        flag = m_PSubProgramDeclarations->definitionErrorDetect();
    }
    if (m_PStatementList)
    {
        flag = m_PStatementList->errorDetect("0") && flag;
    }
    return flag;
}

bool ConstDeclarations::errorDetect(const string &symbolSheetName)
{
    set<string> idSet;
    bool flag = true;
    for (auto const_symbol : m_ConstVector)
    {
        if (symbolSheetName != "0" && const_symbol.first->m_Name == symbolSheetName)
        {
            // 同名检查
            cout << "子程序\"" << symbolSheetName << "\"声明的常量\"" << const_symbol.first->m_Name
                 << "\"存在与子程序名重复的错误" << endl;
            flag = false;
            break;
        }
        auto result = idSet.insert(const_symbol.first->m_Name);
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
    for (auto typeGroup : m_VariableVector)
    {
        for (auto id : typeGroup.first->m_IDVector)
        {
            string idName = id->m_Name;
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
    for (auto subprogram : m_CommonVector)
    {
        string idName = subprogram->getFuncId()->m_Name;
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
    for (auto subprogram : m_CommonVector)
    {
        flag = subprogram->errorDetect() && flag;
    }
    return flag;
}

bool Procedure::errorDetect()
{
    string procedureName = m_PID->m_Name;
    SymbolSheet sheet = SymbolSheetList[procedureName];
    bool flag = true;
    if (m_PParameterList)
        flag = m_PParameterList->errorDetect(procedureName);
    if (m_PConstDeclarations)
        flag = flag && m_PConstDeclarations->errorDetect(procedureName);
    if (m_PVarDeclarations)
        flag = flag && m_PVarDeclarations->errorDetect(procedureName);
    if (m_PStatementList)
        flag = flag && m_PStatementList->errorDetect(procedureName);
    return flag;
}

bool Function::errorDetect()
{
    string functionName = m_PID->m_Name;
    SymbolSheet sheet = SymbolSheetList[functionName];
    bool flag = true;
    if (m_PParameterList)
        flag = m_PParameterList->errorDetect(functionName);
    if (m_PConstDeclarations)
        flag = flag && m_PConstDeclarations->errorDetect(functionName);
    if (m_PVarDeclarations)
        flag = flag && m_PVarDeclarations->errorDetect(functionName);
    if (m_PStatementList)
        flag = flag && m_PStatementList->errorDetect(functionName);
    return flag;
}

bool ParameterList::errorDetect(const string &symbolSheetName)
{
    set<string> idSet;
    bool flag = true;
    for (auto parameter : mv_Patameter)
    {
        bool isValue = parameter->m_IsVal;
        vector<Id *> parameterSymbols = parameter->getIds();
        for (auto id : parameterSymbols)
        {
            id->m_IsVal = isValue;
            string idName = id->m_Name;
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
    for (auto &i : m_StatementVector)
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
    if (mp_AssignOp) //检查赋值语句的错误
    {
        flag = mp_AssignOp->errorDetect(symbolSheetName);
    }
    else if (mp_Procedure_call)
    { //检查过程调用的错误
        flag = mp_Procedure_call->errorDetect(symbolSheetName);
    }
    else if (m_PStatementList)
    { //检查语句列表的错误
        flag = m_PStatementList->errorDetect(symbolSheetName);
    }
    else if (mp_If_Then_Else)
    { //检查分支语句的错误
        flag = mp_If_Then_Else->errorDetect(symbolSheetName);
    }
    else if (mp_For)
    { //检查循环语句的错误
        flag = mp_For->errorDetect(symbolSheetName);
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
    if (mp_Variable) //对赋值变量进#Line 检错
        flag = mp_Variable->errorDetect(symbolSheetName);
    if (mp_Expression) //对表达式进#Line 检错
        flag = flag && mp_Expression->errorDetect(symbolSheetName);
    int variableType = mp_Variable->getType();
    int expressiontype = mp_Expression->getType(); //判断类型是否能转化
    bool flag1 = (variableType == expressiontype ||
                  (variableType == TYPE_INTEGER && expressiontype == TYPE_REAL) ||
                  (expressiontype == TYPE_INTEGER && variableType == TYPE_REAL));
    if (!flag1)
    {
        std::cout << "#Line " << m_Lineno << ": 类型不能转化" << endl;
        flag = false;
    }
    if (flag1 && variableType == 5 && expressiontype == 5)
    { //特殊处理两个数组类型进#Line 赋值
        int leftArrayType = get_array_type(symbolSheetName, mp_Variable->m_PID->getName());
        int rightArrayType = -1;
        try
        {
            rightArrayType = get_array_type(symbolSheetName,
                                            mp_Expression->mp_Simple_Expression->m_PTerm->m_PFactor->mp_Variable->m_PID->getName());
            if (leftArrayType != rightArrayType)
            { //判断元素类型是否相同
                std::cout << "#Line " << m_Lineno << ": 数组类型不能转化" << endl;
                flag = false;
            } //判断数组大小是否相同
            int leftArrayRange = get_symbol_range(symbolSheetName, mp_Variable->m_PID->getName()).size();
            int rightArrayRange = get_symbol_range(symbolSheetName, mp_Expression->mp_Simple_Expression->m_PTerm->m_PFactor->mp_Variable->m_PID->getName()).size();

            if (leftArrayRange != rightArrayRange)
            {
                std::cout << "#Line " << m_Lineno << ": 数组长度不同" << endl;
                flag = false;
            }
        }
        catch (...)
        {
            flag = false;
            std::cout << "#Line " << m_Lineno << ":  AST 错误" << endl;
        }
    }
    if (!mp_Variable || !mp_Expression)
    { // AST 错误
        flag = false;
        std::cout << "#Line " << m_Lineno << ":  AST 错误" << endl;
    }
    return flag;
}

bool IfThenElse::errorDetect(const string &symbolSheetName) const
{
    bool flag = true;
    if (mp_Expression) //判断条件检错
        flag = mp_Expression->errorDetect(symbolSheetName);
    else
    {
        cout << "#Line " << m_Lineno << ":  AST 错误" << endl;
        flag = false;
    }
    if (mp_Statement_1) //then语句检错
        flag = mp_Statement_1->errorDetect(symbolSheetName) && flag;
    if (mp_Statement_1 && mp_Statement_2) //else语句检错
        flag = mp_Statement_2->errorDetect(symbolSheetName) && flag;
    else if (!mp_Statement_1 && mp_Statement_2)
    {
        cout << "#Line " << m_Lineno << ":  AST 错误" << endl;
        flag = false;
    }
    return flag;
}

bool For::errorDetect(const string &symbolSheetName) const
{
    if (m_PID && mp_Expression_1 && mp_Expression_2) //判断 AST 是否出错
    {                                                //循环变量是否声明
        if (lookup_symbol(symbolSheetName, m_PID->getName()))
        {
            m_PID->m_IsVal = get_symbol_var_type(symbolSheetName, m_PID->getName());
            bool flag = true; //起始，终止表达式检错
            int type1 = get_symbol_type(symbolSheetName, m_PID->getName());
            flag = mp_Expression_1->errorDetect(symbolSheetName);
            flag = flag && mp_Expression_2->errorDetect(symbolSheetName);
            int type2 = mp_Expression_1->getType();
            int type3 = mp_Expression_2->getType();
            if (!((type1 == TYPE_INTEGER || type1 == TYPE_CHAR) && type1 == type2 && type1 == type3))
            {
                flag = false;
                std::cout << "#Line " << m_Lineno << ": 循环变量有问题" << endl;

            } //语句检错
            flag = flag && mp_Statement->errorDetect(symbolSheetName);
            return flag;
        }
        else
        {
            std::cout << "#Line " << m_Lineno << ": 未声明变量\"" << m_PID->getName() << "\"" << endl;
            return false;
        }
    }
    else
    {
        std::cout << "#Line " << m_PID->m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool Variable::errorDetect(const string &symbolSheetName)
{
    if (m_PID)
    {
        if (lookup_symbol(symbolSheetName, m_PID->getName()))
        {
            int symbolType = get_symbol_type(symbolSheetName, m_PID->getName());
            m_PID->m_IsVal = get_symbol_var_type(symbolSheetName, m_PID->getName());
            bool flag = true;
            if (mp_Expression_List && symbolType != 5)
            { //判断是否是数组
                m_isArray = false;
                std::cout << "#Line " << m_Lineno << ": 变量非数组" << endl;
                flag = false;
            }
            else if (mp_Expression_List && //判断数组维数
                     mp_Expression_List->getExpressions().size() != get_symbol_range(symbolSheetName, m_PID->getName()).size())
            {
                m_isArray = true;
                std::cout << "#Line " << m_Lineno << ": 数组维数不对" << endl;
                flag = false;
            }
            else if (mp_Expression_List)
            { //检查数组是否越界
                flag = mp_Expression_List->errorDetect(symbolSheetName);
                this->type = get_array_type(symbolSheetName, m_PID->getName());
                vector<int> rangeVal = mp_Expression_List->rangeVal;
                vector<bool> rangeValid = mp_Expression_List->rangeValid;
                vector<pair<int, int>> rangeTemp = get_symbol_range(symbolSheetName, m_PID->getName());
                for (int i = 0; i < rangeTemp.size(); i++)
                {
                    if (rangeValid[i])
                    {
                        if (rangeVal[i] < rangeTemp[i].first || rangeVal[i] > rangeTemp[i].second)
                        {
                            std::cout << "#Line " << m_Lineno << ": 数组越界" << endl;
                            flag = false;
                        }
                    }
                }
            }
            else
            {
                this->type = symbolType;
                m_isArray = false;
            }
            return flag;
        }
        else
        {
            std::cout << "#Line " << m_Lineno << ": 未声明变量\"" << m_PID->getName() << "\"" << endl;
            return false;
        }
    }
    else
    {
        std::cout << "#Line " << m_PID->m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool FunctionCall::errorDetect(const string &symbolSheetName) const
{
    bool flag = lookup_func(m_PID->getName()); //判断是否为函数
    if (!flag)
    {
        std::cout << "#Line " << m_Lineno << ": 非函数" << endl;
        return false;
    }
    int nArgs = get_symbol_narg(symbolSheetName, m_PID->getName());
    if (nArgs)
    {
        if (nArgs == -1)
        {
            if (mp_Expression_List)
            {
                if (!mp_Expression_List->errorDetect(symbolSheetName))
                {
                    return false;
                }
                vector<bool> nargs_var_or_not(this->mp_Expression_List->m_ExpressionVector.size(), false);
                this->mp_Expression_List->m_VarDefineVector = nargs_var_or_not;
            }
            return true;
        }
        else
        {
            if (mp_Expression_List)
            {
                if (!mp_Expression_List->errorDetect(symbolSheetName))
                {
                    return false;
                } //判断形参个数是否匹配
                if (nArgs != mp_Expression_List->getTypes().size())
                {
                    std::cout << "#Line " << m_Lineno << ": 实参形参数量不匹配" << endl;
                    return false;
                }
                vector<int> types = mp_Expression_List->getTypes();
                vector<int> argTypes = get_symbol_narg_type(symbolSheetName, m_PID->getName());
                for (int i = 0; i < types.size(); i++)
                {
                    if (types[i] != argTypes[i])
                    { //判断类型是否匹配
                        std::cout << "#Line " << m_Lineno << ": 第" << i + 1 << "个实参形参不匹配" << endl;
                        flag = false;
                    }
                }
                vector<bool> nArgsVarOrNot = get_symbol_nargs_var_or_not(symbolSheetName, m_PID->getName());
                this->mp_Expression_List->m_VarDefineVector = nArgsVarOrNot;
            }
        }
    }
    return flag;
}

bool ProcedureCall::errorDetect(const string &symbolSheetName)
{
    // set m_proCall_type
    if (m_PID->getName() == "read")
    {
        m_proCall_Tpye = PROCECALL_READ;
    }
    else if (m_PID->getName() == "readln")
    {
        m_proCall_Tpye = PROCECALL_READLN;
    }
    else if (m_PID->getName() == "write")
    {
        m_proCall_Tpye = PROCECALL_WRITE;
    }
    else if (m_PID->getName() == "writeln")
    {
        m_proCall_Tpye = PROCECALL_WRITELN;
    }
    else
    {
        m_proCall_Tpye = PROCECALL_NORMAL;
    }

    bool flag = lookup_procedure(m_PID->getName()) || lookup_func(m_PID->getName());
    if (!flag)
    {
        std::cout << "#Line " << m_Lineno << ": 非过程或者函数" << endl;
        return false;
    }
    int nArgs = get_symbol_narg(symbolSheetName, m_PID->getName());
    if (nArgs)
    { // builtins n == -1, normal procs n > 0
        if (nArgs == -1)
        {
            // if this proc is a builtin
            // nArgs == -1 -> the proc has variable length (or none) of parameters of any type,
            // used in the builtin procedures, which dont require type & num check
            if (mp_Expression_List)
            {
                if (!mp_Expression_List->errorDetect(symbolSheetName))
                {
                    return false;
                }
                // for builtins, the argument cannot be a variable type
                vector<bool> nargs_var_or_not(this->mp_Expression_List->m_ExpressionVector.size(), false);
                this->mp_Expression_List->m_VarDefineVector = nargs_var_or_not;
            }
            return true;
        }
        else
        {
            if (mp_Expression_List)
            {
                if (!mp_Expression_List->errorDetect(symbolSheetName))
                {
                    return false;
                } //判断形参实参个数
                if (nArgs != mp_Expression_List->getTypes().size())
                {
                    std::cout << "#Line " << m_Lineno << ": 实参形参数量不匹配" << endl;
                    return false;
                }
                vector<int> types = mp_Expression_List->getTypes();
                vector<int> argTypes = get_symbol_narg_type(symbolSheetName, m_PID->getName());
                for (int i = 0; i < types.size(); i++)
                {
                    if (types[i] != argTypes[i])
                    { //判断形参实参类型
                        std::cout << "#Line " << m_Lineno << ": 第" << i + 1 << "个实参形参不匹配" << endl;
                        flag = false;
                    }
                }
                vector<bool> nargs_var_or_not = get_symbol_nargs_var_or_not(symbolSheetName, m_PID->getName());
                this->mp_Expression_List->m_VarDefineVector = nargs_var_or_not;
            }
        }
    }
    return flag;
}

bool Expression::errorDetect(const string &symbolSheetName)
{
    if (mp_Relop)
    { //运算符子树检错
        bool flag = mp_Relop->errorDetect(symbolSheetName);
        this->setType(mp_Relop->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    }
    else if (mp_Simple_Expression)
    { //对应的简单表达式检错
        bool flag = mp_Simple_Expression->errorDetect(symbolSheetName);
        setType(mp_Simple_Expression->getType());
        rangeVal = mp_Simple_Expression->getRangeVal();
        rangeValid = mp_Simple_Expression->getRangeValid();
        return flag;
    }
    else
    {
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool ExpressionList::errorDetect(const string &symbolSheetName)
{
    bool flag = true;
    for (auto &i : m_ExpressionVector)
    {
        flag = i->errorDetect(symbolSheetName) && flag; //检测其中所有的表达式
        m_TypeVector.push_back(i->getType());
        rangeVal.push_back(i->getRangeVal());
        rangeValid.push_back(i->getRangeValid());
    }
    return flag;
}

bool RelOp::errorDetect(const string &symbolSheetName)
{
    if (mp_Simple_Expression_1 && mp_Simple_Expression_2)
    {
        bool flag;
        int type1 = mp_Simple_Expression_1->getType();
        int type2 = mp_Simple_Expression_2->getType(); //判断运算符两边是否能进#Line 类型转换
        flag = (type1 == type2 ||
                (type1 == TYPE_INTEGER && type2 == TYPE_REAL) ||
                (type2 == TYPE_INTEGER && type1 == TYPE_REAL));
        if (!flag)
            std::cout << "#Line " << m_Lineno << "逻辑运算符两边操作数不匹配" << endl;
        setType(TYPE_BOOLEAN);
        return flag;
    }
    else
    {
        std::cout << "#Line " << m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool SimpleExpression::errorDetect(const string &symbolSheetName)
{
    if (mp_AddOp)
    { //判断运算符两边是否有错
        bool flag = mp_AddOp->errorDetect(symbolSheetName);
        setType(mp_AddOp->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    }
    else if (m_PTerm)
    { //判断Term是否有错
        bool flag = m_PTerm->errorDetect(symbolSheetName);
        setType(m_PTerm->getType());
        rangeVal = m_PTerm->getRangeVal();
        rangeValid = m_PTerm->getRangeValid();
        return flag;
    }
    else
    {
        setType(-1);
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool AddOp::errorDetect(const string &symbolSheetName)
{
    bool flag1 = mp_Simple_Expression->errorDetect(symbolSheetName);
    bool flag2 = m_PTerm->errorDetect(symbolSheetName);
    bool flag3 = true;
    int type1 = mp_Simple_Expression->getType();
    int type2 = m_PTerm->getType(); //不同的运算符，两边有不同的要求
    if (m_addopType == OP_ADD || m_addopType == OP_SUB)
    {
        flag3 = ((type1 == TYPE_INTEGER || type1 == TYPE_REAL) && (type2 == TYPE_INTEGER || type2 == TYPE_REAL));
        //即使类型不对也会附一个正确类型，出错以后不会再继续执#Line 代码翻译
        if (!flag3)
            std::cout << "#Line " << m_Lineno << "加减号两边应该为integer 或者 real" << endl;
        if (type1 == TYPE_REAL || type2 == TYPE_REAL)
            setType(TYPE_REAL); //设置相应的类型
        else
            setType(TYPE_INTEGER);
    }
    else
    {
        flag3 = (type1 == type2 && type1 == TYPE_BOOLEAN);
        if (!flag3)
            std::cout << "#Line " << m_Lineno << "运算符两边应该为boolean类型" << endl;
        setType(TYPE_BOOLEAN);
    }
    return flag1 && flag2 && flag3;
}

bool Term::errorDetect(const string &symbolSheetName)
{
    if (mp_MulOp)
    {
        bool flag = mp_MulOp->errorDetect(symbolSheetName);
        setType(mp_MulOp->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    }
    else if (m_PFactor)
    {
        bool flag = m_PFactor->errorDetect(symbolSheetName);
        setType(m_PFactor->getType());
        rangeVal = m_PFactor->getRangeVal();
        rangeValid = m_PFactor->getRangeValid();
        return flag;
    }
    else
    { //均为空， AST 错误
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool MulOp::errorDetect(const string &symbolSheetName)
{
    if (m_PTerm && m_PFactor)
    {
        bool flag1 = m_PTerm->errorDetect(symbolSheetName);
        bool flag2 = m_PFactor->errorDetect(symbolSheetName);
        int type1 = m_PTerm->getType();
        int type2 = m_PFactor->getType();
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
                std::cout << "#Line " << m_Lineno << ": 运算符两边类型不匹配." << endl;
            }
            return false;
        }
        return true;
    }
    else
    {
        std::cout << "#Line " << m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool Factor::errorDetect(const string &symbolSheetName)
{
    bool flag = true; //按类型设置节点类型，并进#Line 相应的错误检测
    switch (m_factorType)
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

        rangeVal = m_int;
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
        flag = mp_Variable->errorDetect(symbolSheetName);
        setType(mp_Variable->getType());
        break;
    }
    case FACTOR_FUNCCALL:
    {
        rangeVal = -1;
        rangeValid = false;
        flag = mp_Function_Call->errorDetect(symbolSheetName);
        setType(get_func_return_type(mp_Function_Call->m_PID->getName()));
        break;
    }
    case FACTOR_BRACKETS:
    {
        rangeVal = -1;
        rangeValid = false;
        flag = mp_Expression->errorDetect(symbolSheetName);
        setType(mp_Expression->getType());
        break;
    }
    case FACTOR_NOT:
    {
        rangeVal = -1;
        rangeValid = false;
        flag = mp_Not->errorDetect(symbolSheetName);
        setType(TYPE_BOOLEAN);
        break;
    }
    case FACTOR_UMINUS:
    {
        int typeTemp = mp_Uminus->getType();
        flag = mp_Uminus->errorDetect(symbolSheetName);
        setType(mp_Uminus->getType());
        if (typeTemp != TYPE_INTEGER)
        {
            rangeVal = -1;
            rangeValid = false;
        }
        else
        {
            rangeVal = mp_Uminus->getRangeVal();
            rangeValid = true;
        }
        break;
    }

    default:
    {
        rangeVal = -1;
        rangeValid = false;
        std::cout << "#Line " << m_Lineno << " AST 出错" << endl;
        return false;
    }
    }
    return flag;
}

bool Not::errorDetect(const string &symbolSheetName) const
{
    if (m_PFactor)
    {
        bool flag = true;
        flag = m_PFactor->errorDetect(symbolSheetName);
        int typeTemp = m_PFactor->getType();
        if (typeTemp != TYPE_BOOLEAN)
        { //只有Boolean型能取反
            flag = false;
            std::cout << "#Line " << m_Lineno << ": 非boolean类型不能not" << endl;
        }
        return flag;
    }
    else
    {
        std::cout << "#Line " << m_Lineno << " AST 出错" << endl;
        return false;
    }
}

bool Uminus::errorDetect(const string &symbolSheetName)
{
    if (m_PFactor)
    {
        bool flag = m_PFactor->errorDetect(symbolSheetName);
        int typeTemp = m_PFactor->getType();
        if (typeTemp != TYPE_INTEGER && typeTemp != TYPE_REAL)
        {
            flag = false; //只有整型，实型能去算术取反
            std::cout << "#Line " << m_Lineno << ": 类型不匹配" << endl;
        }
        rangeVal = m_PFactor->getRangeVal();
        rangeVal = m_unimusType == 0 ? rangeVal : rangeValid;
        rangeValid = m_PFactor->getRangeValid();
        setType(typeTemp);
        return flag;
    }
    else
    {
        setType(TYPE_INTEGER);
        std::cout << "#Line " << m_Lineno << ":  AST 出错" << endl;
        return false;
    }
}

// 语义分析接口
bool semantic_analyse(Program *root)
{
    bool flag = true;
    //　创建全局符号表
    if (root->m_PProgramBody)
        flag = root->m_PProgramBody->createSymbolSheet().first;
    if (flag)
        assert(!SymbolSheetList.empty());
    // 为定义的函数、过程建立自符号表
    if (!root->m_PProgramBody->m_PSubProgramDeclarations->m_CommonVector.empty())
    {
        for (auto subprogram : root->m_PProgramBody->m_PSubProgramDeclarations->m_CommonVector)
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
