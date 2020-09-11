/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 6 ".\\yacc\\p2c.y"

	#include "yacc/lex.yy.c"

	#include <cstdio>
	#include <string>
	#include <iostream>

	typedef pair<Id*, ConstValue*> p_Const;
	typedef pair<IdList*, Type*> p_Var;
	typedef pair<int, int> p_Per;

	Program* root;					// AST 根节点
	int errorNum = 0;				// 错误数量

	int yyparse();				    // 语法分析接口
	void yyerror(const char* s);	// 输出错误信息
	extern int yylineno;			// 行号信息

	#define YYERROR_VERBOSE 1		// 输出详细的错误信息

	using namespace std;

#line 91 "p2c.tab.c"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc/p2c.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_AND = 3,                        /* AND  */
  YYSYMBOL_ARRAY = 4,                      /* ARRAY  */
  YYSYMBOL_BEGIN_L = 5,                    /* BEGIN_L  */
  YYSYMBOL_BOOLEAN = 6,                    /* BOOLEAN  */
  YYSYMBOL_CASE = 7,                       /* CASE  */
  YYSYMBOL_CHAR = 8,                       /* CHAR  */
  YYSYMBOL_CONST = 9,                      /* CONST  */
  YYSYMBOL_DIV = 10,                       /* DIV  */
  YYSYMBOL_DO = 11,                        /* DO  */
  YYSYMBOL_DOWNTO = 12,                    /* DOWNTO  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_END = 14,                       /* END  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_FUNCTION = 16,                  /* FUNCTION  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_INTEGER = 18,                   /* INTEGER  */
  YYSYMBOL_MOD = 19,                       /* MOD  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_OF = 21,                        /* OF  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_PROCEDURE = 23,                 /* PROCEDURE  */
  YYSYMBOL_PROGRAM = 24,                   /* PROGRAM  */
  YYSYMBOL_REAL = 25,                      /* REAL  */
  YYSYMBOL_RECORD = 26,                    /* RECORD  */
  YYSYMBOL_REPEAT = 27,                    /* REPEAT  */
  YYSYMBOL_THEN = 28,                      /* THEN  */
  YYSYMBOL_TO = 29,                        /* TO  */
  YYSYMBOL_TYPE = 30,                      /* TYPE  */
  YYSYMBOL_UNTIL = 31,                     /* UNTIL  */
  YYSYMBOL_VAR = 32,                       /* VAR  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_SUBBOUNDARY = 34,               /* SUBBOUNDARY  */
  YYSYMBOL_ASSIGNOP = 35,                  /* ASSIGNOP  */
  YYSYMBOL_LE_OP = 36,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 37,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 38,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 39,                     /* NE_OP  */
  YYSYMBOL_40_ = 40,                       /* '='  */
  YYSYMBOL_41_ = 41,                       /* '<'  */
  YYSYMBOL_42_ = 42,                       /* '>'  */
  YYSYMBOL_43_ = 43,                       /* ','  */
  YYSYMBOL_44_ = 44,                       /* ':'  */
  YYSYMBOL_45_ = 45,                       /* ';'  */
  YYSYMBOL_46_ = 46,                       /* '.'  */
  YYSYMBOL_47_ = 47,                       /* '('  */
  YYSYMBOL_48_ = 48,                       /* ')'  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* '{'  */
  YYSYMBOL_52_ = 52,                       /* '}'  */
  YYSYMBOL_53_ = 53,                       /* '*'  */
  YYSYMBOL_54_ = 54,                       /* '/'  */
  YYSYMBOL_55_ = 55,                       /* '-'  */
  YYSYMBOL_56_ = 56,                       /* '+'  */
  YYSYMBOL_else_conflict = 57,             /* else_conflict  */
  YYSYMBOL_DIGITS = 58,                    /* DIGITS  */
  YYSYMBOL_NUMBER = 59,                    /* NUMBER  */
  YYSYMBOL_IDENTIFIER = 60,                /* IDENTIFIER  */
  YYSYMBOL_LETTER = 61,                    /* LETTER  */
  YYSYMBOL_BOOL = 62,                      /* BOOL  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_program = 64,                   /* program  */
  YYSYMBOL_programhead = 65,               /* programhead  */
  YYSYMBOL_programbody = 66,               /* programbody  */
  YYSYMBOL_identifier_list = 67,           /* identifier_list  */
  YYSYMBOL_const_declarations = 68,        /* const_declarations  */
  YYSYMBOL_const_declaration = 69,         /* const_declaration  */
  YYSYMBOL_const_variable = 70,            /* const_variable  */
  YYSYMBOL_var_declarations = 71,          /* var_declarations  */
  YYSYMBOL_var_declaration = 72,           /* var_declaration  */
  YYSYMBOL_type = 73,                      /* type  */
  YYSYMBOL_standard_type = 74,             /* standard_type  */
  YYSYMBOL_period = 75,                    /* period  */
  YYSYMBOL_SDIGITS = 76,                   /* SDIGITS  */
  YYSYMBOL_subprogramdeclarations = 77,    /* subprogramdeclarations  */
  YYSYMBOL_subprogram = 78,                /* subprogram  */
  YYSYMBOL_subprogramhead = 79,            /* subprogramhead  */
  YYSYMBOL_formal_parameter = 80,          /* formal_parameter  */
  YYSYMBOL_parameter_list = 81,            /* parameter_list  */
  YYSYMBOL_parameter = 82,                 /* parameter  */
  YYSYMBOL_var_parameter = 83,             /* var_parameter  */
  YYSYMBOL_value_parameter = 84,           /* value_parameter  */
  YYSYMBOL_subprogrambody = 85,            /* subprogrambody  */
  YYSYMBOL_compound_statement = 86,        /* compound_statement  */
  YYSYMBOL_statement_list = 87,            /* statement_list  */
  YYSYMBOL_statement = 88,                 /* statement  */
  YYSYMBOL_variable = 89,                  /* variable  */
  YYSYMBOL_IdVarPart = 90,                 /* IdVarPart  */
  YYSYMBOL_call_procedure_statement = 91,  /* call_procedure_statement  */
  YYSYMBOL_else_part = 92,                 /* else_part  */
  YYSYMBOL_expression_list = 93,           /* expression_list  */
  YYSYMBOL_expression = 94,                /* expression  */
  YYSYMBOL_simple_expression = 95,         /* simple_expression  */
  YYSYMBOL_term = 96,                      /* term  */
  YYSYMBOL_SNUMBER = 97,                   /* SNUMBER  */
  YYSYMBOL_factor = 98                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   256

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  219

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      47,    48,    53,    56,    43,    55,    46,    54,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    45,
      41,    40,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,    52,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    57,    58,    59,    60,    61,
      62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   138,   138,   144,   151,   154,   159,   163,   168,   176,
     192,   195,   201,   209,   219,   230,   241,   252,   258,   264,
     270,   276,   282,   288,   294,   302,   305,   312,   316,   323,
     329,   336,   342,   345,   348,   351,   358,   362,   368,   371,
     374,   380,   384,   390,   400,   406,   412,   416,   423,   426,
     432,   436,   444,   449,   456,   462,   468,   471,   476,   482,
     487,   492,   495,   502,   513,   523,   533,   543,   546,   559,
     562,   565,   572,   591,   594,   600,   611,   624,   627,   635,
     639,   646,   652,   658,   664,   670,   676,   682,   691,   694,
     697,   700,   706,   709,   712,   715,   718,   721,   726,   729,
     734,   740,   746,   752,   758,   768,   781,   794,   804
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "AND", "ARRAY",
  "BEGIN_L", "BOOLEAN", "CASE", "CHAR", "CONST", "DIV", "DO", "DOWNTO",
  "ELSE", "END", "FOR", "FUNCTION", "IF", "INTEGER", "MOD", "NOT", "OF",
  "OR", "PROCEDURE", "PROGRAM", "REAL", "RECORD", "REPEAT", "THEN", "TO",
  "TYPE", "UNTIL", "VAR", "WHILE", "SUBBOUNDARY", "ASSIGNOP", "LE_OP",
  "GE_OP", "EQ_OP", "NE_OP", "'='", "'<'", "'>'", "','", "':'", "';'",
  "'.'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'*'", "'/'", "'-'",
  "'+'", "else_conflict", "DIGITS", "NUMBER", "IDENTIFIER", "LETTER",
  "BOOL", "$accept", "program", "programhead", "programbody",
  "identifier_list", "const_declarations", "const_declaration",
  "const_variable", "var_declarations", "var_declaration", "type",
  "standard_type", "period", "SDIGITS", "subprogramdeclarations",
  "subprogram", "subprogramhead", "formal_parameter", "parameter_list",
  "parameter", "var_parameter", "value_parameter", "subprogrambody",
  "compound_statement", "statement_list", "statement", "variable",
  "IdVarPart", "call_procedure_statement", "else_part", "expression_list",
  "expression", "simple_expression", "term", "SNUMBER", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
      61,    60,    62,    44,    58,    59,    46,    40,    41,    91,
      93,   123,   125,    42,    47,    45,    43,   295,   296,   297,
     298,   299,   300
};
#endif

