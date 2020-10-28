#include "symb_table_func.h"

int cur_scope =0;


void init_hash_table() {
  symbol_table = malloc(SYMBOL_TABLE_SIZE * sizeof(List_Symb*));
  for(int i=0;i<SYMBOL_TABLE_SIZE;i++) {symbol_table[i] == NULL ;}
}
unsigned int hash(char *key){
  unsigned int hashval = 0 ;
  for(;*key!='\0';key++) {
    hashval += *key ;
  }
  hashval += key[0]%11 + (key[0]<<3) - key[0];
  return hashval % SYMBOL_TABLE_SIZE ;
}
void insert(char *name,int len,Type_Sym type,int lineno) {
  unsigned int hashval = hash(name) ;
  List_Symb *l = symbol_table[hashval];
  while((l!=NULL) && (strcmp(name,l->NameSymbol)!=0)) {
    l = l->NEXT ;
  }
  if(l==NULL) {
    l = (List_Symb*) malloc(sizeof(List_Symb));
    strncpy(l->NameSymbol,name,len);

    l->SCOPE = cur_scope;
    l->TYPE = type ;
    l->LINES = (Ref_List*) malloc(sizeof(Ref_List));
    l->LINES->LineNo = lineno ;
    l->LINES->SCOPE = cur_scope ;
    l->LINES->TYPE = type ;
    l->LINES->NEXT = NULL ;
    l->NEXT = symbol_table[hashval] ;
    symbol_table[hashval] = l ;
  }
  else {
    Ref_List *t = l->LINES ;
    while(t->NEXT != NULL) {
      t = t->NEXT ;
    }
    t->NEXT =  (Ref_List*) malloc(sizeof(Ref_List));
    t->NEXT->LineNo = lineno ;
    t->NEXT->SCOPE = cur_scope ;
    t->NEXT->TYPE = type ;
    t->NEXT->NEXT = NULL ;
  }
}
List_Symb *lookup(char *name) {
  unsigned int hashval = hash(name);
  List_Symb *l = symbol_table[hashval];
  while((l!=NULL) && (strcmp(name,l->NameSymbol)!=0)) {
    l=l->NEXT ;
  }
  return l ;
}
List_Symb *lookup_scope(char *name,int scope) {
  unsigned int hashval = hash(name);
  List_Symb *l = symbol_table[hashval];
  while((l!=NULL) && (strcmp(name,l->NameSymbol)!=0) && (scope != l->SCOPE)) {
    l=l->NEXT ;
  }
  return l ;
}
void set_type(char *name,Type_Sym type,Type_Sym undertype) {
  List_Symb *l = lookup(name);
  if(l!=NULL) {
    l->TYPE = type ;
    if(undertype != UNDEF) {
      l->UnderType = undertype ;
    }
  }
}
Type_Sym get_type(char *name) {
  List_Symb *l = lookup(name);
  if(l->TYPE == NUM || l->TYPE == COMPLEX || l->TYPE == HEX || l->TYPE == NUM || l->TYPE == CHARACTER) {
    return l->TYPE ;
  }
  else if (l->TYPE == FUNCTION ||  l->TYPE == MATRIX || l->TYPE == VECTOR) {
    return l->UnderType ;
  }
}
Param_Function def_param(Type_Sym type,char *name) {
  Param_Function param ;
  param.TypeParam = type ;
  strncpy(param.NameParam,name,strlen(name));
  return param ;
}
int func_declare(char *name ,Type_Sym returntype , int count_param , Param_Function *param) {
  List_Symb *l = lookup(name);
  if(l->TYPE == UNDEF) {
    l->TYPE = FUNCTION ;
  }
  l->UnderType = returntype ;
  l->ParamCount = count_param ;
  l->PARAMS = param ;
  return 0;
}
void hide_scope() {
  if(cur_scope>0) {
    cur_scope-- ;
  }
}
void incr_scope() {
  cur_scope++;
}
void symb_show() {
  for(int i=0;i<SYMBOL_TABLE_SIZE;i++) {
    List_Symb *l = symbol_table[i];
    while(l!=NULL) {
      Ref_List *ref = l->LINES ;
      printf("Symbole --> %s\n",l->NameSymbol);
      while(ref!=NULL) {
        printf("lineno --> %d ",ref->LineNo);
        printf("scope  --> %d ",ref->SCOPE);
        printf("type   --> %d ",ref->TYPE);
        printf("\n");
        ref = ref->NEXT ;
      }
      printf("\n");
      l = l->NEXT ;
    }
  }
}
