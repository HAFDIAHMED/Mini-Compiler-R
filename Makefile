CC = gcc
FLAGS_C = -c
FLAGS_L = -o
OBJ = ./obj
LEX = ./analy_lex
SYM = ./symbole_table
ERR = ./errors
SYN = ./analy_syn
GEN = ./generer_code

main : ${OBJ}/main.o ${OBJ}/analy_lex_func.o ${OBJ}/symb_table_func.o ${OBJ}/analy_syn_func.o ${OBJ}/errors_func.o ${OBJ}/generer_func.o
	${CC} ${OBJ}/main.o ${OBJ}/analy_lex_func.o ${OBJ}/symb_table_func.o  ${OBJ}/analy_syn_func.o ${OBJ}/errors_func.o ${OBJ}/generer_func.o ${FLAGS_L} main

${OBJ}/main.o : main.c ${LEX}/analy_lex_func.h ${SYN}/analy_syn_func.h
	${CC} ${FLAGS_C} main.c -o $@

${OBJ}/analy_lex_func.o : ${LEX}/analy_lex_func.c	${LEX}/analy_lex_func.h ${LEX}/analy_lex_dec.h ${SYM}/symb_table_func.h
	${CC} ${FLAGS_C} ${LEX}/analy_lex_func.c -o $@

${OBJ}/symb_table_func.o : ${SYM}/symb_table_func.c	${SYM}/symb_table_dec.h ${SYM}/symb_table_func.h
	${CC} ${FLAGS_C} ${SYM}/symb_table_func.c -o $@

${OBJ}/analy_syn_func.o : ${SYN}/analy_syn_func.c	${SYN}/analy_syn_func.h ${SYN}/analy_syn_dec.h ${ERR}/errors_func.h ${GEN}/generer_func.h
	${CC} ${FLAGS_C} ${SYN}/analy_syn_func.c -o $@

${OBJ}/errors_func.o : ${ERR}/errors_func.c ${ERR}/errors_dec.h ${ERR}/errors_func.h
	${CC} ${FLAGS_C} ${ERR}/errors_func.c -o $@

${OBJ}/generer_func.o : ${GEN}/generer_func.c ${GEN}/generer_func.h ${GEN}/generer_dec.h
	${CC} ${FLAGS_C} ${GEN}/generer_func.c -o $@
