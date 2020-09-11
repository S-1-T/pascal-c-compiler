#include "semantic/symbol_sheet.h"

map<SymbolSheetName, SymbolSheet> SymbolSheetList;

// 针对符号表的操作
bool lookup_symbol(const string &symbolSheetName, const string &name)
{
    bool flag = true;
    // 查找全局表
    SymbolSheet global_sheet = SymbolSheetList.at("0");
    SymbolSheet sheet;
    // 全局表名字为 0
    if (symbolSheetName == "0")
    {
        sheet = global_sheet;
        if (sheet.symbols.find(name) != sheet.symbols.end())
        {
            flag = true;
        }
        else
        {
            flag = false;
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(name) != sheet.symbols.end() ||
            global_sheet.symbols.find(name) != global_sheet.symbols.end())
        {
            flag = true;
        }
        else if (global_sheet.symbols.find(name) == global_sheet.symbols.end())
        {
            flag = false;
        }
    }
    else
    {
        cout << "未找到符号表：\"" << symbolSheetName << "\"" << endl;
    }
    return flag;
}

int get_symbol_type(const string &symbolSheetName, const string &symbol_name)
{
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheetName == "0")
    {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            // 不是数组
            if (sheet.symbols[symbol_name].array_ranges.empty())
            {
                return sheet.symbols[symbol_name].type;
            }
            else
            {
                return TYPE_NULL;
            }
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            // 不是数组
            if (sheet.symbols[symbol_name].array_ranges.empty())
            {
                return sheet.symbols[symbol_name].type;
            }
            else
            {
                return TYPE_NULL;
            }
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            // 不是数组
            if (global_sheet.symbols[symbol_name].array_ranges.empty())
            {
                return global_sheet.symbols[symbol_name].type;
            }
            else
            {
                return TYPE_NULL;
            }
        }
    }
    return VOID;
}

Ranges get_symbol_range(const string &symbolSheetName, const string &symbol_name)
{
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheetName == "0")
    {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].array_ranges;
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].array_ranges;
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            return global_sheet.symbols[symbol_name].array_ranges;
        }
    }
    return Ranges();
}

int get_array_type(const string &symbolSheetName, const string &symbol_name)
{
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheetName == "0")
    {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].type;
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].type;
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            return global_sheet.symbols[symbol_name].type;
        }
    }
    return 0;
}

int get_func_return_type(const string &symbol_name)
{
    // 子程序（函数和过程）都存在于全局总表中
    SymbolSheet global_sheet = SymbolSheetList["0"];
    if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end() &&
        global_sheet.symbols[symbol_name].subprogramtype == FUNC)
    {
        return global_sheet.symbols[symbol_name].type;
    }
    return NONE;
}

bool lookup_func(const string &symbol_name)
{
    // 子程序（函数和过程）都存在于全局总表中
    SymbolSheet global_sheet = SymbolSheetList["0"];
    return global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end() &&
           global_sheet.symbols[symbol_name].subprogramtype == FUNC;
}

bool lookup_procedure(const string &symbol_name)
{
    // 子程序（函数和过程）都存在于全局总表中
    SymbolSheet global_sheet = SymbolSheetList["0"];
    return global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end() &&
           global_sheet.symbols[symbol_name].subprogramtype == PROC;
}

int get_symbol_narg(const string &symbolSheetName, const string &symbol_name)
{
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheetName == "0")
    {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].subprogramargs_num;
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].subprogramargs_num;
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            return global_sheet.symbols[symbol_name].subprogramargs_num;
        }
    }
    return -1;
}

vector<bool> get_symbol_nargs_var_or_not(const string &symbolSheetName, const string &symbol_name)
{
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheetName == "0")
    {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].nargs_var_or_not;
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].nargs_var_or_not;
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            return global_sheet.symbols[symbol_name].nargs_var_or_not;
        }
    }
    return vector<bool>();
}

vector<int> get_symbol_narg_type(const string &symbolSheetName, const string &symbol_name)
{
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheetName == "0")
    {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].nargs_types;
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].nargs_types;
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            return global_sheet.symbols[symbol_name].nargs_types;
        }
    }
    return vector<int>();
}

