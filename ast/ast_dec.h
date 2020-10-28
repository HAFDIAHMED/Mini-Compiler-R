#include "../symbole_table/symb_table_dec.h"
typedef enum Node_Type {
  STATEMENT_NODE,
  BASIC_NODE,
  SIMPLE_NODE,
  CONST_NODE,
  DECL_NODE,
  //
  //
  IF_NODE,
  ELSIF_NODE,
  FOR_NODE,
  WHILE_NODE,
  ASSIGN_NODE,
  FUNC_CALL_NODE,
  //
  ARITHM_NODE,
  BOOL_NODE,
  REL_NODE,
  EQU_NODE,
  //
  FUNC_DECL_NODE,
  RETURN_NODE,

} Node_Type;
typedef enum Arithm_Op {
  ADD ,
  SUB ,
  MUL ,
  DIV ,
  POW ,
  DIV_INT ,
}Arithm_Op;
typedef enum Bool_Op {
  OR ,
  OR_WISE,
  AND ,
  AND_WISE,
  NOT
}Bool_Op;
typedef enum Rel_Op {
  GREATER ,
  LESS ,
  GREATER_EQUAL ,
  LESS_EQUAL
}Rel_Op;
typedef enum Equ_Op {
  EQUAL ,
  NOT_EQUAL
}Equ_Op ;
//
typedef struct AST_NODE {
  Node_Type type ;
  struct AST_NODE *left ;
  struct AST_NODE *right ;
}AST_NODE;
//
typedef struct AST_Node_Const{
  Node_Type type ;
  Type_Sym const_type;
  Values val;
}AST_Node_Const;
//
typedef struct AST_Node_Statement{
  Node_Type type ;
  AST_NODE **statements ;
  int count_statement;
}AST_Node_Statement;
//
typedef struct AST_Node_Simple {
  Node_Type type ;
  int statement_type ;
}AST_Node_Simple;
//
typedef struct AST_Node_Decl {
  Node_Type type ;
  Type_Sym data_type;
  List_Symb **names;
  int count_names;
}AST_Node_Decl;
///
typedef struct AST_Node_If {
  Node_Type type ;
  AST_NODE *condition;
  //
  AST_NODE *if_branch;
  //
  AST_NODE *elsif_branch;
  int count_elseif;
  //
  AST_NODE *else_branch;
}AST_Node_If;
///
typedef struct AST_Node_Elsif {
  Node_Type type ;
  AST_NODE *condition;
  AST_NODE *elsif_branch;
}AST_Node_Elsif;
///
typedef struct AST_Node_For {
  Node_Type type ;
  //to continue
  AST_NODE *for_branch;
}AST_Node_For;
///
typedef struct AST_Node_While {
  Node_Type type ;
  AST_NODE *condition;
  AST_NODE *while_branch;
}AST_Node_While;
///
typedef struct AST_Node_Assign {
  Node_Type type ;
  List_Symb *entry;
  AST_NODE *assign_val;
}AST_Node_Assign;
///
typedef struct AST_Node_Func_Call {
  Node_Type type ;
  List_Symb *entry;
  AST_NODE **params;
  int count_param ;
}AST_Node_Func_Call;
//
typedef struct AST_Node_Arithm {
  Node_Type type ;
  Arithm_Op op;
  AST_NODE *left;
  AST_NODE *right;
}AST_Node_Arithm;
///
typedef struct AST_Node_Bool {
  Node_Type type ;
  Bool_Op op;
  AST_NODE *left;
  AST_NODE *right;
}AST_Node_Bool;
///
typedef struct AST_Node_Rel {
  Node_Type type ;
  Rel_Op op;
  AST_NODE *left;
  AST_NODE *right;
}AST_Node_Rel;
///
typedef struct AST_Node_Equ {
  Node_Type type ;
  Equ_Op op;
  AST_NODE *left;
  AST_NODE *right;
}AST_Node_Equ;
//
typedef struct AST_Node_Func_Decl {
  Node_Type type ;
  Type_Sym ret_type ;
  List_Symb *entry;
}AST_Node_Func_Decl;
///
typedef struct AST_Node_Return {
  Node_Type type ;
  Type_Sym ret_type ;
  AST_NODE *ret_val ;
}AST_Node_Return;
