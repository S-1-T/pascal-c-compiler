%code requires {
	#include "const.h"
	#include "syntax_tree.h"
}

%code top {
	#include "lex.yy.c"
	#include <stdio.h>
	#include <string>
	#include <iostream>

	typedef pair<Id*, ConstValue*> p_Const;
	typedef pair<IdList*, Type*> p_Var;
	typedef pair<int, int> p_Per;

	Program* root;					// AST 根节点
	int errorNum = 0;				// 错误数量

	int yyparse(void);				// 语法分析接口
	void yyerror(const char* s);	// 输出错误信息
	extern int yylineno;			// 行号信息

	#define YYERROR_VERBOSE 1		// 输出详细的错误信息
	extern int yydebug;
	#define YYDEBUG 1				// 输出 yacc 的分析过程

	using namespace std;
}


%token AND ARRAY BEGIN_L BOOLEAN CASE CHAR CONST DIV DO DOWNTO ELSE END FOR FUNCTION IF INTEGER MOD 
%token NOT OF OR PROCEDURE PROGRAM REAL RECORD REPEAT THEN TO TYPE UNTIL VAR WHILE
%token SUBBOUNDARY ASSIGNOP LE_OP GE_OP EQ_OP NE_OP
%token '=' '<' '>' ',' ':' ';' '.' '(' ')' '[' ']' '{' '}' '*' '/' '-' '+'

%left else_conflict
%left ELSE


%union {
	Program* program;
	ProgramBody* programBody;
	ConstDeclarations* constDeclarations;
	VarDeclarations* varDeclarations;
	SubProgramDeclarations* subProgramDeclarations;
	StatementList* statementList;
	Common* common;
	Procedure* procedure;
	Function* function;
	Statement* statement;
	ParameterList* parameterList;
	Variable* variable;
	ProcedureCall* procedureCall;
	FunctionCall* functionCall;
	Expression* expression;
	SimpleExpression* simpleExpression;
	Term* term;
	Factor* factor;
	Not* NOt;
	Uminus* uminus;
	Type* type;
	ConstValue* constValue;
	AssignOp* assignOp;
	IfThenElse* ifThenElse;
	For* FOr;
	Parameter* parameter;
	RelOp* relOp;
	AddOp* addOp;
	MulOp* mulOp;
	Id* id;
	IdList* idList;
	Period* period;
	ExpressionList* expressionList;
	ProgramHead* programHead;
	CompoundStatement* compoundStatement;
	ConstDeclaration* constDeclaration;
	VarDeclaration* varDeclaration;
	SubProgramDeclaration* subProgramDeclaration;
	Subprogram* subprogram;
	SubprogramHead* subprogramHead;
	SubprogramBody* subprogramBody;
	FormalParameter* formalParameter;
	VarParameter* varParameter;
	ValueParameter* valueParameter;
	IdVarPart* idVarPart;
	int m_int;
	float m_float;
	std::string* m_str;
	char m_char;
 	bool m_bool;
}

%token <m_int> DIGITS           // 整数
%token <m_float> NUMBER         // 实数
%token <m_str> IDENTIFIER       // 标识符
%token <m_char> LETTER;         // 字符
%token <m_bool> BOOL;           // 布尔值
%type <m_int> SDIGITS           // 有符号整数
%type <m_float> SNUMBER         // 无符号整数

// AST 节点
%type <program> program
%type <programHead> program_head
%type <programBody> program_body
%type <idList> identifier_list
%type <constDeclarations> const_declarations
%type <constDeclaration> const_declaration
%type <constValue> const_variable
%type <varDeclarations> var_declarations
%type <varDeclaration> var_declaration
%type <type> type
%type <m_int> standard_type
%type <period> period
%type <subProgramDeclarations> subprogram_declarations
%type <common> subprogram
%type <subprogramHead> subprogram_head
%type <formalParameter> formal_parameter
%type <parameterList> parameter_list
%type <parameter> parameter
%type <varParameter> var_parameter
%type <valueParameter> value_parameter
%type <subprogramBody> subprogram_body
%type <compoundStatement> compound_statement
%type <statementList> statement_list
%type <statement> statement
%type <variable> variable
%type <idVarPart> IdVarPart
%type <procedureCall> call_procedure_statement
%type <statement> else_part
%type <expressionList> expression_list
%type <expression> expression
%type <simpleExpression> simple_expression
%type <term> term
%type <factor> factor

