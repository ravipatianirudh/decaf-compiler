%{
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()
%}

%%
[ \t\n]         ;
[0-9]+\.[0-9]+  { cout << "Found a floating-point number:" << yytext << endl; }
[0-9]+          { cout << "Found an integer:" << yytext << endl; }
[a-zA-Z0-9]+    { cout << "Found a string: " << yytext << endl; }
%%

int main(int, char**) {
	// lex through the input:
	FILE *myFile = fopen("test.snazzle","r");

	if(!myFile){
		printf("Cannot open file!");
		return -1;
	}

	yyin = myFile;

	yylex();
}