#define YYPACT_NINF (-150)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-75)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,  -150,     6,    30,   196,  -150,    -8,  -150,    49,    19,
      36,    67,    54,    67,    92,    93,  -150,    54,  -150,  -150,
      11,  -150,   162,    74,   159,   107,   103,    95,   127,   103,
     120,   140,  -150,  -150,  -150,  -150,  -150,  -150,   143,   152,
      54,    18,    17,    21,   144,    20,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,   162,  -150,   155,  -150,
    -150,  -150,  -150,  -150,  -150,   163,  -150,    25,    14,    78,
    -150,    -3,  -150,   157,  -150,   166,   161,   171,   161,  -150,
      49,    67,  -150,  -150,   113,   152,   186,   190,   198,   126,
     126,   105,   169,  -150,  -150,   -35,  -150,  -150,  -150,  -150,
     207,   154,   112,  -150,  -150,   126,   126,  -150,  -150,    50,
     126,  -150,   -22,   192,  -150,   193,    67,   232,   181,    10,
     206,  -150,   126,   126,    31,  -150,   194,  -150,  -150,  -150,
      89,    31,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,    75,  -150,   111,  -150,
    -150,  -150,    54,   170,   -17,  -150,  -150,  -150,    99,  -150,
     232,  -150,   113,   220,   113,   233,   214,   234,  -150,  -150,
     119,   234,   112,    -6,    -6,    -6,    -6,    -6,    -6,   112,
     112,  -150,  -150,  -150,  -150,  -150,   126,  -150,  -150,  -150,
      99,   -22,  -150,   200,  -150,   212,    99,  -150,    31,    42,
      31,  -150,  -150,  -150,  -150,  -150,  -150,  -150,   113,  -150,
    -150,   237,   238,  -150,  -150,    31,    31,  -150,  -150
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     0,     0,     0,     4,     0,     1,    11,     0,
       0,    26,     0,    26,     0,     0,     2,     0,    42,     9,
       0,    42,     0,    10,     0,     0,     0,     0,     0,     0,
       0,     0,    22,    19,    16,    23,    24,    13,     0,     0,
      25,     0,     0,     0,     0,     0,     6,     8,     3,     7,
      21,    18,    15,    20,    17,    14,     0,    31,     0,    34,
      35,    32,    33,    28,    29,     0,    62,     0,     0,    75,
      65,     0,    60,     0,    64,     0,    49,     0,    49,    41,
      11,    26,    43,    12,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    98,    74,   102,   103,   100,   104,
       0,    87,    88,   101,    97,     0,     0,    72,    58,     0,
       0,    46,     0,     0,    47,     0,    26,     0,     0,     0,
       0,    27,     0,     0,    71,   108,     0,    40,    99,    39,
       0,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    80,     0,    61,
      59,    63,     0,     0,     0,    51,    52,    53,     0,    45,
       0,    56,     0,     0,     0,     0,     0,    78,   107,   106,
       0,    78,    91,    84,    85,    83,    86,    82,    81,    90,
      89,    94,    95,    96,    92,    93,     0,    76,    73,    54,
       0,     0,    48,     0,    57,     0,     0,    37,    71,     0,
      71,    67,   105,    66,    79,    55,    50,    44,     0,    30,
      69,     0,     0,    77,    36,    71,    71,    70,    68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -150,  -150,  -150,  -150,    76,     0,  -150,   195,   -10,  -150,
     165,  -149,  -150,   -78,   231,  -150,  -150,   175,  -150,    63,
    -150,   104,  -150,   -25,  -150,  -104,   -41,  -150,  -150,    84,
     -93,   -66,    96,   -11,  -150,    -2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    10,   153,    11,    15,    37,    18,    25,
      63,    64,   119,    98,    26,    44,    45,   113,   154,   155,
     156,   157,    82,    70,    71,    72,    99,   107,    74,   201,
     146,   147,   101,   102,   103,   104
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,    46,   100,    21,    49,   150,   120,     5,    13,   193,
     152,   108,   130,   148,   106,    88,   132,     1,    75,    66,
     167,    80,    77,    41,   126,   -11,    86,   171,   191,     9,
       7,   192,   -71,    67,    89,    68,    41,   170,    19,    12,
       2,   205,   109,   211,   151,    81,    67,   209,    68,   139,
     140,   149,   -11,   162,    27,    41,   165,   166,     9,    28,
     163,    90,    89,   -71,   -71,    67,     6,    68,    73,    91,
      92,   117,    93,    94,    95,    96,    97,    76,    69,    14,
     116,    78,    16,    73,   195,    87,   197,   125,    20,    90,
      73,    69,   161,    24,   210,   -71,   213,    91,    92,    17,
      93,    94,    95,    96,    97,    59,   160,    60,    41,    89,
      69,   217,   218,   -74,    19,   141,    65,    61,   186,    42,
     204,   172,   142,   187,    62,   105,    43,   106,   179,   180,
     214,   143,    22,   212,    38,   194,    90,   169,    23,   181,
     182,   183,   184,   185,    91,    92,    89,    93,    94,    95,
      96,    97,    40,    57,   186,    47,    58,    73,    59,    73,
      60,   188,   186,   127,   128,   144,   145,   202,   118,    92,
      61,    93,    48,    90,    73,    73,   132,    62,    50,    51,
      52,    91,    92,    56,    93,    94,    95,    96,    97,    79,
     133,   134,   110,   135,   136,   137,   138,     8,    53,    54,
      55,   -11,    27,    39,    84,     9,    27,    85,   112,   139,
     140,   111,   -11,    27,   190,   122,   114,    30,    31,   -11,
      32,    33,    34,    35,    36,   123,   124,   129,   -11,   173,
     174,   175,   176,   177,   178,   131,   158,    41,   159,   127,
     164,   196,   168,   199,   198,   207,   208,   200,   215,   216,
     121,    83,    29,   115,   206,   203,   189
};

