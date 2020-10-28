#include "ast_func.h"
int main() {
   Values val1,val2 ;
   val1.IntValue = 10 ;
   val2.IntValue = 20 ;
   AST_NODE *const_node1 = new_ast_const_node(NUM, val1);
   AST_NODE *const_node2 = new_ast_const_node(NUM, val2);
   AST_NODE *bool_node = new_ast_bool_node(OR, const_node1, const_node2);
   AST_NODE *simple_node = new_ast_simple_node(0);
   AST_NODE *if_node = new_ast_if_node(bool_node, simple_node, NULL, 0, NULL);
   ast_traversal(if_node);
}
