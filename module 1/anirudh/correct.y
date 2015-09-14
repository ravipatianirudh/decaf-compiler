%{
#include <cstdio>
#include <iostream>
using namespace std;
#include decaf_flex.h
// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);
%}

%union{
	char *identifier;
	

	char *stringLiteral;


}