static const yytype_uint8 yycheck[] =
{
      41,    26,    68,    13,    29,   109,    84,     1,     8,   158,
      32,    14,    47,   106,    49,     1,    22,     1,     1,     1,
     124,     1,     1,     5,    90,     5,     1,   131,    45,     9,
       0,    48,    14,    15,    20,    17,     5,   130,    60,    47,
      24,   190,    45,     1,   110,    45,    15,   196,    17,    55,
      56,     1,    32,    43,    43,     5,   122,   123,     9,    48,
      50,    47,    20,    45,    14,    15,    60,    17,   109,    55,
      56,    81,    58,    59,    60,    61,    62,    60,    60,    60,
      80,    60,    46,   124,   162,    60,   164,    89,    12,    47,
     131,    60,   117,    17,   198,    45,   200,    55,    56,    32,
      58,    59,    60,    61,    62,     6,   116,     8,     5,    20,
      60,   215,   216,    35,    60,     3,    40,    18,    43,    16,
     186,   132,    10,    48,    25,    47,    23,    49,   139,   140,
     208,    19,    40,   199,    60,   160,    47,    48,    45,   141,
     142,   143,   144,   145,    55,    56,    20,    58,    59,    60,
      61,    62,    45,     1,    43,    60,     4,   198,     6,   200,
       8,    50,    43,    58,    59,    53,    54,    48,    55,    56,
      18,    58,    45,    47,   215,   216,    22,    25,    58,    59,
      60,    55,    56,    40,    58,    59,    60,    61,    62,    45,
      36,    37,    35,    39,    40,    41,    42,     1,    58,    59,
      60,     5,    43,    44,    49,     9,    43,    44,    47,    55,
      56,    45,    16,    43,    44,    29,    45,    55,    56,    23,
      58,    59,    60,    61,    62,    35,    28,    58,    32,   133,
     134,   135,   136,   137,   138,    28,    44,     5,    45,    58,
      34,    21,    48,    29,    11,    45,    34,    13,    11,    11,
      85,    56,    21,    78,   191,   171,   152
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    24,    64,    65,     1,    60,     0,     1,     9,
      66,    68,    47,    68,    60,    69,    46,    32,    71,    60,
      67,    71,    40,    45,    67,    72,    77,    43,    48,    77,
      55,    56,    58,    59,    60,    61,    62,    70,    60,    44,
      45,     5,    16,    23,    78,    79,    86,    60,    45,    86,
      58,    59,    60,    58,    59,    60,    40,     1,     4,     6,
       8,    18,    25,    73,    74,    67,     1,    15,    17,    60,
      86,    87,    88,    89,    91,     1,    60,     1,    60,    45,
       1,    68,    85,    70,    49,    44,     1,    60,     1,    20,
      47,    55,    56,    58,    59,    60,    61,    62,    76,    89,
      94,    95,    96,    97,    98,    47,    49,    90,    14,    45,
      35,    45,    47,    80,    45,    80,    68,    71,    55,    75,
      76,    73,    29,    35,    28,    98,    94,    58,    59,    58,
      47,    28,    22,    36,    37,    39,    40,    41,    42,    55,
      56,     3,    10,    19,    53,    54,    93,    94,    93,     1,
      88,    94,    32,    67,    81,    82,    83,    84,    44,    45,
      71,    86,    43,    50,    34,    94,    94,    88,    48,    48,
      93,    88,    96,    95,    95,    95,    95,    95,    95,    96,
      96,    98,    98,    98,    98,    98,    43,    48,    50,    84,
      44,    45,    48,    74,    86,    76,    21,    76,    11,    29,
      13,    92,    48,    92,    94,    74,    82,    45,    34,    74,
      88,     1,    94,    88,    76,    11,    11,    88,    88
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    65,    65,    65,    66,    66,    67,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    73,
      73,    73,    74,    74,    74,    74,    75,    75,    76,    76,
      76,    77,    77,    78,    79,    79,    79,    79,    80,    80,
      81,    81,    82,    82,    83,    84,    85,    85,    86,    87,
      87,    87,    87,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     6,     2,     1,     4,     5,     3,     1,
       3,     0,     5,     3,     2,     2,     1,     2,     2,     1,
       2,     2,     1,     1,     1,     3,     0,     5,     3,     1,
       6,     1,     1,     1,     1,     1,     5,     3,     1,     2,
       2,     3,     0,     2,     6,     4,     3,     3,     3,     0,
       3,     1,     1,     1,     2,     3,     3,     4,     3,     3,
       1,     3,     1,     3,     1,     1,     5,     5,     8,     6,
       8,     0,     2,     3,     0,     1,     4,     2,     0,     3,
       1,     3,     3,     3,     3,     3,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     2,
       1,     1,     1,     1,     1,     4,     3,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: programhead programbody '.'  */
#line 138 ".\\yacc\\p2c.y"
                                        {
		(yyval.program) = new Program((yyvsp[-2].programHead)->mId, (yyvsp[-2].programHead)->mIdList, (yyvsp[-1].programBody));
		root = (yyval.program);
	}
#line 1338 "p2c.tab.c"
    break;

  case 3: /* programhead: PROGRAM IDENTIFIER '(' identifier_list ')' ';'  */
#line 144 ".\\yacc\\p2c.y"
                                                         {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-4].mStr));
		tmp -> mLineno = yylineno;
		tmp -> mIdType = TYPE_ID;
		(yyval.programHead) = new ProgramHead(tmp, (yyvsp[-2].idList));
	}
#line 1350 "p2c.tab.c"
    break;

  case 4: /* programhead: PROGRAM error  */
#line 151 ".\\yacc\\p2c.y"
                        {
		(yyval.programHead) = new ProgramHead(nullptr,nullptr);
	}
#line 1358 "p2c.tab.c"
    break;

  case 5: /* programhead: error  */
#line 154 ".\\yacc\\p2c.y"
                {
		(yyval.programHead) = new ProgramHead(nullptr,nullptr);
	}
#line 1366 "p2c.tab.c"
    break;

  case 6: /* programbody: const_declarations var_declarations subprogramdeclarations compound_statement  */
#line 159 ".\\yacc\\p2c.y"
                                                                                        {
		(yyval.programBody) = new ProgramBody((yyvsp[-3].constDeclarations), (yyvsp[-2].varDeclarations), (yyvsp[-1].subProgramDeclarations), (yyvsp[0].compoundStatement));
	}
#line 1374 "p2c.tab.c"
    break;

  case 7: /* programbody: error const_declarations var_declarations subprogramdeclarations compound_statement  */
#line 163 ".\\yacc\\p2c.y"
                                                                                             {
		(yyval.programBody) = new ProgramBody();
	}
#line 1382 "p2c.tab.c"
    break;

  case 8: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 168 ".\\yacc\\p2c.y"
                                         {
		(yyval.idList) = new IdList();
		(yyval.idList) = (yyvsp[-2].idList);
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[0].mStr));
		tmp -> mLineno = yylineno;
		(yyval.idList) -> mIdVector.push_back(tmp);
	}
#line 1395 "p2c.tab.c"
    break;

  case 9: /* identifier_list: IDENTIFIER  */
#line 176 ".\\yacc\\p2c.y"
                     {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[0].mStr));
		tmp -> mLineno = yylineno;
		(yyval.idList) = new IdList();
		(yyval.idList) -> mIdVector.push_back(tmp);
		(yyval.idList) -> mLineno = yylineno;
	}
#line 1408 "p2c.tab.c"
    break;

  case 10: /* const_declarations: CONST const_declaration ';'  */
#line 192 ".\\yacc\\p2c.y"
                                      {
		(yyval.constDeclarations) = new ConstDeclarations((yyvsp[-1].constDeclaration) -> mConstVector);
	}
#line 1416 "p2c.tab.c"
    break;

  case 11: /* const_declarations: %empty  */
#line 195 ".\\yacc\\p2c.y"
          {
		(yyval.constDeclarations) = new ConstDeclarations();
	}
#line 1424 "p2c.tab.c"
    break;

  case 12: /* const_declaration: const_declaration ';' IDENTIFIER '=' const_variable  */
