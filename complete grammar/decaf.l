%{
#include <iostream>
#include <cstdio>
#include "ast.h"
#include "decaf.tab.h"

#define YY_DECL extern "C" int yylex()
using namespace std;
extern FILE *flex_output;
%}

%%
[ \t\n]+							;


\-									{yylval.op_minus_val = strdup(yytext);return OP_MINUS;}
!									{yylval.negation_val = strdup(yytext);return NEGATION;}

\+									{yylval.op_plus_val = strdup(yytext);return OP_PLUS;}
\*									|
\/									|
%									{yylval.arithmetic_operator_val = strdup(yytext);return ARITHMETIC_OP;}

\<									|
>									|
\<=									|
>=									{yylval.relational_operator_val = strdup(yytext);return RELATIONAL_OP;}

\=\=								|
!=									|
&&									|
\|\|									{yylval.conditional_operator_val  = strdup(yytext);return CONDITIONAL_OP;}
	
\=									|
\+=									|
-=									{yylval.assignment_operator_val = strdup(yytext);return ASSIGNMENT_OP;}

class									{fputs("CLASS\n",flex_output);return CLASS;}
callout									{fputs("CALLOUT\n",flex_output);return CALLOUT;}
if									{fputs("IF",flex_output);return IF;}
for									{fputs("FALSE",flex_output);return FOR;}

return									{return RETURN;}
break									{fputs("BREAK",flex_output);return BREAK;}
continue								{fputs("CONTINUE",flex_output);return CONTINUE;}
void									{return VOID;}
int										{fputs("INT_DECLARATION\n",flex_output); yylval.type_val = strdup(yytext); return TYPE;}
boolean									{fputs("BOOLEAN_DECLARATION\n",flex_output); yylval.type_val = strdup(yytext); return TYPE;}

true									{fputs("BOOLEAN: ",flex_output);fputs(strdup(yytext),flex_output);fputs("\n",flex_output);yylval.boolean_val = 1;return BOOLEAN_LITERAL;}
false									{fputs("BOOLEAN: ",flex_output);fputs(strdup(yytext),flex_output);fputs("\n",flex_output);yylval.boolean_val = 0;return BOOLEAN_LITERAL;}

"//".*"\n" { }

[0-9][0-9]*								{fputs("INT: ",flex_output);fputs(strdup(yytext),flex_output);fputs("\n",flex_output);yylval.decimal_literal = atoi(yytext);return DECIMAL_LITERAL;}

0x[0-9a-fA-F][0-9a-fA-F]*						{fputs("HEX: ",flex_output);fputs(strdup(yytext),flex_output);fputs("\n",flex_output);yylval.hex_literal = atoi(yytext);return HEX_LITERAL;}

[a-zA-Z][0-9a-zA-Z]*							{fputs("ID: ",flex_output);fputs(strdup(yytext),flex_output);fputs("\n",flex_output);yylval.identifier_val = strdup(yytext);return IDENTIFIER;}
\"(\\.|[^\\"])*\" 							{yylval.string_literal = strdup(yytext);fputs("STRING: ",flex_output);fputs(strdup(yytext),flex_output);fputs("\n",flex_output); return STRING_LITERAL;}

"\'\\n\'"|"\'\\t\'"|"\'\\\\\'"|"\'\\\'\'"|"\'\\\"\'"|"\'"."\'"      	{  yylval.char_literal = strdup(yytext);fputs("CHAR: ",flex_output);fputs(strdup(yytext),flex_output);fputs("\n",flex_output);return CHAR_LITERAL; }


\;									{return SEMI_COLON;}
\,									{return COMMA;}
\{									{return START_BLOCK;}
\}									{return CLOSE_BLOCK;}
\(									{return OPEN_PARENTHESIS;}
\)									{return CLOSE_PARENTHESIS;}
\[									{return OPEN_SQUARE_BRACKET;}
\]									{return CLOSE_SQUARE_BRACKET;}
.									{printf("%s",yytext);cout<<endl<<"error"<<endl;}
%%
