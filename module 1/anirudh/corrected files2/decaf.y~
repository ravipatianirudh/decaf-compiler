%{
#include <cstdio>
#include <iostream>

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
	char *type_int;
	char *type_bool;
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
}

%token <op_plus_val> OP_PLUS
%token <identifier_val> IDENTIFIER
%token <type_int> INT
%token <type_bool> BOOLEAN
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


%token CLASS SEMI_COLON COMMA CALLOUT IF ELSE FOR BREAK CONTINUE RETURN VOID START_BLOCK CLOSE_BLOCK OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS UNARY_MINUS

%left RELATIONAL_OP
%left OP_MINUS OP_PLUS
%left ARITHMETIC_OP
%left NEGATION
%left UNARY_MINUS

%%
Program : CLASS IDENTIFIER START_BLOCK declarations CLOSE_BLOCK {printf("Success");cout<<endl;fputs("PROGRAM\n",bison_output);}

declarations: | decl declarations	{printf("Successful declarations");cout<<endl;fputs("DECLARATIONS\n",bison_output);}

decl : field_decl|statement_decl	{printf("Successful decl");cout<<endl;fputs("DECL\n",bison_output);}

field_decl: type field_element_list SEMI_COLON	{printf("Successful field_decl");cout<<endl;fputs("FIELD DECL\n",bison_output);}

type : INT|BOOLEAN {printf("Successful type");cout<<$1<<endl;fputs("TYPE\n",bison_output);}

field_element_list: Field_Element COMMA field_element_list | Field_Element {printf("Successful field_element_list");cout<<endl;fputs("FIELD ELEMENT LIST\n",bison_output);}

Field_Element: IDENTIFIER | IDENTIFIER OPEN_SQUARE_BRACKET DECIMAL_LITERAL CLOSE_SQUARE_BRACKET {printf("Successful Field_Element");cout<<$1<<endl;fputs("FIELD ELEMENT\n",bison_output);}

statement_decl: location  ASSIGNMENT_OP expr SEMI_COLON | CALLOUT OPEN_PARENTHESIS STRING_LITERAL COMMA callout_arg CLOSE_PARENTHESIS SEMI_COLON {printf("Successful statement_decl");cout<<endl;fputs("STATEMENT DECL\n",bison_output);}

location : IDENTIFIER | IDENTIFIER OPEN_SQUARE_BRACKET expr CLOSE_SQUARE_BRACKET {printf("Successful location");cout<<$1<<endl;fputs("LOCATION\n",bison_output);}

expr : binary_exp | unary_op  binary_exp {printf("Successful expr");cout<<endl;fputs("EXPR\n",bison_output);}

binary_exp: common_expr | binary_exp binary_op binary_exp {printf("Successful binary_exp");cout<<endl;fputs("BINARY EXP\n",bison_output);}

common_expr : location  | literal  | OPEN_PARENTHESIS expr CLOSE_PARENTHESIS {printf("Successful common_expr");cout<<endl;fputs("COMMON EXPR\n",bison_output);}

literal : DECIMAL_LITERAL | CHAR_LITERAL | BOOLEAN_LITERAL | STRING_LITERAL {printf("Successful literal");cout<<$1<<endl;fputs("LITERAL\n",bison_output);}

binary_op: OP_MINUS | OP_PLUS | ARITHMETIC_OP | RELATIONAL_OP | EQUALITY_OP | CONDITIONAL_OP {printf("Successful binary_op");cout<<$1<<endl;fputs("BINARY OP\n",bison_output);}

unary_op : NEGATION | OP_MINUS %prec UNARY_MINUS {printf("Successful unary_op");cout<<$1<<endl;fputs("UNARY OP\n",bison_output);}

callout_arg: expr | expr COMMA callout_arg {printf("Successful callout_arg");cout<<endl;fputs("CALLOUT ARG\n",bison_output);}

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