bool get_symbol_var_type(const string &symbolSheetName, const string &symbol_name)
{
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheetName == "0")
    {
        // 总表
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].is_var;
        }
    }
    else if (SymbolSheetList.find(symbolSheetName) != SymbolSheetList.end())
    {
        sheet = SymbolSheetList[symbolSheetName];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end())
        {
            return sheet.symbols[symbol_name].is_var;
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            return global_sheet.symbols[symbol_name].is_var;
        }
    }
    return false;
}

CreateSymbolSheetResult ProgramBody::createSymbolSheet() const
{
    SymbolSheet global_sheet;
    global_sheet.sheet_name = "0";
    bool f0, f1 = false, f2 = false, f3 = false;
    f0 = global_sheet.add_reserved();
    if (!mConstDeclarations->mConstVector.empty() && f0)
    {
        if (mConstDeclarations->errorDetect(global_sheet.sheet_name))
        {
            f1 = global_sheet.add_const_symbols(mConstDeclarations);
            if (!f1)
            {
                cout << "向全局符号表中加入常量符号错误" << endl;
            }
        }
    }
    else
    {
        f1 = true;
    }
    if (!mVarDeclarations->mVariableVector.empty() && f1)
    {
        if (mVarDeclarations->errorDetect(global_sheet.sheet_name))
        {
            f2 = global_sheet.add_var_symbols(mVarDeclarations);
            if (!f2)
            {
                cout << "向全局符号表中加入变量符号错误" << endl;
            }
        }
    }
    else
    {
        f2 = true;
    }
    if (!mSubProgramDeclarations->mCommonVector.empty() && f2)
    {
        if (mSubProgramDeclarations->errorDetect(global_sheet.sheet_name))
        {
            f3 = global_sheet.add_subprogramsymbols(mSubProgramDeclarations);
            if (!f3)
            {
                cout << "向全局符号表中加入子函数失败" << endl;
            }
        }
    }
    else
    {
        f3 = true;
    }
    if (f0 && f1 && f2 && f3)
    {
        auto re = SymbolSheetList.insert(SymbolSheetItem(global_sheet.sheet_name, global_sheet));
        if (!re.second)
        {
            cout << "没有符号被加入到全局符号表中" << endl;
        }
    }
    else
    {
        cout << "构建全局符号表失败" << endl;
    }
    return CreateSymbolSheetResult(!SymbolSheetList.empty(), global_sheet.sheet_name);
}

// 创建过程的子符号表
CreateSymbolSheetResult Procedure::createSymbolSheet()
{
    auto s = SymbolSheetList.size();
    SymbolSheet proc_sheet;
    proc_sheet.sheet_name = mId->mName; // uses proc name
    bool f0, f1 = false, f2 = false, f3 = false;
    f0 = proc_sheet.add_reserved();
    if (mParameterList && f0)
    {
        if (mParameterList->errorDetect(proc_sheet.sheet_name))
        {
            f1 = proc_sheet.add_parameterSymbols(mParameterList);
            if (!f1)
            {
                cout << "插入参数失败：" << proc_sheet.sheet_name << endl;
            }
        }
    }
    else
    {
        f1 = true;
    }
    if (mConstDeclarations && f1)
    {
        if (mConstDeclarations->errorDetect(proc_sheet.sheet_name))
        {
            f2 = proc_sheet.add_const_symbols(mConstDeclarations);
            if (!f2)
            {
                cout << "插入常量符号失败：" << proc_sheet.sheet_name << endl;
            }
        }
    }
    else
    {
        f2 = true;
    }
    if (mVarDeclarations && f2)
    {
        if (mVarDeclarations->errorDetect(proc_sheet.sheet_name))
        {
            f3 = proc_sheet.add_var_symbols(mVarDeclarations);
            if (!f3)
            {
                cout << "插入变量符号失败：" << proc_sheet.sheet_name << endl;
            }
        }
    }
    else
    {
        f3 = true;
    }

    if (f0 && f1 && f2 && f3)
    {
        auto re = SymbolSheetList.insert(SymbolSheetItem(proc_sheet.sheet_name, proc_sheet));
        if (!re.second)
        {
            cout << proc_sheet.sheet_name << "中没有符号加入" << endl;
        }
    }
    else
    {
        cout << "构建符号表：" << proc_sheet.sheet_name << "失败" << endl;
    }
    return CreateSymbolSheetResult(bool(SymbolSheetList.size() - s), proc_sheet.sheet_name);
}

