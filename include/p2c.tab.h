/* A Bison parser, made by GNU Bison 3.7.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_P2C_TAB_H_INCLUDED
#define YY_YY_P2C_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "yacc/p2c.y"

#include "const.h"
#include "syntax_tree.h"

#line 54 "p2c.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
#define YYTOKENTYPE
enum yytokentype
{
  YYEMPTY = -2,
  YYEOF = 0,           /* "end of file"  */
  YYerror = 256,       /* error  */
  YYUNDEF = 257,       /* "invalid token"  */
  AND = 258,           /* AND  */
  ARRAY = 259,         /* ARRAY  */
  BEGIN_L = 260,       /* BEGIN_L  */
  BOOLEAN = 261,       /* BOOLEAN  */
  CASE = 262,          /* CASE  */
  CHAR = 263,          /* CHAR  */
  CONST = 264,         /* CONST  */
  DIV = 265,           /* DIV  */
  DO = 266,            /* DO  */
  DOWNTO = 267,        /* DOWNTO  */
  ELSE = 268,          /* ELSE  */
  END = 269,           /* END  */
  FOR = 270,           /* FOR  */
  FUNCTION = 271,      /* FUNCTION  */
  IF = 272,            /* IF  */
  INTEGER = 273,       /* INTEGER  */
  MOD = 274,           /* MOD  */
  NOT = 275,           /* NOT  */
  OF = 276,            /* OF  */
  OR = 277,            /* OR  */
  PROCEDURE = 278,     /* PROCEDURE  */
  PROGRAM = 279,       /* PROGRAM  */
  REAL = 280,          /* REAL  */
  RECORD = 281,        /* RECORD  */
  REPEAT = 282,        /* REPEAT  */
  THEN = 283,          /* THEN  */
  TO = 284,            /* TO  */
  TYPE = 285,          /* TYPE  */
  UNTIL = 286,         /* UNTIL  */
  VAR = 287,           /* VAR  */
  WHILE = 288,         /* WHILE  */
  SUBBOUNDARY = 289,   /* SUBBOUNDARY  */
  ASSIGNOP = 290,      /* ASSIGNOP  */
  LE_OP = 291,         /* LE_OP  */
  GE_OP = 292,         /* GE_OP  */
  EQ_OP = 293,         /* EQ_OP  */
  NE_OP = 294,         /* NE_OP  */
  else_conflict = 295, /* else_conflict  */
  DIGITS = 296,        /* DIGITS  */
  NUMBER = 297,        /* NUMBER  */
  IDENTIFIER = 298,    /* IDENTIFIER  */
  LETTER = 299,        /* LETTER  */
  BOOL = 300           /* BOOL  */
};
typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "yacc/p2c.y"

  Program *program;
  ProgramBody *programBody;
  ConstDeclarations *constDeclarations;
  VarDeclarations *varDeclarations;
  SubProgramDeclarations *subProgramDeclarations;
  StatementList *statementList;
  Common *common;
  Procedure *procedure;
  Function *function;
  Statement *statement;
  ParameterList *parameterList;
  Variable *variable;
  ProcedureCall *procedureCall;
  FunctionCall *functionCall;
  Expression *expression;
  SimpleExpression *simpleExpression;
  Term *term;
  Factor *factor;
  Not *NOt;
  Uminus *uminus;
  Type *type;
  ConstValue *constValue;
  AssignOp *assignOp;
  IfThenElse *ifThenElse;
  For *FOr;
  Parameter *parameter;
  RelOp *relOp;
  AddOp *addOp;
  MulOp *mulOp;
  Id *id;
  IdList *idList;
  Period *period;
  ExpressionList *expressionList;
  ProgramHead *programHead;
  CompoundStatement *compoundStatement;
  ConstDeclaration *constDeclaration;
  VarDeclaration *varDeclaration;
  SubProgramDeclaration *subProgramDeclaration;
  Subprogram *subprogram;
  SubprogramHead *subprogramHead;
  SubprogramBody *subprogramBody;
  FormalParameter *formalParameter;
  VarParameter *varParameter;
  ValueParameter *valueParameter;
  IdVarPart *idVarPart;
  int m_int;
  float m_float;
  std::string *m_str;
  char m_char;
  bool m_bool;

#line 169 "p2c.tab.h"
};
typedef union YYSTYPE YYSTYPE;
#define YYSTYPE_IS_TRIVIAL 1
#define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

int yyparse(void);

int lexical_and_syntax_analyse();

#endif /* !YY_YY_P2C_TAB_H_INCLUDED  */
