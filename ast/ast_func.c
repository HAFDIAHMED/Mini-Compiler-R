#include "ast_func.h"

AST_NODE *new_ast_node(Node_Type type,AST_NODE *left,AST_NODE *right) {
  AST_NODE *node=malloc(sizeof(AST_NODE));

  node->type = type ;
  node->left = left ;
  node->right = right;

  return node;
}
AST_NODE *new_ast_statement_node(AST_Node_Statement **statements, int statement_count , AST_NODE *statement) {
  AST_Node_Statement *node = malloc(sizeof(AST_Node_Statement));
  node->type = STATEMENT_NODE ;
  if(statements==NULL) {
    statements = (AST_Node_Statement **)malloc(sizeof(AST_Node_Statement *));
    statements[0]=(AST_Node_Statement *)statement;
    statement_count = 1;
  }
  else {
    statements = (AST_Node_Statement **)realloc(statements,(statement_count+1)*sizeof(AST_Node_Statement *));
    statements[statement_count]=(AST_Node_Statement *)statement;
    statement_count++;
  }
  node->statements = (AST_NODE**)statements ;
  node->count_statement = statement_count;
  return (AST_NODE*)node ;
}
AST_NODE *new_ast_simple_node(int statement_type) {
	   AST_Node_Simple *node = malloc (sizeof (AST_Node_Simple));
	   node->type = SIMPLE_NODE;
	   node->statement_type = statement_type;
     return (struct AST_NODE *) node;
}
AST_NODE *new_ast_const_node(Type_Sym type , Values val) {
	   AST_Node_Const *node = malloc (sizeof (AST_Node_Const));
	   node->type = CONST_NODE;
	   node->const_type = type;
     node->val = val;
     return (struct AST_NODE *) node;
}
AST_NODE *new_ast_if_node(AST_NODE *condition,AST_NODE *if_branch,AST_NODE *elsif_branch,int count_elseif,AST_NODE *else_branch) {
  AST_Node_If *node=malloc(sizeof(AST_Node_If));

  node->type = IF_NODE ;
  node->condition = condition ;
  node->if_branch = if_branch ;
  node->elsif_branch = elsif_branch ;
  node->count_elseif = count_elseif ;
  node->else_branch = else_branch ;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_elsif_node(AST_NODE *condition,AST_NODE *elsif_branch) {
  AST_Node_Elsif *node=malloc(sizeof(AST_Node_Elsif));

  node->type = ELSIF_NODE ;
  node->condition = condition ;
  node->elsif_branch = elsif_branch ;


  return (AST_NODE *)node;
}
AST_NODE *new_ast_for_node(AST_NODE *for_branch) {
  AST_Node_For *node=malloc(sizeof(AST_Node_For));
  //to continue
  node->type = FOR_NODE ;
  node->for_branch = for_branch;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_while_node(AST_NODE *condition,AST_NODE *while_branch) {
  AST_Node_While *node=malloc(sizeof(AST_Node_While));

  node->type = WHILE_NODE ;
  node->condition = condition ;
  node->while_branch = while_branch ;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_assign_node(List_Symb *entry,AST_NODE *assign_val) {
  AST_Node_Assign *node=malloc(sizeof(AST_Node_Assign));

  node->type = ASSIGN_NODE ;
  node->entry = entry;
  node->assign_val = assign_val ;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_function_call_node(List_Symb *entry,AST_NODE **params,int count_param) {
  AST_Node_Func_Call *node=malloc(sizeof(AST_Node_Func_Call));

  node->type = FUNC_CALL_NODE ;
  node->entry = entry ;
  node->params = params ;
  node->count_param = count_param ;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_arithm_node(Arithm_Op op,AST_NODE *left,AST_NODE *right) {
  AST_Node_Arithm *node=malloc(sizeof(AST_Node_Arithm));

  node->type = ARITHM_NODE ;
  node->op = op ;
  node->left = left ;
  node->right = right;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_bool_node(Bool_Op op,AST_NODE *left,AST_NODE *right) {
  AST_Node_Arithm *node=malloc(sizeof(AST_Node_Arithm));

  node->type = BOOL_NODE ;
  node->op = op ;
  node->left = left ;
  node->right = right;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_rel_node(Rel_Op op,AST_NODE *left,AST_NODE *right) {
  AST_Node_Arithm *node=malloc(sizeof(AST_Node_Arithm));

  node->type = REL_NODE ;
  node->op = op ;
  node->left = left ;
  node->right = right;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_equ_node(Equ_Op op,AST_NODE *left,AST_NODE *right) {
  AST_Node_Arithm *node=malloc(sizeof(AST_Node_Arithm));

  node->type = EQU_NODE ;
  node->op = op ;
  node->left = left ;
  node->right = right;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_func_dec_node(List_Symb *entry,Type_Sym ret_type) {
  AST_Node_Func_Decl *node=malloc(sizeof(AST_Node_Func_Decl));

  node->type = FUNC_DECL_NODE ;
  node->entry = entry;
  node->ret_type = ret_type ;

  return (AST_NODE *)node;
}
AST_NODE *new_ast_return_node(AST_NODE *ret_val,Type_Sym ret_type) {
  AST_Node_Return *node=malloc(sizeof(AST_Node_Return));

  node->type = RETURN_NODE ;
  node->ret_val = ret_val;
  node->ret_type = ret_type ;

  return (AST_NODE *)node;
}
void ast_print_node(AST_NODE *node) {
  AST_Node_For *temp_for;
  AST_Node_If   *temp_if;
  AST_Node_While *temp_while ;
  AST_Node_Elsif  *temp_elsif ;
  AST_Node_Assign  *temp_assign ;
  AST_Node_Arithm  *temp_arithm ;
  AST_Node_Return  *temp_return ;
  AST_Node_Func_Call  *temp_func_call ;
  AST_Node_Func_Decl  *temp_func_dec ;
  AST_Node_Equ    *temp_equ ;
  AST_Node_Bool   *temp_bool ;
  AST_Node_Decl   *temp_decl ;
  AST_Node_Rel    *temp_rel ;
  AST_Node_Simple *temp_simple ;
  AST_Node_Const *temp_const ;
  switch(node->type) {
    case BASIC_NODE :
      printf("basic node");
      break;
    case FOR_NODE :
      temp_for = (AST_Node_For *)node;
      printf("FOR NODE");
      break;
    //
    case IF_NODE :
      temp_if  = (AST_Node_If *)node;
      printf("IF NODE with %d else if node",temp_if->count_elseif);
      break;
    //
    case WHILE_NODE :
      temp_while = (AST_Node_While *)node;
      printf("WHILE_NODE");
      break;
    //
    case ELSIF_NODE :
      temp_elsif = (AST_Node_Elsif *)node;
      printf("ELSIF_NODE");
      break;
    //
    case ASSIGN_NODE :
      temp_assign = (AST_Node_Assign *)node;
      printf("ASSIGN NODE for entry %s",temp_assign->entry->NameSymbol);
      break;
    //
    case ARITHM_NODE :
      temp_arithm = (AST_Node_Arithm *)node;
      printf("arithmetic node for operator %d",temp_arithm->op);
      break;
    //
    case RETURN_NODE :
      temp_return = (AST_Node_Return *)node;
      printf("return node of return type %d",temp_return->ret_type);
      break;
    //
    case FUNC_CALL_NODE :
      temp_func_call = (AST_Node_Func_Call *)node;
      printf("func call node of %s with number of parameter %d",temp_func_call->entry->NameSymbol,temp_func_call->count_param);
      break;
    //
    case FUNC_DECL_NODE :
      temp_func_dec = (AST_Node_Func_Decl *)node;
      printf("function decl node of %s with return type %d",temp_func_dec->entry->NameSymbol,temp_func_dec->ret_type);
      break;
    //
    case EQU_NODE :
      temp_equ = (AST_Node_Equ *)node;
      printf("EQUAL node for operator %d",temp_equ->op);
      break;
    //
    case BOOL_NODE :
      temp_bool = (AST_Node_Bool *)node;
      printf("bool node for operator %d",temp_bool->op);
      break;
    //
    case DECL_NODE :
      temp_decl = (AST_Node_Decl *)node;
      printf("DECL NODE");
      break;
    //
    case REL_NODE :
      temp_rel = (AST_Node_Rel *)node;
      printf("rel node for operator %d",temp_rel->op);
      break;
    //
    case SIMPLE_NODE :
      temp_simple = (AST_Node_Simple *)node;
      printf("simple node for statement type %d",temp_simple->statement_type);
      break;
    //
    case CONST_NODE :
      temp_const = (AST_Node_Const *)node;
      printf("const node for  type %d",temp_const->const_type);
      break;

    default : printf("error");
  }
  printf("\n");
}
void ast_traversal(AST_NODE *node) {
  if(node==NULL) {return;}
  if(node->type == BASIC_NODE || node->type == EQU_NODE || node->type == REL_NODE || node->type == BOOL_NODE || node->type == ARITHM_NODE ){
    ast_traversal(node->left);
    ast_traversal(node->right);
    ast_print_node(node);
  }
  else if(node->type == IF_NODE) {
    AST_Node_If *temp_if = (AST_Node_If *) node;
    ast_traversal(temp_if->condition);
    ast_traversal(temp_if->if_branch);
    for(int i=0;i<temp_if->count_elseif;i++) {
      ast_traversal(&temp_if->condition[i]);
    }
    ast_traversal(temp_if->else_branch);
    ast_print_node(node);
  }
  else if(node->type == ELSIF_NODE) {
    AST_Node_Elsif *temp_elsif = (AST_Node_Elsif *) node;
    ast_traversal(temp_elsif->condition);
    ast_traversal(temp_elsif->elsif_branch);
    ast_print_node(node);
  }
  else if(node->type ==  FOR_NODE) {
    AST_Node_For *temp_for = (AST_Node_For *) node;
    //to continue
    ast_traversal(temp_for->for_branch);
    ast_print_node(node);
  }
  else if(node->type ==  WHILE_NODE) {
    AST_Node_While *temp_while = (AST_Node_While *) node;
    ast_traversal(temp_while->condition);
    ast_traversal(temp_while->while_branch);
    ast_print_node(node);
  }
  else if(node->type ==  ASSIGN_NODE) {
    AST_Node_Assign *temp_assign = (AST_Node_Assign *) node;
    ast_traversal(temp_assign->assign_val);
    ast_print_node(node);
  }
  else if(node->type ==  FUNC_CALL_NODE) {
    AST_Node_Func_Call *temp_func_call = (AST_Node_Func_Call *) node;
    ast_traversal(*temp_func_call->params);
    ast_print_node(node);
  }
  else if(node->type ==  RETURN_NODE) {
    AST_Node_Return *temp_return = (AST_Node_Return *) node;
    ast_traversal(temp_return->ret_val);
    ast_print_node(node);
  }
  else {
    ast_print_node(node);
  }
}