// 创建函数的子符号表
CreateSymbolSheetResult Function::createSymbolSheet()
{
    auto s = SymbolSheetList.size();
    SymbolSheet func_sheet;
    func_sheet.sheet_name = mId->mName;
    bool f0, f1 = false, f2 = false, f3 = false;
    f0 = func_sheet.add_reserved();
    if (mParameterList && f0)
    {
        if (mParameterList->errorDetect(func_sheet.sheet_name))
        {
            f1 = func_sheet.add_parameterSymbols(mParameterList);
            if (!f1)
            {
                cout << "插入参数失败：" << func_sheet.sheet_name << endl;
            }
        }
    }
    else
    {
        f1 = true;
    }
    if (mConstDeclarations && f1)
    {
        if (mConstDeclarations->errorDetect(func_sheet.sheet_name))
        {
            f2 = func_sheet.add_const_symbols(mConstDeclarations);
            if (!f2)
            {
                cout << "插入常量符号失败：" << func_sheet.sheet_name << endl;
            }
        }
    }
    else
    {
        f2 = true;
    }
    if (mVarDeclarations && f2)
    {
        if (mVarDeclarations->errorDetect(func_sheet.sheet_name))
        {
            f3 = func_sheet.add_var_symbols(mVarDeclarations);
            if (!f3)
            {
                cout << "插入变量符号失败：" << func_sheet.sheet_name << endl;
            }
        }
    }
    else
    {
        f3 = true;
    }

    if (f0 && f1 && f2 && f3)
    {
        auto re = SymbolSheetList.insert(SymbolSheetItem(func_sheet.sheet_name, func_sheet));
        if (!re.second)
        {
            cout << func_sheet.sheet_name << "中无符号加入" << endl;
        }
    }
    else
    {
        cout << "构建符号表：" << func_sheet.sheet_name << "失败" << endl;
    }
    return CreateSymbolSheetResult(bool(SymbolSheetList.size() - s), func_sheet.sheet_name);
}

// SymbolSheet 类方法
bool SymbolSheet::add_reserved()
{
    bool flag = true;
    for (const auto &keyword : keywords)
    {
        TYPES type = RESERVED;
        SUBPROGRAM_TYPE subprogramtype = NONE;
        bool is_const = false;
        float const_val = 0;
        bool is_var = false;
        int func_nargs = 0;
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = 0;
        int ref_line = -1;
        Ranges array_ranges;
        Property p = {
            type,
            is_const,
            const_val,
            is_var,
            array_ranges,
            subprogramtype,
            func_nargs,
            nargs_var_or_not,
            nargs_types,
            dec_line,
            ref_line};
        if (symbols.insert(SymbolItem(keyword, p)).second)
        {
            continue;
        }
        else
        {
            cout << "插入关键字：" << keyword << "失败" << endl;
            flag = false;
            break;
        }
    }
    // 最后转换为 C 语言的 scanf 和 printf
    for (const auto &builtins : BuiltInFunctions)
    {
        TYPES type = RESERVED;
        SUBPROGRAM_TYPE subprgrmtype = PROC;
        bool is_const = false;
        float const_val = 0;
        bool is_var = false;
        int func_nargs = -1; // -1 代表参数长度为变量
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = 0;
        int ref_line = -1;
        Ranges array_ranges;
        Property p = {
            type,
            is_const,
            const_val,
            is_var,
            array_ranges,
            subprgrmtype,
            func_nargs,
            nargs_var_or_not,
            nargs_types,
            dec_line,
            ref_line};
        if (symbols.insert(SymbolItem(builtins, p)).second)
        {
            continue;
        }
        else
        {
            cout << "插入内建函数：" << builtins << "失败" << endl;
            flag = false;
            break;
        }
    }
    return flag;
}

