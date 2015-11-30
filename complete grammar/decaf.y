%{
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
%}

/*
class AST;
class program;
class body;
class field;
class field_declaration;
class statement;
class location;
class c_argument;
class expression;
class Visitor;
*/

/*
%code requires{
	#include "ast.h"
}
*/

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
	ASTexpressionList *eLnode;
	ASTlocation *locNode;
	ASTcalloutArgumentList *callArgListNode;
	ASTcalloutArgument *callArgumentNode;
	ASTexpression *eNode;
}

%type <pNode> program
%type <bNode> body
%type <fNode> field
%type <fdNode> field_declaration
%type <idL> id_list
%type <idC> id_decl
%type <sListNode> statement_list
%type <sNode> statement
%type <locNode> location
%type <callArgListNode> callout_arguments
%type <callArgumentNode> c_arg
%type <eLnode> expression_list
%type <eNode> expression
%type <mthd> method
%type <mthdArgList> method_argument_list
%type <mthdArg> method_argument
%type <blck> block

%token <op_plus_val> OP_PLUS
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


%token CLASS SEMI_COLON COMMA CALLOUT IF ELSE FOR BREAK CONTINUE RETURN VOID START_BLOCK CLOSE_BLOCK OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_PARENTHESIS CLOSE_PARENTHESIS UNARY_MINUS

%left RELATIONAL_OP CONDITIONAL_OP
%left OP_MINUS OP_PLUS
%left ARITHMETIC_OP
%left NEGATION
%left UNARY_MINUS

%%
program:			CLASS IDENTIFIER START_BLOCK body CLOSE_BLOCK			{$$ = new ASTprogram($2,$4);root = $$;}
					| CLASS IDENTIFIER START_BLOCK CLOSE_BLOCK				{$$ = new ASTprogram($2);root = $$;}
					;

body:				field statement_list											{$$ = new ASTbody($1,$2);}
					| field															{$$ = new ASTbody($1);}
					| field method													{$$ = new ASTbody($1,$2);}
					| field method statement_list									{$$ = new ASTbody($1,$2,$3);}
					;

field:				field field_declaration 								{$1->fieldNodeList.push_back($2);$$ = $1;}
					| field_declaration 									{$$ = new ASTfield();$$->fieldNodeList.push_back($1);}
					;

field_declaration:	TYPE id_list SEMI_COLON									{$$ = new ASTfieldDecl($1,$2);
																			for(vector<ASTidDecl*>::iterator it=$2->idList.begin(); it!=$2->idList.end(); it++)	{
																							(*it)->idType = strdup($1);
																				}
																			}
					;

id_list:			id_list COMMA id_decl									{$1->idList.push_back($3);$$ = $1;}
					| id_decl												{$$ =  new ASTidList();$$->idList.push_back($1);}
					;

id_decl:			IDENTIFIER																	{$$ = new ASTidDecl($1);}
					| IDENTIFIER OPEN_SQUARE_BRACKET DECIMAL_LITERAL CLOSE_SQUARE_BRACKET		{$$ = new ASTidDecl($1,$3);}


statement_list:		statement_list statement													{$1->stat_list.push_back($2);$$=$1;}
					| statement																	{$$ = new ASTstatementList();$$->stat_list.push_back($1);}
					;

statement:			location ASSIGNMENT_OP expression SEMI_COLON															{$$ = new ASTstatement($1,$3);}
					| CALLOUT OPEN_PARENTHESIS STRING_LITERAL COMMA callout_arguments CLOSE_PARENTHESIS SEMI_COLON			{$$ = new ASTstatement($3,$5);}
					| IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block												{$$ = new ASTstatement($3,$5);}
					| IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block ELSE block										{$$ = new ASTstatement($3,$5,$7);}
					| FOR IDENTIFIER '=' expression COMMA expression block													{$$ = new ASTstatement($4,$6,$7);}
					| RETURN expression SEMI_COLON																			{$$ = new ASTstatement($2);}
					| BREAK SEMI_COLON																						{$$ = new ASTstatement(7);}
					| CONTINUE SEMI_COLON																					{$$ = new ASTstatement(8);}
					| block																									{$$ = new ASTstatement($1);}
					| IDENTIFIER OPEN_PARENTHESIS CLOSE_PARENTHESIS	SEMI_COLON												{$$ = new ASTstatement($1);}
					| IDENTIFIER OPEN_PARENTHESIS expression_list CLOSE_PARENTHESIS SEMI_COLON								{$$ = new ASTstatement($1,$3);}
					;



