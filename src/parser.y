%code requires{
  #include "ast.hpp"

  #include <cassert>

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

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_EXPONENT
%token T_NUMBER T_VARIABLE
%token INT
%token COMMA
%token IF ELSE BREAK CONTINUE SWITCH CASE DEFAULT WHILE FOR RETURN
%token LTE GTE EQUAL

%type <expr> EXPR TERM UNARY FACTOR SECTION SEQ DECLARE ARGS TYPE FUNCT ASSIGN CONTROL
%type <number> T_NUMBER
%type <string> T_VARIABLE INT

%start ROOT

%%

/*
*/

ROOT : SEQ { g_root = $1; }

SEQ : SECTION    { $$ = $1; }
    | SEQ SECTION  { $$ = new Sequence($1, $2);}
    ;

FUNCT : DECLARE '(' ARGS ')' '{' SEQ '}' {$$ = new UserFunct($1, $3, $6);}
      | DECLARE '(' ')' '{' SEQ '}' {$$ = new SimpleFunct($1, $5);}
      ;

CONTROL : IF '(' EXPR ')' '{' SEQ '}' ELSE '{' SEQ '}' { $$ = new IfElseControl($3, $6, $10); }
        | IF '(' EXPR ')' '{' SEQ '}' { $$ = new IfControl($3, $6); }
        | WHILE '(' EXPR ')' '{' SEQ '}' { $$ = new WhileControl($3, $6 ); }
        | WHILE '(' EXPR ')' '{''}' { $$ = new WhileControl($3, new Empty()); }
        ;
SECTION : EXPR ';' {$$ = $1;}
        | FUNCT {$$ = $1;}
        | ASSIGN ';' { $$ = $1;}
        | RETURN EXPR ';' { $$ = new Return($2);}
        | DECLARE ';' {;}
        | CONTROL { $$ = $1; }
        ;

ARGS : DECLARE  {$$ = $1;}
     | ARGS COMMA DECLARE {$$ = new Args($1,$3);}
     ;

EXPR : TERM           { $$ = $1; }
     | EXPR T_PLUS TERM  { $$ = new AddOperator($1, $3); }
     | EXPR T_MINUS TERM { $$ = new SubOperator($1, $3); }
     | EXPR '<' TERM     { $$ = new LessThanOperator($1, $3); }
     | EXPR '>' TERM     { $$ = new GreaterThanOperator($1, $3); }
     | EXPR LTE TERM     { $$ = new LessThanEqualOperator($1, $3); }
     | EXPR GTE TERM     { $$ = new GreaterThanEqualOperator($1, $3); }
     | EXPR EQUAL TERM   { $$ = new EqualOperator($1, $3); }
     ;

TERM : UNARY          { $$ = $1; }
     | TERM T_TIMES FACTOR  { $$ = new MulOperator($1, $3); }
     | TERM T_DIVIDE FACTOR  { $$ = new DivOperator($1, $3); }
     | TERM '|' FACTOR       { $$ = new OROperator($1, $3); }
     | TERM '&' FACTOR       { $$ = new ANDOperator($1, $3); }
     | TERM '^' FACTOR       { $$ = new XOROperator($1, $3); }
     ;

UNARY : FACTOR        { $$ = $1; }
      | T_MINUS FACTOR  { $$ = new NegOperator($2); }
      ;

FACTOR : T_NUMBER     { $$ = new Number( $1 ); }
       | T_VARIABLE   { $$ = new Variable( *$1 ); }
       | '(' EXPR ')' { $$ = $2; }
       ;

TYPE : INT  {$$ = new Type( *$1 );}
     ;

ASSIGN : FACTOR '=' EXPR { $$ = new Assign($1, $3); }
       | DECLARE '=' EXPR { $$ = new Assign($1, $3); }
       ;

DECLARE : TYPE FACTOR { $$ = new Decleration($1, $2);}
        ;

%%

const Expression *g_root; //

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
