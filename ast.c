#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

//chang num to svalue
//return *yytext

extern char* yytext;
extern int yylex();
extern FILE* yyin;

void showAst(past node,int nest)
{

	if(node == NULL)
		return;
	int i = 0;
	for(i = 0; i < nest; i ++)
		printf("  ");
	if (!strcmp(node->nodeType, "NUMBER"))
    {
        printf("%s %d\n", node->nodeType, node->num);
    }
    else
    {
        printf("%s  %s\n", node->nodeType, node->svalue);
    }	
	int j = 0;
	while (j < node->pnum)
	{
		showAst(node->mid[j++], nest+1);
	}
}

past newID(int value)
{
	past id = newAstNode();
	id->nodeType = "ID";
	char* s;
	s=(char* )malloc(sizeof(char*)*20);
	strcpy(s,yytext);
 	id->svalue = s;
	return id;
}
past newnum(int value){
	past var = newAstNode();
	var->nodeType = "NUMBER";
	var->svalue = "\0";
	var->num = value;
	return var; 
}

past newassign(int value){
	past assign = newAstNode();
	assign->nodeType = "ASSIGN";
	assign->svalue = "=";
	assign->num = value;
	return assign;	
}

past newCMP(int value)
{
	past cmp = newAstNode();
	cmp->nodeType = "CMP";
	if (!strcmp(yytext, ">="))
	{
		cmp->svalue = ">=";
	}
	else if (!strcmp(yytext, "<="))
	{
		cmp->svalue = "<="; 
	}
	else if (!strcmp(yytext, "=="))
	{
		cmp->svalue = "==";
	}
	else if (!strcmp(yytext, "!="))
	{
		cmp->svalue = "!=";
	}
	else if (!strcmp(yytext, ">"))
	{
		cmp->svalue = ">";
	}
	else if (!strcmp(yytext, "<"))
	{
		cmp->svalue = "<";
	}
	else if (!strcmp(yytext, "|"))
	{
		cmp->svalue = "|";
	}
	else if (!strcmp(yytext, "&"))
	{
		cmp->svalue = "&";
	}
	else if (!strcmp(yytext, "&&"))
	{
		cmp->svalue = "&&";
	}
	else if (!strcmp(yytext, "||"))
	{
		cmp->svalue = "||";
	}
	
	return cmp;
}

past newKeyword(int value)
{
	past key = newAstNode();
	key->nodeType = "KEYWORD";
	if (!strcmp(yytext, "print"))
	{
		key->svalue = "print";
	}
	else if (!strcmp(yytext, "if"))
	{
		key->svalue = "if";
	}
	else if (!strcmp(yytext, "else"))
	{
		key->svalue = "else";
	}
	else if (!strcmp(yytext, "while"))
	{
		key->svalue = "while";
	}
	else if (!strcmp(yytext, "return"))
	{
		key->svalue = "return";
	}
	else if (!strcmp(yytext, "scan"))
	{
		key->svalue = "scan";
	}
	else if (!strcmp(yytext, "string")){
		key->svalue = "string";
	}
	else
	{
		printf("error!\n");exit(0);
	}
	return key;
}

past newAstNode()
{
	past node = (past)malloc(sizeof(ast));
	if(node == NULL)
	{
		printf("run out of memory.\n");
		exit(0);
	}
	memset(node, 0, sizeof(ast));
	return node;
}

past newprogram(past a){
	past var = newAstNode();
	var->nodeType = "program";
	var->svalue = "\0";
	var->mid[0] = a;
	var->pnum = 1;
	return var;
}

past newprograms(past a,past b){
	past var = newAstNode();
	var->nodeType = "program";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1] = b;
	var->pnum = 2;
	return var;
}
past newexternal_declaration(past a){
	past var = newAstNode();
	var->nodeType = "external_declaration";
	var->svalue = "\0";
	var->mid[0] = a;
	var->pnum = 1;
	return var;
} 

past newfunction_definition(past a,past b,past c){
	past var = newAstNode();
	var->nodeType = "function_definition";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1]=b;
	var->mid[2]=c;
	var->pnum = 3;
	return var;	
}

past newdeclaration(past a,past b){
	past var = newAstNode();
	var->nodeType = "declaration";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1]=b;
	var->pnum = 2;
	return var;	
}



past newinit_declarator_list(past a,past b){
	past var = newAstNode();
	var->nodeType = "init_declarator_list";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1]=b;
	var->pnum = 2;
	return var;		
}

past newinit_declarator(past a,past b){
	past var = newAstNode();
	var->nodeType = "init_declarator";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1]=b;
	var->pnum = 2;
	return var;		
}

past newintstr_list(past a,past b){
	past var = newAstNode();
	var->nodeType = "intstr_list";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1]=b;
	var->pnum = 2;
	return var;		
}

past newinitializer(int value){
	past var = newAstNode();
	var->nodeType ="initializer";
	char* s;
	s=(char* )malloc(sizeof(char*)*100);
	strcpy(s,yytext);
	var->svalue = s;
	return var;
}

past newdeclarator(past a){
	past var = newAstNode();
	var->nodeType = "declarator";
	var->svalue = "\0";
	var->mid[0] = a;
	var->pnum = 1;
	return var;		
}

past newdirect_declarator(past a,past b){
	past var = newAstNode();
	var->nodeType = "direct_declarator";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1] = b;
	var->pnum = 2;
	return var;		
}

past newparameter_list(past a,past b){
	past var = newAstNode();
	var->nodeType = "parameter_list";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1] = b;
	var->pnum = 2;
	return var;			
}

past newparameter(past a,past b){
	past var = newAstNode();
	var->nodeType = "parameter_list";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1] = b;
	var->pnum = 2;
	return var;			
}