#line 201 ".\\yacc\\p2c.y"
                                                              {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-2].mStr));
		tmp -> mLineno = yylineno;

		(yyvsp[-4].constDeclaration) -> mConstVector.push_back(p_Const(tmp, (yyvsp[0].constValue)));
		(yyval.constDeclaration) = new ConstDeclaration((yyvsp[-4].constDeclaration) -> mConstVector);
	}
#line 1437 "p2c.tab.c"
    break;

  case 13: /* const_declaration: IDENTIFIER '=' const_variable  */
#line 209 ".\\yacc\\p2c.y"
                                        {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-2].mStr));
		tmp -> mLineno = yylineno;
		(yyval.constDeclaration) = new ConstDeclaration();
		(yyval.constDeclaration) -> mConstVector.push_back(p_Const(tmp,(yyvsp[0].constValue)));
	}
#line 1449 "p2c.tab.c"
    break;

  case 14: /* const_variable: '+' IDENTIFIER  */
#line 219 ".\\yacc\\p2c.y"
                         {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mLineno = yylineno;
		(yyval.constValue) -> mPolarity = CONST_POSITIVE;
		(yyval.constValue) -> mValueType = TYPE_ID;
		(yyval.constValue) -> misId = true;
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[0].mStr));
		tmp -> mLineno = yylineno;
		(yyval.constValue) -> mId = tmp;
	}
#line 1465 "p2c.tab.c"
    break;

  case 15: /* const_variable: '-' IDENTIFIER  */
#line 230 ".\\yacc\\p2c.y"
                         {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mLineno = yylineno;
		(yyval.constValue) -> mPolarity = CONST_NEGATIVE;
		(yyval.constValue) -> mValueType = TYPE_ID;
		(yyval.constValue) -> misId = true;
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[0].mStr));
		tmp -> mLineno = yylineno;
		(yyval.constValue) -> mId = tmp;
	}
#line 1481 "p2c.tab.c"
    break;

  case 16: /* const_variable: IDENTIFIER  */
#line 241 ".\\yacc\\p2c.y"
                     {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mLineno = yylineno;
		(yyval.constValue) -> mPolarity = CONST_POSITIVE;
		(yyval.constValue) -> mValueType = TYPE_ID;
		(yyval.constValue) -> misId = true;
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[0].mStr));
		tmp -> mLineno = yylineno;
		(yyval.constValue) -> mId = tmp;
	}
#line 1497 "p2c.tab.c"
    break;

  case 17: /* const_variable: '+' NUMBER  */
#line 252 ".\\yacc\\p2c.y"
                     {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_POSITIVE;
		(yyval.constValue) -> mValueType = TYPE_REAL;
		(yyval.constValue) -> mReal = (yyvsp[0].mFloat);
	}
#line 1508 "p2c.tab.c"
    break;

  case 18: /* const_variable: '-' NUMBER  */
#line 258 ".\\yacc\\p2c.y"
                     {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_NEGATIVE;
		(yyval.constValue) -> mValueType = TYPE_REAL;
		(yyval.constValue) -> mReal = (yyvsp[0].mFloat);
	}
#line 1519 "p2c.tab.c"
    break;

  case 19: /* const_variable: NUMBER  */
#line 264 ".\\yacc\\p2c.y"
                 {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_POSITIVE;
		(yyval.constValue) -> mValueType = TYPE_REAL;
		(yyval.constValue) -> mReal = (yyvsp[0].mFloat);
	}
#line 1530 "p2c.tab.c"
    break;

  case 20: /* const_variable: '+' DIGITS  */
#line 270 ".\\yacc\\p2c.y"
                     {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_POSITIVE;
		(yyval.constValue) -> mValueType = TYPE_INTEGER;
		(yyval.constValue) -> mInt = (yyvsp[0].mInt);
	}
#line 1541 "p2c.tab.c"
    break;

  case 21: /* const_variable: '-' DIGITS  */
#line 276 ".\\yacc\\p2c.y"
                     {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_NEGATIVE;
		(yyval.constValue) -> mValueType = TYPE_INTEGER;
		(yyval.constValue) -> mInt = (yyvsp[0].mInt);
	}
#line 1552 "p2c.tab.c"
    break;

  case 22: /* const_variable: DIGITS  */
#line 282 ".\\yacc\\p2c.y"
                 {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_POSITIVE;
		(yyval.constValue) -> mValueType = TYPE_INTEGER;
		(yyval.constValue) -> mInt = (yyvsp[0].mInt);
	}
#line 1563 "p2c.tab.c"
    break;

  case 23: /* const_variable: LETTER  */
#line 288 ".\\yacc\\p2c.y"
                 {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_NULL;
		(yyval.constValue) -> mValueType = TYPE_CHAR;
		(yyval.constValue) -> mChar = (yyvsp[0].mChar);
	}
#line 1574 "p2c.tab.c"
    break;

  case 24: /* const_variable: BOOL  */
#line 294 ".\\yacc\\p2c.y"
               {
		(yyval.constValue) = new ConstValue();
		(yyval.constValue) -> mPolarity = CONST_NULL;
		(yyval.constValue) -> mValueType = TYPE_BOOLEAN;
		(yyval.constValue) -> mBool = (yyvsp[0].mBool);
	}
#line 1585 "p2c.tab.c"
    break;

  case 25: /* var_declarations: VAR var_declaration ';'  */
#line 302 ".\\yacc\\p2c.y"
                                  {
		(yyval.varDeclarations) = new VarDeclarations((yyvsp[-1].varDeclaration) -> mVariableVector);
	}
#line 1593 "p2c.tab.c"
    break;

  case 26: /* var_declarations: %empty  */
#line 305 ".\\yacc\\p2c.y"
          {
		vector<p_Var> tmp;
		(yyval.varDeclarations) = new VarDeclarations(tmp);
	}
#line 1602 "p2c.tab.c"
    break;

  case 27: /* var_declaration: var_declaration ';' identifier_list ':' type  */
#line 312 ".\\yacc\\p2c.y"
                                                       {
		(yyval.varDeclaration) = new VarDeclaration((yyvsp[-4].varDeclaration) -> mVariableVector);
		(yyval.varDeclaration) -> mVariableVector.push_back(p_Var((yyvsp[-2].idList), (yyvsp[0].type)));
	}
#line 1611 "p2c.tab.c"
    break;

  case 28: /* var_declaration: identifier_list ':' type  */
#line 316 ".\\yacc\\p2c.y"
                                   {
		(yyval.varDeclaration) = new VarDeclaration();
		(yyval.varDeclaration) -> mVariableVector.push_back(p_Var((yyvsp[-2].idList), (yyvsp[0].type)));
	}
#line 1620 "p2c.tab.c"
    break;

  case 29: /* type: standard_type  */
#line 323 ".\\yacc\\p2c.y"
                        {
		(yyval.type) = new Type();
		(yyval.type) -> mSimpleType = (yyvsp[0].mInt);
		(yyval.type) -> misArray = false;
		(yyval.type) -> mLineno = yylineno;
	}
#line 1631 "p2c.tab.c"
    break;

  case 30: /* type: ARRAY '[' period ']' OF standard_type  */
#line 329 ".\\yacc\\p2c.y"
                                                {
		(yyval.type) = new Type();
		(yyval.type) -> mLineno = yylineno;
		(yyval.type) -> misArray = true;
		(yyval.type) -> mPeriod = (yyvsp[-3].period);
		(yyval.type) -> mSimpleType = (yyvsp[0].mInt);
	}
#line 1643 "p2c.tab.c"
    break;

  case 31: /* type: error  */
#line 336 ".\\yacc\\p2c.y"
                {
		(yyval.type) = new Type();
	}
#line 1651 "p2c.tab.c"
    break;

  case 32: /* standard_type: INTEGER  */