%%

program 
	: program_head program_body '.'	{
		$$ = new Program($1->m_ID, $1->m_IDList, $2);
		root = $$;
	} 

program_head 
	: PROGRAM IDENTIFIER '(' identifier_list ')' ';' {
		Id* tmp = new Id();
		tmp -> m_Name = *($2);
		tmp -> m_Lineno = yylineno;
		tmp -> m_IDType = TYPE_ID;
		$$ = new ProgramHead(tmp, $4);
	}
	| PROGRAM error {
		$$ = new ProgramHead(nullptr,nullptr);
	}
	| error {
		$$ = new ProgramHead(nullptr,nullptr);
	}

program_body 
	: const_declarations var_declarations subprogram_declarations compound_statement {
		$$ = new ProgramBody($1, $2, $3, $4);
	}
	//解决声明部分的语法错误
	| error const_declarations var_declarations subprogram_declarations compound_statement{
		$$ = new ProgramBody();
	}

identifier_list 
	: identifier_list ',' IDENTIFIER {
		$$ = new IdList();
		$$ = $1;
		Id* tmp = new Id();
		tmp -> m_Name = *($3);
		tmp -> m_Lineno = yylineno;
		$$ -> m_IDVector.push_back(tmp);
	}
	| IDENTIFIER {
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ = new IdList();
		$$ -> m_IDVector.push_back(tmp);
		$$ -> m_Lineno = yylineno;
	}
	/*
	| error {
		$$ = new IdList();
	}
	*/
	;

const_declarations 
	: CONST const_declaration ';' {
		$$ = new ConstDeclarations($2 -> m_ConstVector);
	}
	| {
		$$ = new ConstDeclarations();
	}
	;

const_declaration 
	: const_declaration ';' IDENTIFIER '=' const_variable {
		Id* tmp = new Id();
		tmp -> m_Name = *($3);
		tmp -> m_Lineno = yylineno;

		$1 -> m_ConstVector.push_back(p_Const(tmp, $5));
		$$ = new ConstDeclaration($1 -> m_ConstVector);
	}
	| IDENTIFIER '=' const_variable {
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ = new ConstDeclaration();
		$$ -> m_ConstVector.push_back(p_Const(tmp,$3));
	}
	;

const_variable 
	: '+' IDENTIFIER {
		$$ = new ConstValue();
		$$ -> m_Lineno = yylineno;
		$$ -> m_postNeg = CONST_POSITIVE;
		$$ -> m_valueType = TYPE_ID;
		$$ -> m_isId = true;
		Id* tmp = new Id();
		tmp -> m_Name = *($2);
		tmp -> m_Lineno = yylineno;
		$$ -> m_PID = tmp;
	}
	| '-' IDENTIFIER {
		$$ = new ConstValue();
		$$ -> m_Lineno = yylineno;
		$$ -> m_postNeg = CONST_NEGATIVE;
		$$ -> m_valueType = TYPE_ID;
		$$ -> m_isId = true;
		Id* tmp = new Id();
		tmp -> m_Name = *($2);
		tmp -> m_Lineno = yylineno;
		$$ -> m_PID = tmp;	
	} 
	| IDENTIFIER {
		$$ = new ConstValue();
		$$ -> m_Lineno = yylineno;
		$$ -> m_postNeg = CONST_POSITIVE;
		$$ -> m_valueType = TYPE_ID;
		$$ -> m_isId = true;
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ -> m_PID = tmp;
	}
	| '+' NUMBER {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_POSITIVE;
		$$ -> m_valueType = TYPE_REAL;
		$$ -> m_real = $2;
	}
	| '-' NUMBER {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_NEGATIVE;
		$$ -> m_valueType = TYPE_REAL;
		$$ -> m_real = $2;	
	}
	| NUMBER {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_POSITIVE;
		$$ -> m_valueType = TYPE_REAL;
		$$ -> m_real = $1;
	}
	| '+' DIGITS {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_POSITIVE;
		$$ -> m_valueType = TYPE_INTEGER;
		$$ -> m_int = $2;
	}
	| '-' DIGITS {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_NEGATIVE;
		$$ -> m_valueType = TYPE_INTEGER;
		$$ -> m_int = $2;
	}
	| DIGITS {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_POSITIVE;
		$$ -> m_valueType = TYPE_INTEGER;
		$$ -> m_int = $1;
	}
	| LETTER {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_NULL;
		$$ -> m_valueType = TYPE_CHAR;
		$$ -> m_char = $1;
	}
	| BOOL {
		$$ = new ConstValue();
		$$ -> m_postNeg = CONST_NULL;
		$$ -> m_valueType = TYPE_BOOLEAN;
		$$ -> m_bool = $1;
	}

