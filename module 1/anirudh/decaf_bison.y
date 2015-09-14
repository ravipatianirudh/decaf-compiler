%{
#include <cstdio>
#include <iostream>
using namespace std;
#include decaf_flex.h
// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	char *stringLiteral;
}
%token CLASS PROGRAM SEMI_COLON COMMA CALLOUT INT_TYPE BOOL_TYPE IF ELSE FOR BREAK CONTINUE RETURN VOID INT_LITERAL CHAR_LITERAL BOOL_LITERAL IDENTIFIER START_BLOCK CLOSE_BLOCK OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_PARANTHESIS CLOSE_PARANTHESIS  EQ_OP NOT_OP OP_ARITH_ASSIGN OP_MINUS REL_OP EQ_OP COND_OP

%token <stringLiteral> STRING_LITERAL

%%

Program : CLASS PROGRAM START_BLOCK Declarations CLOSE_BLOCK {printf("Successful");}

DECLARATIONS: | Decl Declarations

Decl : Field_decl|Statement_decl

Field_decl: Field_Type Field_element_list SEMI_COLON

FieldType: Type_INT | Type_Bool

Field_element_list: Field_elemment COMMA Field_element_list | Field_element

Field_element: IDENTIFIER | IDENTIFIER OPEN_SQUARE_BRACKET CONSTANT_INT CLOSE_SQUARE_BRACKET

Statement_decl: LOCATION ASSIGN_OP EXPR | CALLOUT OPEN_PARANTHESIS STRING_LITERAL OPEN_SQUARE_BRACKET COMMA CALLOUT_ARGS COMMA CLOSE_SQUARE_BRACKET CLOSE_PARANTHESIS

LOCATION: IDENTIFIER | IDENTIFIER START_SQUARE_BRACKET EXPR CLOSE_SQUARE_BRACKET

EXPR : BINERY_EXPR | OP_UNIERY BINERY_EXPR

BINERY_EXPR: COMMON_EXPR | BINERY_EXPR BINERY_OP BINERY_EXPR

COMMON_EXPR: LOCATION | LITERAL | OPEN_PARANTHESIS EXPR CLOSE_PARANTHESIS

LITERAL: INT_LITERAL | CHAR_LITERAL | BOOL_LITERAL | STRING_LITERAL

BINERY_OP: OP_MINUS | ARITH_OP | REL_OP | EQ_OP | COND_OP

OP_UNIERY: OP_MINUS | NOT_OP

CALLOUT_ARGS: EXPR | STRING_LITERAL

%%
int main(int argc, char **argv) {
	// open a file handle to a particular file:
	if(argc>1)
	{
		++argv;
		FILE *myfile = fopen(argv[0], "r");
		// make sure it is valid:
		if (!myfile) {
			cout << "unsuccessful" << endl;
			return -1;
		}
		// set flex to read from it instead of defaulting to STDIN:
		yyin = myfile;
	}
	else
		yyin=stdin;
	// parse through the input until there is no more:
		yyparse();
	
}

void yyerror(const char *s) {
	cout << "unsuccessful" << s << endl;
	// might as well halt now:
	exit(-1);
}