past newtype(int value){
	past var = newAstNode();
	var->nodeType = "type";//?
	var->svalue = "\0";

	return var;			
}

past newstatement(past a){
	past var = newAstNode();
	var->nodeType = "statement";
	var->svalue = "\0";
	var->mid[0]=a;
	var->pnum = 1;
	return var;			
}

past newcompound_statement(int num,past a,past b,past c){
	past var = newAstNode();
	var->nodeType = "compound_statement";
	var->svalue = "\0";
	switch(num){

		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->mid[2]=c;
				var->pnum = 3;}break;
		case 1:{var->mid[0]=a;
				var->mid[1]=b;
				var->mid[2]=c;
				var->pnum = 3;			
				}break;

		default: printf("error!\n");exit(0);break;
	}
	return var;	
}

past newbegin_scope(){
	past var = newAstNode();
	var->nodeType = "begin_scope";
	var->svalue = "{";
	return var;		
}


past newend_scope(){
	past var = newAstNode();
	var->nodeType = "end_scope";
	var->svalue = "}";
	return var;		
}

past newstatement_list(past a){
	past var = newAstNode();
	var->nodeType = "statement_list";
	var->svalue = "\0";
	var->mid[0] = a;
	var->pnum = 1;
	return var;		
}

past newexpression_statement(past a){
	past var = newAstNode();
	var->nodeType = "expression_statement";
	var->svalue = "\0";
	var->mid[0] = a;
	var->pnum = 1;
	return var;		
}

past newselection_statement(int num,past a,past b,past c,past d,past e){
	past var = newAstNode();
	var->nodeType = "selection_statement";
	var->svalue = "\0";
	switch(num){

		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->mid[2]=c;
				var->pnum = 3;}break;
		case 1:{var->mid[0]=a;
				var->mid[1]=b;
				var->mid[2]=c;
				var->mid[3]=d;
				var->mid[4]=e;				
				var->pnum = 5;}break;

		default: printf("error!\n");exit(0);break;
	}
	return var;	
}


past newiteration_statement(past a,past b,past c){
	past var = newAstNode();
	var->nodeType = "iteration_statement";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1] = b;
 	var->mid[2] = c;
	var->pnum = 3;
	return var;
}

past newjump_statement(int num,past a,past b){
	past var = newAstNode();
	var->nodeType = "jump_statement";
	var->svalue = "\0";
	switch(num){

		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 1:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;

		default: printf("error!\n");exit(0);break;
	}
	return var;	
}

past newprint_statement(int value,past a,past b){
	past var = newAstNode();
	var->nodeType = "print_statement";
	var->svalue = "\0";
	switch(value){

		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 1:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;
				var->svalue="PRINT";// can CMP show  concretely?
				}break;

		default: printf("error!\n");exit(0);break;
	}
	return var;
}

past newscan_statement(past a,past b){
	past var = newAstNode();
	var->nodeType = "scan_statement";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1]= b; 
	var->pnum = 2;//problem of defining grammar 
	return var;
}

past newexpr(past a,past b){
	past var = newAstNode();
	var->nodeType = "expr";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1]= b;
	var->pnum = 2; 
	return var;
}

past newassign_expr(int value,past a,past b,past c){
	past var = newAstNode();
	var->nodeType = "assign_expr";
	var->svalue = "\0";
	switch(value){
		
		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 1:{var->mid[0]=a;//whether think assign as a node?
				var->mid[1]=b;
				var->mid[2]= c;
				var->pnum = 3;}break;
		case 2:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;
				}break;
		case 3:{var->mid[0]=a;
				var->mid[1]=b;
				var->mid[2]=c;
				var->pnum = 3;}break;
		default: printf("error!\n");exit(0);break;
	}
	return var;
	
}

past cmp_expr (int value,past a,past b){
	past var = newAstNode();
	var->nodeType = "cmp_expr";
	var->svalue = "\0";
	switch(value){

		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 1:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;

		default: printf("error!\n");exit(0);break;
	}
	return var;
}

past add_expr(int value,past a,past b){
	past var = newAstNode();
	var->nodeType = "add_expr";
	var->svalue = "\0";
	var->mid[0]=a;
	var->mid[1]=b;
	var->pnum = 2;
	return var;
}


past newmul_expr(int value,past a,past b){
	past var = newAstNode();
	var->nodeType = "mul_expr";
	var->svalue = "\0";
	switch(value){
		
		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 1:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 2:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;
				var->svalue= "/";}break;
		case 3:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;
				var->svalue= "%";}break;
		case 4:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;

		default: printf("error!\n");exit(0);break;
	}
	return var;
	
}

past newprimary_expr(int value, past a,past b)
{
	past var = newAstNode();
	var->nodeType = "primary_expr";
	var->svalue = "\0";
	switch(value){

		case 0:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 1:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 2:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 3:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 4:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		case 5:{var->mid[0]=a;
				var->mid[1]=b;
				var->pnum = 2;}break;
		default: printf("error!\n");break;
	}
	return var;
}

past newexpr_list(past a,past b){
	past var = newAstNode();
	var->nodeType = "expr_list";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1] = b;
	var->pnum = 2;
	return var;
}

past newexpr_lists( past a,past b){
	past var = newAstNode();
	var->nodeType = "expr_list";
	var->svalue = "\0";
	var->mid[0] = a;
	var->mid[1] = b;
	var->pnum = 2;
	return var;
}



past newid_list(past a){
	past var = newAstNode();
	var->nodeType = "num";
	var->svalue = "\0";
	return var;//have problem
} 

past newid_lists(past a,past b){
	past var = newAstNode();
	var->nodeType = "id_list";
	var->svalue = "\0";
	//?use for what
	var->mid[0] = a;
	var->mid[1] = b;
	var->pnum = 2;
	var->svalue= "\0";
	return var;	
}