var_declarations 
	: VAR var_declaration ';' {
		$$ = new VarDeclarations($2 -> m_VariableVector);
	}
	| {
		vector<p_Var> tmp;
		$$ = new VarDeclarations(tmp);
	}
	;

var_declaration 
	: var_declaration ';' identifier_list ':' type {
		$$ = new VarDeclaration($1 -> m_VariableVector);
		$$ -> m_VariableVector.push_back(p_Var($3, $5));
	}
	| identifier_list ':' type {
		$$ = new VarDeclaration();
		$$ -> m_VariableVector.push_back(p_Var($1, $3));
	}
	;

type 
	: standard_type {
		$$ = new Type();
		$$ -> m_SimpleType = $1;
		$$ -> m_isArray = false;
		$$ -> m_Lineno = yylineno; 
	}
	| ARRAY '[' period ']' OF standard_type {
		$$ = new Type();
		$$ -> m_Lineno = yylineno;
		$$ -> m_isArray = true;
		$$ -> mp_Period = $3;
		$$ -> m_SimpleType = $6; 
	}
	| error {
		$$ = new Type();
	}
	;

standard_type 
	: INTEGER {
		$$ = TYPE_INTEGER;
	}
	| REAL {
		$$ = TYPE_REAL;
	}
	| BOOLEAN {
		$$ = TYPE_BOOLEAN;
	}
	| CHAR {
		$$ = TYPE_CHAR;
	}
	;


period 
	: period ',' SDIGITS SUBBOUNDARY SDIGITS {
		$$ = new Period($1 -> m_DimsVector);
		$$ -> m_DimsVector.push_back(p_Per($3, $5));
	}
	| SDIGITS SUBBOUNDARY SDIGITS {
		$$ = new Period();
		$$ -> m_DimsVector.push_back(p_Per($1, $3));
	}

SDIGITS
	: DIGITS{
		$$ = $1;
	}	
	| '+' DIGITS{
		$$ = $2;
	}
	| '-' DIGITS{
		$$ = -$2;
	}


subprogram_declarations 
	: subprogram_declarations subprogram ';' {
		$$ = new SubProgramDeclarations($1 -> m_CommonVector);
		$$ -> m_CommonVector.push_back($2);
	}
	| {
		$$ = new SubProgramDeclarations();
	}
	;

subprogram
	: subprogram_head subprogram_body {
		if($1 -> m_SimpleType == TYPE_NULL) {
			$$ = new Procedure(yylineno, $1 -> m_ID, $1-> m_FormalParameter -> m_ParameterList, $2 -> m_ConstDeclarations, $2 -> m_VarDeclarations, $2-> m_CompoundStatement -> m_StatementList);
		}
		else {
			$$ = new Function($1 -> m_SimpleType, yylineno, $1 -> m_ID, $1-> m_FormalParameter -> m_ParameterList, $2 -> m_ConstDeclarations, $2 -> m_VarDeclarations, $2-> m_CompoundStatement -> m_StatementList);
		}
	}

subprogram_head 
	: FUNCTION IDENTIFIER formal_parameter ':' standard_type ';' {
		Id* tmp = new Id();
		tmp -> m_Name = *($2);
		tmp -> m_Lineno = yylineno;
		$$ = new SubprogramHead(tmp, $3, $5);
	}
	| PROCEDURE IDENTIFIER formal_parameter ';' {
		Id* tmp = new Id();
		tmp -> m_Name = *($2);
		tmp -> m_Lineno = yylineno;
		$$ = new SubprogramHead(tmp, $3, TYPE_NULL);
	}
	| FUNCTION error ';' {
		Id* tmp = new Id();
		$$ = new SubprogramHead(tmp,new FormalParameter(),TYPE_NULL);
	}
	| PROCEDURE error ';'{
		Id* tmp = new Id();
		$$ = new SubprogramHead(tmp,new FormalParameter(),TYPE_NULL);
	}
	;

