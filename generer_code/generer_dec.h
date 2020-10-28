typedef enum MNEMONICS {
  ADD,
  SUB,
  MUL,
  DIV,
  EQL,//==
  NEQ,//!=
  GTR,//>
  LSS,//<
  GEQ,//>=
  LEQ,//<=
  PRN,
  INN,
  INT,
  LDI,LDA,LDV,STO,
  BRN,BZE,
  HLT
} MNEMONICS ;
typedef struct MNEMON_STR {
  MNEMONICS MNE;
  char WORD[40];
}MNEMON_STR;

typedef struct INSTR {
  MNEMONICS MNE;
  int      ENTIER;
}INSTR ;
#define TAILLECODE 50
INSTR Pcode[TAILLECODE] ;
