#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {
  IF_TOKEN,ELSE_TOKEN,REPEAT_TOKEN,WHILE_TOKEN,FUNCTION_TOKEN,FOR_TOKEN,IN_TOKEN,NEXT_TOKEN,BREAK_TOKEN,TRUE_TOKEN,
  FALSE_TOKEN,NULL_TOKEN,NAN_TOKEN,NA_INTEGER_TOKEN,NA_REAL_TOKEN,NA_COMPLEX_TOKEN,NA_CHARACTER_TOKEN,
  ADD_TOKEN,SUB_TOKEN,MULT_TOKEN,DIV_TOKEN,EXPONENT_TOKEN, MODULUS_TOKEN,INT_DIV_TOKEN,
  INF_TOKEN,SUP_TOKEN,INFEG_TOKEN,SUPEG_TOKEN,EQUALTO_TOKEN,NOT_EQUAL_TOKEN,
  LOGICAL_NOT_TOKEN,LOGICAL_AND_TOKEN,LOGICAL_OR_TOKEN,ELEMENTWISE_LOGICAL_AND_TOKEN,ELEMENTWISE_LOGICAL_OR_TOKEN,
  LEFT_ASGN_TOKEN,RIGHT_ASGN_TOKEN,PO_TOKEN,PF_TOKEN,AO_TOKEN,AF_TOKEN,PRINT_TOKEN,READLINE_TOKEN,RETURN_TOKEN,CHARACTER_TOKEN,
  PV_TOKEN,COMPLEX_TOKEN,HEX_TOKEN,NUM_TOKEN,ID_TOKEN,ERREUR_TOKEN,APOST_TOKEN,GUIL_TOKEN,TWO_POINT_TOKEN,VIR_TOKEN,EOF_TOKEN,

} TOKENS ;
typedef struct {
  TOKENS TOKEN ; char* WORD ;
} Sym_Struct ;
Sym_Struct *Token_Cour;
typedef struct sym_arr{
  Sym_Struct *Data ;
  struct sym_arr *next;
} Sym_Arr_Struct ;
extern Sym_Arr_Struct *Head_Arr_Symb;
Sym_Arr_Struct *Head_Arr_temp;
//