%{
#include <cstdio>
#include <iostream>

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;

extern void yyerrror(const char* s);
%}

%union{
	char *identifier_val;
	char *type_val;
	int boolean_val;
	char *string_literal;
	char char_literal;
	int hex_literal;
	int decimal_literal;
	char *relational_operator_val;
	char *conditional_operator_val;
	char *arithmetic_operator_val;
	char *assignment_operator_val;
	char *equality_operator_val;
}

%token <identifier_val> ID
%token <type_val> TYPE
%token <boolean_val> BOOLEAN_LITERAL
%token <string_literal> STRING_LITERAL
%token <char_literal> CHAR_LITERAL
%token <hex_literal> HEX_LITERAL
%token <decimal_literal> DECIMAL_LITERAL

%token <relational_operator_val> RELATIONAL_OP
%token <conditional_operator_val> CONDITIONAL_OP
%token <arithmetic_operator_val> ARITHMETIC_OP
%token <assignment_operator_val> ASSIGNMENT_OP
%token <equality_operator_val> EQUALITY_OP

%token CLASS SEMI_COLON COMMA CALLOUT IF ELSE FOR BREAK CONTINUE RETURN VOD ID START_BLOCK CLOSE_BLOCK OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_PARANTHESIS CLOSE_PARANTHESIS

%%
Program : CLASS ID START_BLOCK Declarations CLOSE_BLOCK {printf("Successful");}

Declara: | Decl Declarations

Decl : Field_decl|Statement_decl

Field_decl: Field_Type Field_element_list SEMI_COLON

FieldType: Type_INT | Type_Bool

Field_element_list: Field_elemment COMMA Field_element_list | Field_element

Field_element: IDENTIFIER | IDENTIFIER OPEN_SQUARE_BRACKET CONSTANT_INT CLOSE_SQUARE_BRACKET

Statement_decl: LOCATION ASSIGN_OP EXPR | CALLOUT OPEN_PARANTHESIS STRING_LITERAL OPEN_SQUARE_BRACKET COMMA CALLOUT_ARGS COMMA CLOSE_SQUARE_BRACKET CLOSE_PARANTHESIS

LOCATION: IDENTIFIER | IDENTIFIER START_SQUARE_BRACKET EXPR CLOSE_SQUARE_BRACKET

EXPR : BINARY_EXPR | OP_UNARY BINARY_EXPR

BINARY_EXPR: COMMON_EXPR | BINARY_EXPR BINERY_OP BINARY_EXPR

COMMON_EXPR: LOCATION | LITERAL | OPEN_PARANTHESIS EXPR CLOSE_PARANTHESIS

LITERAL: INT_LITERAL | CHAR_LITERAL | BOOL_LITERAL | STRING_LITERAL

BINERY_OP: OP_MINUS | ARITH_OP | REL_OP | EQ_OP | COND_OP

OP_UNARY: OP_MINUS | NOT_OP

CALLOUT_ARGS: EXPR | STRING_LITERAL
%%
