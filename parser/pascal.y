%{
	#include <iostream>
	using namespace std;

	typedef pair<Id*, ConstVariable*> const_pair;

	extern int yyline;
	Program* ROOT;			// 语法树根节点

	int error_num = 0;
%}

%token AND ARRAY BEGIN_ BOOLEAN CASE CHAR CONST DIV DO DOWNTO ELSE END FOR FUNCTION IF INTEGER MOD 
%token NOT OF OR PROCEDURE PROGRAM REAL RECORD REPEAT THEN TO TYPE UNTIL VAR WHILE
%token SUBBOUNDARY ASSIGNOP LE_OP GE_OP EQ_OP NE_OP
%token '=' '<' '>' ',' ':' ';' '.' '(' ')' '[' ']' '{' '}' '*' '/' '-' '+'

%left else_conflict
%left ELSE

%union {
	int _int;
	float _float;
	char _char;
 	bool _bool;
	std::string* _str;
	Program* program;
	ProgramHead* programHead;
	ProgramBody* programBody;
	Id* id;
	IdentifierList* identifierList;
	ConstDeclarations* constDeclarations;
	ConstDeclaration* constDeclaration;
	VarDeclarations* varDeclarations;
	SubProgramDeclarations* subProgramDeclarations;
	CompoundStatement* compoundStatement;
}

%token <m_int> DIGITS
%token <m_float> NUMBER
%token <m_str> IDENTIFIER
%token <m_char> LETTER;
%token <m_bool> BOOL;

%type <program> programstruct
%type <programBody> program_body
%type <identifierList> identifier_list
%type <constDeclarations> const_declarations
%type <constDeclaration> const_declaration
%type <const_Value> const_variable
%type <varDeclarations> var_declarations
%type <subProgramDeclarations> subprogram_declarations
%type <compoundStatement> compound_statement

%%

programstruct:
	PROGRAM IDENTIFIER '(' identifier_list ')' ';' program_body '.' {
		Id* tmp= new Id();
		tmp -> mType = TYPE_ID;
		tmp -> mName = *($2);
		$$ = new Program(tmp, $4, $7);
		ROOT = $$;
	}
	| PROGRAM IDENTIFIER ';' program_body '.' {
		Id* tmp= new Id();
		tmp -> mType = TYPE_ID;
		tmp -> mName = *($2);
		$$ = new Program(tmp, NULL, $4);
		ROOT = $$;
	}
	;

program_body:
	const_declarations var_declarations subprogram_declarations compound_statement {
		$$ = new ProgramBody($1, $2, $3, $4);
	}
	;

identifier_list:
	identifier_list ',' IDENTIFIER {
		$$ = new IdentifierList($1);
		Id* tmp= new Id();
		tmp -> mType = TYPE_ID;
		tmp -> mName = *($3);
		$$ -> mIdList.push_back(id);
	}
	| IDENTIFIER {
		Id* tmp= new Id();
		tmp -> mType = TYPE_ID;
		tmp -> mName = *($1);
		$$ = new IdentifierList();
		$$ -> mIdList.push_back(id);
	}
	;

const_declarations:
	CONST const_declaration ';' {
		$$ = new ConstDeclarations($2);
	}
	| {
		$$ = new ConstDeclarations();
	}
	;

const_declaration:
	const_declaration ';' IDENTIFIER '=' const_variable {
		Id* tmp= new Id();
		tmp -> mType = TYPE_ID;
		tmp -> mName = *($3);

		$1 -> mConstVariables.push_back(const_pair(tmp, $5));
		$$ = new ConstDeclaration($1 -> mConstVariables);
	}
	| IDENTIFIER '=' const_variable {
		Id* tmp = new Id();
		tmp -> mType = TYPE_ID;
		tmp -> m_name = *($1);

		$$ = new ConstDeclaration();
		$$ -> mConstVariables.push_back(const_pair(tmp, $3));
	}
	;
%%

int Parse() {
	int result = yyparse();
	if (errorNum)
		cout<<"The number of syntax errors is: "<< error_num << endl;
    if (result || error_num != 0 )
    	return 1;
    else
    	return 0;
}


extern votmpyyerror(const char* s) {
	cout << "Line: " << yyline << "Error: " << s << endl;
	error_num++;
}