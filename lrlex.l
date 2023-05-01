%{
#include <stdlib.h>
#include "ast.h"
#include "lrparser.tab.h"

void yyerror(char *);
%}

letter  [a-zA-Z]
digit   [0-9]
NUMBER  [1-9]+{digit}*|[0]
ecomment    "/*"([*]*(([^*/])+([/])*)*)*"*/"
tcomment    "//"+(.)*
SYMBOL      "+"|"-"|"*"|"/"|"%"|"("|")"|"{"|"}"|"["|"]"|","|";"|"="
ASSIGN      "+="|"-="|"/="|"*="|"%="
CMP         ">="|"<="|"=="|"!="|">"|"<"|"|"|"&"|"&&"|"||"
INT	"int"
STR	"str"
VOID	"void"
IF	"if"
ELSE	"else"
WHILE	"while"
RETURN	"return"
SCAN	"scan"
PRINT	"print"
STRING	 \"[^\n"]+\"
ID          [a-zA-Z_]?[a-zA-Z_0-9]*

%%
{tcomment}
{ecomment}
{NUMBER}	{yylval.ivalue = atoi(yytext); return NUMBER;}
{SYMBOL}	{return yytext[0];}
{ASSIGN}	{return ASSIGN;}
{CMP}	{return CMP;}
{STRING}	{return STRING;}
{INT}	{return INT;}
{STR}	{return STR;}
{VOID}	{return VOID;}
{IF}	{return IF;}
{ELSE}	{return ELSE;}
{WHILE}	{return WHILE;}
{RETURN}	{return RETURN;}
{SCAN}	{return SCAN;}
{PRINT}	{return PRINT;}
{ID}	{return ID;}
[ \n\t]	{ /* ignore whitespace */}
<<EOF>>	{return EOF;}
. 	{yyerror("invalid character");}

%%
int yywrap(void)
{
	return 1;
}
