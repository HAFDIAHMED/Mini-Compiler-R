#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SYMBOL_TABLE_SIZE 211

typedef enum {
  UNDEF , COMPLEX , HEX , NUM , CHARACTER , FUNCTION , ARRAY , MATRIX , VECTOR , BOOLEAN , DATA_FRAME
} Type_Sym ;

typedef enum {
  BY_VALUE , BY_REFER
} Pass_Param;

typedef union Values{
  int IntValue ;
  double FloatValue ;
  char *StringValue ;
}Values ;

typedef struct Param_Function {
  Type_Sym TypeParam ;
  char NameParam[90] ;
  Values ValueParam ;
}Param_Function ;

typedef struct RefList{
  int LineNo ;
  Type_Sym TYPE ;
  int SCOPE ;
  struct RefList *NEXT ;
} Ref_List;

typedef struct List_Symb {
  char NameSymbol[90] ;
  int SCOPE ;
  Type_Sym TYPE ;
  // if TYPE == ARRAY || MATRIX || FUNCTION
  Type_Sym UnderType ;
  //
  Values ValueSymbol ;
  // if TYPE  == FUNCTION
  Param_Function *PARAMS;
  int ParamCount;
  //
  Ref_List *LINES;
  struct List_Symb *NEXT ;
} List_Symb ;
//
static List_Symb **symbol_table;
//
