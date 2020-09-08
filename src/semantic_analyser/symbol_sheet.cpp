#include "semantic_analyser/symbol_sheet.h"

// 针对符号表的操作
bool lookup_symbol(const string& symbolSheet_name, const string& symbol_name) {
    bool flag = true;
    // 查找全局表
    SymbolSheet global_sheet = SymbolSheetList.at("0");
    SymbolSheet sheet;
    // 全局表名字为 0
    if (symbolSheet_name == "0") {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            flag = true;
        } else {
            flag = false;
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end() ||
            global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            flag = true;
        } else if (global_sheet.symbols.find(symbol_name) == global_sheet.symbols.end()) {
            flag = false;
        }
    } else {
        cout << "未找到符号表：\"" << symbolSheet_name << "\"" << endl;
    }
    return flag;
}

int get_symbol_type(const string& symbolSheet_name, const string& symbol_name) {
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheet_name == "0") {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            // 不是数组
            if (sheet.symbols[symbol_name].array_ranges.empty()) {
                return sheet.symbols[symbol_name].type;
            } else {
                return TYPE_NULL;
            }
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            // 不是数组
            if (sheet.symbols[symbol_name].array_ranges.empty()) {
                return sheet.symbols[symbol_name].type;
            } else {
                return TYPE_NULL;
            }
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            // 不是数组
            if (global_sheet.symbols[symbol_name].array_ranges.empty()) {
                return global_sheet.symbols[symbol_name].type;
            } else {
                return TYPE_NULL;
            }
        }
    }
    return VOID;
}

Ranges get_symbol_range(const string& symbolSheet_name, const string& symbol_name) {
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheet_name == "0") {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].array_ranges;
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].array_ranges;
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            return global_sheet.symbols[symbol_name].array_ranges;
        }
    }
    return Ranges();
}

int get_array_type(const string& symbolSheet_name, const string& symbol_name) {
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheet_name == "0") {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].type;
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].type;
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            return global_sheet.symbols[symbol_name].type;
        }
    }
    return 0;
}


int get_func_return_type(const string& symbol_name) {
    // 子程序（函数和过程）都存在于全局总表中
    SymbolSheet global_sheet = SymbolSheetList["0"];
    if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end() &&
        global_sheet.symbols[symbol_name].subprogram_type == FUNC) {
        return global_sheet.symbols[symbol_name].type;
    }
    return NONE;
}

bool lookup_func(const string& symbol_name) {
    // 子程序（函数和过程）都存在于全局总表中
    SymbolSheet global_sheet = SymbolSheetList["0"];
    return global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end() &&
           global_sheet.symbols[symbol_name].subprogram_type == FUNC;
}

bool lookup_procedure(const string& symbol_name) {
    // 子程序（函数和过程）都存在于全局总表中
    SymbolSheet global_sheet = SymbolSheetList["0"];
    return global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end() &&
           global_sheet.symbols[symbol_name].subprogram_type == PROC;
}

int get_symbol_narg(const string& symbolSheet_name, const string& symbol_name) {
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheet_name == "0") {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].subprogram_args_num;
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].subprogram_args_num;
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            return global_sheet.symbols[symbol_name].subprogram_args_num;
        }
    }
    return -1;
}

vector<bool> get_symbol_nargs_var_or_not(const string& symbolSheet_name, const string& symbol_name) {
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheet_name == "0") {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].nargs_var_or_not;
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].nargs_var_or_not;
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            return global_sheet.symbols[symbol_name].nargs_var_or_not;
        }
    }
    return vector<bool>();
}

vector<int> get_symbol_narg_type(const string& symbolSheet_name, const string& symbol_name) {
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheet_name == "0") {
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].nargs_types;
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].nargs_types;
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            return global_sheet.symbols[symbol_name].nargs_types;
        }
    }
    return vector<int>();
}

