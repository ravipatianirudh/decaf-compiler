#include "ast.h"

using namespace llvm;

class CodeGenBlock{
  BasicBlock bb;
  std::map<char* name,Value* val,compare> symTable;
};

class CodeGenContext{
  CodeGenBlock basic;
  Function *main;
  Module *module;

  CodeGenBlock(){
    this->module = new Module("main",getGlobalContext());
  }

  static Type *typeOf(char* type)	{
    if (strcmp(type,"int") == 0)
      return Type::getInt64Ty(getGlobalContext());
    else if (strcmp(type,"boolean")==0)
      return Type::getInt1Ty(getGlobalContext());
    return Type::getVoidTy(getGlobalContext());
  }

}
