%{
#include <iostream>
#include <cstdio>
#define YY_DECL extern "C" int yylex()

using namespace std;

%}

%%
[\t\n]							;
class							{cout<<"class"<<endl;}

int								|
boolean							{cout<<"type"<<endl;}

if								{cout<<"IF"<<endl;}
for								{cout<<"FOR"<<endl;}
return							{cout<<"RETURN"<<endl;}
break							{cout<<"BREAK"<<endl;}
continue						{cout<<"CONTINUE"<<endl;}

callout							{cout<<"callout function"<<endl;}

true							|
false							{cout<<"boolean literal"<<endl;}

0x[0-9a-fA-F][0-9a-fA-F]*		{cout<<"Hex literal"<<endl;}
[0-9][0-9]*						{cout<<"Decimal literal"<<endl;}
\"[a-zA-Z0-9]*\"				{cout<<"String literal"<<endl;}
\'[a-zA-Z0-9]\'					{cout<<"Char literal"<<endl;}


[a-zA-Z]+[a-zA-Z0-9]*			{cout<<"identifier"<<endl;}
\{								{cout<<"start block"<<endl;}
\}								{cout<<"end block"<<endl;}

\+								|
-								|
\*								|
\/								|
%								{cout<<"arithmetic operator"<<endl;}

==								|
!=								{cout<<"equality operator"<<endl;}

\<								|
\>								|
\<=								|
\>=								{cout<<"relation operator"<<endl;}

&&								|
\|\|							{cout<<"condition operator"<<endl;}

=								|
\+=								|
-=								{cout<<"assigment operator"<<endl;}
%%

int main(int,char**){
	yylex();
}