bool get_symbol_var_type(const string& symbolSheet_name, const string& symbol_name) {
    SymbolSheet global_sheet = SymbolSheetList["0"];
    SymbolSheet sheet;
    if (symbolSheet_name == "0") {
        // 总表
        sheet = global_sheet;
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].is_var;
        }
    } else if (SymbolSheetList.find(symbolSheet_name) != SymbolSheetList.end()) {
        sheet = SymbolSheetList[symbolSheet_name];
        if (sheet.symbols.find(symbol_name) != sheet.symbols.end()) {
            return sheet.symbols[symbol_name].is_var;
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            return global_sheet.symbols[symbol_name].is_var;
        }
    }
    return false;
}

CreateSymbolSheetResult ProgramBody::createSymbolSheet() const {
    SymbolSheet global_sheet;
    global_sheet.sheet_name = "0";
    bool f0, f1 = false, f2 = false, f3 = false;
    f0 = global_sheet.add_reserved();
    if (!mp_Const_Declarations->mv_Const.empty() && f0) {
        if (mp_Const_Declarations->errorDetect(global_sheet.sheet_name)) {
            f1 = global_sheet.add_const_symbols(mp_Const_Declarations);
            if (!f1) {
                cout << "向全局符号表中加入常量符号错误" << endl;
            }
        }
    } else {
        f1 = true;
    }
    if (!mp_Var_Declarations->mv_Var.empty() && f1) {
        if (mp_Var_Declarations->errorDetect(global_sheet.sheet_name)) {
            f2 = global_sheet.add_var_symbols(mp_Var_Declarations);
            if (!f2) {
                cout << "向全局符号表中加入变量符号错误" << endl;
            }
        }
    } else {
        f2 = true;
    }
    if (!mp_SubProgram_Declarations->mv_Common.empty() && f2) {
        if (mp_SubProgram_Declarations->errorDetect(global_sheet.sheet_name)) {
            f3 = global_sheet.add_subprogram_symbols(mp_SubProgram_Declarations);
            if (!f3) {
                cout << "向全局符号表中加入子函数失败" << endl;
            }
        }
    } else {
        f3 = true;
    }
    if (f0 && f1 && f2 && f3) {
        auto re = SymbolSheetList.insert(SymbolSheetItem(global_sheet.sheet_name, global_sheet));
        if (!re.second) {
            cout << "没有符号被加入到全局符号表中" << endl;
        }
    } else {
        cout << "构建全局符号表失败" << endl;
    }
    return CreateSymbolSheetResult(!SymbolSheetList.empty(), global_sheet.sheet_name);
}

// 创建过程的子符号表
CreateSymbolSheetResult Procedure::createSymbolSheet() {
    auto s = SymbolSheetList.size();
    SymbolSheet proc_sheet;
    proc_sheet.sheet_name = mp_Id->m_name;  // uses proc name
    bool f0, f1 = false, f2 = false, f3 = false;
    f0 = proc_sheet.add_reserved();
    if (mp_Parameter_List && f0) {
        if (mp_Parameter_List->errorDetect(proc_sheet.sheet_name)) {
            f1 = proc_sheet.add_parameter_symbols(mp_Parameter_List);
            if (!f1) {
                cout << "插入参数失败：" << proc_sheet.sheet_name << endl;
            }
        }
    } else {
        f1 = true;
    }
    if (mp_Const_Declarations && f1) {
        if (mp_Const_Declarations->errorDetect(proc_sheet.sheet_name)) {
            f2 = proc_sheet.add_const_symbols(mp_Const_Declarations);
            if (!f2) {
                cout << "插入常量符号失败：" << proc_sheet.sheet_name << endl;
            }
        }
    } else {
        f2 = true;
    }
    if (mp_Var_Declarations && f2) {
        if (mp_Var_Declarations->errorDetect(proc_sheet.sheet_name)) {
            f3 = proc_sheet.add_var_symbols(mp_Var_Declarations);
            if (!f3) {
                cout << "插入变量符号失败：" << proc_sheet.sheet_name << endl;
            }
        }
    } else {
        f3 = true;
    }

    if (f0 && f1 && f2 && f3) {
        auto re = SymbolSheetList.insert(SymbolSheetItem(proc_sheet.sheet_name, proc_sheet));
        if (!re.second) {
            cout << proc_sheet.sheet_name << "中没有符号加入" << endl;
        }
    } else {
        cout << "构建符号表：" << proc_sheet.sheet_name << "失败" << endl;
    }
    return CreateSymbolSheetResult(bool(SymbolSheetList.size() - s), proc_sheet.sheet_name);
}