bool SymbolSheet::add_parameterSymbols(ParameterList *parameter_list)
{
    bool flag = true;
    for (auto parameter : parameter_list->mParameters)
    {
        vector<Id *> parameterSymbols = parameter->getIds();
        auto type = (TYPES)parameter->getType();
        SUBPROGRAM_TYPE subprogramtype = NONE;
        bool is_const = false;
        float const_val = 0;
        bool is_var = parameter->mIsVal;
        int func_nargs = 0;
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = parameter->getLineno();
        int ref_line = -1;
        Ranges array_ranges;
        for (auto parameter_id : parameterSymbols)
        {
            string name = parameter_id->mName;
            // 查看是否为保留字
            if (check_is_reserved(name))
            {
                cout << "标识符 \"" << name << "\" 为保留字，无法使用" << endl;
                flag = false;
                break;
            }
            Property p = {
                type,
                is_const,
                const_val,
                is_var,
                array_ranges,
                subprogramtype,
                func_nargs,
                nargs_var_or_not,
                nargs_types,
                dec_line,
                ref_line};
            if (exists(name))
            {
                symbols[name] = p;
            }
            else
            {
                if (symbols.insert(SymbolItem(name, p)).second)
                {
                    continue;
                }
                else
                {
                    cout << "插入参数：" << name << "失败" << endl;
                    flag = false;
                    break;
                }
            }
        }
        if (!flag)
        {
            break;
        }
    }
    return flag;
}

