%{
#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>

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
	const char *type_int;
	const char *type_bool;
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
Program : CLASS IDENTIFIER START_BLOCK declarations CLOSE_BLOCK 	{fputs("PROGRAM ENCOUNTERED\n",bison_output);}

declarations: | decl declarations	{ // declarations decl	}

decl : field_decl|statement_decl	{ // field_decl_lines statement_decl_lines	}

{ // field_decl_lines : field_decl_lines field_decl similarly for statement }

field_decl: type field_element_list SEMI_COLON

type : 	INT		{fputs($1,bison_output);fputs(" DECLARATION ENCOUNTERED. ",bison_output);}
		|BOOLEAN 	{fputs($1,bison_output);fputs(" DECLARATION ENCOUNTERED. ",bison_output);}


field_element_list:	Field_Element COMMA field_element_list
					| Field_Element

Field_Element: 	IDENTIFIER																					{fputs("ID=",bison_output);fputs($1,bison_output);fputs("\n",bison_output);}
				| IDENTIFIER OPEN_SQUARE_BRACKET DECIMAL_LITERAL CLOSE_SQUARE_BRACKET						{fputs("ID=",bison_output);fputs($1,bison_output);fputs(" SIZE=",bison_output);fprintf(bison_output,"%d",$3);fputs("\n",bison_output);}

statement_decl:	location  ASSIGNMENT_OP expr SEMI_COLON 													{fputs("ASSIGNMENT OPERATION ENCOUNTERED\n",bison_output);}
				|CALLOUT OPEN_PARENTHESIS STRING_LITERAL COMMA callout_arg CLOSE_PARENTHESIS SEMI_COLON 	{fputs("CALLOUT TO ",bison_output);fputs($3,bison_output);fputs(" ENCOUNTERED\n",bison_output);}

location :	IDENTIFIER													{fputs("LOCATION ENCOUNTERED=",bison_output);fputs($1,bison_output);fputs("\n",bison_output);}
			|IDENTIFIER OPEN_SQUARE_BRACKET expr CLOSE_SQUARE_BRACKET	{fputs("LOCATION ENCOUNTERED=",bison_output);fputs($1,bison_output);fputs("\n",bison_output);}

expr :	binary_exp
		| unary_op  binary_exp	

binary_exp:	common_expr 
			| binary_exp binary_op binary_exp	{ // binary_op -> precedence}

common_expr :	location 
				| literal
				| OPEN_PARENTHESIS expr CLOSE_PARENTHESIS

literal :	DECIMAL_LITERAL									{fputs("INT ENCOUNTERD=",bison_output);fprintf(bison_output,"%d",$1);fputs("\n",bison_output);}
			| CHAR_LITERAL									{fputs("CHAR ENCOUNTERED=",bison_output);fputs($1,bison_output);fputs("\n",bison_output);}
			| BOOLEAN_LITERAL								{fputs("BOOLEAN ENCOUNTERED=",bison_output);fprintf(bison_output,"%d",$1);fputs("\n",bison_output);}
			| STRING_LITERAL 								//{fputs("STRING ENCOUNTERED="<<$1<<endl;}

binary_op:	OP_MINUS										{fputs("SUBTRACTION ENCOUNTERED\n",bison_output);}
			| OP_PLUS										{fputs("ADDITION ENCOUNTERED\n",bison_output);}
			| ARITHMETIC_OP									{
																if(strcmp($1,"/"))
																	fputs("DIVISION ENCOUNTERED\n",bison_output);
																else if(strcmp($1,"*"))
																	fputs("MULTIPLICATION ENCOUNTERED\n",bison_output);
																else 
																	fputs("MOD ENCOUNTERED\n",bison_output);
															}
			| RELATIONAL_OP									{
																if(strcmp($1,"<"))
																	fputs("LESS THAN ENCOUNTERED\n",bison_output);
																else
																	fputs("GREATER THAN ENCOUNTERED\n",bison_output);
															}
			| EQUALITY_OP									//{fputs("ENCOUNTERED EQUALITY OP\t"<<$1<<endl;}
			| CONDITIONAL_OP 								//{fputs("ENCOUNTERED CONDITIONAL OP\t"<<$1<<endl;}

unary_op :	NEGATION										//{fputs("ENCOUNTERED NEGATION"<<endl;}
			| OP_MINUS %prec UNARY_MINUS 					//{fputs("ENCOUNTNERED UNARY MINUS"<<endl;}

callout_arg:	expr 
				| expr COMMA callout_arg

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
