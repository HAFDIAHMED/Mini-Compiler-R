#include "ast_dec.h"

AST_NODE *new_ast_node(Node_Type type,AST_NODE *left,AST_NODE *right) ;
AST_NODE *new_ast_simple_node(int statement_type) ;
AST_NODE *new_ast_const_node(Type_Sym type , Values val) ;
AST_NODE *new_ast_statement_node(AST_Node_Statement **statements, int statement_count , AST_NODE *statement) ;
AST_NODE *new_ast_if_node(AST_NODE *condition,AST_NODE *if_branch,AST_NODE *elsif_branch,int count_elseif,AST_NODE *else_branch) ;
AST_NODE *new_ast_elsif_node(AST_NODE *condition,AST_NODE *elsif_branch) ;
AST_NODE *new_ast_for_node(AST_NODE *for_branch) ;
AST_NODE *new_ast_while_node(AST_NODE *condition,AST_NODE *while_branch) ;
AST_NODE *new_ast_assign_node(List_Symb *entry,AST_NODE *assign_val) ;
AST_NODE *new_ast_function_call_node(List_Symb *entry,AST_NODE **params,int count_param) ;
AST_NODE *new_ast_arithm_node(Arithm_Op op,AST_NODE *left,AST_NODE *right) ;
AST_NODE *new_ast_bool_node(Bool_Op op,AST_NODE *left,AST_NODE *right) ;
AST_NODE *new_ast_rel_node(Rel_Op op,AST_NODE *left,AST_NODE *right) ;
AST_NODE *new_ast_equ_node(Equ_Op op,AST_NODE *left,AST_NODE *right) ;
AST_NODE *new_ast_func_dec_node(List_Symb *entry,Type_Sym ret_type) ;
AST_NODE *new_ast_return_node(AST_NODE *ret_val,Type_Sym ret_type) ;
void ast_print_node(AST_NODE *node) ;
void ast_traversal(AST_NODE *node) ;
