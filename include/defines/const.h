#pragma once

#ifndef PASCAL_C_COMPILER_CONST_H
#define PASCAL_C_COMPILER_CONST_H

// the type define
#define TYPE_INTEGER 0
#define TYPE_REAL 1
#define TYPE_BOOLEAN 2
#define TYPE_CHAR 3
#define TYPE_ID 4
#define TYPE_NULL 5

// the const is negative or positive
#define CONST_NULL 0
#define CONST_POSITIVE 1
#define CONST_NEGATIVE 2

// the procedure call type
#define PROCECALL_NORMAL 0
#define PROCECALL_READ 1
#define PROCECALL_READLN 2
#define PROCECALL_WRITE 3
#define PROCECALL_WRITELN 4

// 注意要和词法分析定义的符号区分开
// the Rel type
#define OP_EQUAL 0
#define OP_NOT_EQUAL 1
#define OP_LESS 2
#define OP_LESS_EQUAL 3
#define OP_LARGER 4
#define OP_LARGER_EQUAL 5

// the Add type
#define OP_ADD 0
#define OP_SUB 1
#define OP_OR 2

// the Mul type
#define OP_MULTIPLY 0
#define OP_REAL_DIV 1
#define OP_INT_DIV 2
#define OP_MOD 3
#define OP_AND 4

// the common type
#define SUBPROGRAM_FUNCTION 0
#define SUBPROGRAM_PROCEDURE 1

// the statement type
#define STATEMENT_ASSIGN 0
#define STATEMENT_PROCEDURE 1
#define STATEMENT_COMPOUND 2
#define STATEMENT_IF 3
#define STATEMENT_FOR 4

// the factor Type
#define FACTOR_VAR 0
#define FACTOR_FUNCCALL 1
#define FACTOR_BRACKETS 2
#define FACTOR_NOT 3
#define FACTOR_UMINUS 4
#define FACTOR_VALUE_INT 5
#define FACTOR_VALUE_REAL 6
#define FACTOR_VALUE_CHAR 7
#define FACTOR_VALUE_BOOL 8

// the uminus type
#define UMINUS_POSITIVE 0
#define UMINUS_NEGATIVE 1

#endif //PASCAL_C_COMPILER_CONST_H