#line 342 ".\\yacc\\p2c.y"
                  {
		(yyval.mInt) = TYPE_INTEGER;
	}
#line 1659 "p2c.tab.c"
    break;

  case 33: /* standard_type: REAL  */
#line 345 ".\\yacc\\p2c.y"
               {
		(yyval.mInt) = TYPE_REAL;
	}
#line 1667 "p2c.tab.c"
    break;

  case 34: /* standard_type: BOOLEAN  */
#line 348 ".\\yacc\\p2c.y"
                  {
		(yyval.mInt) = TYPE_BOOLEAN;
	}
#line 1675 "p2c.tab.c"
    break;

  case 35: /* standard_type: CHAR  */
#line 351 ".\\yacc\\p2c.y"
               {
		(yyval.mInt) = TYPE_CHAR;
	}
#line 1683 "p2c.tab.c"
    break;

  case 36: /* period: period ',' SDIGITS SUBBOUNDARY SDIGITS  */
#line 358 ".\\yacc\\p2c.y"
                                                 {
		(yyval.period) = new Period((yyvsp[-4].period) -> mDimsVector);
		(yyval.period) -> mDimsVector.push_back(p_Per((yyvsp[-2].mInt), (yyvsp[0].mInt)));
	}
#line 1692 "p2c.tab.c"
    break;

  case 37: /* period: SDIGITS SUBBOUNDARY SDIGITS  */
#line 362 ".\\yacc\\p2c.y"
                                      {
		(yyval.period) = new Period();
		(yyval.period) -> mDimsVector.push_back(p_Per((yyvsp[-2].mInt), (yyvsp[0].mInt)));
	}
#line 1701 "p2c.tab.c"
    break;

  case 38: /* SDIGITS: DIGITS  */
#line 368 ".\\yacc\\p2c.y"
                {
		(yyval.mInt) = (yyvsp[0].mInt);
	}
#line 1709 "p2c.tab.c"
    break;

  case 39: /* SDIGITS: '+' DIGITS  */
#line 371 ".\\yacc\\p2c.y"
                    {
		(yyval.mInt) = (yyvsp[0].mInt);
	}
#line 1717 "p2c.tab.c"
    break;

  case 40: /* SDIGITS: '-' DIGITS  */
#line 374 ".\\yacc\\p2c.y"
                    {
		(yyval.mInt) = -(yyvsp[0].mInt);
	}
#line 1725 "p2c.tab.c"
    break;

  case 41: /* subprogramdeclarations: subprogramdeclarations subprogram ';'  */
#line 380 ".\\yacc\\p2c.y"
                                                {
		(yyval.subProgramDeclarations) = new SubProgramDeclarations((yyvsp[-2].subProgramDeclarations) -> mCommonVector);
		(yyval.subProgramDeclarations) -> mCommonVector.push_back((yyvsp[-1].common));
	}
#line 1734 "p2c.tab.c"
    break;

  case 42: /* subprogramdeclarations: %empty  */
#line 384 ".\\yacc\\p2c.y"
          {
		(yyval.subProgramDeclarations) = new SubProgramDeclarations();
	}
#line 1742 "p2c.tab.c"
    break;

  case 43: /* subprogram: subprogramhead subprogrambody  */
#line 390 ".\\yacc\\p2c.y"
                                        {
		if((yyvsp[-1].subprogramHead) -> mSimpleType == TYPE_NULL) {
			(yyval.common) = new Procedure(yylineno, (yyvsp[-1].subprogramHead) -> mId, (yyvsp[-1].subprogramHead)-> mFormalParameter -> mParameterList, (yyvsp[0].subprogramBody) -> mConstDeclarations, (yyvsp[0].subprogramBody) -> mVarDeclarations, (yyvsp[0].subprogramBody)-> mCompoundStatement -> mStatementList);
		}
		else {
			(yyval.common) = new Function((yyvsp[-1].subprogramHead) -> mSimpleType, yylineno, (yyvsp[-1].subprogramHead) -> mId, (yyvsp[-1].subprogramHead)-> mFormalParameter -> mParameterList, (yyvsp[0].subprogramBody) -> mConstDeclarations, (yyvsp[0].subprogramBody) -> mVarDeclarations, (yyvsp[0].subprogramBody)-> mCompoundStatement -> mStatementList);
		}
	}
#line 1755 "p2c.tab.c"
    break;

  case 44: /* subprogramhead: FUNCTION IDENTIFIER formal_parameter ':' standard_type ';'  */
#line 400 ".\\yacc\\p2c.y"
                                                                     {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-4].mStr));
		tmp -> mLineno = yylineno;
		(yyval.subprogramHead) = new SubprogramHead(tmp, (yyvsp[-3].formalParameter), (yyvsp[-1].mInt));
	}
#line 1766 "p2c.tab.c"
    break;

  case 45: /* subprogramhead: PROCEDURE IDENTIFIER formal_parameter ';'  */
#line 406 ".\\yacc\\p2c.y"
                                                    {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-2].mStr));
		tmp -> mLineno = yylineno;
		(yyval.subprogramHead) = new SubprogramHead(tmp, (yyvsp[-1].formalParameter), TYPE_NULL);
	}
#line 1777 "p2c.tab.c"
    break;

  case 46: /* subprogramhead: FUNCTION error ';'  */
#line 412 ".\\yacc\\p2c.y"
                             {
		Id* tmp = new Id();
		(yyval.subprogramHead) = new SubprogramHead(tmp,new FormalParameter(),TYPE_NULL);
	}
#line 1786 "p2c.tab.c"
    break;

  case 47: /* subprogramhead: PROCEDURE error ';'  */
#line 416 ".\\yacc\\p2c.y"
                             {
		Id* tmp = new Id();
		(yyval.subprogramHead) = new SubprogramHead(tmp,new FormalParameter(),TYPE_NULL);
	}
#line 1795 "p2c.tab.c"
    break;

  case 48: /* formal_parameter: '(' parameter_list ')'  */
#line 423 ".\\yacc\\p2c.y"
                                 {
		(yyval.formalParameter) = new FormalParameter((yyvsp[-1].parameterList));
	}
#line 1803 "p2c.tab.c"
    break;

  case 49: /* formal_parameter: %empty  */
#line 426 ".\\yacc\\p2c.y"
          {
		(yyval.formalParameter) = new FormalParameter(nullptr);
	}
#line 1811 "p2c.tab.c"
    break;

  case 50: /* parameter_list: parameter_list ';' parameter  */
#line 432 ".\\yacc\\p2c.y"
                                       {
		(yyval.parameterList) = new ParameterList(yylineno, (yyvsp[-2].parameterList) -> mParameters);
		(yyval.parameterList) -> mParameters.push_back((yyvsp[0].parameter));
	}
#line 1820 "p2c.tab.c"
    break;

  case 51: /* parameter_list: parameter  */
#line 436 ".\\yacc\\p2c.y"
                    {
		(yyval.parameterList) = new ParameterList();
		(yyval.parameterList) -> mLineno = yylineno;
		(yyval.parameterList) -> mParameters.push_back((yyvsp[0].parameter));
	}
#line 1830 "p2c.tab.c"
    break;

  case 52: /* parameter: var_parameter  */
#line 444 ".\\yacc\\p2c.y"
                        {
		(yyval.parameter) = new Parameter(true, yylineno, (yyvsp[0].varParameter) -> mValueParameter -> mIdList);
		(yyval.parameter) -> mType = (yyvsp[0].varParameter) -> mValueParameter -> mSimpleType;

	}
#line 1840 "p2c.tab.c"
    break;

  case 53: /* parameter: value_parameter  */
