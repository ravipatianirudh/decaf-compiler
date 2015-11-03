#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>

using namespace std;

class AST;
class ASTprogram;
class ASTbody;
class ASTfield;
class ASTfieldDecl;
class ASTidList;
class ASTidDecl;
class ASTstatementList;
class ASTstatement;
class ASTlocation;
class ASTcalloutArgumentList;
class ASTcalloutArgument;
class ASTexpression;
class Visitor;

class Visitor{
public:
	virtual void visit(AST *node) = 0;
	virtual void visit(ASTprogram *node) = 0;
	virtual void visit(ASTbody *node) = 0;
	virtual void visit(ASTfield *node) = 0;
	virtual void visit(ASTfieldDecl *node) = 0;
	virtual void visit(ASTidList *node) = 0;
	virtual void visit(ASTidDecl *node) = 0;
	virtual void visit(ASTstatementList *node) = 0;
	virtual void visit(ASTstatement *node) = 0;
	virtual void visit(ASTlocation *node) = 0;
	virtual void visit(ASTcalloutArgumentList *node) = 0;
	virtual void visit(ASTcalloutArgument *node) = 0;
	virtual void visit(ASTexpression *node) = 0;
};

class AST{
public:
	ASTprogram *programNode;

	AST(){}
	AST(ASTprogram *p){
		this->programNode = p;
	}

	virtual void accept(Visitor &v) = 0;
};

class ASTprogram : public AST{
public:
	ASTbody* bodyNode;
	char* programIdentifier;

