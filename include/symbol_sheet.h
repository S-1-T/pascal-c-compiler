//
// Created by RinChanNOW! on 2020/5/20.
//

#ifndef PASCAL_C_COMPILER_SYMBOL_SHEET_H
#define PASCAL_C_COMPILER_SYMBOL_SHEET_H

#include <string>
#include <set>
#include <map>
#include <utility>
#include <vector>

class SymbolSheet;

namespace Symbol {
    //
//    enum GENRE {
//        NIL, VAL, SUBPROG, ARRAY
//    };
    // 符号类型
    enum TYPE {
        VOID, INT, REAL, BOOLEAN, CHAR,
        INT_ARRAY, REAL_ARRAY, BOOLEAN_ARRAY, CHAR_ARRAY,
        FUNC, PROC, RESERVED, LIB_FUNC, ID
    };

//    enum FUNC_TYPE {
//        NONE, FUNC, PROC
//    };

    typedef std::string Name;
    // 用于表示数组的上下界，可以是多维数组
    typedef std::pair<int, int> Range;
    typedef std::vector<Range> Ranges;
    // 记录函数与过程类型的参数种类
    typedef std::vector<TYPE> ArgumentsTypes;

    // Pascal-S 的关键字
    const std::set<Name> keywords = {
            "and", "array", "begin", "boolean", "case", "const",
            "div", "do", "downto", "else", "end", "for", "function",
            "if", "integer", "mod", "not", "of", "or", "procedure",
            "program", "real", "record", "repeat", "then", "to",
            "type", "until", "var", "while"
    };

    const std::set<Name> lib_functions = {
            "read", "write"
    };

    union Value {
        int intValue;
        float realValue;
        char charValue;
        bool boolValue;
    };

    struct Property {
        // 是值、数组还是函数
//        GENRE genre = NIL;    // VAL or ARRAY or SUBPROG
        // 类型
        TYPE type = VOID;
//        FUNC_TYPE funcType = NONE;
        // 值类型
        bool isConst = false;
        bool isVal = false;
        Value value;
        // 数组类型
        bool isArray = false;
        Ranges ranges;
        // 函数类型
        int argumentsNum = 0;
        ArgumentsTypes argumentsTypes;
        // 其他信息
        int decLine = 0;
        int refLine = -1;
    };

    // 封装一个表类型
    typedef std::map<Name, Property> Sheet;
    // 封装一个表项类型
    typedef std::pair<Name, Property> SheetItem ;
    // 记录所有符号表
    static std::map<Name, SymbolSheet> SheetList;
}

class SymbolSheet {
public:

    explicit SymbolSheet(Symbol::Name sheetName);

    bool lookUp(Symbol::Name symbolName);
    Symbol::TYPE getType(Symbol::Name symbolName);
    Symbol::TYPE getReturnType(Symbol::Name);
    int getArgumentsNum(Symbol::Name symbolName);
    Symbol::ArgumentsTypes getArgumentsTypes(Symbol::Name symbolName);
    Symbol::Name getSheetName();
private:
    Symbol::Name mSheetName;
    Symbol::Sheet mSheet;
    bool addReservedSymbol();
    // TODO 根据语法树修改符号表
};


#endif //PASCAL_C_COMPILER_SYMBOL_SHEET_H
