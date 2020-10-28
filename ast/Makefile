CC = gcc
FLAGS_C = -c
FLAGS_L = -o
OBJ = ./obj
LEX = ./analy_lex_sem
SYM = ./../symbole_table

main : main.o ast_func.o
	${CC} main.o ast_func.o ${FLAGS_L} main

main.o : main.c ast_func.h ${SYM}/symb_table_dec.h
	${CC} ${FLAGS_C} main.c

ast_func.o :ast_func.c ast_dec.h ast_func.h ${SYM}/symb_table_dec.h
	${CC} ${FLAGS_C} ast_func.c
