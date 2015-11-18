#include "codegen.h"
//#include "parse.tab.hpp"

int validity;
static IRBuilder<> Builder(getGlobalContext());

void CodeGenContext::generateCode(ASTprogram* root)
{
	std::cout << "Generating code...\n";

	vector<const Type*> argTypes;
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "Class Program", module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

	pushBlock(bblock);
	*root->codeGen(*this); /* emit bytecode for the toplevel block */
	popBlock();

	if(validity == 0)
	{
		std::cout << "Code is generated.\n";
		PassManager pm;
		pm.add(createPrintModulePass(&outs()));
		pm.run(*module);
	}

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


Value *ASTprogram::codeGen(CodeGenContext& context)
{
	int i;
	cout<<"Program Created"<<endl;
	Value *last = NULL;

	last = bodyNode->codeGen(context);

}

Value *ASTbody::codeGen(CodeGenContext& context){

	fieldNode->codeGen(context);
	statementNode -> codeGen(context);

	return NULL;
}

Value *ASTfield::codeGen(CodeGenContext& context){
	for(int i= 0;i<fieldNodeList.size();i++){
		fieldNodeList->codeGen(context);
	}
	return NULL;
}

Value *ASTfieldDecl::codeGen(CodeGenContext& context){
	for(int i =0;i<field_id_list->idList.size();i++){
		field_id_list->idList[i]->codeGen(context);
	}
	return NULL;
}

Value *ASTidDecl::codeGen(CodeGenContext& context){
	Value *v;
	AllocaInst *alloc = new AllocaInst(typeOf(idType), decl_id, context.currentBlock());
	context.locals()[decl_id] = alloc;
	v=alloc;

	return v;
}

Value *ASRstatementList::codeGen(CodeGenContext& context){
for(int i=0;i<statementNode.size();i++)
	{
		statementNode[i].codegen(context);
	}
	return NULL;
}

Value *ASTStatement::codeGen(CodeGenContext& context)
{

	if(flag == 0)
	{
		return 	ass->codeGen(context);
	}

	if(flag==1)
	{
		return rt->codeGen(context);
	}



	if(flag == 3)
	{
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "block");
	context.pushBlock(bblock);
	*blk->codeGen(context);
	context.popBlock();
	}

	if(flag==4)
	{
		return fr->codeGen(context);
	}

	if(flag==5)
	{
		return ifel->codeGen(context);
	}

	if(flag==7)
	{
		return mc->codeGen(context);
	}
	return NULL;
}

Value *ASTNormalMethodCall::codeGen(CodeGenContext& context)
{
	Function *function = context.module->getFunction(id_);
	if(function==NULL)
	{
		cerr<<id_<<"function not declared"<<endl;
		validity = 1;
		return NULL;
	}
	int i;
	vector<Value*> args;

	for(i=0;i<el_.size();i++)
	{
		args.push_back(el_[i].codeGen(context));
	}

	CallInst *call = NULL;
	call = CallInst::Create(function,args.begin(),args.end(),"",context.currentBlock());


	return call;
}

Value *ASTMethodCall::codeGen(CodeGenContext& context)
{
	if(flag==0)
	{
		Value * call = nm->codeGen(context);
		return call;
	}
}

Value *ASTBinexpr::codeGen(CodeGenContext& context)
{
	Instruction::BinaryOps instr;
	if(op_.compare("+")==0)
	{
		instr=Instruction::Add;
	}

	else if(op_.compare("-")==0)
	{
		instr=Instruction::Sub;
	}

	else if(op_.compare("*")==0)
	{
		instr=Instruction::Mul;
	}

	else if(op_.compare("/")==0)
	{
		instr=Instruction::SDiv;
	}

	else if(op_.compare("%")==0)
	{
		instr=Instruction::SRem;
	}

	else if(op_.compare("&&")==0)
	{
		instr=Instruction::And;
	}

	else if(op_.compare("||")==0)
	{
		instr=Instruction::Or;
	}

	else if(op_.compare("||")==0)
	{
		instr=Instruction::Or;
	}

	else if(op_.compare("==")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, lhs.codeGen(context), rhs.codeGen(context),"",context.currentBlock());
	}

	else if(op_.compare("<=")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULE, lhs.codeGen(context), rhs.codeGen(context),"",context.currentBlock());
	}

	else if(op_.compare(">=")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGE, lhs.codeGen(context), rhs.codeGen(context),"",context.currentBlock());
	}

	else if(op_.compare("<")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULT, lhs.codeGen(context), rhs.codeGen(context),"",context.currentBlock());
	}

	else if(op_.compare(">")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGT, lhs.codeGen(context), rhs.codeGen(context),"",context.currentBlock());
	}

	else if(op_.compare("!=")==0)
	{
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_NE, lhs.codeGen(context), rhs.codeGen(context),"",context.currentBlock());
	}

	Value *bin=NULL;

	Value *l = lhs.codeGen(context);
	Value *r = rhs.codeGen(context);

	if(l!=NULL && r!=NULL)
		bin = BinaryOperator::Create(instr, lhs.codeGen(context),rhs.codeGen(context), "", context.currentBlock());

	return bin;

}


Value *ASTUnexpr::codeGen(CodeGenContext& context)
{
	Value *OperandV = sc.codeGen(context);
	return NULL;

	if(OperandV == NULL)return NULL;

	Function *F = context.module->getFunction(std::string("unary")+op_);
	if(F==0)
	{
		cerr<<"Unknown Operand"<<endl;
		validity = 1;
	}

	return Builder.CreateCall(F,OperandV,"unop");
}

Value *ASTLiteral::codeGen(CodeGenContext& context)
{
	char s[1000006];
	strcpy(s,val.c_str());
	int value = atoi(s);

	return ConstantInt::get(Type::getInt64Ty(getGlobalContext()),value,true);
}



Value *ASTExpr::codeGen(CodeGenContext& context)
{
	if(flag==0)
	{
		return m->codeGen(context);
	}


	if(flag == 1)
	{
		return be->codeGen(context);
	}


	if(flag==2)
	{
	if (context.locals().find(lc->id_) == context.locals().end())
	{
		std::cerr << "undeclared variable in expression " << lc->id_ << std::endl;
		validity = 1;
		return NULL;
	}
	return new LoadInst(context.locals()[lc->id_], "", false, context.currentBlock());
	}

	if(flag==4)
	{
		return ue->codeGen(context);
	}

	if(flag==3)
	{
		return li->codeGen(context);
	}
	return NULL;
}
