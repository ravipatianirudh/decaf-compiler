%{
#include <iostream>
#include <cstdio>
#include "decaf.tab.h"
#define YY_DECL extern "C" int yylex()

using namespace std;

%}

%%
[ \t\n]+							;
\,									{return COMMA;}
\;									{return SEMI_COLON;}
class								{return CLASS;}
callout								{return CALLOUT;}
if									{return IF;}
for									{return FOR;}
return								{return RETURN;}
break								{return BREAK;}
continue							{return CONTINUE;}
void								{return VOID;}
int									|
boolean								{ yylval.type_val = strdup(yytext);return TYPE;}

true								{yylval.boolean_val = 1;return BOOLEAN_LITERAL;}
false								{yylval.boolean_val = 0;return BOOLEAN_LITERAL;}

"\'\\n\'"|"\'\\t\'"|"\'\\\\\'"|"\'\\\'\'"|"\'\\\"\'"|"\'"."\'"	{yylval.string_literal = strdup(yytext);return STRING_LITERAL;}
\"(\\.|[^\\"])*\"					{yylval.char_literal = strdup(yytext);return CHAR_LITERAL;}

[a-zA-Z][0-9a-zA-Z]*				{yylval.identifier_val = strdup(yytext);return IDENTIFIER;}


0x[0-9a-fA-F][0-9a-fA-F]*			{yylval.hex_literal = atoi(yytext);return HEX_LITERAL;}
[0-9][0-9]*							{yylval.decimal_literal = atoi(yytext);return DECIMAL_LITERAL;}

\{									{return START_BLOCK;}
\}									{return CLOSE_BLOCK;}
\(									{return OPEN_PARENTHESIS;}
\)									{return CLOSE_PARENTHESIS;}
\[									{return OPEN_SQUARE_BRACKET;}
\]									{return CLOSE_SQUARE_BRACKET;}

\<									|
>									|
\<=									|
>=									{yylval.relational_operator_val = strdup(yytext);return RELATIONAL_OP;}

\-									{yylval.op_minus_val = strdup(yytext);return OP_MINUS;}
!									{yylval.negation_val = strdup(yytext);return NEGATION;}

\+									|
\*									|
\/									|
%									{yylval.arithmetic_operator_val = strdup(yytext);return ARITHMETIC_OP;}

&&									|
\|\|								{yylval.conditional_operator_val  = strdup(yytext);return CONDITIONAL_OP;}

\=									|
\+=									|
-=									{yylval.assignment_operator_val = strdup(yytext);return ASSIGNMENT_OP;}

\=\=								|
!=									{yylval.equality_operator_val = strdup(yytext);return EQUALITY_OP;}
.									{printf("%s",yytext);cout<<endl<<"ERROR"<<endl;}
%%