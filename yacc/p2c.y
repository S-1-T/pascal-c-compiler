%code requires {
	#include "const.h"
	#include "syntax_tree.h"
}

%code top {
	#include "lex.yy.c"
	#include <cstdio>
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
	int mInt;
	float mFloat;
	std::string* mStr;
	char mChar;
 	bool mBool;
}

%token <mInt> DIGITS           // 整数
%token <mFloat> NUMBER         // 实数
%token <mStr> IDENTIFIER       // 标识符
%token <mChar> LETTER;         // 字符
%token <mBool> BOOL;           // 布尔值
%type <mInt> SDIGITS           // 有符号整数
%type <mFloat> SNUMBER         // 无符号整数

// AST 节点
%type <program> program
%type <programHead> programhead
%type <programBody> programbody
%type <idList> identifier_list
%type <constDeclarations> const_declarations
%type <constDeclaration> const_declaration
%type <constValue> const_variable
%type <varDeclarations> var_declarations
%type <varDeclaration> var_declaration
%type <type> type
%type <mInt> standard_type
%type <period> period
%type <subProgramDeclarations> subprogramdeclarations
%type <common> subprogram
%type <subprogramHead> subprogramhead
%type <formalParameter> formal_parameter
%type <parameterList> parameter_list
%type <parameter> parameter
%type <varParameter> var_parameter
%type <valueParameter> value_parameter
%type <subprogramBody> subprogrambody
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
	: programhead programbody '.'	{
		$$ = new Program($1->mId, $1->mIdList, $2);
		root = $$;
	} 

programhead
	: PROGRAM IDENTIFIER '(' identifier_list ')' ';' {
		Id* tmp = new Id();
		tmp -> mName = *($2);
		tmp -> mLineno = yylineno;
		tmp -> mIdType = TYPE_ID;
		$$ = new ProgramHead(tmp, $4);
	}
	| PROGRAM error {
		$$ = new ProgramHead(nullptr,nullptr);
	}
	| error {
		$$ = new ProgramHead(nullptr,nullptr);
	}

programbody
	: const_declarations var_declarations subprogramdeclarations compound_statement {
		$$ = new ProgramBody($1, $2, $3, $4);
	}
	//解决声明部分的语法错误
	| error const_declarations var_declarations subprogramdeclarations compound_statement{
		$$ = new ProgramBody();
	}

identifier_list 
	: identifier_list ',' IDENTIFIER {
		$$ = new IdList();
		$$ = $1;
		Id* tmp = new Id();
		tmp -> mName = *($3);
		tmp -> mLineno = yylineno;
		$$ -> mIdVector.push_back(tmp);
	}
	| IDENTIFIER {
		Id* tmp = new Id();
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ = new IdList();
		$$ -> mIdVector.push_back(tmp);
		$$ -> mLineno = yylineno;
	}
	/*
	| error {
		$$ = new IdList();
	}
	*/
	;

const_declarations 
	: CONST const_declaration ';' {
		$$ = new ConstDeclarations($2 -> mConstVector);
	}
	| {
		$$ = new ConstDeclarations();
	}
	;

const_declaration 
	: const_declaration ';' IDENTIFIER '=' const_variable {
		Id* tmp = new Id();
		tmp -> mName = *($3);
		tmp -> mLineno = yylineno;

		$1 -> mConstVector.push_back(p_Const(tmp, $5));
		$$ = new ConstDeclaration($1 -> mConstVector);
	}
	| IDENTIFIER '=' const_variable {
		Id* tmp = new Id();
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ = new ConstDeclaration();
		$$ -> mConstVector.push_back(p_Const(tmp,$3));
	}
	;

