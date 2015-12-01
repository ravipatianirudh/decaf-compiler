/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "decaf.y" /* yacc.c:339  */

#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>

//#include "codegen.h"
#include "ast.h"


using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;

FILE *bison_output;
FILE *flex_output;
FILE *xml_output;
void yyerror(const char *s);
ASTprogram *root;

#line 89 "decaf.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OP_PLUS = 258,
    IDENTIFIER = 259,
    TYPE = 260,
    BOOLEAN_LITERAL = 261,
    STRING_LITERAL = 262,
    CHAR_LITERAL = 263,
    HEX_LITERAL = 264,
    DECIMAL_LITERAL = 265,
    ERROR = 266,
    RELATIONAL_OP = 267,
    CONDITIONAL_OP = 268,
    ARITHMETIC_OP = 269,
    ASSIGNMENT_OP = 270,
    EQUALITY_OP = 271,
    OP_MINUS = 272,
    NEGATION = 273,
    CLASS = 274,
    SEMI_COLON = 275,
    COMMA = 276,
    CALLOUT = 277,
    IF = 278,
    ELSE = 279,
    FOR = 280,
    BREAK = 281,
    CONTINUE = 282,
    RETURN = 283,
    VOID = 284,
    START_BLOCK = 285,
    CLOSE_BLOCK = 286,
    OPEN_SQUARE_BRACKET = 287,
    CLOSE_SQUARE_BRACKET = 288,
    OPEN_PARENTHESIS = 289,
    CLOSE_PARENTHESIS = 290,
    UNARY_MINUS = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 43 "decaf.y" /* yacc.c:355  */

	char *identifier_val;
	char *type_val;
	int boolean_val;
	char *string_literal;
	char *char_literal;
	int hex_literal;
	int decimal_literal;
	char *relational_operator_val;
	char *conditional_operator_val;
	char *arithmetic_operator_val;
	char *assignment_operator_val;
	char *equality_operator_val;
	char *negation_val;
	char *op_minus_val;
	char *error;
	char *op_plus_val;

	ASTprogram *pNode;
	ASTbody *bNode;
	ASTfield *fNode;
	ASTfieldDecl *fdNode;
	ASTidList *idL;
	ASTidDecl *idC;
	ASTmethodList *mtL;
	ASTmethod* mthd;
	ASTmethodArgumentList* mthdArgList;
	ASTmethodArgument* mthdArg;
	ASTblock* blck;
	ASTstatementList *sListNode;
	ASTstatement *sNode;
	ASTmethodCall *mcNode;
	ASTexpressionList *eLnode;
	ASTlocation *locNode;
	ASTcalloutArgumentList *callArgListNode;
	ASTcalloutArgument *callArgumentNode;
	ASTexpression *eNode;

#line 202 "decaf.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 217 "decaf.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   308

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   130,   130,   131,   134,   135,   136,   137,   140,   141,
     144,   145,   148,   155,   156,   159,   160,   163,   164,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     180,   181,   185,   186,   187,   188,   190,   191,   193,   195,
     196,   197,   198,   200,   201,   204,   205,   208,   209,   211,
     212,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OP_PLUS", "IDENTIFIER", "TYPE",
  "BOOLEAN_LITERAL", "STRING_LITERAL", "CHAR_LITERAL", "HEX_LITERAL",
  "DECIMAL_LITERAL", "ERROR", "RELATIONAL_OP", "CONDITIONAL_OP",
  "ARITHMETIC_OP", "ASSIGNMENT_OP", "EQUALITY_OP", "OP_MINUS", "NEGATION",
  "CLASS", "SEMI_COLON", "COMMA", "CALLOUT", "IF", "ELSE", "FOR", "BREAK",
  "CONTINUE", "RETURN", "VOID", "START_BLOCK", "CLOSE_BLOCK",
  "OPEN_SQUARE_BRACKET", "CLOSE_SQUARE_BRACKET", "OPEN_PARENTHESIS",
  "CLOSE_PARENTHESIS", "UNARY_MINUS", "$accept", "program", "body",
  "method_list", "field", "field_declaration", "id_list", "id_decl",
  "statement_list", "statement", "method_call", "method",
  "method_argument_list", "method_argument", "block", "location",
  "callout_arguments", "c_arg", "expression_list", "expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
