#ifndef AST_H
#define AST_H
#include "nodeVisitor.h"
#endif

using namespace std;

class program;
class body;
class field;
class statement;
class field_declaration;
/*
%%
program:			CLASS IDENTIFIER START_BLOCK body CLOSE_BLOCK
					| CLASS IDENTIFIER START_BLOCK CLOSE_BLOCK

body:				field statement
					| field

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
*/

class ast
{
public:
	program *programNode;
	
	virtual void accept(class nodeVisitor *v) = 0;
	
	ast(){};
	~ast(){};
};

class program : public ast{
	public:
		char *programIdentifier;
		body *bodyNode;
		
		program(){}
		program(char* name,body* b){
			this->programIdentifier = name;
			this->bodyNode = b;
		}
		void accept(nodeVisitor &v){v.visit(this);}


};

class body : public program{
	public:
		field *fieldNode;
		statement statementNode*;
};

class field : public body{
	public:
		field_declaration *field_declaration_node;
		field *field_nodes;

		field(){};
		field(field_declaration *fd,field *f){
		}
		void accept(nodeVisitor &v){v.visit(this);}
	
};


class field_declaration
{
public:
	char* type;
	char* field_id;
	int field_int;

	field_declaration();
	field_declaration(char* t,char* n){
		this->type = t;
		this->field_id = n;
	}
	field_declaration(char* t,char* n,int f_i){
		this->type = t;
		this->field_id = n;
		this.field_int = f_i;
	}

	void accept(nodeVisitor &v){v.visit(this);}
};
