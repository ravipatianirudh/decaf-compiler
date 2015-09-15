%{
#include <cstdio>
#include <iostream>

using namespace std;

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE* yyin;

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
}

%token <identifier_val> IDENTIFIER
%token <type_val> TYPE
%token <boolean_val> BOOLEAN_LITERAL
%token <string_literal> STRING_LITERAL
%token <char_literal> CHAR_LITERAL
%token <hex_literal> HEX_LITERAL
%token <decimal_literal> DECIMAL_LITERAL
%token <error> ERROR

%token <relational_operator_val> RELATIONAL_OP
%token <conditional_operator_val> CONDITIONAL_OP
%token <arithmetic_operator_val> ARITHMETIC_OP
%token <assignment_operator_val> ASSIGNMENT_OP
%token <equality_operator_val> EQUALITY_OP
%token <op_minus_val> OP_MINUS
%token <negation_val> NEGATION


%token CLASS SEMI_COLON COMMA CALLOUT IF ELSE FOR BREAK CONTINUE RETURN VOID START_BLOCK CLOSE_BLOCK OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS

%%
Program : CLASS IDENTIFIER START_BLOCK declarations CLOSE_BLOCK {printf("Successful");cout<<endl;}

declarations: | decl declarations	{printf("Successful declarations");cout<<endl;}

decl : field_decl|statement_decl	{printf("Successful decl");cout<<endl;}

field_decl: type field_element_list SEMI_COLON	{printf("Successful field_decl");cout<<endl;}

type : TYPE {printf("Successful type");cout<<$1<<endl;}

field_element_list: Field_Element COMMA field_element_list | Field_Element {printf("Successful field_element_list");cout<<endl;}

Field_Element: IDENTIFIER | IDENTIFIER OPEN_SQUARE_BRACKET DECIMAL_LITERAL CLOSE_SQUARE_BRACKET {printf("Successful Field_Element");cout<<$1<<endl;}

statement_decl: location  ASSIGNMENT_OP expr | CALLOUT OPEN_PARENTHESIS STRING_LITERAL OPEN_SQUARE_BRACKET COMMA callout_arg COMMA CLOSE_SQUARE_BRACKET CLOSE_PARENTHESIS {printf("Successful statement_decl");cout<<endl;}

location : IDENTIFIER | IDENTIFIER 	OPEN_SQUARE_BRACKET expr CLOSE_SQUARE_BRACKET {printf("Successful location");cout<<$1<<endl;}

expr : binary_exp | unary_op  binary_exp {printf("Successful expr");cout<<endl;}

binary_exp: common_expr  | binary_exp binary_op binary_exp {printf("Successful binary_exp");cout<<endl;}

common_expr : location  | literal  | OPEN_PARENTHESIS expr CLOSE_PARENTHESIS {printf("Successful common_expr");cout<<endl;}

literal : DECIMAL_LITERAL | CHAR_LITERAL | BOOLEAN_LITERAL | STRING_LITERAL {printf("Successful literal");cout<<$1<<endl;}

binary_op: OP_MINUS | ARITHMETIC_OP | RELATIONAL_OP | EQUALITY_OP | CONDITIONAL_OP {printf("Successful binary_op");cout<<$1<<endl;}

unary_op : OP_MINUS | NEGATION {printf("Successful unary_op");cout<<$1<<endl;}

callout_arg: expr {printf("Successful callout_arg");cout<<endl;}
%%

int main(int argc,char** argv){
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
		do {
		yyparse();
	} while (!feof(yyin));
}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}