# endif

#define YYPACT_NINF -24

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-24)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -17,     6,    42,   -19,   -24,    -1,    40,   -24,    22,   223,
     -24,    17,   -15,   -24,   -24,   -13,    50,    27,    28,    68,
      57,    60,   106,    69,   161,   232,   -24,   243,   -24,    61,
     -24,   -24,    -3,    72,   -24,    40,   139,   103,    18,    71,
     139,    79,   -24,   -24,   -24,   -24,   -24,   139,   139,   -24,
     139,   -24,   -24,   276,    63,   -24,   171,   181,    80,   243,
     -24,   -24,   -24,   139,    62,   -24,   147,   -24,     8,   165,
      -2,    81,    10,   139,   -24,   -24,    73,   139,   139,   139,
     139,   139,   -24,    12,   -24,   191,   -24,    67,   288,   -24,
     -24,   139,   -24,   102,    85,    25,   -24,   124,    85,   264,
     -24,   104,    86,    86,   -24,   104,    85,    53,   -24,   -24,
     165,   -24,   -24,   112,    85,   -24,    58,   -24,   165,    95,
     139,   -24,    85,   -24,   -24,   124,   105,    85,   212,   -24,
     -24,   -24,   -24,   -24
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     3,     0,     5,
      11,    15,     0,    14,     2,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,    10,     4,    18,     0,
       9,    27,     0,     0,    12,     0,     0,     0,    15,     0,
       0,     0,    25,    26,    54,    53,    52,     0,     0,    29,
       0,    63,    51,     0,     0,    39,     0,     0,     0,     7,
       8,    17,    28,     0,     0,    13,     0,    30,     0,    50,
       0,     0,     0,     0,    56,    55,     0,     0,     0,     0,
       0,     0,    24,     0,    40,     0,    42,     0,     0,    16,
      44,     0,    31,     0,     0,     0,    37,     0,     0,     0,
      62,    58,    60,    61,    59,    57,     0,     0,    41,    19,
      49,    38,    32,     0,     0,    48,     0,    46,    47,    21,
       0,    34,     0,    36,    33,     0,     0,     0,     0,    35,
      45,    20,    22,    23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -24,   -24,   -24,   -24,    98,    -8,   -24,    92,   -16,   -20,
       7,   108,    46,    23,   -23,    11,   -24,    14,   -24,   -22
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     8,    25,     9,    10,    12,    13,    27,    28,
      51,    30,    95,    96,    31,    52,   116,   117,    68,   118
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,    26,     1,    93,     6,    34,    35,    61,    57,    59,
       3,     5,    63,    77,    66,    69,    29,    93,    72,    36,
      32,    37,    78,    79,    80,    74,    75,    81,    76,    91,
       7,    29,    29,    94,    29,    32,    32,    61,    32,    61,
      85,    88,     4,    92,    11,    98,   113,   106,    26,    33,
      33,    99,    70,    14,    38,   101,   102,   103,   104,   105,
     114,    39,    40,    29,    29,    61,    29,    32,    32,   110,
      32,   112,    41,    54,   113,   119,    77,    42,    71,   125,
      43,    62,    64,   121,    87,    78,    79,    80,   122,    77,
      81,   124,    29,   126,    73,    89,    32,    83,   128,   129,
      80,    70,    97,    81,   132,   133,   111,    15,   100,    44,
      15,    45,    44,    46,    45,    24,    46,    93,    80,   127,
      47,    48,    56,    47,    48,   131,    49,    65,    15,   107,
      44,   115,    45,    60,    46,     0,   123,    50,    67,   130,
      50,    47,    48,    15,     0,    44,     0,    45,     0,    46,
      77,     0,     0,     0,     0,     0,    47,    48,    50,    78,
      79,    80,     0,     0,    81,    15,     6,     0,    77,     0,
       0,     0,     0,    50,     0,    15,     6,    78,    79,    80,
      90,     0,    81,    17,    18,    15,    19,    20,    21,    22,
       0,    24,    55,    17,    18,    15,    19,    20,    21,    22,
       0,    24,    84,    17,    18,     0,    19,    20,    21,    22,
       0,    24,    86,    17,    18,    77,    19,    20,    21,    22,
       0,    24,   108,     0,    78,    79,    80,    15,    16,    81,
       0,     0,     0,     0,     0,     0,    15,    58,     0,     0,
       0,     0,    24,     0,     0,    17,    18,    15,    19,    20,
      21,    22,    23,    24,    17,    18,     0,    19,    20,    21,
      22,    23,    24,     0,     0,    17,    18,    77,    19,    20,
      21,    22,     0,    24,     0,     0,    78,    79,    80,    77,
       0,    81,     0,     0,     0,   120,     0,     0,    78,    79,
      80,    77,     0,    81,     0,     0,    82,     0,     0,     0,
      78,    79,    80,     0,     0,    81,     0,     0,   109
};

