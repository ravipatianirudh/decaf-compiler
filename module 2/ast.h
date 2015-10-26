#ifndef AST_H
#define AST_H
#include <iostream>

using namespace std;

class AST;
class program;
class body;
class Visitor;

class Visitor{
public:
	void visit(program *p){
		cout<<"Hello there program!\n";
	}
};

class AST{
public:
	program *programNode;

	AST(){}
	AST(program *p){
		programNode = p;
	}

	virtual void accept(Visitor &v) = 0;
};

class program : public AST{
public:
	body* bodyNode;
	char* programIdentifier;

	program(){}
	program(body* b,char *name){
		bodyNode = b;
		programIdentifier = name;
	}
	program(char *name){
		programIdentifier = name;
	}

	void accept(Visitor &v){
		v.visit(this);
	}
};

class body : public program {
public:
	char* junk;

	body(){}
	body(char* j){
		junk = j;
	}

	void accept(Visitor &v){
		v.visit(this);
	}
};

#endif