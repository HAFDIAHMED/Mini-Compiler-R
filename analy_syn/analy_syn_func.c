#include "analy_syn_func.h"
#include "../generer_code/generer_func.h"

void Symbole_Suiv(void) {
  Head_Arr_temp = Head_Arr_temp->next ;
  Token_Cour = Head_Arr_temp->Data ;
}

void Test_Symbole(TOKENS token,ERRORS erreur) {
  if(Token_Cour->TOKEN == token) {
    if(token != EOF_TOKEN) {
      Symbole_Suiv();
    }
  }
  else {
    raise_error(erreur);
  }
}

void INSTS() {
  if(Token_Cour->TOKEN  == AO_TOKEN) {
    Symbole_Suiv();
    INST();
    if(Token_Cour->TOKEN==PV_TOKEN) {
      Symbole_Suiv();
    }
    while(Token_Cour->TOKEN == PRINT_TOKEN || Token_Cour->TOKEN == WHILE_TOKEN || Token_Cour->TOKEN == FOR_TOKEN  || Token_Cour->TOKEN == IF_TOKEN  || Token_Cour->TOKEN == ID_TOKEN || Token_Cour->TOKEN == NUM_TOKEN || Token_Cour->TOKEN == GUIL_TOKEN || Token_Cour->TOKEN == PO_TOKEN) {
      INST();
      if(Token_Cour->TOKEN==PV_TOKEN) {
        Symbole_Suiv();
      }
    }
    Test_Symbole(AF_TOKEN,EXPECTED_TOKEN_AF);
  }
  else {
    INST();
    if(Token_Cour->TOKEN==PV_TOKEN) {
      Symbole_Suiv();
    }
    while(Token_Cour->TOKEN == PRINT_TOKEN || Token_Cour->TOKEN == WHILE_TOKEN || Token_Cour->TOKEN == FOR_TOKEN  || Token_Cour->TOKEN == IF_TOKEN  || Token_Cour->TOKEN == ID_TOKEN || Token_Cour->TOKEN == NUM_TOKEN || Token_Cour->TOKEN == GUIL_TOKEN || Token_Cour->TOKEN == PO_TOKEN) {
      INST();
      if(Token_Cour->TOKEN==PV_TOKEN) {
        Symbole_Suiv();
      }
    }
  }
  generer1(HLT);
  Test_Symbole(EOF_TOKEN,EXPECTED_TOKEN_EOF);
}

void INST() {
  switch (Token_Cour->TOKEN) {
    case PRINT_TOKEN : Symbole_Suiv();PRINT()        ; break ;
    case WHILE_TOKEN : Symbole_Suiv();BOUCLE_WHILE() ; break ;
    case FOR_TOKEN   : Symbole_Suiv();BOUCLE_FOR()   ; break ;
    case IF_TOKEN    : Symbole_Suiv();IF()           ; break ;
    case ID_TOKEN    : generer2(LDA,0);Symbole_Suiv();AFTER_ID()     ; break ;
    default          : EXPR() ;
                       if(Token_Cour->TOKEN==RIGHT_ASGN_TOKEN) {
                          Symbole_Suiv();RIGHT_ASSIGN();
                       }
  }
}

