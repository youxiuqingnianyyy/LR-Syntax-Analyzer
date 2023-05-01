
#include<stdlib.h>
#include<stdio.h>
extern FILE* yyin;
void yyparse();
void yyerror(char *s)
{
	printf("%s\n", s);
}

int main()
{
	
	yyin = fopen("test.c","r");
	yyparse();
	

	return 0;
}


