


#include <stdio.h>
typedef struct _ast ast;
typedef struct _ast *past;
struct _ast{
	int num;
	char* svalue;
	char* nodeType;
	past left;
	past right;
	past mid[100];
	int pnum;
	
};

past newprogram(past a);
past newprograms(past a,past b);
past newExpr(int oper, past left,past right);
void showAst(past node,int nest);
past newID(int value);
past newassign(int value);
past newCMP(int value);
past newKeyword(int value);
past newAstNode();
past newnum(int value);
past newexternal_declaration(past a);
past newfunction_definition(past a,past b,past c);
past newdeclaration(past a,past b);
past newinit_declarator_list(past a,past b);
past newinit_declarator(past a,past b);
past newintstr_list(past a,past b);
past newinitializer(int value);
past newdeclarator(past a);
past newdirect_declarator(past a,past b);
past newparameter_list(past a,past b);
past newparameter(past a,past b);
past newtype(int value);
past newstatement(past a);
past newcompound_statement(int value,past a,past b,past c);
past newbegin_scope();
past newend_scope();
past newstatement_list(past a);
past newexpression_statement(past a);
past newselection_statement(int value,past a,past b,past c,past d,past e);
past newiteration_statement(past a,past b,past c);
past newjump_statement(int value,past a,past b);
past newprint_statement(int value,past a,past b);
past newscan_statement(past a,past b);
past newexpr(past a,past b);
past newassign_expr(int value,past a,past b,past c);
past cmp_expr (int value,past a,past b);
past add_expr(int value,past a,past b);
past newmul_expr(int value,past a,past b);
past newprimary_expr(int value, past a,past b);
past newexpr_list(past a,past b);
past newexpr_lists( past a,past b);
past newid_list(past a);
past newid_lists(past a,past b);
past newnum(int value);