#line 449 ".\\yacc\\p2c.y"
                          {
		(yyval.parameter) = new Parameter(false, yylineno, (yyvsp[0].valueParameter) -> mIdList);
		(yyval.parameter) -> mType = (yyvsp[0].valueParameter) -> mSimpleType;
	}
#line 1849 "p2c.tab.c"
    break;

  case 54: /* var_parameter: VAR value_parameter  */
#line 456 ".\\yacc\\p2c.y"
                              {
		(yyval.varParameter) = new VarParameter((yyvsp[0].valueParameter));
	}
#line 1857 "p2c.tab.c"
    break;

  case 55: /* value_parameter: identifier_list ':' standard_type  */
#line 462 ".\\yacc\\p2c.y"
                                            {
		(yyval.valueParameter) = new ValueParameter((yyvsp[-2].idList), (yyvsp[0].mInt));
	}
#line 1865 "p2c.tab.c"
    break;

  case 56: /* subprogrambody: const_declarations var_declarations compound_statement  */
#line 468 ".\\yacc\\p2c.y"
                                                                 {
		(yyval.subprogramBody) = new SubprogramBody((yyvsp[-2].constDeclarations), (yyvsp[-1].varDeclarations), (yyvsp[0].compoundStatement));
	}
#line 1873 "p2c.tab.c"
    break;

  case 57: /* subprogrambody: error const_declarations var_declarations compound_statement  */
#line 471 ".\\yacc\\p2c.y"
                                                                      {
		(yyval.subprogramBody) = new SubprogramBody(nullptr,nullptr,new CompoundStatement());
	}
#line 1881 "p2c.tab.c"
    break;

  case 58: /* compound_statement: BEGIN_L statement_list END  */
#line 476 ".\\yacc\\p2c.y"
                                     {
		(yyval.compoundStatement) = new CompoundStatement((yyvsp[-1].statementList));
	}
#line 1889 "p2c.tab.c"
    break;

  case 59: /* statement_list: statement_list ';' statement  */
#line 482 ".\\yacc\\p2c.y"
                                       {
		(yyval.statementList) = new StatementList((yyvsp[-2].statementList) -> mStatementVector);
		if((yyvsp[0].statement) != nullptr)
			(yyval.statementList) -> mStatementVector.push_back((yyvsp[0].statement));
	}
#line 1899 "p2c.tab.c"
    break;

  case 60: /* statement_list: statement  */
#line 487 ".\\yacc\\p2c.y"
                    {
		(yyval.statementList) = new StatementList();
		if((yyvsp[0].statement) != nullptr)
			(yyval.statementList) -> mStatementVector.push_back((yyvsp[0].statement));
	}
#line 1909 "p2c.tab.c"
    break;

  case 61: /* statement_list: statement_list ';' error  */
#line 492 ".\\yacc\\p2c.y"
                                   {
		(yyval.statementList) = new StatementList();
	}
#line 1917 "p2c.tab.c"
    break;

  case 62: /* statement_list: error  */
#line 495 ".\\yacc\\p2c.y"
                {
		(yyval.statementList) = new StatementList();
	}
#line 1925 "p2c.tab.c"
    break;

  case 63: /* statement: variable ASSIGNOP expression  */
#line 502 ".\\yacc\\p2c.y"
                                       {	//赋值
		(yyval.statement) = new Statement();
		(yyval.statement) -> mStateType = STATEMENT_ASSIGN;
		(yyval.statement) -> mLineno = yylineno;
		(yyval.statement) -> mAssignOp = new AssignOp((yyvsp[-2].variable), (yyvsp[0].expression));
		(yyval.statement) -> mAssignOp -> mLineno = yylineno;
		(yyval.statement) -> mProcedure_call = nullptr;
		(yyval.statement) -> mStatementList = nullptr;
		(yyval.statement) -> mIfThenElse = nullptr;
		(yyval.statement) -> mFor = nullptr;
	}
#line 1941 "p2c.tab.c"
    break;

  case 64: /* statement: call_procedure_statement  */
#line 513 ".\\yacc\\p2c.y"
                                   {	//函数
		(yyval.statement) = new Statement();
		(yyval.statement) -> mStateType = STATEMENT_PROCEDURE;
		(yyval.statement) -> mLineno = yylineno;
		(yyval.statement) -> mProcedure_call = (yyvsp[0].procedureCall);
		(yyval.statement) -> mAssignOp = nullptr;
		(yyval.statement) -> mStatementList = nullptr;
		(yyval.statement) -> mIfThenElse = nullptr;
		(yyval.statement) -> mFor = nullptr;
	}
#line 1956 "p2c.tab.c"
    break;

  case 65: /* statement: compound_statement  */
#line 523 ".\\yacc\\p2c.y"
                             {	//函数内部
		(yyval.statement) = new Statement();
		(yyval.statement) -> mStateType = STATEMENT_COMPOUND;
		(yyval.statement) -> mLineno = yylineno;
		(yyval.statement) -> mStatementList = (yyvsp[0].compoundStatement) -> mStatementList;
		(yyval.statement) -> mAssignOp = nullptr;
		(yyval.statement) -> mProcedure_call = nullptr;
		(yyval.statement) -> mIfThenElse = nullptr;
		(yyval.statement) -> mFor = nullptr;
	}
#line 1971 "p2c.tab.c"
    break;

  case 66: /* statement: IF expression THEN statement else_part  */
#line 533 ".\\yacc\\p2c.y"
                                                 {	//if语句
		(yyval.statement) = new Statement();
		(yyval.statement) -> mStateType = STATEMENT_IF;
		(yyval.statement) -> mLineno = yylineno;
		(yyval.statement) -> mIfThenElse = new IfThenElse((yyvsp[-3].expression), (yyvsp[-1].statement), (yyvsp[0].statement));
		(yyval.statement) -> mAssignOp = nullptr;
		(yyval.statement) -> mProcedure_call = nullptr;
		(yyval.statement) -> mStatementList = nullptr;
		(yyval.statement) -> mFor = nullptr;
	}
#line 1986 "p2c.tab.c"
    break;

  case 67: /* statement: IF error THEN statement else_part  */
#line 543 ".\\yacc\\p2c.y"
                                            {	//expression部分出错
		(yyval.statement) = new Statement();
	}
#line 1994 "p2c.tab.c"
    break;

  case 68: /* statement: FOR IDENTIFIER ASSIGNOP expression TO expression DO statement  */
#line 546 ".\\yacc\\p2c.y"
                                                                        {	//for循环
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-6].mStr));
		tmp -> mLineno = yylineno;
		(yyval.statement) = new Statement();
		(yyval.statement) -> mStateType = STATEMENT_FOR;
		(yyval.statement) -> mLineno = yylineno;
		(yyval.statement) -> mFor = new For(tmp, (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement));
		(yyval.statement) -> mAssignOp = nullptr;
		(yyval.statement) -> mProcedure_call = nullptr;
		(yyval.statement) -> mStatementList = nullptr;
		(yyval.statement) -> mIfThenElse = nullptr;
	}
#line 2012 "p2c.tab.c"
    break;

  case 69: /* statement: FOR error TO expression DO statement  */
#line 559 ".\\yacc\\p2c.y"
                                               {
		(yyval.statement) = new Statement();
	}
#line 2020 "p2c.tab.c"
    break;

  case 70: /* statement: FOR IDENTIFIER ASSIGNOP expression TO error DO statement  */
#line 562 ".\\yacc\\p2c.y"
                                                                   {
		(yyval.statement) = new Statement();
	}
#line 2028 "p2c.tab.c"
    break;

  case 71: /* statement: %empty  */
#line 565 ".\\yacc\\p2c.y"
          {
		(yyval.statement) = nullptr;
	}
#line 2036 "p2c.tab.c"
    break;

  case 72: /* variable: IDENTIFIER IdVarPart  */
