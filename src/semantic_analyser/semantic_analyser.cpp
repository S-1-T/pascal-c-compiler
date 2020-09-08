#include "semantic_analyser/semantic_analyser.h"
#include <iostream>
#include <map>
#include <cassert>
#include <utility>

// 语义分析，DFS
bool Program::errorDetect() const {
    bool flag = true;
    if (this->mp_Program_Body)
        flag = mp_Program_Body->errorDetect();
    return flag;
}

bool ProgramBody::errorDetect() const {
    bool flag = true;
    if (mp_SubProgram_Declarations) {
        flag = mp_SubProgram_Declarations->definitionErrorDetect();
    }
    if (mp_Statement_List) {
        flag = mp_Statement_List->errorDetect("0") && flag;
    }
    return flag;
}

bool ConstDeclarations::errorDetect(const string& symbolSheet_name) {
    set <string> id_set;
    bool flag = true;
    for (auto const_symbol: mv_Const) {
        if (symbolSheet_name != "0" && const_symbol.first->m_name == symbolSheet_name) {
        	// 同名检查
            cout << "子程序\"" << symbolSheet_name << "\"声明的常量\"" << const_symbol.first->m_name
                 << "\"不能与子程序名相同" << endl;
            flag = false;
            break;
        }
        auto result = id_set.insert(const_symbol.first->m_name);
        if (!result.second) {  // 重复声明检查
            if (symbolSheet_name == "0") {
                cout << "全局常量声明中存在重复声明错误" << endl;
            } else {
                cout << "子程序\"" << symbolSheet_name << "\"常量声明中存在重复声明错误";
            }
            flag = false;
            break;
        }
    }
    return flag;
}