const_variable 
	: '+' IDENTIFIER {
		$$ = new ConstValue();
		$$ -> mLineno = yylineno;
		$$ -> mPolarity = CONST_POSITIVE;
		$$ -> mValueType = TYPE_ID;
		$$ -> misId = true;
		Id* tmp = new Id();
		tmp -> mName = *($2);
		tmp -> mLineno = yylineno;
		$$ -> mId = tmp;
	}
	| '-' IDENTIFIER {
		$$ = new ConstValue();
		$$ -> mLineno = yylineno;
		$$ -> mPolarity = CONST_NEGATIVE;
		$$ -> mValueType = TYPE_ID;
		$$ -> misId = true;
		Id* tmp = new Id();
		tmp -> mName = *($2);
		tmp -> mLineno = yylineno;
		$$ -> mId = tmp;
	} 
	| IDENTIFIER {
		$$ = new ConstValue();
		$$ -> mLineno = yylineno;
		$$ -> mPolarity = CONST_POSITIVE;
		$$ -> mValueType = TYPE_ID;
		$$ -> misId = true;
		Id* tmp = new Id();
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ -> mId = tmp;
	}
	| '+' NUMBER {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_POSITIVE;
		$$ -> mValueType = TYPE_REAL;
		$$ -> mReal = $2;
	}
	| '-' NUMBER {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_NEGATIVE;
		$$ -> mValueType = TYPE_REAL;
		$$ -> mReal = $2;
	}
	| NUMBER {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_POSITIVE;
		$$ -> mValueType = TYPE_REAL;
		$$ -> mReal = $1;
	}
	| '+' DIGITS {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_POSITIVE;
		$$ -> mValueType = TYPE_INTEGER;
		$$ -> mInt = $2;
	}
	| '-' DIGITS {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_NEGATIVE;
		$$ -> mValueType = TYPE_INTEGER;
		$$ -> mInt = $2;
	}
	| DIGITS {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_POSITIVE;
		$$ -> mValueType = TYPE_INTEGER;
		$$ -> mInt = $1;
	}
	| LETTER {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_NULL;
		$$ -> mValueType = TYPE_CHAR;
		$$ -> mChar = $1;
	}
	| BOOL {
		$$ = new ConstValue();
		$$ -> mPolarity = CONST_NULL;
		$$ -> mValueType = TYPE_BOOLEAN;
		$$ -> mBool = $1;
	}

var_declarations 
	: VAR var_declaration ';' {
		$$ = new VarDeclarations($2 -> mVariableVector);
	}
	| {
		vector<p_Var> tmp;
		$$ = new VarDeclarations(tmp);
	}
	;

var_declaration 
	: var_declaration ';' identifier_list ':' type {
		$$ = new VarDeclaration($1 -> mVariableVector);
		$$ -> mVariableVector.push_back(p_Var($3, $5));
	}
	| identifier_list ':' type {
		$$ = new VarDeclaration();
		$$ -> mVariableVector.push_back(p_Var($1, $3));
	}
	;

