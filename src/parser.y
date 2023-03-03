%code requires{
    #include "ast.hpp"

    extern const Expression *g_root; // A way of getting the AST out

    //! This is to fix problems when generating C++
    // We are declaring the functions provided by Flex, so
    // that Bison generated code can call them.
    int yylex(void);
    void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}

%token Number Word Syntax Operator Type

%type <expr> EXPR TERM UNARY FACTOR
%type <number>  Number
%type <string>  Word Syntax Type

%start ROOT

%%

ROOT : EXPR { g_root = $1; }

%%

int main(){
  yyparse();
}
