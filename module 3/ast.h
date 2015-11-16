#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <string>
// #include <bits/stdc++.h>
// #include <llvm/Value.h>

using namespace std;

extern FILE *xml_output;

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

	virtual void codeGen(CodeGenContext &context) = 0;
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

	virtual void codeGen(CodeGenContext &context) = 0;

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

	virtual void codeGen(CodeGenContext &context) = 0;
};

class ASTfield : public ASTbody{
public:
	std::vector<ASTfieldDecl*> fieldNodeList;

	ASTfield(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual void codeGen(CodeGenContext &context) = 0;
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

	virtual void codeGen(CodeGenContext &context) = 0;

};

class ASTidList : public ASTfieldDecl {
public:
	std::vector<ASTidDecl*> idList;

	ASTidList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual void codeGen(CodeGenContext &context) = 0;
};

class ASTidDecl : public ASTidList {
public:
	char *idType;
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

	virtual void codeGen(CodeGenContext &context) = 0;
};


class ASTstatementList : public ASTbody {
public:
	std::vector<ASTstatement*> stat_list;

	ASTstatementList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual void codeGen(CodeGenContext &context) = 0;
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

	virtual void codeGen(CodeGenContext &context) = 0;
};

class ASTcalloutArgumentList : public ASTstatement {
public:
	std::vector<ASTcalloutArgument*> callout_args_list;

	ASTcalloutArgumentList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual void codeGen(CodeGenContext &context) = 0;
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

	virtual void codeGen(CodeGenContext &context) = 0;
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
		}else if(strcmp(sgn,"/") == 0){
			this->binSignVal = 2;
		}else if(strcmp(sgn,"%") == 0){
			this->binSignVal = 3;
		}else if(strcmp(sgn,"<") == 0){
			this->binSignVal = 4;
		}else if(strcmp(sgn,">") == 0){
			this->binSignVal = 5;
		}else if(strcmp(sgn,"<=") == 0){
			this->binSignVal = 6;
		}else if(strcmp(sgn,">=") == 0){
			this->binSignVal = 7;
		}else if(strcmp(sgn,"&&") == 0){
			this->binSignVal = 8;
		}else if(strcmp(sgn,"||") == 0){
			this->binSignVal = 9;
		}else if(strcmp(sgn,"==") == 0){
			this->binSignVal = 10;
		}else if(strcmp(sgn,"!=") == 0){
			this->binSignVal = 11;
		}
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual void codeGen(CodeGenContext &context) = 0;
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
			cout<<"<"<<node->programIdentifier<<">"<<endl;
			fputs("<",xml_output);
			fputs(node->programIdentifier,xml_output);
			fputs(">\n",xml_output);

