/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_DECAF_TAB_H_INCLUDED
# define YY_YY_DECAF_TAB_H_INCLUDED
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
#line 43 "decaf.y" /* yacc.c:1909  */

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
	ASTmethod* mthd;
	ASTmethodArgumentList* mthdArgList;
	ASTmethodArgument* mthdArg;
	ASTblock* blck;
	ASTstatementList *sListNode;
	ASTstatement *sNode;
	ASTlocation *locNode;
	ASTcalloutArgumentList *callArgListNode;
	ASTcalloutArgument *callArgumentNode;
	ASTexpression *eNode;

#line 127 "decaf.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DECAF_TAB_H_INCLUDED  */
