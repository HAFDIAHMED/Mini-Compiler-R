#include "analy_lex_func.h"
#include "analy_lex_dec.h"
#include "../symbole_table/symb_table_func.h"
extern int cur_scope ;
void push() {
  Sym_Arr_Struct *current = Head_Arr_Symb;
  if(Head_Arr_Symb == NULL) {
    Head_Arr_Symb->Data = Token_Cour ;
    Head_Arr_Symb->next = NULL ;
 }
  else {
    while(current->next != NULL) {
      current=current->next;
    }
    current->next=(Sym_Arr_Struct*)malloc(sizeof(Sym_Arr_Struct));
    current->next->Data = (Sym_Struct*)malloc(sizeof(Sym_Struct));
    current->next->Data->WORD = (char*)malloc(21);
    current->next->Data->TOKEN = Token_Cour->TOKEN ;
    memcpy(current->next->Data->WORD,Token_Cour->WORD,sizeof(Token_Cour->WORD));
    current->next->next = NULL ;
 }
}
void show() {
  Sym_Arr_Struct *current = Head_Arr_Symb;
  while(current->next != NULL) {
    printf("%s ----> %s\n",ARR_TOK[current->next->Data->TOKEN].TOKENS,current->next->Data->WORD);
    current=current->next;
  }
}
void Next_Car() {
  Car_Cour = fgetc(file);
}
void Next_Word() {
  int count_car = 0 ;
  *(Token_Cour->WORD+count_car)=Car_Cour;
  count_car++;
  if(Car_Cour == '.') {
    Next_Car();
    if(!(('a'<=Car_Cour && Car_Cour<='z')||('A'<=Car_Cour && Car_Cour<='Z')||(Car_Cour == '.')||(Car_Cour == '_'))) {
      //error
    }
    *(Token_Cour->WORD+count_car)=Car_Cour;
    count_car++;
  }
  Next_Car();
  while(('a'<=Car_Cour && Car_Cour<='z')||('A'<=Car_Cour && Car_Cour<='Z')||('0'<=Car_Cour && Car_Cour<='9')) {
    *(Token_Cour->WORD+count_car)=Car_Cour;
    count_car++;
    Next_Car();
  }
  //printf("%s\n",Token_Cour->WORD);
  Check_Token();
}
void Next_Number() {
  int count_car = 0 ;
  *(Token_Cour->WORD+count_car)=Car_Cour;
  count_car++;
  Next_Car();
  if(Car_Cour == 'x' || Car_Cour == 'X') {
    *(Token_Cour->WORD+count_car)=Car_Cour;
    count_car++;
    Next_Car();
    while(('0'<=Car_Cour && Car_Cour<='9')||('a'<=Car_Cour && Car_Cour<='f')||('A'<=Car_Cour && Car_Cour<='F')) {
      *(Token_Cour->WORD+count_car)=Car_Cour;
      count_car++;
      Next_Car();
    }
    Token_Cour->TOKEN = HEX_TOKEN ;
  }
  else {
    while(('0'<=Car_Cour && Car_Cour<='9')) {
      *(Token_Cour->WORD+count_car)=Car_Cour;
      count_car++;
      Next_Car();
    }
    if(Car_Cour == 'L') {
      *(Token_Cour->WORD+count_car)=Car_Cour;
      count_car++;
      Next_Car();
    }
    Token_Cour->TOKEN = NUM_TOKEN ;
  }

}
void Next_Character() {
  int count_car = 0 ;
  const char type_start_char = Car_Cour ;
  if(type_start_char == '\'') {
    Token_Cour->TOKEN = APOST_TOKEN ;
    *Token_Cour->WORD = '\'' ;
  }
  else {
    Token_Cour->TOKEN = GUIL_TOKEN ;
    *Token_Cour->WORD = '"' ;
  }
  //
  push();
  Token_Cour->TOKEN = NULL_TOKEN ;
  Token_Cour->WORD=memset(Token_Cour->WORD,'\0',sizeof(Token_Cour->WORD));
  //
  *(Token_Cour->WORD+count_car)=Car_Cour;
  count_car++;
  Next_Car();
  while(1) {
    if(Car_Cour == type_start_char) {
      if(*(Token_Cour->WORD+count_car-1)!='\\') {
        Token_Cour->TOKEN = CHARACTER_TOKEN ;
        break;
      }
    }
    *(Token_Cour->WORD+count_car)=Car_Cour;
    count_car++;
    Next_Car();
  }
  push();
  Token_Cour->TOKEN = NULL_TOKEN ;
  Token_Cour->WORD=memset(Token_Cour->WORD,'\0',sizeof(Token_Cour->WORD));
  if(type_start_char == '\'') {
    Token_Cour->TOKEN = APOST_TOKEN ;
    *Token_Cour->WORD = '\'' ;
  }
  else {
    Token_Cour->TOKEN = GUIL_TOKEN ;
    *Token_Cour->WORD = '"' ;
  }
  Next_Car();
}
void Check_Token() {
  if(strcmp("if",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = IF_TOKEN ;
  }
  else if(strcmp("else",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = ELSE_TOKEN ;
  }
  else if(strcmp("repeat",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = REPEAT_TOKEN ;
  }
  else if(strcmp("while",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = WHILE_TOKEN ;
  }
  else if(strcmp("for",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = FOR_TOKEN ;
  }
  else if(strcmp("in",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = IN_TOKEN ;
  }
  else if(strcmp("function",Token_Cour->WORD)==0) {
    cur_scope++;
    count_status++;
    STATUS_FUNCTION = TRUE ;
    Token_Cour->TOKEN = FUNCTION_TOKEN ;
  }
  else if(strcmp("next",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = NEXT_TOKEN ;
  }
  else if(strcmp("break",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = BREAK_TOKEN ;
  }
  else if(strcmp("true",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = TRUE_TOKEN ;
  }
  else if(strcmp("false",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = FALSE_TOKEN ;
  }
  else if(strcmp("null",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = NULL_TOKEN ;
  }
  else if(strcmp("print",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = PRINT_TOKEN ;
  }
  else if(strcmp("readline",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = READLINE_TOKEN ;
  }
  else if(strcmp("return",Token_Cour->WORD)==0) {
    Token_Cour->TOKEN = RETURN_TOKEN ;
  }
  else {
    insert(Token_Cour->WORD,strlen(Token_Cour->WORD),UNDEF,current_line);
    Token_Cour->TOKEN = ID_TOKEN ;
  }
}
void Break_Comment() {
  Next_Car();
  while(1) {
    if(Car_Cour == 42) {
      Next_Car();
      if(Car_Cour == 125) {
        break;
      }
    }
    else {
      Next_Car();
    }
  }
}
void Next_Sym() {
  Token_Cour->TOKEN = NULL_TOKEN ;
  Token_Cour->WORD=memset(Token_Cour->WORD,'\0',sizeof(Token_Cour->WORD));
  switch(Car_Cour) {
    case 10 : current_line++;Next_Car(); break;
    case 32 : Next_Car(); break;
    case ';': Token_Cour->TOKEN = PV_TOKEN ;
              *Token_Cour->WORD = ';' ;
              Next_Car(); break;
    case '+': Token_Cour->TOKEN = ADD_TOKEN ;
              *Token_Cour->WORD = '+' ;
              Next_Car(); break;
    //
    case '-': Next_Car();
              switch(Car_Cour) {
                case '>' : Next_Car();
                           switch(Car_Cour) {
                             case '>' : Token_Cour->TOKEN = RIGHT_ASGN_TOKEN ;
                                        Token_Cour->WORD=strcpy(Token_Cour->WORD,"->>");
                                        Next_Car(); break;
                             default  : Token_Cour->TOKEN = RIGHT_ASGN_TOKEN ;
                                        Token_Cour->WORD=strcpy(Token_Cour->WORD,"->");
                                        Next_Car(); break;
                           }; break ;
                default  : Token_Cour->TOKEN = SUB_TOKEN ;
                           *Token_Cour->WORD = '-' ;
                           break;
              }; break ;
    //
    case '*': Token_Cour->TOKEN = MULT_TOKEN ;
              *Token_Cour->WORD = '*' ;
              Next_Car(); break;
    //
    case '/': Token_Cour->TOKEN = DIV_TOKEN ;
              *Token_Cour->WORD = '/' ;
              Next_Car(); break;
    //
    case '^': Token_Cour->TOKEN = EXPONENT_TOKEN ;
              *Token_Cour->WORD = '^' ;
              Next_Car(); break;
    //
    case '%': Next_Car();
              switch(Car_Cour) {
                case '%' : Token_Cour->TOKEN = MODULUS_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,"%%");
                           Next_Car(); break;
                case '/' : Next_Car();
                           switch(Car_Cour) {
                             case '%' : Token_Cour->TOKEN = INT_DIV_TOKEN ;
                                        Token_Cour->WORD=strcpy(Token_Cour->WORD,"%/%");
                                        Next_Car(); break;
                             default  : Token_Cour->TOKEN = ERREUR_TOKEN ;
                           }; break ;
                default  : Token_Cour->TOKEN = ERREUR_TOKEN ;
              }; break ;
    //
    case '&': Next_Car();
              switch(Car_Cour) {
                case '&' : Token_Cour->TOKEN = LOGICAL_AND_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,"&&");
                           Next_Car(); break;
                default  : Token_Cour->TOKEN = ELEMENTWISE_LOGICAL_AND_TOKEN ;
                           *Token_Cour->WORD = '&' ;
                           break;
              }; break ;
    //
    case '|': Next_Car();
              switch(Car_Cour) {
                case '|' : Token_Cour->TOKEN = LOGICAL_OR_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,"||");
                           Next_Car(); break;
                default  : Token_Cour->TOKEN = ELEMENTWISE_LOGICAL_OR_TOKEN ;
                           *Token_Cour->WORD = '|' ;
                           break;
              }; break ;
    //
    case '=': Next_Car();
              switch(Car_Cour) {
                case '=' : Token_Cour->TOKEN = EQUALTO_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,"==");
                           Next_Car(); break;
                default  : Token_Cour->TOKEN = LEFT_ASGN_TOKEN ;
                           *Token_Cour->WORD = '=' ;
                           break;
              }; break ;
    //
    case '!': Next_Car();
              switch(Car_Cour) {
                case '=' : Token_Cour->TOKEN = NOT_EQUAL_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,"!=");
                           Next_Car(); break;
                default  : Token_Cour->TOKEN = LOGICAL_NOT_TOKEN ;
                           *Token_Cour->WORD = '!' ;
                            break;
              }; break ;
    //
    case '<': Next_Car();
              switch(Car_Cour) {
                case '=' : Token_Cour->TOKEN = INFEG_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,"<=");
                           Next_Car(); break;
                //
                case '-' : Token_Cour->TOKEN = LEFT_ASGN_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,"<-");
                           Next_Car(); break;
                //
                case '<' : Next_Car();
                           switch(Car_Cour) {
                             case '-' : Token_Cour->TOKEN = LEFT_ASGN_TOKEN ;
                                        Token_Cour->WORD=strcpy(Token_Cour->WORD,"<<-");
                                        Next_Car(); break;
                             default  : Token_Cour->TOKEN = ERREUR_TOKEN ;
                           }; break ;
                default  : Token_Cour->TOKEN = INF_TOKEN ;
                           *Token_Cour->WORD = '<' ;
                            break;
              }; break ;
    //
    case '>': Next_Car();
              switch(Car_Cour) {
                case '=' : Token_Cour->TOKEN = SUPEG_TOKEN ;
                           Token_Cour->WORD=strcpy(Token_Cour->WORD,">=");
                           Next_Car(); break;
                default  : Token_Cour->TOKEN = SUP_TOKEN ;
                           *Token_Cour->WORD = '>' ;
                           break;
              }; break ;
    //
    case '(': Token_Cour->TOKEN = PO_TOKEN ;
              *Token_Cour->WORD = '(' ;
              Next_Car(); break;
    //
    case ')': Token_Cour->TOKEN = PF_TOKEN ;
              *Token_Cour->WORD = ')' ;
              Next_Car(); break;
    //
    case '{': Token_Cour->TOKEN = AO_TOKEN ;
              *Token_Cour->WORD = '{' ;
              Next_Car(); break;
    //
    case '}': Token_Cour->TOKEN = AF_TOKEN ;
              *Token_Cour->WORD = '}' ;
              Next_Car();
              if(STATUS_FUNCTION == TRUE) {
                  count_status--;
                  if(count_status==0) {
                    STATUS_FUNCTION = FALSE ;
                  }
              };
              break;
    //
    case ':': Token_Cour->TOKEN = TWO_POINT_TOKEN ;
              *Token_Cour->WORD = ':' ;
              Next_Car(); break;
    //
    case ',': Token_Cour->TOKEN = VIR_TOKEN ;
              *Token_Cour->WORD = ',' ;
              Next_Car(); break;
    case '\'' :
    case '"'  : Next_Character(); break;
    default : if(('a'<=Car_Cour && Car_Cour<='z')||('A'<=Car_Cour && Car_Cour<='Z')||Car_Cour=='.'){Next_Word();}
              else if('0'<=Car_Cour && Car_Cour<='9') {Next_Number();}
              else {Next_Car();}
    }
}

int analy_lex(char *filename) {
  file=fopen(filename,"a+");
  Head_Arr_Symb = (Sym_Arr_Struct*)malloc(sizeof(Sym_Arr_Struct));
  Token_Cour = (Sym_Struct*)malloc(sizeof(Sym_Struct));
  Token_Cour->WORD = (char*)malloc(90);
  init_hash_table();
  Next_Car();
  while(Car_Cour != EOF) {
    Next_Sym();
    if(Token_Cour->TOKEN != NULL_TOKEN) {
      push();
    }
    if(Car_Cour == EOF) {
      Token_Cour->TOKEN = EOF_TOKEN ;
      Token_Cour->WORD=strcpy(Token_Cour->WORD,"eof");
      push();
    }
  }

  show();
  symb_show();
  return 0;
}