formal_parameter 
	: '(' parameter_list ')' {
		$$ = new FormalParameter($2);
	}
	| {
		$$ = new FormalParameter(nullptr);
	}
	;

parameter_list 
	: parameter_list ';' parameter {
		$$ = new ParameterList(yylineno, $1 -> mv_Patameter);
		$$ -> mv_Patameter.push_back($3);
	}
	| parameter {
		$$ = new ParameterList();
		$$ -> m_Lineno = yylineno;
		$$ -> mv_Patameter.push_back($1);
	}
	;

parameter
	: var_parameter {
		$$ = new Parameter(true, yylineno, $1 -> m_ValueParameter -> m_IDList);
		$$ -> m_Type = $1 -> m_ValueParameter -> m_SimpleType;

	}
	| value_parameter {
		$$ = new Parameter(false, yylineno, $1 -> m_IDList);
		$$ -> m_Type = $1 -> m_SimpleType;
	}
	;

var_parameter 
	: VAR value_parameter {
		$$ = new VarParameter($2);
	}
	;

value_parameter 
	: identifier_list ':' standard_type {
		$$ = new ValueParameter($1, $3);
	}
	;

subprogram_body 
	: const_declarations var_declarations compound_statement {
		$$ = new SubprogramBody($1, $2, $3);
	}
	| error const_declarations var_declarations compound_statement{
		$$ = new SubprogramBody(nullptr,nullptr,new CompoundStatement());
	}

compound_statement 
	: BEGIN_L statement_list END {
		$$ = new CompoundStatement($2);
	}
	;

statement_list 
	: statement_list ';' statement {
		$$ = new StatementList($1 -> m_StatementVector);
		if($3 != nullptr)
			$$ -> m_StatementVector.push_back($3);
	}
	| statement {
		$$ = new StatementList();
		if($1 != nullptr)
			$$ -> m_StatementVector.push_back($1);
	}
	| statement_list ';' error {
		$$ = new StatementList();
	}
	| error {
		$$ = new StatementList();
	}
	;


statement 
	: variable ASSIGNOP expression {	//赋值
		$$ = new Statement();
		$$ -> m_stateType = STATEMENT_ASSIGN;
		$$ -> m_Lineno = yylineno;
		$$ -> mp_AssignOp = new AssignOp($1, $3);
		$$ -> mp_AssignOp -> m_Lineno = yylineno;
		$$ -> mp_Procedure_call = nullptr;
		$$ -> m_PStatementList = nullptr;
		$$ -> mp_If_Then_Else = nullptr;
		$$ -> mp_For = nullptr;
	}
	| call_procedure_statement {	//函数
		$$ = new Statement();
		$$ -> m_stateType = STATEMENT_PROCEDURE;
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Procedure_call = $1;
		$$ -> mp_AssignOp = nullptr;
		$$ -> m_PStatementList = nullptr;
		$$ -> mp_If_Then_Else = nullptr;
		$$ -> mp_For = nullptr;
	}
	| compound_statement {	//函数内部
		$$ = new Statement();
		$$ -> m_stateType = STATEMENT_COMPOUND;
		$$ -> m_Lineno = yylineno;
		$$ -> m_PStatementList = $1 -> m_StatementList;
		$$ -> mp_AssignOp = nullptr;
		$$ -> mp_Procedure_call = nullptr;
		$$ -> mp_If_Then_Else = nullptr;
		$$ -> mp_For = nullptr;
	}
	| IF expression THEN statement else_part {	//if语句
		$$ = new Statement();
		$$ -> m_stateType = STATEMENT_IF;
		$$ -> m_Lineno = yylineno;
		$$ -> mp_If_Then_Else = new IfThenElse($2, $4, $5);
		$$ -> mp_AssignOp = nullptr;
		$$ -> mp_Procedure_call = nullptr;
		$$ -> m_PStatementList = nullptr;
		$$ -> mp_For = nullptr;
	}
	| IF error THEN statement else_part {	//expression部分出错
		$$ = new Statement();
	} 
	| FOR IDENTIFIER ASSIGNOP expression TO expression DO statement {	//for循环
		Id* tmp = new Id();
		tmp -> m_Name = *($2);
		tmp -> m_Lineno = yylineno;
		$$ = new Statement();
		$$ -> m_stateType = STATEMENT_FOR;
		$$ -> m_Lineno = yylineno;
		$$ -> mp_For = new For(tmp, $4, $6, $8);
		$$ -> mp_AssignOp = nullptr;
		$$ -> mp_Procedure_call = nullptr;
		$$ -> m_PStatementList = nullptr;
		$$ -> mp_If_Then_Else = nullptr;
	}
	| FOR error TO expression DO statement {
		$$ = new Statement();
	}
	| FOR IDENTIFIER ASSIGNOP expression TO error DO statement {
		$$ = new Statement();
	}
	| {
		$$ = nullptr;
	}
	;


