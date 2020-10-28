Type_Sym  get_result(Type_Sym type1,Type_Sym type2,Type_Op type_op) {
  switch(type_op) {
    case NONE : break ;
    case ARITHM_OP :
      if(type1 == CHARACTER || type2 == CHARACTER || type1 == ARRAY || type2 == ARRAY) {
        type_error(type1,type2,type_op);
      }
      else if(type1 == NUM || type2 == NUM) {
        return ((type1 == NUM)?(type2):(type1)) ;
      }
      else if(type1 == HEX || type2 == HEX) {
        return ((type1 == HEX)?(type2):(type1)) ;
      }
      else if(type1 == COMPLEX || type2 == COMPLEX) {
        return ((type1 == COMPLEX)?(type2):(type1)) ;
      }
      else if(type1 == VECTOR || type2 == VECTOR) {
        return ((type1 == VECTOR)?(type2):(type1)) ;
      }
      else if(type1 == MATRIX || type2 == MTRIX) {
        return MATRIX ;
      };
      break;
    case BOOL_OP :
      if(type1 == CHARACTER || type2 == CHARACTER || type1 == ARRAY || type2 == ARRAY) {
        type_error(type1,type2,type_op);
      }
      else if(type1 == NUM || type2 == NUM) {
        return ((type1 == NUM)?(type2):(type1)) ;
      }
      else if(type1 == HEX || type2 == HEX) {
        return ((type1 == HEX)?(type2):(type1)) ;
      }
      else if(type1 == COMPLEX || type2 == COMPLEX) {
        return ((type1 == COMPLEX)?(type2):(type1)) ;
      }
      else if(type1 == VECTOR || type2 == VECTOR) {
        return ((type1 == VECTOR)?(type2):(type1)) ;
      }
      else if(type1 == MATRIX || type2 == MTRIX) {
        return MATRIX ;
      };
      break;
    //
    case NOT_OP :
      if(type1 == CHARACTER || type1 == ARRAY ) {
        type_error(type1,type2,type_op);
      }
      else if(type1 == NUM ) {
        return BOOLEAN ;
      }
      else if(type1 == HEX ) {
        return BOOLEAN ;
      }
      else if(type1 == COMPLEX ) {
        return BOOLEAN ;
      }
      else if(type1 == VECTOR || type2 == VECTOR) {
        return BOOLEAN ;
      }
      else if(type1 == MATRIX || type2 == MTRIX) {
        return BOOLEAN ;
      };
      break;
  }
}
void type_error(Type_Sym type1,Type_Sym type2,Type_Op type_op) {
  printf("type conflit between %d and %d using op type %d\n",type1,type2,type_op);
}
int func_param_check(char *name , int count_param , Param_Function *param) {
  Type_Sym type1,type2 ;
  List_Symb *l= lookup(name);
  if(l->ParamCount == count_param) {
    printf("function parameter error");
    exit(1);
  }
  for(int i =0;i<count_param;i++) {
    type1 = l->PARAMS[i].TypeParam ;
    type2 = param[i].TypeParam ;
    get_result(type1,type2,NONE);
  }
  return 0 ;
}