// 创建函数的子符号表
CreateSymbolSheetResult Function::createSymbolSheet() {
    auto s = SymbolSheetList.size();
    SymbolSheet func_sheet;
    func_sheet.sheet_name = mp_Id->m_name;
    bool f0, f1 = false, f2 = false, f3 = false;
    f0 = func_sheet.add_reserved();
    if (mp_Parameter_List && f0) {
        if (mp_Parameter_List->errorDetect(func_sheet.sheet_name)) {
            f1 = func_sheet.add_parameter_symbols(mp_Parameter_List);
            if (!f1) {
                cout << "插入参数失败：" << func_sheet.sheet_name << endl;
            }
        }
    } else {
        f1 = true;
    }
    if (mp_Const_Declarations && f1) {
        if (mp_Const_Declarations->errorDetect(func_sheet.sheet_name)) {
            f2 = func_sheet.add_const_symbols(mp_Const_Declarations);
            if (!f2) {
                cout << "插入常量符号失败：" << func_sheet.sheet_name << endl;
            }
        }
    } else {
        f2 = true;
    }
    if (mp_Var_Declarations && f2) {
        if (mp_Var_Declarations->errorDetect(func_sheet.sheet_name)) {
            f3 = func_sheet.add_var_symbols(mp_Var_Declarations);
            if (!f3) {
                cout << "插入变量符号失败：" << func_sheet.sheet_name << endl;
            }
        }
    } else {
        f3 = true;
    }

    if (f0 && f1 && f2 && f3) {
        auto re = SymbolSheetList.insert(SymbolSheetItem(func_sheet.sheet_name, func_sheet));
        if (!re.second) {
            cout << func_sheet.sheet_name << "中无符号加入" << endl;
        }
    } else {
        cout << "构建符号表：" << func_sheet.sheet_name << "失败" << endl;
    }
    return CreateSymbolSheetResult(bool(SymbolSheetList.size() - s), func_sheet.sheet_name);
}

// SymbolSheet 类方法
bool SymbolSheet::add_reserved() {
    bool flag = true;
    for (const auto& keyword: keywords) {
        TYPES type = RESERVED;
        SUBPROGRAM_TYPE subprogram_type = NONE;
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
                subprogram_type,
                func_nargs,
                nargs_var_or_not,
                nargs_types,
                dec_line,
                ref_line
        };
        if (symbols.insert(SymbolItem(keyword, p)).second) {
            continue;
        } else {
            cout << "插入关键字：" << keyword << "失败" << endl;
            flag = false;
            break;
        }
    }
    // 最后转换为 C 语言的 scanf 和 printf
    for (const auto& builtins: BuiltInFunctions) {
        TYPES type = RESERVED;
        SUBPROGRAM_TYPE subprgrm_type = PROC;
        bool is_const = false;
        float const_val = 0;
        bool is_var = false;
        int func_nargs = -1;  // -1 代表参数长度为变量
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
                subprgrm_type,
                func_nargs,
                nargs_var_or_not,
                nargs_types,
                dec_line,
                ref_line
        };
        if (symbols.insert(SymbolItem(builtins, p)).second) {
            continue;
        } else {
            cout << "插入内建函数：" << builtins << "失败" << endl;
            flag = false;
            break;
        }
    }
    return flag;
}