variable 
	: IDENTIFIER IdVarPart {
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ = new Variable();
		$$ -> m_PID = tmp;
		$$ -> m_Lineno = yylineno;
		if($2 -> m_ExpressionList != nullptr){
			$$ -> m_isArray = true;
			$$ -> mp_Expression_List = $2 -> m_ExpressionList;
		}else {
			$$ -> m_isArray =false;
			$$ -> mp_Expression_List = nullptr;
		}
	}



IdVarPart
	: '[' expression_list ']' {
		$$ = new IdVarPart($2);
	}
	| {
		$$ = new IdVarPart(nullptr);
	}
	;	

call_procedure_statement 
	: IDENTIFIER {
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ = new ProcedureCall();
		$$ -> m_Lineno = yylineno;
		$$ -> m_expNum = 0;
		$$ -> m_PID = tmp;
		$$ -> mp_Expression_List = nullptr;

	}
	| IDENTIFIER '(' expression_list ')' {
		$$ = new ProcedureCall();
		$$ -> m_Lineno = yylineno;
		$$ -> m_expNum = $3 -> m_ExpressionVector.size();
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ -> m_PID = tmp;
		$$ -> mp_Expression_List = $3;
	}
	;

else_part 
	: ELSE statement {
		$$ = $2;
	}
	|%prec else_conflict {
		$$ = nullptr;
	}
	;



expression_list 
	: expression_list ',' expression {
		$$ = new ExpressionList($1 -> m_ExpressionVector, $1 -> m_TypeVector);
		$$ -> m_ExpressionVector.push_back($3);
	}
	| expression {
		$$ = new ExpressionList();
		$$ -> m_ExpressionVector.push_back($1);
	}
	;

expression 
	: simple_expression '>' simple_expression {
		$$ = new Expression();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Simple_Expression = nullptr;
		$$ -> mp_Relop = new RelOp(OP_LARGER, yylineno, $1, $3);
	}
	| simple_expression '<' simple_expression {
		$$ = new Expression();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Simple_Expression = nullptr;
		$$ -> mp_Relop = new RelOp(OP_LESS, yylineno, $1, $3);
	}
	| simple_expression NE_OP simple_expression {
		$$ = new Expression();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Simple_Expression = nullptr;
		$$ -> mp_Relop = new RelOp(OP_NOT_EQUAL, yylineno, $1, $3);
	}
	| simple_expression LE_OP simple_expression {
		$$ = new Expression();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Simple_Expression = nullptr;
		$$ -> mp_Relop = new RelOp(OP_LESS_EQUAL, yylineno, $1, $3);
	}
	| simple_expression GE_OP simple_expression {
		$$ = new Expression();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Simple_Expression = nullptr;
		$$ -> mp_Relop = new RelOp(OP_LARGER_EQUAL, yylineno, $1, $3);
	}
	| simple_expression '=' simple_expression {
		$$ = new Expression();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Simple_Expression = nullptr;
		$$ -> mp_Relop = new RelOp(OP_EQUAL, yylineno, $1, $3);
	}
	| simple_expression {
		$$ = new Expression();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Simple_Expression = $1;
		$$ -> mp_Relop = nullptr;
	}
	;

simple_expression 
	: term {
		$$ = new SimpleExpression(yylineno, nullptr, $1);
	}
	| simple_expression '+' term {
		$$ = new SimpleExpression(yylineno, new AddOp(OP_ADD, yylineno, $1, $3),nullptr);
	}
	| simple_expression '-' term {
		$$ = new SimpleExpression(yylineno, new AddOp(OP_SUB, yylineno, $1, $3),nullptr);
	}
	| simple_expression OR term {
		$$ = new SimpleExpression(yylineno, new AddOp(OP_OR, yylineno, $1, $3),nullptr);
	}
	;

