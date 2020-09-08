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

// the Rel type
#define EQUAL 0
#define NOT_EQUAL 1
#define LESS 2
#define LESS_EQUAL 3
#define LARGER 4
#define LARGER_EQUAL 5

// the Add type
#define ADD 0
#define SUB 1
#define OR 2

// the Mul type
#define MULTIPLY 0
#define REAL_DIV 1
#define INT_DIV 2
#define MOD 3
#define AND 4

// the common type
#define FUNCTION 0
#define PROCEDURE 1

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
