%{
#include <iostream>
#include <cstdio>
#define YY_DECL extern "C" int yylex()

using namespace std;

%}

%%
[\t\n]							;
class								{return CLASS;}
void								{return VOID;}
int								{return INT_TYPE;}
boolean								{return BOOL_TYPE}
if								{return IF;}
else								{return ELSE;}
for								{return FOR;}
return								{return RETURN;}
break								{return BREAK;}
continue							{return CONTINUE;}
callout								{return CLLOUT_FUNCTION;}
true								|
false								{cout<<"BOOL_CONSTANT"<<endl;}
DIGIT [0-9]
HEXADECIMAL_DIGIT[0-9a-fA-F]
ALPHA [a-zA-Z_]

\"(\\.|[^\\"])*\" { 
    return STRING_LITERAL; 
}
"\'\\n\'"|"\'\\t\'"|"\'\\\\\'"|"\'\\\'\'"|"\'\\\"\'"|"\'"."\'" {
    return CHAR_LITERAL;
}

DIGIT+
{
	int a = atoi(yytext);
	if(a >= -21483648 && a <= 21483647)
	return INT_LITERAL
	else
	{
	printf("unsuccessful\n");
	}
}

"0x"{HEXADECIMAL_DIGIT}+|"0X"{HEXADECIMAL_DIGIT}+ {
    unsigned int a;
    sscanf(yytext, "%x", &a);
    if(a <= 21483647){
        return INT_LITERAL; 
    } else {
        printf("unsuccessful\n");
    }
}

\"[a-zA-Z0-9]*\"						{cout<<"String literal"<<endl;}
\'[a-zA-Z0-9]\'							{cout<<"Char literal"<<endl;}
{ALPHA}+[ALPHA0-9]*						{return IDENTIFIER;}

\[								{return START_SQUARE_BRACKET;}
\]								{return CLOSE_SQUARE_BRACKET;}

"-"								{return OP_MINUS;}

"!"								{return NOT_OP;}

"+"								|
"*"								|
"/"								|
"%"								{return ARITH_OP;}

">"								|
"<"								|
">="								|
"<="								{return REL_OP;}

"!="								|
"=="								{return EQ_OP;}

"&&"								|
"||"								{return COND_OP;}

"="								|
"+="								|
"-="								{return ASSIGN_OP;}

; 								{return SEMI_COLON;}
, 								{return COMMA;}
\{								{return START_BLOCK;}
\}								{return CLOSE_BLOCK;}
\(								{return START_PARANTHESIS;}
\)								{return CLOSE_PARANTHESIS;}

%%

int main(int,char**){
	yylex();
}