	ASTprogram(){}
	ASTprogram(char* name, ASTbody* b){
		this->bodyNode = b;
		this->programIdentifier = strdup(name);
	}
	ASTprogram(char *name){
		this->programIdentifier = strdup(name);
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTbody : public ASTprogram {
public:
	ASTfield* fieldNode;
	ASTstatementList* statementListNode;
	bool statementsPresent;

	ASTbody(){}
	ASTbody(ASTfield* f){
		this->fieldNode = f;
		this->statementsPresent = false;
	}
	ASTbody(ASTfield* f,ASTstatementList* s){
		this->fieldNode = f;
		this->statementListNode = s;
		this->statementsPresent = true;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTfield : public ASTbody{
public:
	std::vector<ASTfieldDecl*> fieldNodeList;

	ASTfield(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTfieldDecl : public ASTfield{
public:
	char* field_type;
	ASTidList *field_id_list;

	ASTfieldDecl(){}
	ASTfieldDecl(char *t,ASTidList *l){
		this->field_type = strdup(t);
		this->field_id_list = l;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

};

class ASTidList : public ASTfieldDecl {
public:
	std::vector<ASTidDecl*> idList;

	ASTidList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTidDecl : public ASTidList {
public:
	char *decl_id;
	int decl_val;
	bool valPresent;

	ASTidDecl(){}
	ASTidDecl(char *i){
		this->decl_id = strdup(i);
		valPresent = false;
	}
	ASTidDecl(char *i,int d){
		this->decl_id = strdup(i);
		this->decl_val = d;
		valPresent = true;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};


class ASTstatementList : public ASTbody {
public:
	std::vector<ASTstatement*> stat_list;

	ASTstatementList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTstatement : public ASTstatementList{
public:
	ASTlocation *stat_locationNode;
	ASTexpression *stat_expressionNode;
	ASTcalloutArgumentList *statement_callout;
	char* name_callout;
	bool statementIsLocationAssign;

	ASTstatement(){}
	ASTstatement(ASTlocation* loc,ASTexpression *expr){
		this->stat_locationNode = loc;
		this->stat_expressionNode = expr;
		this->statementIsLocationAssign = true;
	}
	ASTstatement(char* s, ASTcalloutArgumentList *c){
		this->name_callout = strdup(s);
		this->statement_callout = c;
		this->statementIsLocationAssign = false;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

};

class ASTcalloutArgumentList : public ASTstatement {
public:
	std::vector<ASTcalloutArgument*> callout_args_list;

	ASTcalloutArgumentList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTcalloutArgument : public ASTcalloutArgumentList{
public:
	ASTexpression *c_arg_expression;
	char* c_arg_string;
	bool isExpression;

	ASTcalloutArgument(){}
	ASTcalloutArgument(ASTexpression *expr){
		this->c_arg_expression = expr;
		this->isExpression  = true;
	}
	ASTcalloutArgument(char* str){
		this->c_arg_string = strdup(str);
		this->isExpression  = false;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTexpression : public ASTfieldDecl{
public:
	int int_exp_literal;
	char char_exp_literal;
	bool bool_exp_literal;
	bool isBinary;
	int expressionID;
	int binSignVal;

	ASTlocation *loc_exp;

	std::vector<ASTexpression*> expressionList;

	ASTexpression(){}
	ASTexpression(ASTlocation *loc){
		this->loc_exp = loc;
		this->isBinary = false;
		this->expressionID = 1;
	}
	ASTexpression(int lit){
		this->int_exp_literal = lit;
		this->isBinary = false;
		this->expressionID = 2;
	}
	ASTexpression(char lit){
		this->char_exp_literal = lit;
		this->isBinary = false;
		this->expressionID = 3;
	}
	ASTexpression(bool lit){
		this->bool_exp_literal = lit;
		this->isBinary = false;
		this->expressionID = 4;
	}

	ASTexpression(ASTexpression *unary_expr,int expID){
		this->expressionList.push_back(unary_expr);
		this->isBinary = false;
		this->expressionID = expID;
	}
	ASTexpression(ASTexpression *bin1,ASTexpression *bin2,int expID){
		this->expressionList.push_back(bin1);
		this->expressionList.push_back(bin2);
		this->isBinary = true;
		this->expressionID = expID;
	}
	ASTexpression(ASTexpression *bin1,ASTexpression *bin2,int expID,char* sgn){
		this->expressionList.push_back(bin1);
		this->expressionList.push_back(bin2);
		this->isBinary = true;
		this->expressionID = expID;
		if(strcmp(sgn,"*") == 0){
			this->binSignVal = 1;
		}else if(strcmp(sgn,"/")){
			this->binSignVal = 2;
		}else if(strcmp(sgn,"%")){
			this->binSignVal = 3;
		}else if(strcmp(sgn,"<")){
			this->binSignVal = 4;
		}else if(strcmp(sgn,">")){
			this->binSignVal = 5;
		}else if(strcmp(sgn,"<=")){
			this->binSignVal = 6;
		}else if(strcmp(sgn,">=")){
			this->binSignVal = 7;
		}else if(strcmp(sgn,"&&")){
			this->binSignVal = 8;
		}else if(strcmp(sgn,"||")){
			this->binSignVal = 9;
		}
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTlocation : public ASTstatement{
public:
	char* loc_id;
	ASTexpression *loc_expr;
	bool locExpressionPresent;

	ASTlocation(){}
	ASTlocation(char *c){
		this->loc_id = strdup(c);
		this->locExpressionPresent = false;
	}
	ASTlocation(char *c,ASTexpression *e){
		this->loc_id = strdup(c);
		this->loc_expr = e;
		this->locExpressionPresent = true;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class XML : public Visitor {
public:
	void visit(AST *node){
	}
	void visit(ASTprogram *node){
		if (node != NULL){
			cout<<"THIS IS THE PROGRAM NODE -- "<<node->programIdentifier<<endl;
			node->bodyNode->accept(*this);
		}
	}
	void visit(ASTbody *node){
		cout<<"THIS IS THE BODY NODE\n";
		node->fieldNode->accept(*this);
		if(node -> statementsPresent == true){
			node->statementListNode->accept(*this);
		}
	}

	void visit(ASTfield *node){
		cout<<"THIS IS THE FIELD NODE\n";
		for(vector<ASTfieldDecl*>::iterator it = node->fieldNodeList.begin(); it!= node->fieldNodeList.end(); it++){
			cout<<"iterating through field production\n";
			(*it)->accept(*this);

		}
	}
	void visit(ASTfieldDecl *node){
		cout<<"THIS IS THE FIELD DECL of type "<<node->field_type<<endl;
		node->field_id_list->accept(*this);
	}
	void visit(ASTidList *node){
		cout<<"THIS IS THE ID LIST NODE\n";
		for(vector<ASTidDecl*>::iterator it = node->idList.begin(); it!= node->idList.end(); it++){
			(*it)->accept(*this);
		}
	}
	void visit(ASTidDecl *node){
		cout<<"THIS IS THE ID DECL NODE of name "<<node->decl_id<<endl;
		if(node->valPresent == true){
			cout<<" and value "<<node->decl_val<<endl;
		}
	}

	void visit(ASTstatementList *node){
		cout<<"THIS IS THE STATEMENT LIST NODE\n";
		for(vector<ASTstatement*>::iterator it = node->stat_list.begin(); it!= node->stat_list.end(); it++){
			(*it)->accept(*this);
		}
	}
	void visit(ASTstatement *node){
		cout<<"THIS IS THE STATEMENT NODE\n";
		if(node->statementIsLocationAssign == true){
			node->stat_locationNode->accept(*this);
			node->stat_expressionNode->accept(*this);
		}
		else{
			cout<<"CALLOUT CALLED "<<node->name_callout<<endl;
			node->statement_callout->accept(*this);
		}
	}
	void visit(ASTlocation *node){
		cout<<"THIS IS THE LOCATION NODE\n";
		cout<<"LOCATION NAME IS "<<node->loc_id<<endl;
		if(node->locExpressionPresent == true){
			node->loc_expr->accept(*this);
		}
		cout<<"DONE LOCATION\n";
	}
	void visit(ASTcalloutArgumentList *node){
		cout<<"THE CALLOUT ARGUMENT LIST NODE\n";
		for(vector<ASTcalloutArgument*>::iterator it = node->callout_args_list.begin(); it!= node->callout_args_list.end() ; it++){
			(*it)->accept(*this);
		}
	}
	void visit(ASTcalloutArgument *node){
		if(node->isExpression == false){
			cout<<"THE STRING LITERAL IS "<<node->c_arg_string<<endl;
		}else{
			node->c_arg_expression->accept(*this);
		}
	}
	void visit(ASTexpression *node){
		cout<<"FUCKED!\n";
		switch(node->expressionID){
			case 1: node->loc_exp->accept(*this);
					break;
			case 2:	cout<<"EXPRESSION INT "<<node->int_exp_literal<<endl;
					break;
			case 3:	cout<<"EXPRESSION STRING "<<node->char_exp_literal<<endl;
					break;
			case 4:	cout<<"EXPRESSION BOOLEAN "<<node->bool_exp_literal<<endl;
					break;
			case 5:	cout<<"EXPRESSION NEGATION\n";
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					break;
			case 6:	cout<<"EXPRESSION UNARY MINUS\n";
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					break;
			case 7:	cout<<"EXPRESSION BINARY MINUS\n";
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					break;
			case 8:	cout<<"EXPRESSION BINARY PLUS\n";
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					break;
			case 9:	cout<<"EXPRESSION BINARY ARITHMETIC\n";
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					break;
			case 10:	cout<<"EXPRESSION BINARY RELATIONAL\n";
						for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
							(*it)->accept(*this);
						}
						break;

			case 11: 	cout<<"EXPRESSION BINARY CONDITIONAL\n";
						for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
							(*it)->accept(*this);
						}
						break;
			case 12: 	cout<<"EXPRESSION EXPRESSION \n";
					 	for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
							(*it)->accept(*this);
						}
						break;
		}
	}
};
