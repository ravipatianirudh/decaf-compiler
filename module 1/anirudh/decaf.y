%{
#include <cstdio>
#include <iostream>

using namespace std;
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *s);
%}

%union{
	
}