term 
	: term '*' factor {
		$$ = new Term(yylineno, new MulOp(OP_MULTIPLY, yylineno, $1, $3), nullptr);
	}
	| term '/' factor {
		$$ = new Term(yylineno, new MulOp(OP_REAL_DIV, yylineno, $1, $3), nullptr);
	}
	| term AND factor {
		$$ = new Term(yylineno, new MulOp(OP_AND, yylineno, $1, $3), nullptr);
	}
	| term DIV factor {
		$$ = new Term(yylineno, new MulOp(OP_INT_DIV, yylineno, $1, $3), nullptr);
	}
	| term MOD factor {
		$$ = new Term(yylineno, new MulOp(OP_MOD, yylineno, $1, $3), nullptr);
	}
	| factor {
		$$ = new Term(yylineno, nullptr, $1);
	}
	;

SNUMBER: NUMBER{
		$$ = $1;
	}
	| '-' NUMBER{
		$$ = -$2;
	}

factor 
	: SDIGITS {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> m_int = $1;
		$$ -> m_factorType = FACTOR_VALUE_INT;
	}
	| SNUMBER {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> m_real = $1;
		$$ -> m_factorType = FACTOR_VALUE_REAL;
	}
	| LETTER {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> m_char = $1;
		$$ -> m_factorType = FACTOR_VALUE_CHAR;
	}
	| BOOL {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> m_bool = $1;
		$$ -> m_factorType = FACTOR_VALUE_BOOL;
	}
	| variable {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Variable = $1;
		$$ -> mp_Function_Call = nullptr;
		$$ -> mp_Expression = nullptr;
		$$ -> mp_Not = nullptr;
		$$ -> mp_Uminus = nullptr;
		$$ -> m_factorType = FACTOR_VAR;
	}
	| IDENTIFIER '(' expression_list ')' {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Variable = nullptr;
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ -> mp_Function_Call = new FunctionCall($3 -> m_ExpressionVector.size(), yylineno, tmp, $3);
		$$ -> mp_Expression = nullptr;
		$$ -> mp_Not = nullptr;
		$$ -> mp_Uminus = nullptr;
		$$ -> m_factorType = FACTOR_FUNCCALL;
	}
	| IDENTIFIER '(' ')'{
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Variable = nullptr;
		Id* tmp = new Id();
		tmp -> m_Name = *($1);
		tmp -> m_Lineno = yylineno;
		$$ -> mp_Function_Call = new FunctionCall(0, yylineno, tmp, nullptr);
		$$ -> mp_Expression = nullptr;
		$$ -> mp_Not = nullptr;
		$$ -> mp_Uminus = nullptr;
		$$ -> m_factorType = FACTOR_FUNCCALL;
	}
	| '(' expression ')' {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Variable = nullptr;
		$$ -> mp_Function_Call = nullptr;
		$$ -> mp_Expression = $2;
		$$ -> mp_Not = nullptr;
		$$ -> mp_Uminus = nullptr;
		$$ -> m_factorType = FACTOR_BRACKETS;
	}
	| NOT factor {
		$$ = new Factor();
		$$ -> m_Lineno = yylineno;
		$$ -> mp_Variable = nullptr;
		$$ -> mp_Function_Call = nullptr;
		$$ -> mp_Expression = nullptr;
		$$ -> mp_Not = new Not();
		$$ -> mp_Not -> m_PFactor = $2;
		$$ -> mp_Not -> m_Lineno = yylineno;
		$$ -> mp_Uminus = nullptr;
		$$ -> m_factorType = FACTOR_NOT;
	}
	;
%%


int lexical_and_syntax_analyse() {
	yydebug = 0;
	int ans = yyparse();
	if(errorNum)
		cout<< "The number of syntax error is: "<< errorNum <<endl;
    if(ans || errorNum !=0 )
    	return 1;
    else
    	return 0;
}


extern void yyerror(const char* s) {
	printf("line: %d, Error '%s'\n",yylineno,s);
	errorNum++;
}