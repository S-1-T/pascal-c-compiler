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


"true"			{ yylval.m_bool=true; yyrowno += yyleng;  return BOOL;}
"false"			{ yylval.m_bool=false; yyrowno += yyleng;  return BOOL;}
"and"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return AND; }
"array"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ARRAY; }
"begin"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return BEGIN_L; }
"boolean"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return BOOLEAN; }
"case"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return CASE; }
"char"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return CHAR; }
"const"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return CONST; }
"div"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return DIV; }
"do"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return DO; }
"downto"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return DOWNTO; }
"else"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ELSE; }
"end"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return END; }
"for"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return FOR; }
"function"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return FUNCTION; }
"if"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return IF; }
"integer"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return INTEGER; }
"mod"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return MOD; }
"not"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return NOT; }
"of"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return OF; }
"or"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return OR; }
"procedure"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return PROCEDURE; }
"program"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return PROGRAM; }
"real"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return REAL; }
"record"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return RECORD; }
"repeat"		{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return REPEAT; }
"then"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return THEN; }
"to"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return TO; }
"type"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return TYPE; }
"until"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return UNTIL; }
"var"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return VAR; }
"while"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return WHILE; }

{space}         { yyrowno += 1; }
{character}     { yylval.m_char = yytext[1]; yyrowno += yyleng;  return LETTER; }
{id}            { yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return IDENTIFIER; }
{digits}        { yylval.m_int = atoi(yytext); yyrowno += yyleng;  return DIGITS; }
{num}           { yylval.m_float = atof(yytext); yyrowno += yyleng;  return NUMBER; }
".."			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return SUBBOUNDARY; }
":="            { yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ASSIGNOP; }


"<="			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return LE_OP; }
">="			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return GE_OP; }
"<>"			{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return NE_OP; }
"="				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '='; }
"<"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '<'; }
">"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '>'; }

","				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ','; }
":"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ':'; }
";"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ';'; }
"."				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '.'; }
"("				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '('; }
")"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ')'; }
"["				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '['; }
"]"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return ']'; }
"{"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '{'; }
"}"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '}'; }

"*"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '*'; }
"/"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '/'; }
"-"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '-'; }
"+"				{ yylval.m_str = new std::string(yytext); yyrowno += yyleng;  return '+'; }


[\r]			{}
[\n]            { yyrowno = 1; }
[\t]		    { yyrowno += 4; }
.				{ printf("row: %d, line: %d-%d error: lexical analyse error : %s \n", yylineno, yyrowno - yyleng + 1, yyrowno, yytext); }
%%
int yywrap(){
    return 1;
}