void AFTER_ID(void) {
  switch (Token_Cour->TOKEN) {
    case LEFT_ASGN_TOKEN  : Symbole_Suiv();LEFT_ASSIGN();break ;
    case RIGHT_ASGN_TOKEN : Symbole_Suiv();RIGHT_ASSIGN();break ;
    default               : EXPR();
                            if(Token_Cour->TOKEN == RIGHT_ASGN_TOKEN) {
                              Symbole_Suiv();
                              RIGHT_ASSIGN();
                            }; break ;
  }
}
void LEFT_ASSIGN(void) {
  switch (Token_Cour->TOKEN) {
    case FUNCTION_TOKEN   : Symbole_Suiv();
                            FUNC();
                            break ;
    case READLINE_TOKEN   : Symbole_Suiv();
                            READ_LINE();
                            break ;
    default               : INST() ; break ;
  }
  generer1(STO);


}
void RIGHT_ASSIGN(void) {
  Test_Symbole(ID_TOKEN,EXPECTED_TOKEN_ID);
  generer1(STO);
}
//
void PRINT(void) {
  Test_Symbole(PO_TOKEN,EXPECTED_TOKEN_PO);
  switch(Token_Cour->TOKEN) {
    case ID_TOKEN : generer2(LDA,0);generer1(LDV);Symbole_Suiv();
    default       : EXPR();
  }
  Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  generer1(PRN);
}
//
void IF(void) {
  Test_Symbole(PO_TOKEN,EXPECTED_TOKEN_PO);
  COND();
  Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  Test_Symbole(AO_TOKEN,EXPECTED_TOKEN_AO);
  generer1(BZE);
  while(Token_Cour->TOKEN!=AF_TOKEN) {
    Symbole_Suiv();
    INST();
  }
  Test_Symbole(AF_TOKEN,EXPECTED_TOKEN_AF);
  while(Token_Cour->TOKEN  == ELSE_TOKEN) {
    Symbole_Suiv();
    Test_Symbole(AO_TOKEN,EXPECTED_TOKEN_AO);
    while(Token_Cour->TOKEN!=AF_TOKEN) {
      Symbole_Suiv();
      INST();
    }
    Test_Symbole(AF_TOKEN,EXPECTED_TOKEN_AF);
  }
}
//
void BOUCLE_FOR(void) {
  Test_Symbole(PO_TOKEN,EXPECTED_TOKEN_PO);
  Test_Symbole(ID_TOKEN,EXPECTED_TOKEN_ID);
  Test_Symbole(IN_TOKEN,EXPECTED_TOKEN_IN);
  SEQ();
  Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  Test_Symbole(AO_TOKEN,EXPECTED_TOKEN_AO);
  while(Token_Cour->TOKEN == PRINT_TOKEN || Token_Cour->TOKEN == WHILE_TOKEN || Token_Cour->TOKEN == FOR_TOKEN  || Token_Cour->TOKEN == IF_TOKEN  || Token_Cour->TOKEN == ID_TOKEN || Token_Cour->TOKEN == NUM_TOKEN || Token_Cour->TOKEN == GUIL_TOKEN || Token_Cour->TOKEN == PO_TOKEN) {
    Symbole_Suiv();
    INST();
  }
  Test_Symbole(AF_TOKEN,EXPECTED_TOKEN_AF);
  }
void BOUCLE_WHILE(void) {
  Test_Symbole(PO_TOKEN,EXPECTED_TOKEN_PO);
  COND();
  generer1(BZE);
  Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  Test_Symbole(AO_TOKEN,EXPECTED_TOKEN_AO);
  while(Token_Cour->TOKEN == PRINT_TOKEN || Token_Cour->TOKEN == WHILE_TOKEN || Token_Cour->TOKEN == FOR_TOKEN  || Token_Cour->TOKEN == IF_TOKEN  || Token_Cour->TOKEN == ID_TOKEN || Token_Cour->TOKEN == NUM_TOKEN || Token_Cour->TOKEN == GUIL_TOKEN || Token_Cour->TOKEN == PO_TOKEN) {
    Symbole_Suiv();
    INST();
  }
  Test_Symbole(AF_TOKEN,EXPECTED_TOKEN_AF);
  generer1(BRN);
  }