#line 572 ".\\yacc\\p2c.y"
                               {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-1].mStr));
		tmp -> mLineno = yylineno;
		(yyval.variable) = new Variable();
		(yyval.variable) -> mId = tmp;
		(yyval.variable) -> mLineno = yylineno;
		if((yyvsp[0].idVarPart) -> mExpressionList != nullptr){
			(yyval.variable) -> misArray = true;
			(yyval.variable) -> mExpressionList = (yyvsp[0].idVarPart) -> mExpressionList;
		}else {
			(yyval.variable) -> misArray =false;
			(yyval.variable) -> mExpressionList = nullptr;
		}
	}
#line 2056 "p2c.tab.c"
    break;

  case 73: /* IdVarPart: '[' expression_list ']'  */
#line 591 ".\\yacc\\p2c.y"
                                  {
		(yyval.idVarPart) = new IdVarPart((yyvsp[-1].expressionList));
	}
#line 2064 "p2c.tab.c"
    break;

  case 74: /* IdVarPart: %empty  */
#line 594 ".\\yacc\\p2c.y"
          {
		(yyval.idVarPart) = new IdVarPart(nullptr);
	}
#line 2072 "p2c.tab.c"
    break;

  case 75: /* call_procedure_statement: IDENTIFIER  */
#line 600 ".\\yacc\\p2c.y"
                     {
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[0].mStr));
		tmp -> mLineno = yylineno;
		(yyval.procedureCall) = new ProcedureCall();
		(yyval.procedureCall) -> mLineno = yylineno;
		(yyval.procedureCall) -> mExpressionsNum = 0;
		(yyval.procedureCall) -> mId = tmp;
		(yyval.procedureCall) -> mExpressionList = nullptr;

	}
#line 2088 "p2c.tab.c"
    break;

  case 76: /* call_procedure_statement: IDENTIFIER '(' expression_list ')'  */
#line 611 ".\\yacc\\p2c.y"
                                             {
		(yyval.procedureCall) = new ProcedureCall();
		(yyval.procedureCall) -> mLineno = yylineno;
		(yyval.procedureCall) -> mExpressionsNum = (yyvsp[-1].expressionList) -> mExpressionVector.size();
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-3].mStr));
		tmp -> mLineno = yylineno;
		(yyval.procedureCall) -> mId = tmp;
		(yyval.procedureCall) -> mExpressionList = (yyvsp[-1].expressionList);
	}
#line 2103 "p2c.tab.c"
    break;

  case 77: /* else_part: ELSE statement  */
#line 624 ".\\yacc\\p2c.y"
                         {
		(yyval.statement) = (yyvsp[0].statement);
	}
#line 2111 "p2c.tab.c"
    break;

  case 78: /* else_part: %empty  */
#line 627 ".\\yacc\\p2c.y"
                             {
		(yyval.statement) = nullptr;
	}
#line 2119 "p2c.tab.c"
    break;

  case 79: /* expression_list: expression_list ',' expression  */
#line 635 ".\\yacc\\p2c.y"
                                         {
		(yyval.expressionList) = new ExpressionList((yyvsp[-2].expressionList) -> mExpressionVector, (yyvsp[-2].expressionList) -> mTypeVector);
		(yyval.expressionList) -> mExpressionVector.push_back((yyvsp[0].expression));
	}
#line 2128 "p2c.tab.c"
    break;

  case 80: /* expression_list: expression  */
#line 639 ".\\yacc\\p2c.y"
                     {
		(yyval.expressionList) = new ExpressionList();
		(yyval.expressionList) -> mExpressionVector.push_back((yyvsp[0].expression));
	}
#line 2137 "p2c.tab.c"
    break;

  case 81: /* expression: simple_expression '>' simple_expression  */
#line 646 ".\\yacc\\p2c.y"
                                                  {
		(yyval.expression) = new Expression();
		(yyval.expression) -> mLineno = yylineno;
		(yyval.expression) -> mSimpleExpression = nullptr;
		(yyval.expression) -> mRelOp = new RelOp(OP_LARGER, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].simpleExpression));
	}
#line 2148 "p2c.tab.c"
    break;

  case 82: /* expression: simple_expression '<' simple_expression  */
#line 652 ".\\yacc\\p2c.y"
                                                  {
		(yyval.expression) = new Expression();
		(yyval.expression) -> mLineno = yylineno;
		(yyval.expression) -> mSimpleExpression = nullptr;
		(yyval.expression) -> mRelOp = new RelOp(OP_LESS, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].simpleExpression));
	}
#line 2159 "p2c.tab.c"
    break;

  case 83: /* expression: simple_expression NE_OP simple_expression  */
#line 658 ".\\yacc\\p2c.y"
                                                    {
		(yyval.expression) = new Expression();
		(yyval.expression) -> mLineno = yylineno;
		(yyval.expression) -> mSimpleExpression = nullptr;
		(yyval.expression) -> mRelOp = new RelOp(OP_NOT_EQUAL, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].simpleExpression));
	}
#line 2170 "p2c.tab.c"
    break;

  case 84: /* expression: simple_expression LE_OP simple_expression  */
#line 664 ".\\yacc\\p2c.y"
                                                    {
		(yyval.expression) = new Expression();
		(yyval.expression) -> mLineno = yylineno;
		(yyval.expression) -> mSimpleExpression = nullptr;
		(yyval.expression) -> mRelOp = new RelOp(OP_LESS_EQUAL, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].simpleExpression));
	}
#line 2181 "p2c.tab.c"
    break;

  case 85: /* expression: simple_expression GE_OP simple_expression  */
#line 670 ".\\yacc\\p2c.y"
                                                    {
		(yyval.expression) = new Expression();
		(yyval.expression) -> mLineno = yylineno;
		(yyval.expression) -> mSimpleExpression = nullptr;
		(yyval.expression) -> mRelOp = new RelOp(OP_LARGER_EQUAL, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].simpleExpression));
	}
#line 2192 "p2c.tab.c"
    break;

  case 86: /* expression: simple_expression '=' simple_expression  */
#line 676 ".\\yacc\\p2c.y"
                                                  {
		(yyval.expression) = new Expression();
		(yyval.expression) -> mLineno = yylineno;
		(yyval.expression) -> mSimpleExpression = nullptr;
		(yyval.expression) -> mRelOp = new RelOp(OP_EQUAL, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].simpleExpression));
	}
#line 2203 "p2c.tab.c"
    break;

  case 87: /* expression: simple_expression  */
#line 682 ".\\yacc\\p2c.y"
                            {
		(yyval.expression) = new Expression();
		(yyval.expression) -> mLineno = yylineno;
		(yyval.expression) -> mSimpleExpression = (yyvsp[0].simpleExpression);
		(yyval.expression) -> mRelOp = nullptr;
	}
#line 2214 "p2c.tab.c"
    break;

  case 88: /* simple_expression: term  */
#line 691 ".\\yacc\\p2c.y"
               {
		(yyval.simpleExpression) = new SimpleExpression(yylineno, nullptr, (yyvsp[0].term));
	}
#line 2222 "p2c.tab.c"
    break;

  case 89: /* simple_expression: simple_expression '+' term  */
#line 694 ".\\yacc\\p2c.y"
                                     {
		(yyval.simpleExpression) = new SimpleExpression(yylineno, new AddOp(OP_ADD, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].term)),nullptr);
	}
#line 2230 "p2c.tab.c"
    break;

  case 90: /* simple_expression: simple_expression '-' term  */
#line 697 ".\\yacc\\p2c.y"
                                     {
		(yyval.simpleExpression) = new SimpleExpression(yylineno, new AddOp(OP_SUB, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].term)),nullptr);
	}