			node->bodyNode->accept(*this);
			cout<<"</"<<node->programIdentifier<<">"<<endl;
			fputs("</",xml_output);
			fputs(node->programIdentifier,xml_output);
			fputs(">\n",xml_output);
		}
	}
	void visit(ASTbody *node){
		//cout<<"THIS IS THE BODY NODE\n";
		node->fieldNode->accept(*this);
		if(node -> statementsPresent == true){
			node->statementListNode->accept(*this);
		}
	}

	void visit(ASTfield *node){
		int a1 = (node->fieldNodeList.size());
		cout<<"    <field_declarations count=\""<<a1<<"\">" <<endl;
			fputs("    <field_declarations count=\"",xml_output);
			cout<<a1<<endl;
			//char *c = itoa(a1);
			fprintf(xml_output,"%d",a1);
			fputs("\">\n",xml_output);
		for(vector<ASTfieldDecl*>::iterator it = node->fieldNodeList.begin(); it!= node->fieldNodeList.end(); it++){
			(*it)->accept(*this);
		}
		cout<<"    </field_declarations>"<<endl;
		fputs("    </field_declarations>\n",xml_output);
	}
	void visit(ASTfieldDecl *node){
		//cout<<"THIS IS THE FIELD DECL of type "<<node->field_type<<endl;
		node->field_id_list->accept(*this);
	}
	void visit(ASTidList *node){
		//cout<<"THIS IS THE ID LIST NODE\n";
		for(vector<ASTidDecl*>::iterator it = node->idList.begin(); it!= node->idList.end(); it++){
			(*it)->accept(*this);
		}
	}
	void visit(ASTidDecl *node){
		cout<<"        <declaration name=\""<<node->decl_id<<"\"";
		fputs("        <declaration name=\"",xml_output);
		fputs(node->decl_id,xml_output);
		fputs("\"",xml_output);
		if(node->valPresent == true){
			cout<<" count=\""<<node->decl_val<<"\"";
			fputs(" count=\"",xml_output);
			fprintf(xml_output, "%d",node->decl_val );
			fputs("\"",xml_output);
			}
			cout<<" type=";
			fputs(" type=",xml_output);
		//cout<<node->idType<<endl;
		//cout<<s1<<endl;
		if(strcmp(node->idType,strdup("int"))==0)
		{
			cout<<"\"integer\"/>"<<endl;
			fputs("\"integer\" />\n",xml_output);
		}
		else
		{
			cout<<"\"boolean\"/>"<<endl;
			fputs("\"boolean\" />\n",xml_output);
		}
	}

	void visit(ASTstatementList *node){
		int a2= (node->stat_list.size());
		cout<<"    <statement_declarations count=\""<<a2<<"\">"<<endl;
		fputs("    <statement_declarations count=\"",xml_output);
		fprintf(xml_output,"%lu",node->stat_list.size());
		fputs("\">\n",xml_output);

		for(vector<ASTstatement*>::iterator it = node->stat_list.begin(); it!= node->stat_list.end(); it++){
			(*it)->accept(*this);
		}
		cout<<"    </statement_declarations>"<<endl;
		fputs("    </statement_declarations>\n",xml_output);
	}
	void visit(ASTstatement *node){
		//cout<<"THIS IS THE STATEMENT NODE\n";
		if(node->statementIsLocationAssign == true){
			cout<<"        <assignment>"<<endl;
			fputs("        <assignment>\n",xml_output);
			node->stat_locationNode->accept(*this);
			node->stat_expressionNode->accept(*this);
			cout<<"        </assignment"<<endl;
			fputs("        </assignment>\n",xml_output);
		}
		else{
			cout<<"        <callout function=\""<<node->name_callout<<"\">"<<endl;
			fputs("        <callout function=\"",xml_output);
			fputs(node->name_callout,xml_output);
			fputs("\">\n",xml_output);
			node->statement_callout->accept(*this);
			cout<<"        </callout>"<<endl;
			fputs("        </callout>\n",xml_output);
		}
	}
	void visit(ASTlocation *node){
		//cout<<"THIS IS THE LOCATION NODE\n";
		if(node!=NULL)
		{
			if(node->locExpressionPresent == false){
				cout<<"            <location id=\""<<node->loc_id<<"\" />\n";
				fputs("            <location id=\"",xml_output);
				fputs(node->loc_id,xml_output);
				fputs("\" />\n",xml_output);
			}
			if(node->locExpressionPresent == true){
				cout<<"            <location id=\""<<node->loc_id<<"\">"<<endl;
				fputs("            <location id=\"",xml_output);
				fputs(node->loc_id,xml_output);
				fputs("\" />\n",xml_output);
				cout<<"            <position>"<<endl;
				fputs("            <position>\n",xml_output);
				node->loc_expr->accept(*this);
				cout<<"                </position>"<<endl;
				fputs("                </position>\n",xml_output);
				cout<<"            </location>"<<endl;
				fputs("            </location>\n",xml_output);
			}
	}
}
	void visit(ASTcalloutArgumentList *node){
		//cout<<"THE CALLOUT ARGUMENT LIST NODE\n";
		for(vector<ASTcalloutArgument*>::iterator it = node->callout_args_list.begin(); it!= node->callout_args_list.end() ; it++){
			(*it)->accept(*this);
		}
	}
	void visit(ASTcalloutArgument *node){
		if(node->isExpression == false){
			cout<<"            "<<node->c_arg_string<<endl;
			fputs("            ",xml_output);
			fputs(node->c_arg_string,xml_output);
			fputs("\n",xml_output);
		}else{
			node->c_arg_expression->accept(*this);
		}
	}
	void visit(ASTexpression *node){
		//cout<<"FUCKED!\n";
		switch(node->expressionID){
			case 1: node->loc_exp->accept(*this);
					break;
			case 2:	cout<<"<integer value=\""<<node->int_exp_literal<<"\"/>"<<endl;
					fputs("<integer value=\"",xml_output);
					fprintf(xml_output, "%d",node->int_exp_literal);
					fputs("\"/>\n",xml_output);
					break;
			case 3:	cout<<"<string value=\""<<node->char_exp_literal<<endl;
					fputs("<string value=\"",xml_output);
					fprintf(xml_output, "%c",node->char_exp_literal);
					fputs("\"/>\n",xml_output);
					break;
			case 4:	cout<<"boolean value=\""<<node->bool_exp_literal<<"\"/>"<<endl;
					fputs("<string value=\"",xml_output);
					fprintf(xml_output, node->bool_exp_literal? "true" : "false");
					fputs("\"/>\n",xml_output);
					break;
			case 5:	cout<<"            <unary_expression type=\"not\">"<<endl;
					fputs("            <unary_expression type=\"not\">\n",xml_output);
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					cout<<"            </unary_expression>"<<endl;
					fputs("            </unary_expression>\n",xml_output);
					break;
			case 6:	cout<<"            <unary_expression type=\"minus\">"<<endl;
					fputs("            <unary_expression type=\"minus\">\n",xml_output);
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					cout<<"            </unary_expression>"<<endl;
					fputs("            </unary_expression>\n",xml_output);
					break;
			case 7:	cout<<"            <binary_expression type=\"subtraction\">"<<endl;
					fputs("            <binary_expression type=\"subtraction\">\n",xml_output);
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					cout<<"            </binary_expression>"<<endl;
					fputs("            </binary_expression>\n",xml_output);
					break;
			case 8:	cout<<"            <binary_expression type=\"addition\">"<<endl;
					fputs("            <binary_expression type=\"addition\">\n",xml_output);
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					cout<<"            </binary_expression>"<<endl;
					fputs("            </binary_expression>\n",xml_output);
					break;
			case 9:	cout<<"            <binary_expression type=\"";
					fputs("            <binary_expression type=\"",xml_output);
					switch(node->binSignVal){
					case 1:
					cout<<"multiplication\">"<<endl;
					fputs("multiplication\">\n",xml_output);
					break;
					case 2:
					cout<<"division\">"<<endl;
					fputs("division\">\n",xml_output);
					break;
					case 3:
					cout<<"remainder\">"<<endl;
					fputs("remainder\">\n",xml_output);
					break;
					}
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					cout<<"            </binary_expression>"<<endl;
					fputs("            </binary_expression>\n",xml_output);
					break;
			case 10:	//cout<<"EXPRESSION BINARY RELATIONAL\n";
					cout<<"            <binary_expression type=\"";
					fputs("            <binary_expression type=\"",xml_output);
					switch(node->binSignVal){
					case 4:
					cout<<"less_than\">"<<endl;
					fputs("less_than\">\n",xml_output);
					break;
					case 5:
					cout<<"greater_than\">"<<endl;
					fputs("greater_than\">\n",xml_output);
					break;
					case 6:
					cout<<"less_equal\">"<<endl;
					fputs("less_equal\">\n",xml_output);
					break;
					case 7:
					cout<<"greater_equal\">"<<endl;
					fputs("greater_equal\">\n",xml_output);
					break;
					}
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					cout<<"            </binary_expression>"<<endl;
					fputs("            </binary_expression>\n",xml_output);
					break;

			case 11: //	cout<<"EXPRESSION BINARY CONDITIONAL\n";
					cout<<"            <binary_expression type=\"";
					fputs("            <binary_expression type=\"",xml_output);
					switch(node->binSignVal){
					case 8:
					cout<<"and\">"<<endl;
					fputs("and\">\n",xml_output);
					break;
					case 9:
					cout<<"or\">"<<endl;
					fputs("or\">\n",xml_output);
					break;
					case 10:
					cout<<"is_equal\">"<<endl;
					fputs("is_equal\">\n",xml_output);
					break;
					case 11:
					cout<<"is_not_equal\">"<<endl;
					fputs("is_not_equal\">\n",xml_output);
					break;
					}
					for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
						(*it)->accept(*this);
					}
					cout<<"            </binary_expression>"<<endl;
					fputs("            </binary_expression>\n",xml_output);
					break;
					case 12: 	//cout<<"EXPRESSION EXPRESSION \n";
					 	for(vector<ASTexpression*>::iterator it = node->expressionList.begin(); it!= node->expressionList.end() ; it++){
							(*it)->accept(*this);
						}
						break;
		}
	}
};

using namespace llvm;

class CodeGenBlock {
public:
	BasicBlock block;
	std::map<string,Value*> locals;
};

class CodeGenContext{
public:
	std::stack<CodeGenBlock*> blockStack;
	Function main;
	Module* theModule;

	CodeGenContext(){
		theModule = new Module("main",getGlobalContext());
	}
	std::map<std::string,Value*> &locals(){
		return blockStack.top()->locals;
	}
}
