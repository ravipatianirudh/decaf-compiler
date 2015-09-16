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
Program : CLASS IDENTIFIER START_BLOCK declarations CLOSE_BLOCK 	{cout<<"PROGRAM ENCOUNTERED\t"<<$2<<endl;}

declarations: | decl declarations

decl : field_decl|statement_decl

field_decl: type field_element_list SEMI_COLON

<<<<<<< HEAD
type : INT|BOOLEAN {printf("Successful type");cout<<$1<<endl;fputs("TYPE\n",bison_output);}
=======
type : TYPE 														{cout<<"TYPE ENCOUNTERED\t"<<$1<<endl;}
>>>>>>> 30a8ace9a440980794bec30ac049b0c3b2fc29de

field_element_list:	Field_Element COMMA field_element_list
					| Field_Element

Field_Element: 	IDENTIFIER
				| IDENTIFIER OPEN_SQUARE_BRACKET DECIMAL_LITERAL CLOSE_SQUARE_BRACKET						{cout<<"IDENTIFIER FOR ARRAY\t"<<$1<<endl<<"INT LITERAL\t"<<$3<<endl;}

statement_decl:	location  ASSIGNMENT_OP expr SEMI_COLON 													{cout<<"STATEMENT DECLARATION\n";}
				|CALLOUT OPEN_PARENTHESIS STRING_LITERAL COMMA callout_arg CLOSE_PARENTHESIS SEMI_COLON 	{cout<<"CALLOUT ENCOUNTERED of\t"<<$3<<endl;}

location :	IDENTIFIER													
			|IDENTIFIER OPEN_SQUARE_BRACKET expr CLOSE_SQUARE_BRACKET

expr :	binary_exp
		| unary_op  binary_exp	

binary_exp:	common_expr 
			| binary_exp binary_op binary_exp

common_expr :	location 
				| literal
				| OPEN_PARENTHESIS expr CLOSE_PARENTHESIS

literal :	DECIMAL_LITERAL									{cout<<"INT LITERAL\t"<<$1<<endl;}
			| CHAR_LITERAL									{cout<<"CHAR LITERAL\t"<<$1<<endl;}
			| BOOLEAN_LITERAL								{cout<<"BOOLEAN LITERAL\t"<<$1<<endl;}
			| STRING_LITERAL 								{cout<<"ENCOUNTERED STRING LITERAL\t"<<$1<<endl;}

binary_op:	OP_MINUS
			| OP_PLUS										{cout<<"ENCOUNTERED PLUS OP\t"<<$1<<endl;}
			| ARITHMETIC_OP									{cout<<"ENCOUNTERED ARITHMETIC OP\t"<<$1<<endl;}
			| RELATIONAL_OP									{cout<<"ENCOUNTERED RELATIONAL OP\t"<<$1<<endl;}
			| EQUALITY_OP									{cout<<"ENCOUNTERED EQUALITY OP\t"<<$1<<endl;}
			| CONDITIONAL_OP 								{cout<<"ENCOUNTERED CONDITIONAL OP\t"<<$1<<endl;}

unary_op :	NEGATION										{cout<<"ENCOUNTERED NEGATION"<<endl;}
			| OP_MINUS %prec UNARY_MINUS 					{cout<<"ENCOUTNERED UNARY MINUS"<<endl;}

callout_arg: expr | expr COMMA callout_arg

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