bool SymbolSheet::add_parameter_symbols(ParameterList *parameter_list) {
    bool flag = true;
    for (auto parameter: parameter_list->mv_Patameter) {
        vector<Id *> parameter_symbols = parameter->getIds();
        auto type = (TYPES) parameter->getType();
        SUBPROGRAM_TYPE subprogram_type = NONE;
        bool is_const = false;
        float const_val = 0;
        bool is_var = parameter->m_isVal;
        int func_nargs = 0;
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = parameter->getLineno();
        int ref_line = -1;
        Ranges array_ranges;
        for (auto parameter_id: parameter_symbols) {
            string name = parameter_id->m_name;
            // 查看是否为保留字
            if (check_is_reserved(name))  {
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
                    subprogram_type,
                    func_nargs,
                    nargs_var_or_not,
                    nargs_types,
                    dec_line,
                    ref_line
            };
            if (exists(name)) {
                symbols[name] = p;
            } else {
                if (symbols.insert(SymbolItem(name, p)).second) {
                    continue;
                } else {
                    cout << "插入参数：" << name << "失败" << endl;
                    flag = false;
                    break;
                }
            }
        }
        if (!flag) {
            break;
        }
    }
    return flag;
}

bool SymbolSheet::add_const_symbols(ConstDeclarations *const_declarations) {
    bool flag = true;
    for (auto const_symbol: const_declarations->mv_Const) {
        string name = const_symbol.first->m_name;
        if (check_is_reserved(name))  {
            cout << "常量标识符\"" << name << "\"为保留字，无法使用" << endl;
            flag = false;
            break;
        }
        TYPES type;
        SUBPROGRAM_TYPE subprogram_type = NONE;
        float const_val = 0;
        bool is_const = true;
        if (!const_symbol.second->mp_Id) {
            type = (TYPES) const_symbol.second->m_valueType;
            if (type == INT) {
                const_val = const_symbol.second->m_int;
            } else if (type == _REAL) {
                const_val = const_symbol.second->m_real;
            } else if (type == _CHAR) {
                const_val = const_symbol.second->m_char;
            } else if (type == _BOOLEAN) {
                const_val = const_symbol.second->m_bool;
            } else {
                std::cout << "Line " << const_symbol.second->m_lineno << ": 常量声明的类型错误" << endl;
                flag = false;
                break;
            }
        } else {
            Id * that_symbol = const_symbol.second->mp_Id;
            type = (TYPES) that_symbol->m_idType;
            const_val = get_const_symbol_value(that_symbol->m_name);
            if (type != INT && type != _REAL && type != _CHAR && type != _BOOLEAN) {
                std::cout << "Line: " << const_symbol.second->m_lineno << ": 常量声明的类型错误" << endl;
                flag = false;
                break;
            }
        }
        if (const_symbol.second->m_postNeg == CONST_NEGATIVE)  // 负常量
            const_val = - const_val;
        bool is_var = false;
        Ranges array_ranges = {};
        int func_nargs = 0;
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = const_symbol.second->m_lineno;
        int ref_line = -1;
        Property p = {
                type,
                is_const,
                const_val,
                is_var,
                array_ranges,
                subprogram_type,
                func_nargs,
                nargs_var_or_not,
                nargs_types,
                dec_line,
                ref_line
        };
        if (exists(name)) {
            symbols[name] = p;
        } else {
            if (symbols.insert(SymbolItem(name, p)).second) {
                continue;
            } else {
                cout << "插入常量符号：" << name << "失败" << endl;
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool SymbolSheet::add_var_symbols(VarDeclarations *var_declarations) {
    bool flag = true;
    for (auto vars: var_declarations->mv_Var) {
        vector<Id *> var_symbols = vars.first->mv_Id;
        auto type = (TYPES) vars.second->checkSimpleType();
        SUBPROGRAM_TYPE subprogram_type = NONE;
        bool is_const = false;
        float const_val = 0;
        bool is_var = false;
        Ranges array_ranges;
        if (vars.second->checkIsArray()) {
            array_ranges = vars.second->getPeriod();
        }
        int func_nargs = 0;
        vector<bool> nargs_var_or_not = {false};
        SubprogramArgsType nargs_types;
        int dec_line = vars.second->getLineno();
        int ref_line = -1;

        for (auto var_symbol: var_symbols) {
            string name = var_symbol->m_name;
            if (check_is_reserved(name))  {
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
                    subprogram_type,
                    func_nargs,
                    nargs_var_or_not,
                    nargs_types,
                    dec_line,
                    ref_line
            };
            if (exists(name)) {
                symbols[name] = p;
            } else {
                if (symbols.insert(SymbolItem(name, p)).second) {
                    continue;
                } else {
                    cout << "插入变量符号" << name << "失败" << endl;
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}

bool SymbolSheet::add_subprogram_symbols(SubProgramDeclarations *subProgram_declarations) {
    bool flag = true;
    for (auto subprogram: subProgram_declarations->mv_Common) {
        string name = subprogram->getFuncId()->m_name;
        if (check_is_reserved(name))  {
            cout << "子函数标识符\"" << name << "\"为关键字，无法使用" << endl;
            flag = false;
            break;
        }
        // 如果是函数则代表返回值，如果是过程则为　VOID
        auto type = (TYPES) subprogram->checkReturnType();
        // 子程序类型（函数、过程）
        auto subprogram_type = (SUBPROGRAM_TYPE) subprogram->getCommonType();
        bool is_const = false;
        float const_val = 0;
        bool is_var = false;
        Ranges array_ranges;
        int subprogram_args_num = 0;
        vector<bool> nargs_var_or_not;
        SubprogramArgsType nargs_types;
        if (subprogram->getParamList()) {
            vector<Parameter *> parameters = subprogram->getParamList()->mv_Patameter;
            for (auto ids: parameters) {
                bool isVar = ids->m_isVal;
                subprogram_args_num += ids->getIdList()->getIdNum();
                IdList *id_list = ids->getIdList();
                for (auto id: id_list->mv_Id) {
                    nargs_types.push_back(id->m_idType);
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
                subprogram_type,
                subprogram_args_num,
                nargs_var_or_not,
                nargs_types,
                dec_line,
                ref_line
        };
        if (symbols.insert(SymbolItem(name, p)).second) {
            continue;
        } else {
            cout << "插入子程序符号：" << name << "失败" << endl;
            flag = false;
            break;
        }
    }
    return flag;
}

bool SymbolSheet::exists(const string &symbol_name) {
    SymbolItems::iterator it;
    it = this->symbols.find(symbol_name);
    return it != this->symbols.end();
}

bool SymbolSheet::check_is_reserved(const string &symbol_name) {
    return keywords.find(symbol_name) != keywords.end() || BuiltInFunctions.find(symbol_name) != BuiltInFunctions.end();
}

float SymbolSheet::get_const_symbol_value(const string &symbol_name) {
    if (this->sheet_name == "0") {
        if (this->symbols.find(symbol_name) != this->symbols.end()) {
            return this->symbols[symbol_name].const_val;
        }
    } else {
        SymbolSheet global_sheet;
        if (SymbolSheetList.find("0") != SymbolSheetList.end())
            global_sheet = SymbolSheetList["0"];
        else {
            cout << "error: 未找到全局符号表" << endl;
            exit(1);
        }
        if (this->symbols.find(symbol_name) != this->symbols.end()) {
            return this->symbols[symbol_name].const_val;
        } else if (global_sheet.symbols.find(symbol_name) != global_sheet.symbols.end()) {
            return global_sheet.symbols[symbol_name].const_val;
        }
    }
    return 0;
}






