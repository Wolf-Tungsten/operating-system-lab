CC=gcc
CFLAGS=-g -Wall
LEXSRC=parse.lex
SRC=myshell.c lex.yy.c cd.c pipe.c redirect.c
all:
	flex $(LEXSRC)
	$(CC) $(CFLAGS) -o grhshell $(SRC) -lfl