#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <string>
#include <bits/stdc++.h>

// #include <map>
// #include <stack>
// #include <llvm/IR/Module.h>
// #include <llvm/IR/IRBuilder.h>
// #include <llvm/IR/Function.h>
// #include <llvm/IR/Type.h>
// #include <llvm/IR/DerivedTypes.h>
// #include <llvm/IR/LLVMContext.h>
// //#include <llvm/IR/PassManager.h>
// #include <llvm/PassManager.h>
// #include <llvm/IR/Instructions.h>
// #include <llvm/IR/CallingConv.h>
// #include <llvm/Bitcode/ReaderWriter.h>
// #include <llvm/Analysis/Verifier.h>
// #include <llvm/Assembly/PrintModulePass.h>
// #include <llvm/IR/IRBuilder.h>
// //#include <llvm/ModuleProvider.h>
// #include <llvm/Support/TargetSelect.h>
// #include <llvm/ExecutionEngine/GenericValue.h>
// // #include <llvm/ExecutionEngine/JIT.h>
// #include <llvm/Support/raw_ostream.h>

// int validity;
// using namespace llvm;
// static IRBuilder<> Builder(getGlobalContext());

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
class ASTmethodCall;
class ASTexpressionList;
class ASTlocation;
class ASTcalloutArgumentList;
class ASTcalloutArgument;
class ASTexpression;
class Visitor;

class CodeGenBlock;
class CodeGenContext;

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
	virtual void visit(ASTmethod *node) = 0;
	virtual void visit(ASTmethodArgumentList *node) = 0;
	virtual void visit(ASTmethodArgument *node) = 0;
	virtual void visit(ASTblock *node) = 0;
	virtual void visit(ASTmethodCall *node) = 0;
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);

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

	// virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTfield : public ASTbody{
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTfieldDecl*> fieldNodeList;

	ASTfield(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);

};

class ASTidList : public ASTfieldDecl {
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTidDecl*> idList;

