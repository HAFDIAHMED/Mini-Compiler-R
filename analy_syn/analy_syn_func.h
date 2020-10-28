#include "analy_syn_dec.h"
#include "../errors/errors_func.h"

void Symbole_Suiv(void) ;
void Test_Symbole(TOKENS token,ERRORS erreur) ;
//
void INSTS() ;
void INST() ;
//
void AFTER_ID(void) ;
void LEFT_ASSIGN(void) ;
void RIGHT_ASSIGN(void) ;
//
void PRINT(void) ;
//
void IF(void) ;
//
void BOUCLE_FOR(void) ;
void BOUCLE_WHILE(void) ;
//
void FUNC(void) ;
//
void SEQ();
void READ_LINE(void) ;
//
void COND(void) ;
void COND1(void);
void COND2(void) ;
void COND3(void) ;
void COND4(void) ;
void EXPR(void) ;
void TERM(void) ;
void FACT(void) ;
void CALL_FUNC(void) ;
int analy_syn() ;