static const yytype_int16 yycheck[] =
{
      22,     9,    19,     5,     5,    20,    21,    27,    24,    25,
       4,    30,    15,     3,    36,    37,     9,     5,    40,    32,
       9,    34,    12,    13,    14,    47,    48,    17,    50,    21,
      31,    24,    25,    35,    27,    24,    25,    57,    27,    59,
      56,    63,     0,    35,     4,    35,    21,    35,    56,    32,
      32,    73,    34,    31,     4,    77,    78,    79,    80,    81,
      35,    34,    34,    56,    57,    85,    59,    56,    57,    91,
      59,    94,     4,     4,    21,    98,     3,    20,     7,    21,
      20,    20,    10,   106,     4,    12,    13,    14,    35,     3,
      17,   114,    85,    35,    15,    33,    85,    34,   120,   122,
      14,    34,    21,    17,   127,   128,     4,     4,    35,     6,
       4,     8,     6,    10,     8,    30,    10,     5,    14,    24,
      17,    18,    24,    17,    18,    20,    20,    35,     4,    83,
       6,     7,     8,    25,    10,    -1,   113,    34,    35,   125,
      34,    17,    18,     4,    -1,     6,    -1,     8,    -1,    10,
       3,    -1,    -1,    -1,    -1,    -1,    17,    18,    34,    12,
      13,    14,    -1,    -1,    17,     4,     5,    -1,     3,    -1,
      -1,    -1,    -1,    34,    -1,     4,     5,    12,    13,    14,
      33,    -1,    17,    22,    23,     4,    25,    26,    27,    28,
      -1,    30,    31,    22,    23,     4,    25,    26,    27,    28,
      -1,    30,    31,    22,    23,    -1,    25,    26,    27,    28,
      -1,    30,    31,    22,    23,     3,    25,    26,    27,    28,
      -1,    30,    31,    -1,    12,    13,    14,     4,     5,    17,
      -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    22,    23,     4,    25,    26,
      27,    28,    29,    30,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    -1,    -1,    22,    23,     3,    25,    26,
      27,    28,    -1,    30,    -1,    -1,    12,    13,    14,     3,
      -1,    17,    -1,    -1,    -1,    21,    -1,    -1,    12,    13,
      14,     3,    -1,    17,    -1,    -1,    20,    -1,    -1,    -1,
      12,    13,    14,    -1,    -1,    17,    -1,    -1,    20
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    38,     4,     0,    30,     5,    31,    39,    41,
      42,     4,    43,    44,    31,     4,     5,    22,    23,    25,
      26,    27,    28,    29,    30,    40,    42,    45,    46,    47,
      48,    51,    52,    32,    20,    21,    32,    34,     4,    34,
      34,     4,    20,    20,     6,     8,    10,    17,    18,    20,
      34,    47,    52,    56,     4,    31,    41,    45,     5,    45,
      48,    46,    20,    15,    10,    44,    56,    35,    55,    56,
      34,     7,    56,    15,    56,    56,    56,     3,    12,    13,
      14,    17,    20,    34,    31,    45,    31,     4,    56,    33,
      33,    21,    35,     5,    35,    49,    50,    21,    35,    56,
      35,    56,    56,    56,    56,    56,    35,    49,    31,    20,
      56,     4,    51,    21,    35,     7,    53,    54,    56,    51,
      21,    51,    35,    50,    51,    21,    35,    24,    56,    51,
      54,    20,    51,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    37,    38,    38,    39,    39,    39,    39,    40,    40,
      41,    41,    42,    43,    43,    44,    44,    45,    45,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    48,    48,    49,    49,    50,    51,
      51,    51,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     4,     2,     1,     2,     3,     2,     1,
       2,     1,     3,     3,     1,     1,     4,     2,     1,     4,
       7,     5,     7,     7,     3,     2,     2,     1,     2,     2,
       3,     4,     5,     6,     5,     6,     3,     1,     2,     2,
       3,     4,     3,     1,     4,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     3,
       3,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 130 "decaf.y" /* yacc.c:1646  */
    {(yyval.pNode) = new ASTprogram((yyvsp[-3].identifier_val),(yyvsp[-1].bNode));root = (yyval.pNode);}
#line 1418 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 131 "decaf.y" /* yacc.c:1646  */
    {(yyval.pNode) = new ASTprogram((yyvsp[-2].identifier_val));root = (yyval.pNode);}
#line 1424 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 134 "decaf.y" /* yacc.c:1646  */
    {(yyval.bNode) = new ASTbody((yyvsp[-1].fNode),(yyvsp[0].sListNode));}
#line 1430 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 135 "decaf.y" /* yacc.c:1646  */
    {(yyval.bNode) = new ASTbody((yyvsp[0].fNode));}
#line 1436 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 136 "decaf.y" /* yacc.c:1646  */
    {(yyval.bNode) = new ASTbody((yyvsp[-1].fNode),(yyvsp[0].mtL));}
#line 1442 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 137 "decaf.y" /* yacc.c:1646  */
    {(yyval.bNode) = new ASTbody((yyvsp[-2].fNode),(yyvsp[-1].mtL),(yyvsp[0].sListNode));}
#line 1448 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 140 "decaf.y" /* yacc.c:1646  */
    {(yyvsp[-1].mtL)->methods_list.push_back((yyvsp[0].mthd));(yyval.mtL) = (yyvsp[-1].mtL);}
#line 1454 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 141 "decaf.y" /* yacc.c:1646  */
    {(yyval.mtL) = new ASTmethodList();(yyval.mtL)->methods_list.push_back((yyvsp[0].mthd));}
#line 1460 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 144 "decaf.y" /* yacc.c:1646  */
    {(yyvsp[-1].fNode)->fieldNodeList.push_back((yyvsp[0].fdNode));(yyval.fNode) = (yyvsp[-1].fNode);}
#line 1466 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 145 "decaf.y" /* yacc.c:1646  */
    {(yyval.fNode) = new ASTfield();(yyval.fNode)->fieldNodeList.push_back((yyvsp[0].fdNode));}
#line 1472 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 148 "decaf.y" /* yacc.c:1646  */
    {(yyval.fdNode) = new ASTfieldDecl((yyvsp[-2].type_val),(yyvsp[-1].idL));
																			for(vector<ASTidDecl*>::iterator it=(yyvsp[-1].idL)->idList.begin(); it!=(yyvsp[-1].idL)->idList.end(); it++)	{
																							(*it)->idType = strdup((yyvsp[-2].type_val));
																				}
																			}
#line 1482 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 155 "decaf.y" /* yacc.c:1646  */
    {(yyvsp[-2].idL)->idList.push_back((yyvsp[0].idC));(yyval.idL) = (yyvsp[-2].idL);}
#line 1488 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 156 "decaf.y" /* yacc.c:1646  */
    {(yyval.idL) =  new ASTidList();(yyval.idL)->idList.push_back((yyvsp[0].idC));}
#line 1494 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 159 "decaf.y" /* yacc.c:1646  */
    {(yyval.idC) = new ASTidDecl((yyvsp[0].identifier_val));}
#line 1500 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 160 "decaf.y" /* yacc.c:1646  */
    {(yyval.idC) = new ASTidDecl((yyvsp[-3].identifier_val),(yyvsp[-1].decimal_literal));}
#line 1506 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 163 "decaf.y" /* yacc.c:1646  */
    {(yyvsp[-1].sListNode)->stat_list.push_back((yyvsp[0].sNode));(yyval.sListNode)=(yyvsp[-1].sListNode);}
#line 1512 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 164 "decaf.y" /* yacc.c:1646  */
    {(yyval.sListNode) = new ASTstatementList();(yyval.sListNode)->stat_list.push_back((yyvsp[0].sNode));}
#line 1518 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 167 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[-3].locNode),(yyvsp[-1].eNode));}
#line 1524 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 168 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[-4].string_literal),(yyvsp[-2].callArgListNode));}
#line 1530 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 169 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[-2].eNode),(yyvsp[0].blck));}
#line 1536 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 170 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[-4].eNode),(yyvsp[-2].blck),(yyvsp[0].blck));}
#line 1542 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 171 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[-3].eNode),(yyvsp[-1].eNode),(yyvsp[0].blck));}
#line 1548 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 172 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[-1].eNode));}
#line 1554 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 173 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement(7);}
#line 1560 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 174 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement(8);}
#line 1566 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 175 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[0].blck));}
#line 1572 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 176 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement((yyvsp[-1].mcNode));}
#line 1578 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 177 "decaf.y" /* yacc.c:1646  */
    {(yyval.sNode) = new ASTstatement(11);}
#line 1584 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 180 "decaf.y" /* yacc.c:1646  */
    {(yyval.mcNode) = new ASTmethodCall((yyvsp[-2].identifier_val));}
#line 1590 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 181 "decaf.y" /* yacc.c:1646  */
    {(yyval.mcNode) = new ASTmethodCall((yyvsp[-3].identifier_val),(yyvsp[-1].eLnode));}
#line 1596 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 185 "decaf.y" /* yacc.c:1646  */
    {(yyval.mthd) = new ASTmethod((yyvsp[-4].type_val),(yyvsp[-3].identifier_val),(yyvsp[0].blck));}
#line 1602 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 186 "decaf.y" /* yacc.c:1646  */
    {(yyval.mthd) = new ASTmethod((yyvsp[-5].type_val),(yyvsp[-4].identifier_val),(yyvsp[0].blck),(yyvsp[-2].mthdArgList));}
#line 1608 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 187 "decaf.y" /* yacc.c:1646  */
    {(yyval.mthd) = new ASTmethod((yyvsp[-3].identifier_val),(yyvsp[0].blck));}
#line 1614 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 188 "decaf.y" /* yacc.c:1646  */
    {(yyval.mthd) = new ASTmethod((yyvsp[-4].identifier_val),(yyvsp[0].blck),(yyvsp[-2].mthdArgList));}
#line 1620 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 190 "decaf.y" /* yacc.c:1646  */
    {(yyvsp[-2].mthdArgList)->method_arguments.push_back((yyvsp[0].mthdArg));(yyval.mthdArgList) = (yyvsp[-2].mthdArgList);}
#line 1626 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 191 "decaf.y" /* yacc.c:1646  */
    {(yyval.mthdArgList) = new ASTmethodArgumentList();(yyval.mthdArgList)->method_arguments.push_back((yyvsp[0].mthdArg));}
#line 1632 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 193 "decaf.y" /* yacc.c:1646  */
    {(yyval.mthdArg) = new ASTmethodArgument((yyvsp[-1].type_val),(yyvsp[0].identifier_val));}
#line 1638 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 195 "decaf.y" /* yacc.c:1646  */
    {(yyval.blck) = new ASTblock();cout<<"HERE!\n";}
#line 1644 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 196 "decaf.y" /* yacc.c:1646  */
    {(yyval.blck) = new ASTblock((yyvsp[-1].fNode));}
#line 1650 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 197 "decaf.y" /* yacc.c:1646  */
    {(yyval.blck) = new ASTblock((yyvsp[-2].fNode),(yyvsp[-1].sListNode));}
#line 1656 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 198 "decaf.y" /* yacc.c:1646  */
    {(yyval.blck) = new ASTblock((yyvsp[-1].sListNode));}
#line 1662 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 200 "decaf.y" /* yacc.c:1646  */
    {(yyval.locNode) = new ASTlocation((yyvsp[0].identifier_val));}
#line 1668 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 201 "decaf.y" /* yacc.c:1646  */
    {(yyval.locNode) = new ASTlocation((yyvsp[-3].identifier_val),(yyvsp[-1].eNode));}
#line 1674 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 204 "decaf.y" /* yacc.c:1646  */
    {(yyvsp[-2].callArgListNode)->callout_args_list.push_back((yyvsp[0].callArgumentNode));(yyval.callArgListNode) = (yyvsp[-2].callArgListNode);}
#line 1680 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 205 "decaf.y" /* yacc.c:1646  */
    {(yyval.callArgListNode) = new ASTcalloutArgumentList();(yyval.callArgListNode)->callout_args_list.push_back((yyvsp[0].callArgumentNode));}
#line 1686 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 208 "decaf.y" /* yacc.c:1646  */
    {(yyval.callArgumentNode) = new ASTcalloutArgument((yyvsp[0].eNode));}
#line 1692 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 209 "decaf.y" /* yacc.c:1646  */
    {(yyval.callArgumentNode) = new ASTcalloutArgument((yyvsp[0].string_literal));}
#line 1698 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 211 "decaf.y" /* yacc.c:1646  */
    {(yyvsp[-2].eLnode)->expression_list.push_back((yyvsp[0].eNode));(yyval.eLnode) = (yyvsp[-2].eLnode);}
#line 1704 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 212 "decaf.y" /* yacc.c:1646  */
    {(yyval.eLnode) = new ASTexpressionList();(yyval.eLnode)->expression_list.push_back((yyvsp[0].eNode));}
#line 1710 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 215 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[0].locNode));}
#line 1716 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 216 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[0].decimal_literal));}
#line 1722 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 217 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[0].char_literal));}
#line 1728 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 218 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[0].boolean_val));}
#line 1734 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 219 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[0].eNode),5);}
#line 1740 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 220 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[0].eNode),6);}
#line 1746 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 221 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[-2].eNode),(yyvsp[0].eNode),7);}
#line 1752 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 222 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[-2].eNode),(yyvsp[0].eNode),8);}
#line 1758 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 223 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[-2].eNode),(yyvsp[0].eNode),9,(yyvsp[-1].arithmetic_operator_val));}
#line 1764 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 224 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[-2].eNode),(yyvsp[0].eNode),10,(yyvsp[-1].relational_operator_val));}
#line 1770 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 225 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[-2].eNode),(yyvsp[0].eNode),11,(yyvsp[-1].conditional_operator_val));}
#line 1776 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 226 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[-1].eNode),12);}
#line 1782 "decaf.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 227 "decaf.y" /* yacc.c:1646  */
    {(yyval.eNode) = new ASTexpression((yyvsp[0].mcNode),13);}
#line 1788 "decaf.tab.c" /* yacc.c:1646  */
    break;


#line 1792 "decaf.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 229 "decaf.y" /* yacc.c:1906  */


int main(int argc,char** argv){
	cout<<"201303004\n201303008"<<endl;
	bison_output = fopen("bison_output.txt","w+");
	flex_output  = fopen("flex_output.txt","w+");
	xml_output = fopen("xml_output.txt","w+");
	int done;
	if(argc>1)
	{
		++argv;
		FILE *myfile = fopen(argv[0], "r");
		// make sure it is valid:
		if (!myfile) {
			cout << "File Reading Error" << endl;
			return -1;
		}
		// set flex to read from it instead of defaulting to STDIN:
		yyin = myfile;
	}
	else
		yyin=stdin;
	// parse through the input until there is no more:
		do {
		done = yyparse();
	} while (!feof(yyin));

	if(done == 0){

		cout<<"Success\n";
		XML v;
		root->accept(v);

	}
	fclose(bison_output);
}

void yyerror(const char *s) {
	cout << "Syntax Error" << endl;
	// might as well halt now:
	exit(-1);
}
