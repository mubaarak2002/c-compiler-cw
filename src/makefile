CPPFLAGS += -W -Wall -g

# This avoids error: ‘fileno’ was not declared in this scope
CPPFLAGS += -std=c++0x

# Avoid warnings about yyunput not used
CPPFLAGS += -Wno-unused-function

all : lexer

lexer.yy.cpp : lexer.flex
	flex -o lexer.yy.cpp  lexer.flex

lexer : lexer.yy.o lexer_main.o
	g++ $(CPPFLAGS) -o lexer  lexer.yy.o lexer_main.o

clean :
	-rm -f lexer lexer.exe lexer_main.o lexer.yy.o
	-rm -f *.yy.cpp
	-rm -f test/lexer/*