bool VarDeclarations::errorDetect(const string& symbolSheet_name) {
    set <string> id_set;
    SymbolSheet sheet;
    bool flag = true;
    for (auto type_group: mv_Var) {
        for (auto id: type_group.first->mv_Id) {
            string id_name = id->m_name;
            // 同名检查
            if (symbolSheet_name != "0" && id_name == symbolSheet_name) {
                cout << "子程序\"" << symbolSheet_name << "\"声明的变量\"" << id_name
                     << "\"不能与子程序名相同" << endl;
                flag = false;
                break;
            }
            auto result = id_set.insert(id_name);
            if (!result.second) {  // 重复声明检查
                if (symbolSheet_name == "0") {
                    cout << "全局变量声明行中存在重复声明错误" << endl;
                } else {
                    cout << "子程序\"" << symbolSheet_name << "\"变量声明行中存在重复声明错误";
                }
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool SubProgramDeclarations::errorDetect(const string& symbolSheet_name) {
    set <string> id_set;
    bool flag = true;
    for (auto subprogram: mv_Common) {
        string id_name = subprogram->getFuncId()->m_name;
        auto result = id_set.insert(id_name);
        if (!result.second) {  // 重复声明检查
            cout << "子程序\"" << id_name << "\"重复声明错误" << endl;
            flag = false;
            break;
        }
    }
    return flag;
}

bool SubProgramDeclarations::definitionErrorDetect() {
    bool flag = true;
    for (auto subprogram: mv_Common) {
        flag = subprogram->errorDetect() && flag;
    }
    return flag;
}

bool Procedure::errorDetect() {
    string proc_name = mp_Id->m_name;
    SymbolSheet sheet = SymbolSheetList[proc_name];
    bool flag = true;
    if (mp_Parameter_List)
        flag = mp_Parameter_List->errorDetect(proc_name);
    if (mp_Const_Declarations)
        flag = flag && mp_Const_Declarations->errorDetect(proc_name);
    if (mp_Var_Declarations)
        flag = flag && mp_Var_Declarations->errorDetect(proc_name);
    if (mp_Statement_List)
        flag = flag && mp_Statement_List->errorDetect(proc_name);
    return flag;
}

bool Function::errorDetect() {
    string func_name = mp_Id->m_name;
    SymbolSheet sheet = SymbolSheetList[func_name];
    bool flag = true;
    if (mp_Parameter_List)
        flag = mp_Parameter_List->errorDetect(func_name);
    if (mp_Const_Declarations)
        flag = flag && mp_Const_Declarations->errorDetect(func_name);
    if (mp_Var_Declarations)
        flag = flag && mp_Var_Declarations->errorDetect(func_name);
    if (mp_Statement_List)
        flag = flag && mp_Statement_List->errorDetect(func_name);
    return flag;
}

bool ParameterList::errorDetect(const string& symbolSheet_name) {
    set <string> id_set;
    bool flag = true;
    for (auto parameter: mv_Patameter) {
        bool is_Val = parameter->m_isVal;
        vector < Id * > parameter_symbols = parameter->getIds();
        for (auto id: parameter_symbols) {
            id->m_isVal = is_Val;
            string id_name = id->m_name;
            if (id_name == symbolSheet_name) {  // 同名检查
                cout << "子程序\"" << symbolSheet_name << "\"声明的形式参数\"" << id_name
                     << "\"不能与子程序名相同" << endl;
                flag = false;
                break;
            }
            auto result = id_set.insert(id_name);
            if (!result.second) {  // 重复声明检查
                cout << "子程序\"" << symbolSheet_name << "\"声明行中形式参数\"" << id_name
                     << "\"存在重复声明错误" << endl;
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool StatementList::errorDetect(const string& symbol_sheet_name) {
    bool flag = true;
    for (auto & i : mv_Statement) {
        if (i) {
            bool flag1=true;
            flag1 = i->errorDetect(symbol_sheet_name);
            flag =flag &&flag1;
        }
    }
    return flag;
}

bool Statement::errorDetect(const string& symbol_sheet_name) const {
    bool flag = true;
    if (mp_AssignOp)                                            //检查赋值语句的错误
    {
        //cout<<"fuzhi"<<endl;
        flag = mp_AssignOp->errorDetect(symbol_sheet_name);
    }
    else if (mp_Procedure_call) {                               //检查过程调用的错误
        //cout<<"Procedure_call"<<endl;
        flag = mp_Procedure_call->errorDetect(symbol_sheet_name);

    }
    else if (mp_Statement_List) {                               //检查语句列表的错误
        //cout<<"statement_list"<<endl;
        flag = mp_Statement_List->errorDetect(symbol_sheet_name);

    }
    else if (mp_If_Then_Else) {                                 //检查分支语句的错误
        //cout<<"IfThenElse"<<endl;
        flag = mp_If_Then_Else->errorDetect(symbol_sheet_name);
    }
    else if (mp_For) {                                          //检查循环语句的错误
        //cout<<"For"<<endl;
        flag = mp_For->errorDetect(symbol_sheet_name);
    }
    else
        cout << "null" << endl;
    // cout<<flag<<" return Statement"<<endl;
    return flag;
}

bool AssignOp::errorDetect(const string& symbol_sheet_name) const {
    bool flag = true;
    if (mp_Variable)                                            //对赋值变量进行检错
        flag = mp_Variable->errorDetect(symbol_sheet_name);
    if (mp_Expression)                                          //对表达式进行检错
        flag = flag && mp_Expression->errorDetect(symbol_sheet_name);
    int type1=mp_Variable->getType();
    int type2=mp_Expression->getType();                         //判断类型是否能转化
    bool flag1 = (type1 == type2 || type1 == TYPE_INTEGER&&type2 == TYPE_REAL ||
                  type2 == TYPE_INTEGER&&type1 == TYPE_REAL);
    if(!flag1) {
        std::cout << "行" << m_lineno << ": 类型不能转化" << endl;
        flag = false;
    }
    if(flag1&&type1==5&&type2==5)
    {                                                           //特殊处理两个数组类型进行赋值
        int type3= get_array_type(symbol_sheet_name, mp_Variable->mp_Id->getName());
        int type4=-1;
        try {
            type4 = get_array_type(symbol_sheet_name,
                                   mp_Expression->mp_Simple_Expression->mp_Term->mp_Factor->mp_Variable->mp_Id->getName());
            if(type3!=type4) {                                 //判断元素类型是否相同
                std::cout << "行" << m_lineno << ": 数组类型不能转化" << endl;
                flag=false;
            }                                                  //判断数组大小是否相同
            int arrayRange1 = get_symbol_range(symbol_sheet_name, mp_Variable->mp_Id->getName()).size();
            int arrayRange2 = get_symbol_range(symbol_sheet_name, mp_Expression->mp_Simple_Expression->mp_Term->mp_Factor->mp_Variable->mp_Id->getName()).size();

            if (arrayRange1 != arrayRange2) {
                std::cout << "行" << m_lineno << ": 数组长度不同" << endl;
                flag = false;
            }

        }
        catch(...)
        {
            flag=false;
            std::cout << "行" << m_lineno << ": 语法树错误" << endl;
        }


    }
    if (!mp_Variable || !mp_Expression) {                      //语法树错误
        flag = false;
        std::cout << "行" << m_lineno << ": 语法树错误" << endl;
    }
    return flag;
}

bool IfThenElse::errorDetect(const string& symbol_sheet_name) const {
    bool flag = true;
    if (mp_Expression)                                      //判断条件检错
        flag = mp_Expression->errorDetect(symbol_sheet_name);
    else {
        cout << "行" << m_lineno << ": 语法树错误" << endl;
        flag = false;
    }
    if (mp_Statement_1)                                    //then语句检错
        flag = mp_Statement_1->errorDetect(symbol_sheet_name)&&flag;
    if (mp_Statement_1 && mp_Statement_2)                  //else语句检错
        flag = mp_Statement_2->errorDetect(symbol_sheet_name)&&flag;
    else if (!mp_Statement_1 && mp_Statement_2) {
        cout << "行" << m_lineno << ": 语法树错误" << endl;
        flag = false;
    }
    return flag;
}

bool For::errorDetect(const string& symbol_sheet_name) const {
    if (mp_Id && mp_Expression_1 && mp_Expression_2)            //判断语法树是否出错
    {                                                           //循环变量是否声明
        if (lookup_symbol(symbol_sheet_name, mp_Id->getName())) {
            mp_Id->m_isVal = get_symbol_var_type(symbol_sheet_name, mp_Id->getName());
            bool flag = true;                                   //起始，终止表达式检错
            int type1 = get_symbol_type(symbol_sheet_name, mp_Id->getName());
            flag = mp_Expression_1->errorDetect(symbol_sheet_name);
            flag = flag && mp_Expression_2->errorDetect(symbol_sheet_name);
            int type2 = mp_Expression_1->getType();
            int type3 = mp_Expression_2->getType();
            if ((type1 == TYPE_INTEGER || type1 == TYPE_CHAR) && type1 == type2 && type1 == type3){

            }
            else {
                flag = false;
                std::cout << "行" << m_lineno << ": 循环变量有问题" << endl;

            }                                                   //语句检错
            flag = flag && mp_Statement->errorDetect(symbol_sheet_name);
            return flag;
        } else {
            std::cout << "行" << m_lineno << ": 未声明变量\"" << mp_Id->getName() << "\"" << endl;
            return false;
        }
    } else {
        std::cout << "行" << mp_Id->m_lineno << "语法树出错" << endl;
        return false;
    }
}

bool Variable::errorDetect(const string& symbol_sheet_name) {
    if (mp_Id) {
        if (lookup_symbol(symbol_sheet_name, mp_Id->getName())) {
            int type1 = get_symbol_type(symbol_sheet_name, mp_Id->getName());
            mp_Id->m_isVal = get_symbol_var_type(symbol_sheet_name, mp_Id->getName());
            // cout<<"Variable "<<type1<<endl;
            bool flag = true;
            if (mp_Expression_List && type1 != 5) {              //判断是否是数组
                m_isArray = false;
                std::cout << "行" << m_lineno << ": 变量非数组" << endl;
                flag = false;
            } else if (mp_Expression_List &&                     //判断数组维数
                       mp_Expression_List->getExpressions().size()
                       != get_symbol_range(symbol_sheet_name, mp_Id->getName()).size()) {
                m_isArray = true;
                std::cout << "行" << m_lineno << ": 数组维数不对" << endl;
                flag = false;
            } else if (mp_Expression_List) {                     //检查数组是否越界
                flag = mp_Expression_List->errorDetect(symbol_sheet_name);
                this->type = get_array_type(symbol_sheet_name, mp_Id->getName());
                vector<int> rangeVal1 = mp_Expression_List->rangeVal;
                vector<bool> rangeValid1 = mp_Expression_List->rangeValid;
                vector <pair<int, int>> rangeTemp = get_symbol_range(symbol_sheet_name, mp_Id->getName());
                for (int i = 0; i < rangeTemp.size(); i++) {
                    if (rangeValid1[i]) {
                        if (rangeVal1[i] < rangeTemp[i].first || rangeVal1[i] > rangeTemp[i].second) {
                            std::cout << "行" << m_lineno << ": 数组越界" << endl;
                            flag = false;
                        }
                    }
                }
            } else {
                this->type = type1;
                m_isArray = false;
            }
            return flag;
        } else {
            std::cout << "行" << m_lineno << ": 未声明变量\"" << mp_Id->getName() << "\"" << endl;
            return false;
        }
    } else {
        std::cout << "行" << mp_Id->m_lineno << "语法树出错" << endl;
        return false;
    }

}

bool FunctionCall::errorDetect(const string& symbol_sheet_name) const
{
    bool flag = lookup_func(mp_Id->getName());                    //判断是否为函数
    if (!flag) {
        std::cout << "行" << m_lineno << ": 非函数" << endl;
        return false;
    }
    int nargs = get_symbol_narg(symbol_sheet_name, mp_Id->getName());
    if (nargs) {  // builtins n == -1, normal procs n > 0
        if (nargs == -1) {
            // if this proc is a builtin
            // nargs == -1 -> the proc has variable length (or none) of parameters of any type,
            // used in the builtin procedures, which dont require type & num check
            if (mp_Expression_List) {
                if (!mp_Expression_List->errorDetect(symbol_sheet_name)) {
                    return false;
                }
                // for builtins, the argument cannot be a variable type
                vector<bool> nargs_var_or_not(this->mp_Expression_List->mv_Expression.size(), false);
                this->mp_Expression_List->mv_VarDefine = nargs_var_or_not;
            }
            return true;
        } else {
            if (mp_Expression_List) {
                if (!mp_Expression_List->errorDetect(symbol_sheet_name)) {
                    return false;
                }                                                        //判断形参个数是否匹配
                if (nargs != mp_Expression_List->getTypes().size()) {
                    std::cout << "行" << m_lineno << ": 实参形参数量不匹配" << endl;
                    return false;
                }
                vector<int> types = mp_Expression_List->getTypes();
                vector<int> arg_types = get_symbol_narg_type(symbol_sheet_name, mp_Id->getName());
                for (int i = 0; i < types.size(); i++) {
                    if (types[i] != arg_types[i]) {                      //判断类型是否匹配
                        std::cout << "行" << m_lineno << ": 第" << i + 1 << "个实参形参不匹配" << endl;
                        flag = false;
                    }
                }
                vector<bool> nargs_var_or_not = get_symbol_nargs_var_or_not(symbol_sheet_name, mp_Id->getName());
                this->mp_Expression_List->mv_VarDefine = nargs_var_or_not;
            }
        }
    }
    return flag;
}

bool ProcedureCall::errorDetect(const string& symbol_sheet_name)
{
    // set m_proCall_type
    if (mp_Id->getName() == "read") {
        m_proCall_Tpye = PROCECALL_READ;
    } else if (mp_Id->getName() == "readln") {
        m_proCall_Tpye = PROCECALL_READLN;
    } else if (mp_Id->getName() == "write") {
        m_proCall_Tpye = PROCECALL_WRITE;
    } else if (mp_Id->getName() == "writeln") {
        m_proCall_Tpye = PROCECALL_WRITELN;
    } else {
        m_proCall_Tpye = PROCECALL_NORMAL;
    }

    bool flag = lookup_procedure(mp_Id->getName())||lookup_func(mp_Id->getName());
    if (!flag) {
        std::cout << "行" << m_lineno << ": 非过程或者函数" << endl;
        return false;
    }
    int nargs = get_symbol_narg(symbol_sheet_name, mp_Id->getName());
    if (nargs) {  // builtins n == -1, normal procs n > 0
        if (nargs == -1) {
            // if this proc is a builtin
            // nargs == -1 -> the proc has variable length (or none) of parameters of any type,
            // used in the builtin procedures, which dont require type & num check
            if (mp_Expression_List) {
                if (!mp_Expression_List->errorDetect(symbol_sheet_name)) {
                    return false;
                }
                // for builtins, the argument cannot be a variable type
                vector<bool> nargs_var_or_not(this->mp_Expression_List->mv_Expression.size(), false);
                this->mp_Expression_List->mv_VarDefine = nargs_var_or_not;
            }
            return true;
        } else {
            if (mp_Expression_List) {
                if (!mp_Expression_List->errorDetect(symbol_sheet_name)) {
                    return false;
                }                                             //判断形参实参个数
                if (nargs != mp_Expression_List->getTypes().size()) {
                    std::cout << "行" << m_lineno << ": 实参形参数量不匹配" << endl;
                    return false;
                }
                vector<int> types = mp_Expression_List->getTypes();
                vector<int> arg_types = get_symbol_narg_type(symbol_sheet_name, mp_Id->getName());
                for (int i = 0; i < types.size(); i++) {
                    if (types[i] != arg_types[i]) {            //判断形参实参类型
                        std::cout << "行" << m_lineno << ": 第" << i + 1 << "个实参形参不匹配" << endl;
                        flag = false;
                    }
                }
                vector<bool> nargs_var_or_not = get_symbol_nargs_var_or_not(symbol_sheet_name, mp_Id->getName());
                this->mp_Expression_List->mv_VarDefine = nargs_var_or_not;
            }
        }
    }
    // cout << "finish " << mp_Id->getName() << endl;
    return flag;
}

bool Expression::errorDetect(const string& symbol_sheet_name) {
    if (mp_Relop) {                                       //运算符子树检错
        bool flag = mp_Relop->errorDetect(symbol_sheet_name);
        this->setType(mp_Relop->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    } else if (mp_Simple_Expression) {                    //对应的简单表达式检错
        bool flag = mp_Simple_Expression->errorDetect(symbol_sheet_name);
        setType(mp_Simple_Expression->getType());
        rangeVal = mp_Simple_Expression->getRangeVal();
        rangeValid = mp_Simple_Expression->getRangeValid();
        return flag;
    } else {
        rangeVal = -1;
        rangeValid = false;
        std::cout << "行" << m_lineno << "语法树出错" << endl;
        return false;
    }

}

bool ExpressionList::errorDetect(const string& symbol_sheet_name) {
    bool flag = true;
    for (auto &i : mv_Expression) {
        flag = i->errorDetect(symbol_sheet_name)&&flag;//检测其中所有的表达式
        mv_Type.push_back(i->getType());
        rangeVal.push_back(i->getRangeVal());
        rangeValid.push_back(i->getRangeValid());
    }
    return flag;
}

bool RelOp::errorDetect(const string& symbol_sheet_name) {
    if (mp_Simple_Expression_1 && mp_Simple_Expression_2) {
        bool flag;
        int type1 = mp_Simple_Expression_1->getType();
        int type2 = mp_Simple_Expression_2->getType();   //判断运算符两边是否能进行类型转换
        flag = (type1 == type2 || type1 == TYPE_INTEGER && type2 == TYPE_REAL ||
                type2 == TYPE_INTEGER && type1 == TYPE_REAL);
        if(!flag)
            std::cout << "行" << m_lineno << "逻辑运算符两边操作数不匹配" << endl;
        setType(TYPE_BOOLEAN);
        return flag;
    } else {
        std::cout << "行" << m_lineno << "语法树出错" << endl;
        return false;
    }
}

bool SimpleExpression::errorDetect(const string& symbol_sheet_name) {
    if (mp_AddOp) {                                     //判断运算符两边是否有错
        bool flag = mp_AddOp->errorDetect(symbol_sheet_name);
        setType(mp_AddOp->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    } else if (mp_Term) {                              //判断Term是否有错
        bool flag = mp_Term->errorDetect(symbol_sheet_name);
        setType(mp_Term->getType());
        rangeVal = mp_Term->getRangeVal();
        rangeValid = mp_Term->getRangeValid();
        return flag;
    } else {
        setType(-1);
        rangeVal = -1;
        rangeValid = false;
        std::cout << "行" << m_lineno << "语法树出错" << endl;
        return false;
    }
}

bool AddOp::errorDetect(const string& symbol_sheet_name) {
    bool flag1 = mp_Simple_Expression->errorDetect(symbol_sheet_name);
    bool flag2 = mp_Term->errorDetect(symbol_sheet_name);
    bool flag3 = true;
    int type1 = mp_Simple_Expression->getType();
    int type2 = mp_Term->getType();                     //不同的运算符，两边有不同的要求
    if (m_addopType == ADD || m_addopType == SUB) {
        flag3 = ((type1 == TYPE_INTEGER || type1 == TYPE_REAL) && (type2 == TYPE_INTEGER || type2 == TYPE_REAL));
        //即使类型不对也会附一个正确类型，出错以后不会再继续执行代码翻译
        if(!flag3)
            std::cout << "行" << m_lineno << "加减号两边应该为integer 或者 real" << endl;
        if (type1 == TYPE_REAL || type2 == TYPE_REAL)
            setType(TYPE_REAL);                               //设置相应的类型
        else
            setType(TYPE_INTEGER);
    } else {
        flag3 = (type1 == type2 && type1 == TYPE_BOOLEAN);
        if(!flag3)
            std::cout << "行" << m_lineno << "运算符两边应该为boolean类型" << endl;
        setType(TYPE_BOOLEAN);
    }
    return flag1 && flag2 && flag3;
}

bool Term::errorDetect(const string& symbol_sheet_name) {
    if (mp_MulOp) {                                           //对Mulop运算符子树进行检错
        bool flag = mp_MulOp->errorDetect(symbol_sheet_name);
        setType(mp_MulOp->getType());
        rangeVal = -1;
        rangeValid = false;
        return flag;
    } else if (mp_Factor) {                                  //对因子进行检错
        bool flag = mp_Factor->errorDetect(symbol_sheet_name);
        setType(mp_Factor->getType());
        rangeVal = mp_Factor->getRangeVal();
        rangeValid = mp_Factor->getRangeValid();
        return flag;
    } else {                                                 //都为空，语法树错误
        rangeVal = -1;
        rangeValid = false;
        std::cout << "行" << m_lineno << "语法树出错" << endl;
        return false;
    }
}

bool MulOp::errorDetect(const string& symbol_sheet_name) {
    if (mp_Term && mp_Factor) {
        bool flag1 = mp_Term->errorDetect(symbol_sheet_name);
        bool flag2 = mp_Factor->errorDetect(symbol_sheet_name);
        int type1 = mp_Term->getType();
        int type2 = mp_Factor->getType();
        int opType = this->checkMulOpType();
        bool flag3 = true;                                    //两边必须为整型或者实型
        if (opType == MULTIPLY || opType == INT_DIV || opType == REAL_DIV) {
            flag3 = ((type1 == TYPE_INTEGER || type1 == TYPE_REAL) && (type2 == TYPE_INTEGER || type2 == TYPE_REAL));
            if (type1 == TYPE_REAL || type2 == TYPE_REAL)
                setType(TYPE_REAL);
            else
                setType(TYPE_INTEGER);
        } else if (opType == MOD) {                     //模运算两边必须为整型
            flag3 = (type1 == type2) && (type1 == TYPE_INTEGER);
            setType(TYPE_INTEGER);
        } else {                                              //逻辑运算符两边必须为boolean 型
            flag3 = (type1 == type2 && type1 == TYPE_BOOLEAN);
            setType(TYPE_BOOLEAN);
        }
        if (!(flag1 && flag2 && flag3)) {
            if(!flag3) {
                std::cout << "行" << m_lineno << ": 运算符两边类型不匹配." << endl;
            }
            return false;
        }
        return true;

    } else {
        std::cout << "行" << m_lineno << "语法树出错" << endl;
        return false;
    }
}

bool Factor::errorDetect(const string& symbol_sheet_name) {
    bool flag = true;                                        //按类型设置节点类型，并进行相应的错误检测
    switch (m_factorType) {
        case FACTOR_VALUE_BOOL: {
            rangeVal = -1;
            rangeValid = false;
            setType(TYPE_BOOLEAN);
            break;
        }
        case FACTOR_VALUE_INT: {

            rangeVal = m_int;
            rangeValid = true;
            setType(TYPE_INTEGER);
            break;
        }
        case FACTOR_VALUE_CHAR: {
            rangeVal = -1;
            rangeValid = false;
            setType(TYPE_CHAR);
            break;
        }
        case FACTOR_VALUE_REAL: {
            rangeVal = -1;
            rangeValid = false;
            setType(TYPE_REAL);
            break;
        }
        case FACTOR_VAR: {
            rangeVal = -1;
            rangeValid = false;
            flag = mp_Variable->errorDetect(symbol_sheet_name);
            setType(mp_Variable->getType());
            break;
        }
        case FACTOR_FUNCCALL: {
            rangeVal = -1;
            rangeValid = false;
            flag = mp_Function_Call->errorDetect(symbol_sheet_name);
            setType(get_func_return_type(mp_Function_Call->mp_Id->getName()));
            break;
        }
        case FACTOR_BRACKETS: {
            rangeVal = -1;
            rangeValid = false;
            flag = mp_Expression->errorDetect(symbol_sheet_name);
            setType(mp_Expression->getType());
            break;
        }
        case FACTOR_NOT: {
            rangeVal = -1;
            rangeValid = false;
            flag = mp_Not->errorDetect(symbol_sheet_name);
            setType(TYPE_BOOLEAN);
            break;
        }
        case FACTOR_UMINUS: {
            int typeTemp = mp_Uminus->getType();
            flag = mp_Uminus->errorDetect(symbol_sheet_name);
            setType(mp_Uminus->getType());
            if (typeTemp != TYPE_INTEGER) {
                rangeVal = -1;
                rangeValid = false;
            } else {
                rangeVal = mp_Uminus->getRangeVal();
                rangeValid = true;
            }
            break;
        }

        default: {
            rangeVal = -1;
            rangeValid = false;
            std::cout << "行" << m_lineno << "语法树出错" << endl;
            return false;
        }
    }
    return flag;
}

bool Not::errorDetect(const string& symbol_sheet_name) const {
    if (mp_Factor) {
        bool flag = true;
        flag = mp_Factor->errorDetect(symbol_sheet_name);
        int typeTemp = mp_Factor->getType();
        if (typeTemp != TYPE_BOOLEAN) {                     //只有Boolean型能取反
            flag = false;
            std::cout << "行" << m_lineno << ": 非boolean类型不能not" << endl;
        }
        return flag;
    } else {
        std::cout << "行" << m_lineno << "语法树出错" << endl;
        return false;
    }
}

bool Uminus::errorDetect(const string& symbol_sheet_name) {
    if (mp_Factor) {
        bool flag = mp_Factor->errorDetect(symbol_sheet_name);
        int typeTemp = mp_Factor->getType();
        if (typeTemp != TYPE_INTEGER && typeTemp != TYPE_REAL) {
            flag = false;                                 //只有整型，实型能去算术取反
            std::cout << "行" << m_lineno << ": 类型不匹配" << endl;
        }
        rangeVal = mp_Factor->getRangeVal();
        rangeVal = m_unimusType == 0 ? rangeVal : rangeValid;
        rangeValid = mp_Factor->getRangeValid();
        setType(typeTemp);
        return flag;
    } else {
        setType(TYPE_INTEGER);
        std::cout << "行" << m_lineno << ": 语法树出错" << endl;
        return false;
    }
}

// 语义分析接口
bool semantic_analyse(Program* root) {
    bool flag = true;
    //　创建全局符号表
    if (root->mp_Program_Body)
        flag = root->mp_Program_Body->createSymbolSheet().first;
    if (flag)
        assert(!SymbolSheetList.empty());
    // 为定于的函数、过程建立自符号表
    if (!root->mp_Program_Body->mp_SubProgram_Declarations->mv_Common.empty()) {
        for (auto subprogram: root->mp_Program_Body->mp_SubProgram_Declarations->mv_Common) {
            flag = flag && subprogram->createSymbolSheet().first;
            if (!flag) {
                break;
            }
        }
    }
    if (flag)
        assert(SymbolSheetList.find("0") != SymbolSheetList.end());
    // 从语法树根节点开始进行语义分析
    if (flag) {
        flag = root->errorDetect()&&flag;
    }
    return flag;
}