bool SymbolSheet::add_const_symbols(ConstDeclarations *const_declarations)
{
    bool flag = true;
    for (auto const_symbol : const_declarations->mConstVector)
    {
        string name = const_symbol.first->mName;
        if (check_is_reserved(name))
        {
            cout << "常量标识符\"" << name << "\"为保留字，无法使用" << endl;
            flag = false;
            break;
        }
        TYPES type;
        SUBPROGRAM_TYPE subprogramtype = NONE;
        float const_val = 0;
        bool is_const = true;
        if (!const_symbol.second->mId)
        {
            type = (TYPES)const_symbol.second->mValueType;
            if (type == INT)
            {
                const_val = const_symbol.second->mInt;
            }
            else if (type == _REAL)
            {
                const_val = const_symbol.second->mReal;
            }
            else if (type == _CHAR)
            {
                const_val = const_symbol.second->mChar;
            }
            else if (type == _BOOLEAN)
            {
                const_val = const_symbol.second->mBool;
            }
            else
            {
                std::cout << "Line " << const_symbol.second->mLineno << ": 常量声明的类型错误" << endl;
                flag = false;
                break;
            }
        }
        else
        {
            Id *that_symbol = const_symbol.second->mId;
            type = (TYPES)that_symbol->mIdType;
            const_val = get_const_symbol_value(that_symbol->mName);
            if (type != INT && type != _REAL && type != _CHAR && type != _BOOLEAN)
            {
                std::cout << "Line: " << const_symbol.second->mLineno << ": 常量声明的类型错误" << endl;
                flag = false;
                break;
            }
        }
        if (const_symbol.second->mPolarity == CONST_NEGATIVE) // 负常量
            const_val = -const_val;
        bool is_var = false;
        Ranges array_ranges = {};
        int func_nargs = 0;
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = const_symbol.second->mLineno;
        int ref_line = -1;
        Property p = {
            type,
            is_const,
            const_val,
            is_var,
            array_ranges,
            subprogramtype,
            func_nargs,
            nargs_var_or_not,
            nargs_types,
            dec_line,
            ref_line};
        if (exists(name))
        {
            symbols[name] = p;
        }
        else
        {
            if (symbols.insert(SymbolItem(name, p)).second)
            {
                continue;
            }
            else
            {
                cout << "插入常量符号：" << name << "失败" << endl;
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool SymbolSheet::add_var_symbols(VarDeclarations *var_declarations)
{
    bool flag = true;
    for (auto vars : var_declarations->mVariableVector)
    {
        vector<Id *> var_symbols = vars.first->mIdVector;
        auto type = (TYPES)vars.second->checkSimpleType();
        SUBPROGRAM_TYPE subprogramtype = NONE;
        bool is_const = false;
        float const_val = 0;
        bool is_var = false;
        Ranges array_ranges;
        if (vars.second->checkIsArray())
        {
            array_ranges = vars.second->getPeriod();
        }
        int func_nargs = 0;
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = vars.second->getLineno();
        int ref_line = -1;

        for (auto var_symbol : var_symbols)
        {
            string name = var_symbol->mName;
            if (check_is_reserved(name))
            {
                cout << "变量标识符\"" << name << "\"为关键字，无法使用" << endl;
                flag = false;
                break;
            }
            Property p = {
                type,
                is_const,
                const_val,
                is_var,
                array_ranges,
                subprogramtype,
                func_nargs,
                nargs_var_or_not,
                nargs_types,
                dec_line,
                ref_line};
            if (exists(name))
            {
                symbols[name] = p;
            }
            else
            {
                if (symbols.insert(SymbolItem(name, p)).second)
                {
                    continue;
                }
                else
                {
                    cout << "插入变量符号" << name << "失败" << endl;
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}

bool SymbolSheet::add_subprogramsymbols(SubProgramDeclarations *subProgramdeclarations)
{
    bool flag = true;
    for (auto subprogram : subProgramdeclarations->mCommonVector)
    {
        string name = subprogram->getFuncId()->mName;
        if (check_is_reserved(name))
        {
            cout << "子函数标识符\"" << name << "\"为关键字，无法使用" << endl;
            flag = false;
            break;
        }
        // 如果是函数则代表返回值，如果是过程则为　VOID
        auto type = (TYPES)subprogram->checkReturnType();
        // 子程序类型（函数、过程）
        auto subprogramtype = (SUBPROGRAM_TYPE)subprogram->getCommonType();
        bool is_const = false;
        float const_val = 0;
        bool is_var = false;
        Ranges array_ranges;
        int subprogramargs_num = 0;
        vector<bool> nargs_var_or_not;
        SubprogramArgsType nargs_types;
        if (subprogram->getParamList())
        {
            vector<Parameter *> parameters = subprogram->getParamList()->mParameters;
            for (auto ids : parameters)
            {
                bool isVar = ids->mIsVal;
                subprogramargs_num += ids->getIdList()->getIdNum();
                IdList *id_list = ids->getIdList();
                for (auto id : id_list->mIdVector)
                {
                    nargs_types.push_back(id->mIdType);
                    nargs_var_or_not.push_back(isVar);
                }
            }
        }
        int dec_line = subprogram->getLineno();
        int ref_line = -1;
        Property p = {
            type,
            is_const,
            const_val,
            is_var,
            array_ranges,
            subprogramtype,
            subprogramargs_num,
            nargs_var_or_not,
            nargs_types,
            dec_line,
            ref_line};
        if (symbols.insert(SymbolItem(name, p)).second)
        {
            continue;
        }
        else
        {
            cout << "插入子程序符号：" << name << "失败" << endl;
            flag = false;
            break;
        }
    }
    return flag;
}

bool SymbolSheet::exists(const string &symbol_name)
{
    SymbolItems::iterator it;
    it = this->symbols.find(symbol_name);
    return it != this->symbols.end();
}

bool SymbolSheet::check_is_reserved(const string &symbol_name)
{
    return keywords.find(symbol_name) != keywords.end() || BuiltInFunctions.find(symbol_name) != BuiltInFunctions.end();
}

float SymbolSheet::get_const_symbol_value(const string &symbol_name)
{
    if (this->sheet_name == "0")
    {
        if (this->symbols.find(symbol_name) != this->symbols.end())
        {
            return this->symbols[symbol_name].const_val;
        }
    }
    else
    {
        SymbolSheet global_sheet;
        if (SymbolSheetList.find("0") != SymbolSheetList.end())
            global_sheet = SymbolSheetList["0"];
        else
        {
            cout << "error: 未找到全局符号表" << endl;
            exit(1);
        }
        if (this->symbols.find(symbol_name) != this->symbols.end())
        {
            return this->symbols[symbol_name].const_val;
        }
        else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end())
        {
            return global_sheet.symbols[symbol_name].const_val;
        }
    }
    return 0;
}
