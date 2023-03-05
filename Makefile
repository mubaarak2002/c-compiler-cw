CPPFLAGS += -std=c++20 -W -Wall -g -I include

.PHONY: default

default: bin/c_compiler

bin/c_compiler : src/cli.cpp src/compiler.cpp src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	@mkdir -p bin
	g++ $(CPPFLAGS) -o bin/c_compiler $^

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

bin/print_canonical : src/print_canonical.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

bin/eval_expr : src/eval_expr.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/eval_expr $^

clean :
	rm -rf bin/
	rm src/*.tab.cpp
	rm src/*.yy.cpp
	rm src/parser.output
	rm src/*.tab.*
	rm src/*.o
