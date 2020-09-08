#ifndef PASCAL_C_COMPILER_SYMBOL_SHEET_H
#define PASCAL_C_COMPILER_SYMBOL_SHEET_H

#include <string>
#include <set>
#include <vector>
#include <map>

#include "syntax_tree/syntax_tree.h"
#include "../defines/types.h"

using namespace std;

typedef string SymbolSheetName;
typedef string SymbolName;

const set<SymbolName> keywords = {
        "program", "var", "const", "function", "procedure", "begin", "end", "array", "of", "integer", "real", "boolean",
        "char", "true", "false", "and", "or", "not", "div", "mod", "if", "then", "else", "for", "to", "do"
};

// read 和 write 函数，方便测试时读写，转换C语言时转换为 scanf 和 printf
const set<SymbolName> BuiltInFunctions = {
        "read", "readln", "write", "writeln"
};

struct Property {
    TYPES type;                             // 符号类型

    bool is_const;                          // 是否是常量
    float const_val;                        // 常量值

    bool is_var;                            // 是否是变量，若不是则是数组

    Ranges array_ranges;                    // 数组的范围（可能是多维）

    SUBPROGRAM_TYPE subprogram_type;        // 若是子程序（函数或过程）则记录返回类型
    int subprogram_args_num;                // 子程序参数个数
    vector<bool> nargs_var_or_not;     // 参数是否是变量（每个参数）
    SubprogramArgsType nargs_types;         // 每个参数的类型

    // 其他信息
    int dec_line;                           // 定义处的行数
    int ref_line;                           // 引用处的行数
};

typedef pair<SymbolName, Property> SymbolItem;
typedef map<SymbolName, Property> SymbolItems;
class SymbolSheet;
static map <SymbolSheetName, SymbolSheet> SymbolSheetList;
typedef map<SymbolSheetName, SymbolSheet>::value_type SymbolSheetItem;
typedef pair<bool, SymbolSheetName> CreateSymbolSheetResult;

// 针对符号表的方法
// 查看符号是否存在
bool lookup_symbol(const string& symbolSheet_name, const string& symbol_name);
// 获取符号类型
int get_symbol_type(const string& symbolSheet_name, const string& symbol_name);
// 获取数组类型的下标范围
Ranges get_symbol_range(const string& symbolSheet_name, const string& symbol_name);
// 获取数组每一维的类型
int get_array_type(const string& symbolSheet_name, const string& symbol_name);
// 获取函数返回值
int get_func_return_type(const string& symbol_name);
// 判断是否是函数
bool lookup_func(const string& symbol_name);
// 判断是否是过程
bool lookup_procedure(const string& symbol_name);
// 返回参数个数
int get_symbol_narg(const string& symbolSheet_name, const string& symbol_name);
// 查看参数列表类型（变量或者常量）
vector<bool> get_symbol_nargs_var_or_not(const string& symbolSheet_name, const string& symbol_name);
// 获取参数列表类型
vector<int> get_symbol_narg_type(const string& symbolSheet_name, const string& symbol_name);
// 判断符号表中符号是否为变量
bool get_symbol_var_type(const string& symbolSheet_name, const string& symbol_name);

class SymbolSheet {
public:
    string sheet_name;
    SymbolItems symbols;

    // 将保留字加入符号表
    bool add_reserved();
    // 将参数列表加入符号表
    bool add_parameter_symbols(ParameterList *parameter_list);
    // 将常量加入符号表
    bool add_const_symbols(ConstDeclarations *const_declarations);
    // 将变量加入符号表
    bool add_var_symbols(VarDeclarations *var_declarations);
    // 将子函数加入符号便
    bool add_subprogram_symbols(SubProgramDeclarations *subProgram_declarations);
    // 判断符号表中是否有某符号
    bool exists(const string &symbol_name);
    // 判断某符号是否为保留字
    static bool check_is_reserved(const string &symbol_name);
    // 获取常量符号的值
    float get_const_symbol_value(const string &symbol_name);

};

#endif //PASCAL_C_COMPILER_SYMBOL_SHEET_H
