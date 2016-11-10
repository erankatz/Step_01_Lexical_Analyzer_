%{
#include <string.h>
#include <math.h>
#include "../../HEADER_FILES/util.h"
#include "../../HEADER_FILES/errormsg.h"
#include "../../BISON/BISON_01_For_First_Exercise/tiger.tab.h"
int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

%}

%%
" "																	{adjust(); continue;}
\n																	{adjust(); EM_newline(); return NEWLINE;}
","																	{adjust(); return COMMA;}
";"																	{adjust(); return SEMICOLON;}
for																	{adjust(); return FOR;}
while																{adjust(); return WHILE;}
"("																	{adjust(); return LPAREN;}
")"																	{adjust(); return RPAREN;}
"["																	{adjust(); return LBRACK;}
"]"																	{adjust(); return RBRACK;}
"{"																	{adjust(); return LBRACE;}
"}"																	{adjust(); return RBRACE;}
"+"																	{adjust(); return PLUS;}
"-"																	{adjust(); return MINUS;}
"*"																	{adjust(); return TIMES;}
"/"																	{adjust(); return DIVIDE;}
"<"																	{adjust(); return LT;}
"="																	{adjust(); return EQ;}
":="																{adjust(); return ASSIGN;}
-+>																	{adjust(); return ARROW;}
[<]-{3,}>																{adjust(); return REPLACEARROW;}
R[0-9]+																{adjust(); yylval.sval=String(yytext + 1); yylval.ival=atoi(yylval.sval); return ROWID;}
-{0,1}[0-9]+\/[0-9]+												{adjust(); yylval.sval=String(yytext); return FRACTION;}
-{0,1}[0-9]+[0-9]*													{adjust(); yylval.ival=atoi(yytext); return INT;}
[-+]?([0-9]*\.[0-9]+|[0-9]+)										{adjust(); yylval.fval=atof(yytext); return FLOAT;}
[a-zA-Z]+[0-9a-zA-Z]*												{adjust(); yylval.sval=String(yytext); return ID;}
@																	{adjust(); EM_error(EM_tokPos,"illegal token");}