	ASTidList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTmethod : public ASTbody{
public:
	// llvm::Value *retLLVMval;

	char* int_or_bool;
	bool isVoid;
	bool hasArgs;
	char* methodID;
	ASTmethodArgumentList* methodArgList;
	ASTblock* method_block;

	ASTmethod(){}

	ASTmethod(char *type,char* id,ASTblock *b){
		this->int_or_bool = type;
		this->methodID = id;
		this->method_block = b;
		this->isVoid = false;
		this->hasArgs = false;
	}

	ASTmethod(char* id,ASTblock *b){
		this->methodID = id;
		this->method_block = b;
		this->isVoid = true;
		this->hasArgs = false;
	}
	ASTmethod(char* type,char* id,ASTblock *b,ASTmethodArgumentList* mal){
		this->int_or_bool = type;
		this->methodID = id;
		this->method_block = b;
		this->methodArgList = mal;
		this->isVoid = false;
		this->hasArgs = true;
	}
	ASTmethod(char* id,ASTblock *b,ASTmethodArgumentList* mal){
		this->isVoid = true;
		this->methodID = id;
		this->method_block = b;
		this->methodArgList = mal;
		this->hasArgs = true;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	// virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTmethodArgumentList :public ASTmethod {
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTmethodArgument*> method_arguments;

	ASTmethodArgumentList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	virtual void accept(Visitor &v){
		v.visit(this);
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTstatement : public ASTstatementList{
public:
	// llvm::Value *retLLVMval;
	ASTmethodCall *stat_mc;
	ASTexpressionList *method_call_arguments;
	ASTlocation *stat_locationNode;
	ASTexpression *stat_expressionNode;
	ASTcalloutArgumentList *statement_callout;
	std::vector<ASTexpression*> loop_conditional_expression;
	std::vector<ASTblock*> statement_block;
	char* name_callout;
	bool statementIsLocationAssign;
	bool statementIsMethodCall;
	int statementID;

	ASTstatement(){}
	ASTstatement(ASTlocation* loc,ASTexpression *expr){
		this->stat_locationNode = loc;
		this->stat_expressionNode = expr;
		this->statementIsLocationAssign = true;
		this->statementID = 1;
		this->statementIsMethodCall = false;
	}
	ASTstatement(char* s, ASTcalloutArgumentList *c){
		this->name_callout = strdup(s);
		this->statement_callout = c;
		this->statementIsLocationAssign = false;
		this->statementID = 2;
		this->statementIsMethodCall = false;
	}
	ASTstatement(ASTexpression* e,ASTblock *b){
		this->loop_conditional_expression.push_back(e);
		this->statement_block.push_back(b);
		this->statementID = 3;
		this->statementIsMethodCall = false;
	}
	ASTstatement(ASTexpression* e,ASTblock *b1,ASTblock *b2){
		this->loop_conditional_expression.push_back(e);
		this->statement_block.push_back(b1);
		this->statement_block.push_back(b2);
		this->statementID = 4;
		this->statementIsMethodCall = false;
	}
	ASTstatement(ASTexpression* e1,ASTexpression* e2,ASTblock* b){
		this->loop_conditional_expression.push_back(e1);
		this->loop_conditional_expression.push_back(e2);
		this->statement_block.push_back(b);
		this->statementID = 5;
		this->statementIsMethodCall = false;
	}
	ASTstatement(ASTexpression *e){
		this->loop_conditional_expression.push_back(e);
		this->statementID = 6;
		this->statementIsMethodCall = false;
	}

	ASTstatement(int id){
		this->statementID = id;
		this->statementIsMethodCall = false;
	}

	ASTstatement(ASTblock* b){
		this->statement_block.push_back(b);
		this->statementID = 9;
		this->statementIsMethodCall = false;
	}

	ASTstatement(ASTmethodCall *mc){
		this->stat_mc = mc;
		this->statementID = 10;
		this->statementIsMethodCall = true;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	// virtual llvm::Value* codeGen(CodeGenContext &context);
};

class ASTmethodCall : public ASTstatement
{
public:
	char *call_id;
	bool argAvail;
	ASTexpressionList* call_expression_list;

	ASTmethodCall(char* s){
		this->call_id = s;
		this->argAvail = false;
	}

	ASTmethodCall(char* s,ASTexpressionList* e){
		this->call_id = s;
		this->call_expression_list = e;
		this->argAvail = true;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

};

class ASTexpressionList : public ASTstatement{
public:
	std::vector<ASTexpression *> expression_list;
	ASTexpressionList(){}
	virtual void accept(Visitor &v){
		v.visit(this);
	}
};

class ASTcalloutArgumentList : public ASTstatement {
public:
	// llvm::Value *retLLVMval;
	std::vector<ASTcalloutArgument*> callout_args_list;

	ASTcalloutArgumentList(){}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	ASTmethodCall *expr_mc;
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
	ASTexpression(ASTmethodCall* mc,int id){
		this->expr_mc = mc;
		this->expressionID = id;
		this->isBinary = false;
	}

	virtual void accept(Visitor &v){
		v.visit(this);
	}

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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

	// virtual llvm::Value* codeGen(CodeGenContext &context);
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
		if(node-> methodPresent == true ){
			node->methodNode->accept(*this);
		}
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

	void visit(ASTmethod *node) {
		if(node->isVoid == true){
			cout<<"    <method_define = \""<<node->methodID<<"\",type == VOID>\n";
		}else{
			cout<<"    <method_define = \""<<node->methodID<<"\",type == "<<node->int_or_bool<<" >\n";
		}
		if(node->hasArgs == true){
			node->methodArgList->accept(*this);
		}

		node->method_block->accept(*this);
	}

	void visit(ASTmethodArgumentList *node) {
		for(vector<ASTmethodArgument*>::iterator it = node->method_arguments.begin(); it!= node->method_arguments.end(); it++){
			(*it)->accept(*this);
		}
	}
	void visit(ASTmethodArgument *node) {
		cout<<"         <method_argument type = "<<node->methArgType<<" id = \""<<node->methArgID<<"\">\n";
	}

	void visit(ASTblock *node){
		if(node->fieldPresent == true){
			node->block_field->accept(*this);
		}
		if(node->statPresent == true){
			node->block_stat->accept(*this);
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
		switch (node->statementID) {
			case 1:
							cout<<"        <assignment>"<<endl;
							fputs("        <assignment>\n",xml_output);
							node->stat_locationNode->accept(*this);
							node->stat_expressionNode->accept(*this);
							cout<<"        </assignment"<<endl;
							fputs("        </assignment>\n",xml_output);
							break;
			case 2:
							cout<<"        <callout function=\""<<node->name_callout<<"\">"<<endl;
							fputs("        <callout function=\"",xml_output);
							fputs(node->name_callout,xml_output);
							fputs("\">\n",xml_output);
							node->statement_callout->accept(*this);
							cout<<"        </callout>"<<endl;
							fputs("        </callout>\n",xml_output);
							break;
			case 3:
							cout<<"        <if>\n";
							cout<<"        <if expression>\n";
							node->loop_conditional_expression[0]->accept(*this);
							cout<<"        <if block>\n";
							node->statement_block[0]->accept(*this);
							cout<<"        </if>\n";
							break;
			case 4:
							cout<<"        <if>\n";
							cout<<"        <if expression>\n";
							node->loop_conditional_expression[0]->accept(*this);
							cout<<"        <if block>\n";
							node->statement_block[0]->accept(*this);
							cout<<"        </if>\n";
							cout<<"        <else>\n";
							cout<<"        <else block>\n";
							node->statement_block[1]->accept(*this);
							cout<<"        </else>\n";
							break;
			case 5:
							cout<<"        <for>\n";
							cout<<"        <for expression 1>\n";
							node->loop_conditional_expression[0]->accept(*this);
							cout<<"        <for expression 2>\n";
							node->loop_conditional_expression[1]->accept(*this);
							cout<<"        <for block>\n";
							node->statement_block[0]->accept(*this);
							cout<<"        </for>\n";
							break;
			case 6:
							cout<<"       <return expression>\n";
							node->loop_conditional_expression[0]->accept(*this);
							cout<<"       </return>\n";
							break;
			case 7:
							cout<<"       <break>\n";
							break;

			case 8:
							cout<<"       <continue>\n";
							break;
			case 9:
							cout<<"<block>\n";
							node->statement_block[0]->accept(*this);
							cout<<"</block>\n";
							break;
			case 10:
							node->stat_mc->accept(*this);
							break;
			// 				cout<<"        <method_call = \""<<node->name_callout<<"\">"<<endl;
			// 				fputs("        <method_call=\"",xml_output);
			// 				fputs(node->name_callout,xml_output);
			// 				fputs("\">\n",xml_output);
			// 				cout<<"        </method_call>"<<endl;
			// 				fputs("        </method_call>\n",xml_output);
			// 				break;
			// case 11:
			// 				cout<<"        <method_call = \""<<node->name_callout<<"\">"<<endl;
			// 				fputs("        <method_call=\"",xml_output);
			// 				fputs(node->name_callout,xml_output);
			// 				fputs("\">\n",xml_output);
			// 				cout<<"        <method_call_args>\n";
			// 				node->method_call_arguments->accept(*this);
			// 				cout<<"        </method_call>"<<endl;
			// 				fputs("        </method_call>\n",xml_output);
			// 				break;
		}
	}

	void visit(ASTmethodCall *node){
		if(node->argAvail == true){
			cout<<"       <method_call id = \""<<node->call_id<<"\" >\n";
			cout<<"        <method_call arguments>\n";
			node->call_expression_list->accept(*this);
			cout<<"       </method_call>\n";
		}else{
			cout<<"       <method_call id = \""<<node->call_id<<"\" >\n";
			cout<<"       </method_call>\n";
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

	void visit(ASTexpressionList *node) {
		for(vector<ASTexpression*>::iterator it = node->expression_list.begin(); it!= node->expression_list.end() ; it++){
			(*it)->accept(*this);
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
			case 13:
					node->expr_mc->accept(*this);
					break;
		}
	}
};
