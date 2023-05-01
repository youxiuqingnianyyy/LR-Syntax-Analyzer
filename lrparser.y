%{

#include "ast.h"

#include <stdio.h>

int yylex(void);
void yyerror(char *);



%}

%union{
	int			ivalue;

	past		ast;
};

%token <ivalue>  NUMBER INT STR VOID ID STRING IF ELSE WHILE RETURN SCAN PRINT CMP ASSIGN
%type  <ast>	cmp id if else return print while scan program external_declaration function_definition declaration type declarator compound_statement init_declarator_list init_declarator add_expr intstr_list initializer direct_declarator parameter_list parameter statement expression_statement selection_statement iteration_statement jump_statement print_statement scan_statement begin_scope end_scope statement_list expr expr_list id_list assign_expr mul_expr cmp_expr primary_expr  assign
%expect 1

%%

  program: external_declaration 			 {showAst($1,0);}
            | program external_declaration     {showAst($2,0); } 
			;
 external_declaration: function_definition	{$$=newexternal_declaration($1);}
                     | declaration	  {$$=newexternal_declaration($1);}
			;
 function_definition: type declarator compound_statement
 									{$$=newfunction_definition($1,$2,$3);}
;
 declaration: type init_declarator_list ';'		{$$=newdeclaration($1,$2);}
;
 init_declarator_list: init_declarator			{$$=newinit_declarator_list($1,NULL);} 
         | init_declarator_list ',' init_declarator {$$=newinit_declarator_list($1,$3);}
;
 init_declarator: declarator				{$$=newinit_declarator($1,NULL);}
               | declarator '=' add_expr	{$$=newinit_declarator($1,$3);}
               | declarator '=' '{' intstr_list '}'	{$$=newinit_declarator($1,$4);}
			;

intstr_list: initializer						{$$=newintstr_list($1,NULL);}
           | intstr_list ',' initializer			{$$=newintstr_list($1,$3);}
			;
initializer: NUMBER							{$$=newnum($1);}
      | STRING								{$$=newinitializer($1);}
	  ;
 declarator: direct_declarator					{$$=newdeclarator($1);}
;
 direct_declarator: id							{$$=newdirect_declarator($1,NULL);}
          | direct_declarator '(' parameter_list ')'	{$$=newdirect_declarator($1,$3);}
                    | direct_declarator '(' ')'		{$$=newdirect_declarator($1,NULL);}
                    | id '[' expr ']'			{$$=newdirect_declarator($1,$3);}
                  | id '[' ']'					{$$=newdirect_declarator($1,NULL);}
;
    parameter_list: parameter				  	 {$$=newparameter_list($1,NULL);}
              | parameter_list ',' parameter	    {$$=newparameter_list($1,$3);}
;    
    parameter: type id								 {$$=newparameter($1,$2);}
;
 type: INT										   {$$=newtype($1);}
      | STR										{$$=newtype($1);}
       | VOID									{$$=newtype($1);}
;
 statement: compound_statement				{$$=newstatement($1);}
           | expression_statement						{$$=newstatement($1);}
           | selection_statement						{$$=newstatement($1);}
          | iteration_statement							{$$=newstatement($1);}
            | jump_statement							{$$=newstatement($1);}
         | print_statement								{$$=newstatement($1);}
         | scan_statement								{$$=newstatement($1);}
           | declaration								{$$=newstatement($1);}
;
    compound_statement: begin_scope end_scope			{$$=newcompound_statement(0,$1,$2,NULL);};
                   | begin_scope statement_list end_scope	{$$=newcompound_statement(1,$1,$2,$3);}
    ;
 begin_scope: '{'					{$$=newbegin_scope();}
	;
 end_scope: '}'							{$$=newend_scope();}
	;
   statement_list: statement							{$$=newstatement_list($1);}
                  | statement_list statement			{$$=newstatement_list($1);}
	;
  expression_statement: ';'						{$$=NULL;}		
                    | expr ';'				{$$=newexpression_statement($1);}		;

selection_statement: if '(' expr ')' statement                                                                                                                                                                   {$$=newselection_statement(0,$1,$3,$5,NULL,NULL);}
    | if '(' expr ')' statement else statement   {$$=newselection_statement(1,$1,$3,$5,$6,$7);}
    ;
  iteration_statement: while '(' expr ')' statement  {$$=newiteration_statement($1,$3,$5);}
	;
   jump_statement: return ';'				{$$=newjump_statement(0,$1,NULL);}
                  | return expr ';'		        {$$=newjump_statement(1,$1,$2);}
	;
   print_statement: print ';'				     {$$=newprint_statement(0,$1,NULL);}
                  | print expr_list ';'		     {$$=newprint_statement(1,$1,$2);}	
	;
    scan_statement: scan id_list ';'			{$$=newscan_statement($1,$2);}
	;
   expr: assign_expr						{$$=newexpr($1,NULL);}
	;
    assign_expr: cmp_expr					{$$=newassign_expr(0,$1,NULL,NULL);}
             | id assign assign_expr		  {$$=newassign_expr(1,$1,$2,$3);}
              | id '=' assign_expr			     {$$=newassign_expr(2,$1,$3,NULL);}
            | id '[' expr ']' '=' assign_expr		{$$=newassign_expr(3,$1,$3,$6);}
    ;
    cmp_expr: add_expr						{$$=cmp_expr(0,$1,NULL);}
          | cmp_expr cmp add_expr			{$$=cmp_expr(1,$1,$3);}
    ;
    add_expr: mul_expr						{$$=add_expr(0,$1,NULL);}
            | add_expr '+' mul_expr			    {$$=add_expr(0,$1,$3);}
         | add_expr '-' mul_expr			    {$$=add_expr(0L,$1,$3);}
    ;
    mul_expr: primary_expr					{$$=newmul_expr(0,$1,NULL);}
           | mul_expr '*' primary_expr	    	{$$=newmul_expr(1,$1,$3);}
          | mul_expr '/' primary_expr		     {$$=newmul_expr(2,$1,$3);}
           | mul_expr '%' primary_expr		   {$$=newmul_expr(3,$1,$3);}
            | '-' primary_expr				{$$=newmul_expr(4,NULL,$2);}
    ;
    primary_expr: id '(' expr_list ')' 	{$$=newprimary_expr(0,$1,$3);}
                | id '(' ')'	{$$=newprimary_expr(1,$1,NULL);}
              | '(' expr ')'	{$$=newprimary_expr(2,$2,NULL);}
               | id			{$$=newprimary_expr(3,$1,NULL);}
               | initializer	{$$=newprimary_expr(4,$1,NULL);}
             | id '[' expr ']'	     {$$=newprimary_expr(5,$1,$3);}
 	;
 expr_list: expr				{$$=newexpr_list($1,NULL);}
             | expr_list ',' expr	{$$=newexpr_lists($1,$3);}
	;
    id_list: id			    {$$=newid_list($1);}
           | id_list ',' id	{$$=newid_lists($1,$3);}
	;

id: ID     {$$=newID($1);}
;
cmp: CMP   {$$=newCMP($1);}
;

if: IF     {$$=newKeyword($1);}
;
else: ELSE     {$$=newKeyword($1);}
;
return: RETURN     {$$=newKeyword($1);}
;
print: PRINT     {$$=newKeyword($1);}
;
while: WHILE     {$$=newKeyword($1);}
;
scan: SCAN     {$$=newKeyword($1);}
;

assign:  ASSIGN     {$$=newKeyword($1);}
;







%%

