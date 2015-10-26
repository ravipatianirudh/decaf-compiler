#include "ast.h"
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv){
	cout<<"EXECUTING TEST!"<<endl;
	program *p = new program("char");
	Visitor v;

	p->accept(v);
}