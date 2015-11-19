#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <string>
#include <bits/stdc++.h>

#include <map>
#include <stack>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
//#include <llvm/IR/PassManager.h>
#include <llvm/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
//#include <llvm/ModuleProvider.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

int validity;
using namespace llvm;
static IRBuilder<> Builder(getGlobalContext());

using namespace std;

extern FILE *xml_output;

class AST;
class ASTprogram;
class ASTbody;
class ASTfield;
class ASTfieldDecl;
class ASTidList;
class ASTidDecl;
class ASTmethod;
class ASTmethodArgumentList;
class ASTmethodArgument;
class ASTblock;
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
	// llvm::Value *retLLVMval;
	ASTprogram *programNode;

	AST(){}
	AST(ASTprogram *p){
		this->programNode = p;
	}

	virtual void accept(Visitor &v) = 0;

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTprogram : public AST{
public:
	// llvm::Value *retLLVMval;
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

	virtual llvm::Value* codeGen(CodeGenContext &context);

};

class ASTbody : public ASTprogram {
public:
	// llvm::Value *retLLVMval;
	ASTfield* fieldNode;
	ASTstatementList* statementListNode;
	ASTmethod* methodNode;
	bool statementsPresent;
	bool methodPresent;

	ASTbody(){}
	ASTbody(ASTfield* f){
		this->fieldNode = f;
		this->statementsPresent = false;
		this->methodPresent = false;
	}
	ASTbody(ASTfield* f,ASTstatementList* s){
		this->fieldNode = f;
		this->statementListNode = s;
		this->statementsPresent = true;
		this->methodPresent = false;
	}
	ASTbody(ASTfield* f,ASTmethod* m){
		this->fieldNode = f;
		this->methodNode = m;
		this->methodPresent = true;
		this->statementsPresent = false;
	}
	ASTbody(ASTfield* f,ASTmethod* m,ASTstatementList *s){
		this->fieldNode = f;
		this->methodNode = m;
		this->statementListNode = s;
		this->methodPresent = true;
		this->statementsPresent = true;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTfield : public ASTbody{
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTfieldDecl*> fieldNodeList;

	ASTfield(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTfieldDecl : public ASTfield{
public:
	// llvm::Value *retLLVMval;
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

	virtual llvm::Value* codeGen(CodeGenContext &context);

};

class ASTidList : public ASTfieldDecl {
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTidDecl*> idList;

	ASTidList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTidDecl : public ASTidList {
public:
	// llvm::Value *retLLVMval;
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

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTmethod : public ASTbody{
public:
	// llvm::Value *retLLVMval;

	char* int_or_bool;
	bool isVoid;
	char* methodID;
	ASTmethodArgumentList* methodArgList;
	ASTblock* method_block;

	ASTmethod(){}

	ASTmethod(char *type,char* id,ASTblock *b){
		this->int_or_bool = type;
		this->methodID = id;
		this->method_block = b;
		this->isVoid = false;
	}

	ASTmethod(char* id,ASTblock *b){
		this->methodID = id;
		this->method_block = b;
		this->isVoid = true;
	}
	ASTmethod(char* type,char* id,ASTblock *b,ASTmethodArgumentList* mal){
		this->int_or_bool = type;
		this->methodID = id;
		this->method_block = b;
		this->methodArgList = mal;
		this->isVoid = false;
	}
	ASTmethod(char* id,ASTblock *b,ASTmethodArgumentList* mal){
		this->isVoid = true;
		this->methodID = id;
		this->method_block = b;
		this->methodArgList = mal;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTmethodArgumentList :public ASTmethod {
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTmethodArgument*> method_arguments;

	ASTmethodArgumentList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTmethodArgument : public ASTmethodArgumentList {
public:
	// llvm::Value *retLLVMval;
	char* methArgType;
	char* methArgID;

	ASTmethodArgument(char* type,char* id){
		this->methArgType = type;
		this-> methArgID = id;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTblock : public	ASTmethod {
public:
	// llvm::Value *retLLVMval;
	ASTstatementList* block_stat;
	ASTfield* block_field;
	bool fieldPresent;
	bool statPresent;

	ASTblock(){
		this->fieldPresent =false;
		this-> statPresent = false;
	}
	ASTblock(ASTfield* f){
		this->block_field = f;
		this->fieldPresent = true;
		this->statPresent = false;
	}
	ASTblock(ASTstatementList* s){
		this->block_stat = s;
		this->fieldPresent = false;
		this->statPresent = true;
	}
	ASTblock(ASTfield *f,ASTstatementList *s){
		this->block_stat = s;
		this->block_field = f;
		this->fieldPresent = true;
		this->statPresent = true;
	}
};

class ASTstatementList : public ASTbody {
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTstatement*> stat_list;

	ASTstatementList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTstatement : public ASTstatementList{
public:
	// llvm::Value *retLLVMval;
	ASTlocation *stat_locationNode;
	ASTexpression *stat_expressionNode;
	ASTcalloutArgumentList *statement_callout;
	std::vector<ASTexpression*> loop_conditional_expression;
	std::vector<ASTblock*> statement_block;
	char* name_callout;
	bool statementIsLocationAssign;
	int statementID;

	ASTstatement(){}
	ASTstatement(ASTlocation* loc,ASTexpression *expr){
		this->stat_locationNode = loc;
		this->stat_expressionNode = expr;
		this->statementIsLocationAssign = true;
		this->statementID = 1;
	}
	ASTstatement(char* s, ASTcalloutArgumentList *c){
		this->name_callout = strdup(s);
		this->statement_callout = c;
		this->statementIsLocationAssign = false;
		this->statementID = 2;
	}
	ASTstatement(ASTexpression* e,ASTblock *b){
		this->loop_conditional_expression.push_back(e);
		this->statement_block.push_back(b);
		this->statementID = 3;
	}
	ASTstatement(ASTexpression* e,ASTblock *b1,ASTblock *b2){
		this->loop_conditional_expression.push_back(e);
		this->statement_block.push_back(b1);
		this->statement_block.push_back(b2);
		this->statementID = 4;
	}
	ASTstatement(ASTexpression* e1,ASTexpression* e2,ASTblock* b){
		this->loop_conditional_expression.push_back(e1);
		this->loop_conditional_expression.push_back(e2);
		this->statement_block.push_back(b);
		this->statementID = 5;
	}
	ASTstatement(ASTexpression *e){
		this->loop_conditional_expression.push_back(e);
		this->statementID = 6;
	}

	ASTstatement(int id){
		this->statementID = id;
	}

	ASTstatement(ASTblock* b){
		this->statement_block.push_back(b);
		this->statementID = 9;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTcalloutArgumentList : public ASTstatement {
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTcalloutArgument*> callout_args_list;

	ASTcalloutArgumentList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTcalloutArgument : public ASTcalloutArgumentList{
public:
	// llvm::Value *retLLVMval;
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

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTexpression : public ASTfieldDecl{
public:
	// llvm::Value *retLLVMval;
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

	virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTlocation : public ASTstatement{
public:
	// llvm::Value *retLLVMval;
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

	virtual llvm::Value* codeGen(CodeGenContext &context);
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

class CodeGenBlock {
    public:
        BasicBlock *block;
        std::map<std::string, Value*> locals;
};

class CodeGenContext {
    std::stack<CodeGenBlock *> blocks;
    Function *mainFunction;

    public:
    Module *module;
    CodeGenContext() { module = new Module("main", getGlobalContext()); }

    void generateCode(ASTProgram* root);
    GenericValue runCode();
    std::map<std::string, Value*>& locals() { return blocks.top()->locals; }
    BasicBlock *currentBlock() { return blocks.top()->block; }
    void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->block = block; }
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
};

void CodeGenContext::generateCode(ASTProgram* root)
{
	std::cout << "Generating code...\n";

	vector<const Type*> argTypes;
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "Class Program", module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

	pushBlock(bblock);
	*root->codeGen(*this); /* emit bytecode for the toplevel block */
	popBlock();

		std::cout << "Code is generated.\n";
		PassManager pm;
		pm.add(createPrintModulePass(&outs()));
		pm.run(*module);

}

static const Type *typeOf(string type)
{
	if (type.compare("int") == 0) {
		return Type::getInt64Ty(getGlobalContext());
	}
	else if (type.compare("boolean")==0)
		return Type::getInt1Ty(getGlobalContext());

	return Type::getVoidTy(getGlobalContext());
}

Value* ASTprogram::codeGen(CodeGenContext& context){
	cout<<"LLVM in program!\n";
	Value *last = NULL;
	this->bodyNode->codeGen(context);
}

Value* ASTbody::codeGen(CodeGenContext& context){
	cout<<"LLVM in body!\n";
	Value *last = NULL;
	this->fieldNode->codeGen(context);
	if(this->statementsPresent == true)
		this->statementListNode->codeGen(context);
	if(this->methodPresent == true)
		this->methodNode->codeGen(context);
}

Value* ASTfield::codeGen(CodeGenContext& context){
	cout<<"LLVM in field\n";
	Value *last = NULL;
	int i;
	for(int i = 0;i < this->fieldNodeList.size();i++){
		this->fieldNodeList[i]->codeGen(context);
	}
}

Value* ASTfieldDecl::codeGen(CodeGenContext& context){
	cout<<"LLVM in field Declaration\n";
	Value *last = NULL;
	this->field_id_list->codeGen(context);
}

Value* ASTidList::codeGen(CodeGenContext& context){
	cout<<"LLVM in id list \n";
	Value *last = NULL;
	int i;
	for(int i = 0 ; i < this-> idList.size() ;i++){
		this->idList[i]->codeGen(context);
	}
}

Value* ASTidDecl::codeGen(CodeGenContext& context){
	cout<<"LLVM in id declaration\n";
	Value* v;

	AllocaInst *alloc = new AllocaInst(typeOf(this->idType), this->decl_id, context.currentBlock());
	context.locals()[this->decl_id] = alloc;
	v = alloc;

	return v;
}

Value* ASTstatementList::codeGen(CodeGenContext& context){
	cout<<"LLVM in statement list\n";
	Value *last=NULL;
	int i;
	for(int  i=0;i<this->stat_list.size();i++){
		this->stat_list[i]->codeGen(context);
	}
}

Value* ASTstatement::codeGen(CodeGenContext& context){
	cout<<"LLVM in statement\n";
	if(this->statementIsLocationAssign == true){
		this->stat_locationNode->codeGen(context);
		this->stat_expressionNode->codeGen(context);
	}
}

Value* ASTexpression::codeGen(CodeGenContext& context){
	switch(this->expressionID){
		case 1:	this->loc_exp->codeGen(context);
				break;
		case 2:	return ConstantInt::get(Type::getInt64Ty(getGlobalContext()),this->int_exp_literal,true);			//	int literal
				break;

		case 3:	return ConstantInt::get(Type::getInt8Ty(getGlobalContext()),(int)this->char_exp_literal,true);		//	char literal
				break;

		case 4:	return ConstantInt::get(Type::getInt1Ty(getGlobalContext()),(int)this->bool_exp_literal,true);		//	bool literal
				break;

		case 5:
				return Builder.CreateNot(this->expressionList[0]->codeGen(context), "notInst");
				break;
		case 6:
				return Builder.CreateFNeg(this->expressionList[0]->codeGen(context), "notInst");
				break;
		case 7:	return Builder.CreateFSub(this->expressionList[1]->codeGen(context), this->expressionList[1]->codeGen(context), "subInst");
				break;

		case 8:	return Builder.CreateFAdd(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "addInst");
				break;

		case 9: switch(this->binSignVal){
					case 1:	return Builder.CreateFMul(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "mulInst");
							break;
					case 2: return Builder.CreateFDiv(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "divInst");
							break;
					case 3: return Builder.CreateFRem(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "modInst");
							break;
					case 4: return Builder.CreateICmpSLT(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "ltCmp");
							break;
					case 5: return Builder.CreateICmpSGT(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "gtCmp");
							break;
					case 6: return Builder.CreateICmpSLE(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "leCmp");
							break;
					case 7: return Builder.CreateICmpSGE(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "geCmp");
							break;
					case 8: return Builder.CreateAnd(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "andCmp");
							break;
					case 9: return Builder.CreateOr(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "orCmp");
							break;
					case 10: 	return Builder.CreateICmpEQ(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "eqCmp");
								break;
					case 11: 	return Builder.CreateICmpNE(this->expressionList[0]->codeGen(context), this->expressionList[1]->codeGen(context), "neqCmp");
								break;
		}
	}
}


Value* ASTlocation::codeGen(CodeGenContext& context){
	return NULL;
}