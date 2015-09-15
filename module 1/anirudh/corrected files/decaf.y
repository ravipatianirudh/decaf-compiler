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
}
%token <identifier_val> ID
%token <type_val> TYPE
%token <boolean_val> BOOLEAN_LITERAL
%token <string_literal> STRING_LITERAL
%token <char_literal> CHAR_LITERAL
%token <hex_literal> HEX_LITERAL
%token <decimal_literal> DECIMAL_LITERAL

%token CLASS SEMI_COLON COMMA CALLOUT IF ELSE FOR BREAK CONTINUE RETURN VOID ID START_BLOCK CLOSE_BLOCK OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_PARANTHESIS CLOSE_PARANTHESIS  EQ_OP NOT_OP OP_ARITH_ASSIGN OP_MINUS REL_OP EQ_OP COND_OP