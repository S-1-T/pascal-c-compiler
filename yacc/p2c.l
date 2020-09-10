%{
#include <stdio.h>
#include "p2c.tab.h"
#include <string.h>
extern YYSTYPE yylval;
extern char* yytext;
int yyrowno = 1;
%}

%option yylineno

comments1  \{[^\}]*\}
comments2  \(\*([^\*^\)]*|[\*^\)*]*|[^\**\)]*)*\*\)
comments3  \/\/[^\n]*

space [' ']
digit [0-9]
digits {digit}+
letter [a-zA-Z]
E [E][+-]?{digit}+

id {letter}({letter}|{digit})*
num {digit}+("."{digit}+)?({E})?

character [\']({letter}|{digit}|[' '])[\']

%%
{comments3}     {yyrowno += yyleng;}
{comments2}     {yyrowno += yyleng;}
{comments1}     {yyrowno += yyleng;}


"true"			{ yylval.mBool=true; yyrowno += yyleng;  return BOOL;}
"false"			{ yylval.mBool=false; yyrowno += yyleng;  return BOOL;}
"and"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return AND; }
"array"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ARRAY; }
"begin"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return BEGIN_L; }
"boolean"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return BOOLEAN; }
"case"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return CASE; }
"char"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return CHAR; }
"const"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return CONST; }
"div"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return DIV; }
"do"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return DO; }
"downto"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return DOWNTO; }
"else"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ELSE; }
"end"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return END; }
"for"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return FOR; }
"function"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return FUNCTION; }
"if"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return IF; }
"integer"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return INTEGER; }
"mod"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return MOD; }
"not"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return NOT; }
"of"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return OF; }
"or"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return OR; }
"procedure"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return PROCEDURE; }
"program"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return PROGRAM; }
"real"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return REAL; }
"record"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return RECORD; }
"repeat"		{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return REPEAT; }
"then"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return THEN; }
"to"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return TO; }
"type"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return TYPE; }
"until"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return UNTIL; }
"var"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return VAR; }
"while"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return WHILE; }

{space}         { yyrowno += 1; }
{character}     { yylval.mChar = yytext[1]; yyrowno += yyleng;  return LETTER; }
{id}            { yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return IDENTIFIER; }
{digits}        { yylval.mInt = atoi(yytext); yyrowno += yyleng;  return DIGITS; }
{num}           { yylval.mFloat = atof(yytext); yyrowno += yyleng;  return NUMBER; }
".."			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return SUBBOUNDARY; }
":="            { yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ASSIGNOP; }


"<="			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return LE_OP; }
">="			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return GE_OP; }
"<>"			{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return NE_OP; }
"="				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '='; }
"<"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '<'; }
">"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '>'; }

","				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ','; }
":"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ':'; }
";"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ';'; }
"."				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '.'; }
"("				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '('; }
")"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ')'; }
"["				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '['; }
"]"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return ']'; }
"{"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '{'; }
"}"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '}'; }

"*"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '*'; }
"/"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '/'; }
"-"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '-'; }
"+"				{ yylval.mStr = new std::string(yytext); yyrowno += yyleng;  return '+'; }


[\r]			{}
[\n]            { yyrowno = 1; }
[\t]		    { yyrowno += 4; }
.				{ printf("line %d, row %d error: lexical analyse error : %s\n", yylineno, yyrowno, yytext); }
%%
int yywrap(){
    return 1;
}