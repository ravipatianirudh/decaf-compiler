#ifndef NODEVISITOR_H
#define NODEVISITOR_H
#include "ast.h"
#include <iostream>
#endif

class nodeVisitor;

class nodeVisitor
{
	public:
		void visit(program p){cout<<"visited program!"<<endl;}
		void visit(body b){cout<<"visted body!"<<endl;}
		void visit(field f){cout<<"visited field!"<<endl;}
		void visit(field_decalaration f_d){cout<<"visited field decalaration!"<<endl;}
};