#include "analy_lex/analy_lex_func.h"
#include "analy_syn/analy_syn_func.h"
int main(int *argv,char *argc[]) {
  if(argv<2) {
    printf("compiler:\033[1;31m fatal error:\033[0m no input files\ncompilation terminated.\n");
    return EXIT_FAILURE ;
  }
  analy_lex(argc[1]);
  analy_syn();
}