type 
	: standard_type {
		$$ = new Type();
		$$ -> mSimpleType = $1;
		$$ -> misArray = false;
		$$ -> mLineno = yylineno;
	}
	| ARRAY '[' period ']' OF standard_type {
		$$ = new Type();
		$$ -> mLineno = yylineno;
		$$ -> misArray = true;
		$$ -> mPeriod = $3;
		$$ -> mSimpleType = $6;
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
		$$ = new Period($1 -> mDimsVector);
		$$ -> mDimsVector.push_back(p_Per($3, $5));
	}
	| SDIGITS SUBBOUNDARY SDIGITS {
		$$ = new Period();
		$$ -> mDimsVector.push_back(p_Per($1, $3));
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


subprogramdeclarations
	: subprogramdeclarations subprogram ';' {
		$$ = new SubProgramDeclarations($1 -> mCommonVector);
		$$ -> mCommonVector.push_back($2);
	}
	| {
		$$ = new SubProgramDeclarations();
	}
	;

subprogram
	: subprogramhead subprogrambody {
		if($1 -> mSimpleType == TYPE_NULL) {
			$$ = new Procedure(yylineno, $1 -> mId, $1-> mFormalParameter -> mParameterList, $2 -> mConstDeclarations, $2 -> mVarDeclarations, $2-> mCompoundStatement -> mStatementList);
		}
		else {
			$$ = new Function($1 -> mSimpleType, yylineno, $1 -> mId, $1-> mFormalParameter -> mParameterList, $2 -> mConstDeclarations, $2 -> mVarDeclarations, $2-> mCompoundStatement -> mStatementList);
		}
	}

subprogramhead
	: FUNCTION IDENTIFIER formal_parameter ':' standard_type ';' {
		Id* tmp = new Id();
		tmp -> mName = *($2);
		tmp -> mLineno = yylineno;
		$$ = new SubprogramHead(tmp, $3, $5);
	}
	| PROCEDURE IDENTIFIER formal_parameter ';' {
		Id* tmp = new Id();
		tmp -> mName = *($2);
		tmp -> mLineno = yylineno;
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
		$$ = new ParameterList(yylineno, $1 -> mParameters);
		$$ -> mParameters.push_back($3);
	}
	| parameter {
		$$ = new ParameterList();
		$$ -> mLineno = yylineno;
		$$ -> mParameters.push_back($1);
	}
	;

parameter
	: var_parameter {
		$$ = new Parameter(true, yylineno, $1 -> mValueParameter -> mIdList);
		$$ -> mType = $1 -> mValueParameter -> mSimpleType;

	}
	| value_parameter {
		$$ = new Parameter(false, yylineno, $1 -> mIdList);
		$$ -> mType = $1 -> mSimpleType;
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

subprogrambody
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
		$$ = new StatementList($1 -> mStatementVector);
		if($3 != nullptr)
			$$ -> mStatementVector.push_back($3);
	}
	| statement {
		$$ = new StatementList();
		if($1 != nullptr)
			$$ -> mStatementVector.push_back($1);
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
		$$ -> mStateType = STATEMENT_ASSIGN;
		$$ -> mLineno = yylineno;
		$$ -> mAssignOp = new AssignOp($1, $3);
		$$ -> mAssignOp -> mLineno = yylineno;
		$$ -> mProcedure_call = nullptr;
		$$ -> mStatementList = nullptr;
		$$ -> mIfThenElse = nullptr;
		$$ -> mFor = nullptr;
	}
	| call_procedure_statement {	//函数
		$$ = new Statement();
		$$ -> mStateType = STATEMENT_PROCEDURE;
		$$ -> mLineno = yylineno;
		$$ -> mProcedure_call = $1;
		$$ -> mAssignOp = nullptr;
		$$ -> mStatementList = nullptr;
		$$ -> mIfThenElse = nullptr;
		$$ -> mFor = nullptr;
	}
	| compound_statement {	//函数内部
		$$ = new Statement();
		$$ -> mStateType = STATEMENT_COMPOUND;
		$$ -> mLineno = yylineno;
		$$ -> mStatementList = $1 -> mStatementList;
		$$ -> mAssignOp = nullptr;
		$$ -> mProcedure_call = nullptr;
		$$ -> mIfThenElse = nullptr;
		$$ -> mFor = nullptr;
	}
	| IF expression THEN statement else_part {	//if语句
		$$ = new Statement();
		$$ -> mStateType = STATEMENT_IF;
		$$ -> mLineno = yylineno;
		$$ -> mIfThenElse = new IfThenElse($2, $4, $5);
		$$ -> mAssignOp = nullptr;
		$$ -> mProcedure_call = nullptr;
		$$ -> mStatementList = nullptr;
		$$ -> mFor = nullptr;
	}
	| IF error THEN statement else_part {	//expression部分出错
		$$ = new Statement();
	} 
	| FOR IDENTIFIER ASSIGNOP expression TO expression DO statement {	//for循环
		Id* tmp = new Id();
		tmp -> mName = *($2);
		tmp -> mLineno = yylineno;
		$$ = new Statement();
		$$ -> mStateType = STATEMENT_FOR;
		$$ -> mLineno = yylineno;
		$$ -> mFor = new For(tmp, $4, $6, $8);
		$$ -> mAssignOp = nullptr;
		$$ -> mProcedure_call = nullptr;
		$$ -> mStatementList = nullptr;
		$$ -> mIfThenElse = nullptr;
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
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ = new Variable();
		$$ -> mId = tmp;
		$$ -> mLineno = yylineno;
		if($2 -> mExpressionList != nullptr){
			$$ -> misArray = true;
			$$ -> mExpressionList = $2 -> mExpressionList;
		}else {
			$$ -> misArray =false;
			$$ -> mExpressionList = nullptr;
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
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ = new ProcedureCall();
		$$ -> mLineno = yylineno;
		$$ -> mExpressionsNum = 0;
		$$ -> mId = tmp;
		$$ -> mExpressionList = nullptr;

	}
	| IDENTIFIER '(' expression_list ')' {
		$$ = new ProcedureCall();
		$$ -> mLineno = yylineno;
		$$ -> mExpressionsNum = $3 -> mExpressionVector.size();
		Id* tmp = new Id();
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ -> mId = tmp;
		$$ -> mExpressionList = $3;
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
		$$ = new ExpressionList($1 -> mExpressionVector, $1 -> mTypeVector);
		$$ -> mExpressionVector.push_back($3);
	}
	| expression {
		$$ = new ExpressionList();
		$$ -> mExpressionVector.push_back($1);
	}
	;

expression 
	: simple_expression '>' simple_expression {
		$$ = new Expression();
		$$ -> mLineno = yylineno;
		$$ -> mSimpleExpression = nullptr;
		$$ -> mRelOp = new RelOp(OP_LARGER, yylineno, $1, $3);
	}
	| simple_expression '<' simple_expression {
		$$ = new Expression();
		$$ -> mLineno = yylineno;
		$$ -> mSimpleExpression = nullptr;
		$$ -> mRelOp = new RelOp(OP_LESS, yylineno, $1, $3);
	}
	| simple_expression NE_OP simple_expression {
		$$ = new Expression();
		$$ -> mLineno = yylineno;
		$$ -> mSimpleExpression = nullptr;
		$$ -> mRelOp = new RelOp(OP_NOT_EQUAL, yylineno, $1, $3);
	}
	| simple_expression LE_OP simple_expression {
		$$ = new Expression();
		$$ -> mLineno = yylineno;
		$$ -> mSimpleExpression = nullptr;
		$$ -> mRelOp = new RelOp(OP_LESS_EQUAL, yylineno, $1, $3);
	}
	| simple_expression GE_OP simple_expression {
		$$ = new Expression();
		$$ -> mLineno = yylineno;
		$$ -> mSimpleExpression = nullptr;
		$$ -> mRelOp = new RelOp(OP_LARGER_EQUAL, yylineno, $1, $3);
	}
	| simple_expression '=' simple_expression {
		$$ = new Expression();
		$$ -> mLineno = yylineno;
		$$ -> mSimpleExpression = nullptr;
		$$ -> mRelOp = new RelOp(OP_EQUAL, yylineno, $1, $3);
	}
	| simple_expression {
		$$ = new Expression();
		$$ -> mLineno = yylineno;
		$$ -> mSimpleExpression = $1;
		$$ -> mRelOp = nullptr;
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
		$$ -> mLineno = yylineno;
		$$ -> mInt = $1;
		$$ -> mFactorType = FACTOR_VALUE_INT;
	}
	| SNUMBER {
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mReal = $1;
		$$ -> mFactorType = FACTOR_VALUE_REAL;
	}
	| LETTER {
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mChar = $1;
		$$ -> mFactorType = FACTOR_VALUE_CHAR;
	}
	| BOOL {
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mBool = $1;
		$$ -> mFactorType = FACTOR_VALUE_BOOL;
	}
	| variable {
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mVariable = $1;
		$$ -> mFunction_Call = nullptr;
		$$ -> mExpression = nullptr;
		$$ -> mNot = nullptr;
		$$ -> mUminus = nullptr;
		$$ -> mFactorType = FACTOR_VAR;
	}
	| IDENTIFIER '(' expression_list ')' {
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mVariable = nullptr;
		Id* tmp = new Id();
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ -> mFunction_Call = new FunctionCall($3 -> mExpressionVector.size(), yylineno, tmp, $3);
		$$ -> mExpression = nullptr;
		$$ -> mNot = nullptr;
		$$ -> mUminus = nullptr;
		$$ -> mFactorType = FACTOR_FUNCCALL;
	}
	| IDENTIFIER '(' ')'{
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mVariable = nullptr;
		Id* tmp = new Id();
		tmp -> mName = *($1);
		tmp -> mLineno = yylineno;
		$$ -> mFunction_Call = new FunctionCall(0, yylineno, tmp, nullptr);
		$$ -> mExpression = nullptr;
		$$ -> mNot = nullptr;
		$$ -> mUminus = nullptr;
		$$ -> mFactorType = FACTOR_FUNCCALL;
	}
	| '(' expression ')' {
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mVariable = nullptr;
		$$ -> mFunction_Call = nullptr;
		$$ -> mExpression = $2;
		$$ -> mNot = nullptr;
		$$ -> mUminus = nullptr;
		$$ -> mFactorType = FACTOR_BRACKETS;
	}
	| NOT factor {
		$$ = new Factor();
		$$ -> mLineno = yylineno;
		$$ -> mVariable = nullptr;
		$$ -> mFunction_Call = nullptr;
		$$ -> mExpression = nullptr;
		$$ -> mNot = new Not();
		$$ -> mNot -> mFactor = $2;
		$$ -> mNot -> mLineno = yylineno;
		$$ -> mUminus = nullptr;
		$$ -> mFactorType = FACTOR_NOT;
	}
	;
%%


int lexical_and_syntax_analyse() {
	int ans = yyparse();
	if(errorNum)
		cout<< "The number of syntax error is: "<< errorNum <<endl;
    if(ans || errorNum !=0 )
    	return 1;
    else
    	return 0;
}


extern void yyerror(const char* s) {
	printf("line %d: '%s'\n", yylineno, s);
	errorNum++;
}