method:						TYPE IDENTIFIER OPEN_PARENTHESIS CLOSE_PARENTHESIS block										{$$ = new ASTmethod($1,$2,$5);}
							| TYPE IDENTIFIER OPEN_PARENTHESIS method_argument_list CLOSE_PARENTHESIS block					{$$ = new ASTmethod($1,$2,$6,$4);}
							| VOID IDENTIFIER OPEN_PARENTHESIS CLOSE_PARENTHESIS block										{$$ = new ASTmethod($2,$5);}
							| VOID IDENTIFIER OPEN_PARENTHESIS method_argument_list CLOSE_PARENTHESIS block					{$$ = new ASTmethod($2,$6,$4);}

method_argument_list: 		method_argument_list COMMA method_argument														{$1->method_arguments.push_back($3);$$ = $1;}
							| method_argument																				{$$ = new ASTmethodArgumentList();$$->method_arguments.push_back($1);}

method_argument:			TYPE IDENTIFIER																					{$$ = new ASTmethodArgument($1,$2);}

block:				START_BLOCK CLOSE_BLOCK																					{$$ = new ASTblock();cout<<"HERE!\n";}
					| START_BLOCK field CLOSE_BLOCK																			{$$ = new ASTblock($2);}
					| START_BLOCK field statement_list CLOSE_BLOCK															{$$ = new ASTblock($2,$3);}
					| START_BLOCK statement_list CLOSE_BLOCK																{$$ = new ASTblock($2);}

location:			IDENTIFIER															{$$ = new ASTlocation($1);}
					| IDENTIFIER OPEN_SQUARE_BRACKET expression CLOSE_SQUARE_BRACKET	{$$ = new ASTlocation($1,$3);}
					;

callout_arguments:	callout_arguments COMMA c_arg										{$1->callout_args_list.push_back($3);$$ = $1;}
					| c_arg																{$$ = new ASTcalloutArgumentList();$$->callout_args_list.push_back($1);}
					;

c_arg:				expression															{$$ = new ASTcalloutArgument($1);}
					| STRING_LITERAL													{$$ = new ASTcalloutArgument($1);}
					;
expression_list:	expression_list COMMA expression									{$1->expression_list.push_back($3);$$ = $1;}
					| expression														{$$ = new ASTexpressionList();$$->expression_list.push_back($1);}

expression:			location															{$$ = new ASTexpression($1);}
					| DECIMAL_LITERAL													{$$ = new ASTexpression($1);}
					| CHAR_LITERAL														{$$ = new ASTexpression($1);}
					| BOOLEAN_LITERAL													{$$ = new ASTexpression($1);}
					| NEGATION expression												{$$ = new ASTexpression($2,5);}
					| OP_MINUS expression %prec UNARY_MINUS								{$$ = new ASTexpression($2,6);}
					| expression OP_MINUS expression									{$$ = new ASTexpression($1,$3,7);}
					| expression OP_PLUS expression										{$$ = new ASTexpression($1,$3,8);}
					| expression ARITHMETIC_OP expression								{$$ = new ASTexpression($1,$3,9,$2);}
					| expression RELATIONAL_OP expression								{$$ = new ASTexpression($1,$3,10,$2);}
					| expression CONDITIONAL_OP expression								{$$ = new ASTexpression($1,$3,11,$2);cout<<$2;}
					| OPEN_PARENTHESIS expression CLOSE_PARENTHESIS						{$$ = new ASTexpression($2,12);}
					;
%%

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
