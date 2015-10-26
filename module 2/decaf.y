%{
#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "ast.h"

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;

FILE *bison_output;
FILE *flex_output;
void yyerror(const char *s);
%}

%union{
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

	program* p;
	body *b;
}

%token <op_plus_val> OP_PLUS
%token <identifier_val> IDENTIFIER
%token <type_val> TYPE
%token <boolean_val> BOOLEAN_LITERAL
%token <string_literal> STRING_LITERAL
%token <char_literal> CHAR_LITERAL
%token <hex_literal> HEX_LITERAL
%token <decimal_literal> DECIMAL_LITERAL
%token <error> ERROR

%type <program> program;
%type <body> body;

%token <relational_operator_val> RELATIONAL_OP
%token <conditional_operator_val> CONDITIONAL_OP
%token <arithmetic_operator_val> ARITHMETIC_OP
%token <assignment_operator_val> ASSIGNMENT_OP
%token <equality_operator_val> EQUALITY_OP
%token <op_minus_val> OP_MINUS
%token <negation_val> NEGATION


%token CLASS SEMI_COLON COMMA CALLOUT IF ELSE FOR BREAK CONTINUE RETURN VOID START_BLOCK CLOSE_BLOCK OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS UNARY_MINUS

%left RELATIONAL_OP
%left OP_MINUS OP_PLUS
%left ARITHMETIC_OP
%left NEGATION
%left UNARY_MINUS

%%
program:			CLASS IDENTIFIER START_BLOCK body CLOSE_BLOCK							{$$ = new program($4,$2);};
					| CLASS IDENTIFIER START_BLOCK CLOSE_BLOCK								{$$ = new program($2);}

body:				field statement															{$$ = new body("found it!\n");}
					| field																	{$$ = new body("FOUND IT!\n");}

field:				field_declaration field
					| field_declaration 

field_declaration:	TYPE IDENTIFIER SEMI_COLON
					| TYPE IDENTIFIER OPEN_SQUARE_BRACKET DECIMAL_LITERAL CLOSE_SQUARE_BRACKET SEMI_COLON

statement:			location ASSIGNMENT_OP expression SEMI_COLON
					| CALLOUT OPEN_PARENTHESIS STRING_LITERAL OPEN_SQUARE_BRACKET callout_arguments CLOSE_SQUARE_BRACKET CLOSE_PARENTHESIS SEMI_COLON

location:			IDENTIFIER
					| IDENTIFIER OPEN_SQUARE_BRACKET expression CLOSE_SQUARE_BRACKET

callout_arguments:	COMMA c_arg
					| c_arg

c_arg:				expression
					| STRING_LITERAL
				
expression:			location
					| DECIMAL_LITERAL
					| CHAR_LITERAL
					| BOOLEAN_LITERAL
					| NEGATION expression
					| OP_MINUS expression %prec UNARY_MINUS
					| expression OP_MINUS expression
					| expression OP_PLUS expression
					| expression ARITHMETIC_OP expression
					| expression RELATIONAL_OP expression
					| OPEN_PARENTHESIS expression CLOSE_PARENTHESIS
%%

int main(int argc,char** argv){
	bison_output = fopen("bison_output.txt","w+");
	flex_output  = fopen("flex_output.txt","w+");

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
		yyparse();
	} while (!feof(yyin));
	fclose(bison_output);
}

void yyerror(const char *s) {
	cout << "Syntax Error" << endl;
	// might as well halt now:
	exit(-1);
}