#line 2238 "p2c.tab.c"
    break;

  case 91: /* simple_expression: simple_expression OR term  */
#line 700 ".\\yacc\\p2c.y"
                                    {
		(yyval.simpleExpression) = new SimpleExpression(yylineno, new AddOp(OP_OR, yylineno, (yyvsp[-2].simpleExpression), (yyvsp[0].term)),nullptr);
	}
#line 2246 "p2c.tab.c"
    break;

  case 92: /* term: term '*' factor  */
#line 706 ".\\yacc\\p2c.y"
                          {
		(yyval.term) = new Term(yylineno, new MulOp(OP_MULTIPLY, yylineno, (yyvsp[-2].term), (yyvsp[0].factor)), nullptr);
	}
#line 2254 "p2c.tab.c"
    break;

  case 93: /* term: term '/' factor  */
#line 709 ".\\yacc\\p2c.y"
                          {
		(yyval.term) = new Term(yylineno, new MulOp(OP_REAL_DIV, yylineno, (yyvsp[-2].term), (yyvsp[0].factor)), nullptr);
	}
#line 2262 "p2c.tab.c"
    break;

  case 94: /* term: term AND factor  */
#line 712 ".\\yacc\\p2c.y"
                          {
		(yyval.term) = new Term(yylineno, new MulOp(OP_AND, yylineno, (yyvsp[-2].term), (yyvsp[0].factor)), nullptr);
	}
#line 2270 "p2c.tab.c"
    break;

  case 95: /* term: term DIV factor  */
#line 715 ".\\yacc\\p2c.y"
                          {
		(yyval.term) = new Term(yylineno, new MulOp(OP_INT_DIV, yylineno, (yyvsp[-2].term), (yyvsp[0].factor)), nullptr);
	}
#line 2278 "p2c.tab.c"
    break;

  case 96: /* term: term MOD factor  */
#line 718 ".\\yacc\\p2c.y"
                          {
		(yyval.term) = new Term(yylineno, new MulOp(OP_MOD, yylineno, (yyvsp[-2].term), (yyvsp[0].factor)), nullptr);
	}
#line 2286 "p2c.tab.c"
    break;

  case 97: /* term: factor  */
#line 721 ".\\yacc\\p2c.y"
                 {
		(yyval.term) = new Term(yylineno, nullptr, (yyvsp[0].factor));
	}
#line 2294 "p2c.tab.c"
    break;

  case 98: /* SNUMBER: NUMBER  */
#line 726 ".\\yacc\\p2c.y"
               {
		(yyval.mFloat) = (yyvsp[0].mFloat);
	}
#line 2302 "p2c.tab.c"
    break;

  case 99: /* SNUMBER: '-' NUMBER  */
#line 729 ".\\yacc\\p2c.y"
                    {
		(yyval.mFloat) = -(yyvsp[0].mFloat);
	}
#line 2310 "p2c.tab.c"
    break;

  case 100: /* factor: SDIGITS  */
#line 734 ".\\yacc\\p2c.y"
                  {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mInt = (yyvsp[0].mInt);
		(yyval.factor) -> mFactorType = FACTOR_VALUE_INT;
	}
#line 2321 "p2c.tab.c"
    break;

  case 101: /* factor: SNUMBER  */
#line 740 ".\\yacc\\p2c.y"
                  {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mReal = (yyvsp[0].mFloat);
		(yyval.factor) -> mFactorType = FACTOR_VALUE_REAL;
	}
#line 2332 "p2c.tab.c"
    break;

  case 102: /* factor: LETTER  */
#line 746 ".\\yacc\\p2c.y"
                 {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mChar = (yyvsp[0].mChar);
		(yyval.factor) -> mFactorType = FACTOR_VALUE_CHAR;
	}
#line 2343 "p2c.tab.c"
    break;

  case 103: /* factor: BOOL  */
#line 752 ".\\yacc\\p2c.y"
               {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mBool = (yyvsp[0].mBool);
		(yyval.factor) -> mFactorType = FACTOR_VALUE_BOOL;
	}
#line 2354 "p2c.tab.c"
    break;

  case 104: /* factor: variable  */
#line 758 ".\\yacc\\p2c.y"
                   {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mVariable = (yyvsp[0].variable);
		(yyval.factor) -> mFunction_Call = nullptr;
		(yyval.factor) -> mExpression = nullptr;
		(yyval.factor) -> mNot = nullptr;
		(yyval.factor) -> mUminus = nullptr;
		(yyval.factor) -> mFactorType = FACTOR_VAR;
	}
#line 2369 "p2c.tab.c"
    break;

  case 105: /* factor: IDENTIFIER '(' expression_list ')'  */
#line 768 ".\\yacc\\p2c.y"
                                             {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mVariable = nullptr;
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-3].mStr));
		tmp -> mLineno = yylineno;
		(yyval.factor) -> mFunction_Call = new FunctionCall((yyvsp[-1].expressionList) -> mExpressionVector.size(), yylineno, tmp, (yyvsp[-1].expressionList));
		(yyval.factor) -> mExpression = nullptr;
		(yyval.factor) -> mNot = nullptr;
		(yyval.factor) -> mUminus = nullptr;
		(yyval.factor) -> mFactorType = FACTOR_FUNCCALL;
	}
#line 2387 "p2c.tab.c"
    break;

  case 106: /* factor: IDENTIFIER '(' ')'  */
#line 781 ".\\yacc\\p2c.y"
                            {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mVariable = nullptr;
		Id* tmp = new Id();
		tmp -> mName = *((yyvsp[-2].mStr));
		tmp -> mLineno = yylineno;
		(yyval.factor) -> mFunction_Call = new FunctionCall(0, yylineno, tmp, nullptr);
		(yyval.factor) -> mExpression = nullptr;
		(yyval.factor) -> mNot = nullptr;
		(yyval.factor) -> mUminus = nullptr;
		(yyval.factor) -> mFactorType = FACTOR_FUNCCALL;
	}
#line 2405 "p2c.tab.c"
    break;

  case 107: /* factor: '(' expression ')'  */
#line 794 ".\\yacc\\p2c.y"
                             {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mVariable = nullptr;
		(yyval.factor) -> mFunction_Call = nullptr;
		(yyval.factor) -> mExpression = (yyvsp[-1].expression);
		(yyval.factor) -> mNot = nullptr;
		(yyval.factor) -> mUminus = nullptr;
		(yyval.factor) -> mFactorType = FACTOR_BRACKETS;
	}
#line 2420 "p2c.tab.c"
    break;

  case 108: /* factor: NOT factor  */
#line 804 ".\\yacc\\p2c.y"
                     {
		(yyval.factor) = new Factor();
		(yyval.factor) -> mLineno = yylineno;
		(yyval.factor) -> mVariable = nullptr;
		(yyval.factor) -> mFunction_Call = nullptr;
		(yyval.factor) -> mExpression = nullptr;
		(yyval.factor) -> mNot = new Not();
		(yyval.factor) -> mNot -> mFactor = (yyvsp[0].factor);
		(yyval.factor) -> mNot -> mLineno = yylineno;
		(yyval.factor) -> mUminus = nullptr;
		(yyval.factor) -> mFactorType = FACTOR_NOT;
	}
#line 2437 "p2c.tab.c"
    break;


#line 2441 "p2c.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 817 ".\\yacc\\p2c.y"



int lexical_and_syntax_analyse() {
	int failed = yyparse();
	if (errorNum != 0)
		cout<< "检测出语法错误数: "<< errorNum << endl;
    if (failed != 0 || errorNum != 0 )
    	return 1;
    else
    	return 0;
}


extern void yyerror(const char* s) {
	printf("line %d: '%s'\n", yylineno, s);
	errorNum++;
}