//
void FUNC(void) {
  Test_Symbole(PO_TOKEN,EXPECTED_TOKEN_PO);
  Test_Symbole(ID_TOKEN,EXPECTED_TOKEN_ID);
  while( Token_Cour->TOKEN == VIR_TOKEN) {
    Symbole_Suiv();
    Test_Symbole(ID_TOKEN,EXPECTED_TOKEN_ID);
  }
  Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  Test_Symbole(AO_TOKEN,EXPECTED_TOKEN_AO);
  while(Token_Cour->TOKEN == PRINT_TOKEN || Token_Cour->TOKEN == WHILE_TOKEN || Token_Cour->TOKEN == FOR_TOKEN  || Token_Cour->TOKEN == IF_TOKEN  || Token_Cour->TOKEN == ID_TOKEN || Token_Cour->TOKEN == NUM_TOKEN || Token_Cour->TOKEN == GUIL_TOKEN || Token_Cour->TOKEN == PO_TOKEN) {
    INST();
  }
  Test_Symbole(RETURN_TOKEN,EXPECTED_TOKEN_RETURN);
  Test_Symbole(PO_TOKEN,EXPECTED_TOKEN_PO);
  switch (Token_Cour->TOKEN) {
    case ID_TOKEN: generer2(LDA,0);generer1(LDV);Symbole_Suiv();
    default      : EXPR();
  }

  Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  Test_Symbole(AF_TOKEN,EXPECTED_TOKEN_AF);
}
//
void SEQ() {}
void READ_LINE(void) {
  Test_Symbole(PO_TOKEN,EXPECTED_TOKEN_PO);
  if(Token_Cour->TOKEN == GUIL_TOKEN ) {
    Test_Symbole(CHARACTER_TOKEN,EXPECTED_TOKEN_CHARACTER);
    Test_Symbole(GUIL_TOKEN,EXPECTED_TOKEN_GUIL);
  }
  Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  generer1(INN);
}
//
void COND(void) {
  COND1();
  while(Token_Cour->TOKEN == LOGICAL_AND_TOKEN || Token_Cour->TOKEN == LOGICAL_OR_TOKEN ) {
    Symbole_Suiv();
    COND1();
  }
}
void COND1(void) {
  if(Token_Cour->TOKEN == PO_TOKEN ) {
    COND2();
    Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF);
  }
  COND2();
}
void COND2(void) {
  if(Token_Cour->TOKEN == LOGICAL_NOT_TOKEN) {Symbole_Suiv();}
  COND3();
}
void COND3(void) {
  TOKENS op = NULL_TOKEN ;
  COND4() ;
  while(Token_Cour->TOKEN == INF_TOKEN || Token_Cour->TOKEN == SUP_TOKEN || Token_Cour->TOKEN == INFEG_TOKEN || Token_Cour->TOKEN == SUPEG_TOKEN || Token_Cour->TOKEN == EQUALTO_TOKEN || Token_Cour->TOKEN == NOT_EQUAL_TOKEN) {
    op = Token_Cour->TOKEN ;
    Symbole_Suiv();
    COND4();
    switch(op) {
      case INF_TOKEN   : generer1(LSS);break;
      case SUP_TOKEN   : generer1(GTR);break;
      case INFEG_TOKEN : generer1(LEQ);break;
      case SUPEG_TOKEN : generer1(GEQ);break;
      case EQUALTO_TOKEN : generer1(EQL);break;
      case NOT_EQUAL_TOKEN : generer1(NEQ);break;
    }
  }
}
void COND4(void) {
  switch(Token_Cour->TOKEN) {
    case TRUE_TOKEN  : Symbole_Suiv() ; break ;
    case FALSE_TOKEN : Symbole_Suiv() ; break ;
    case ID_TOKEN    : generer2(LDA,0);generer1(LDV);Symbole_Suiv();
    default          : EXPR();
  }
}
//
void EXPR(void) {
  TOKENS op = NULL_TOKEN ;
  TERM();
  while(Token_Cour->TOKEN == ADD_TOKEN || Token_Cour->TOKEN == SUB_TOKEN) {
    op = Token_Cour->TOKEN ;
    Symbole_Suiv();
    switch(Token_Cour->TOKEN) {
      case ID_TOKEN : generer2(LDA,0);generer1(LDV);Symbole_Suiv();
      default       : TERM();
    }
    if(op!=NULL_TOKEN) {
      switch(op) {
        case ADD_TOKEN  : generer1(ADD) ; break ;
        case SUB_TOKEN  : generer1(SUB) ; break ;
      }
    }
  }
}
void TERM(void) {
  TOKENS op = NULL_TOKEN ;
  FACT();
  while(Token_Cour->TOKEN == MULT_TOKEN || Token_Cour->TOKEN == DIV_TOKEN) {
    op = Token_Cour->TOKEN ;
    Symbole_Suiv();
    switch(Token_Cour->TOKEN) {
      case ID_TOKEN : generer2(LDA,0);generer1(LDV);Symbole_Suiv();
      default       : FACT();
    }

    if(op!=NULL_TOKEN) {
      switch(op) {
        case MULT_TOKEN :generer1(MUL) ; break ;
        case DIV_TOKEN  :generer1(DIV) ; break ;
      }
    }
  }
}
void FACT(void) {
  switch(Token_Cour->TOKEN) {
    case NUM_TOKEN  : generer2(LDI,atoi(Token_Cour->WORD));Symbole_Suiv(); break ;
    case GUIL_TOKEN : Symbole_Suiv();
                      Test_Symbole(CHARACTER_TOKEN,EXPECTED_TOKEN_CHARACTER);
                      generer2(LDI,0);
                      Test_Symbole(GUIL_TOKEN,EXPECTED_TOKEN_GUIL);
                      break ;
    case PO_TOKEN  : Symbole_Suiv();
                     switch(Token_Cour->TOKEN) {
                       case ID_TOKEN : generer2(LDA,0);generer1(LDV);Symbole_Suiv(); break ;
                       default : EXPR();
                     }
                     while(Token_Cour->TOKEN==VIR_TOKEN){
                       Symbole_Suiv();
                       switch(Token_Cour->TOKEN) {
                              case ID_TOKEN : generer2(LDA,0);generer1(LDV);Symbole_Suiv(); break ;
                              default : EXPR();
                            }
                     }
                     Test_Symbole(PF_TOKEN,EXPECTED_TOKEN_PF); break ;
  }
}
//
int analy_syn() {
  Head_Arr_temp = Head_Arr_Symb->next ;
  Token_Cour = (Sym_Struct*)malloc(sizeof(Sym_Struct));
  Token_Cour->WORD = (char*)malloc(90);
  Token_Cour = Head_Arr_temp->Data;
  INSTS();
  afficher_pcode();
  return 0;
}
