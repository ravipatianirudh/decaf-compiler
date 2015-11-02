#include <iostream>
#include <stdlib.h>
#include <vector>

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
		this->programIdentifier = name;
	}
	ASTprogram(char *name){
		this->programIdentifier = name;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTbody : public ASTprogram {
public:
	ASTfield* fieldNode;
	ASTstatementList* statementListNode;

	ASTbody(){}
	ASTbody(ASTfield* f){
		this->fieldNode = f;
	}
	ASTbody(ASTfield* f,ASTstatementList* s){
		this->fieldNode = f;
		this->statementListNode = s;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTfield : public ASTbody{
public:
	std::vector<ASTfield *> fieldNodeList;
	// ASTfield* fieldNodeList;
	ASTfieldDecl* f_decl;

	ASTfield(){}
	// ASTfield(ASTfieldDecl *f_d,ASTfield *f){
	// 	this->fieldNodeList = f;
	// 	this->f_decl = f_d;
	// }
	ASTfield(ASTfieldDecl *f_d){
		this->f_decl = f_d;
	}

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
		this->field_type = t;
		this->field_id_list = l;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

};

class ASTidList : public ASTfieldDecl {
public:
	std::vector<ASTidList *> list;
	// ASTidList *list;
	ASTidDecl *decl;

	ASTidList(){}
	// ASTidList(ASTidList *l,ASTidDecl *d){
	// 	this->list = l;
	// 	this->decl = d;
	// }
	ASTidList(ASTidDecl *d){
		this->decl = d;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTidDecl : public ASTidList {
public:
	char *decl_id;
	int decl_val;

	ASTidDecl(){}
	ASTidDecl(char *i){
		this->decl_id = i;
	}
	ASTidDecl(char *i,int d){
		this->decl_id = i;
		this->decl_val = d;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};


class ASTstatementList : public ASTbody {
public:
	std::vector<ASTstatementList*> stat_list;
	// ASTstatementList *stat_list;
	ASTstatement *stat;

	ASTstatementList(){}
	// ASTstatementList(ASTstatementList *l,ASTstatement *s){
	// 	this->stat_list = l;
	// 	this->stat = s;
	// }
	ASTstatementList( ASTstatement *s){
		this->stat = s;
	}


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

	ASTstatement(){}
	ASTstatement(ASTlocation* loc,ASTexpression *expr){
		this->stat_locationNode = loc;
		this->stat_expressionNode = expr;
	}
	ASTstatement(char* s, ASTcalloutArgumentList *c){
		this->name_callout = s;
		this->statement_callout = c;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

};

class ASTlocation : public ASTstatement{
public:
	char* loc_id;
	ASTexpression *loc_expr;

	ASTlocation(){}
	ASTlocation(char *c){
		this->loc_id = c;
	}
	ASTlocation(char *c,ASTexpression *e){
		this->loc_id = c;
		this->loc_expr = e;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTcalloutArgumentList : public ASTstatement {
public:
	std::vector<ASTcalloutArgument*> callout_args_list;
	// ASTcalloutArgumentList *callout_args_list;

	ASTcalloutArgumentList(){}
	// ASTcalloutArgumentList(ASTcalloutArgumentList *c_args,ASTcalloutArgument *c_a){
	// 	this->callout_args_list = c_args;
	// 	this->c_arg = c_a;
	// }
	// ASTcalloutArgumentList(ASTcalloutArgument *c){
	// 	this->c_arg = c;
	// }

	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTcalloutArgument : public ASTcalloutArgumentList{
public:
	ASTexpression *c_arg_expression;
	char* c_arg_string;

	ASTcalloutArgument(){}
	ASTcalloutArgument(ASTexpression *expr){
		this->c_arg_expression = expr;
	}
	ASTcalloutArgument(char* str){
		this->c_arg_string = str;
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

	ASTlocation *loc_exp;

	std::vector<ASTexpression> expressionList;

	ASTexpression(){}
	ASTexpression(int lit){
		this->int_exp_literal = lit;
		this->isBinary = false;
	}
	ASTexpression(char lit){
		this->char_exp_literal = lit;
		this->isBinary = false;
	}
	ASTexpression(bool lit){
		this->bool_exp_literal = lit;
		this->isBinary = false;
	}
	ASTexpression(ASTlocation *loc){
		this->loc_exp = loc;
		this->isBinary = false;
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
		node->statementListNode->accept(*this);
	}

	void visit(ASTfield *node){
		cout<<"THIS IS THE FIELD NODE\n";
	}
	void visit(ASTfieldDecl *node){
		cout<<"THIS IS THE FIELD DECL of type "<<node->field_type<<endl;
	}
};
