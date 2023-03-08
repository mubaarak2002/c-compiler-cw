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

%token T_NUMBER T_VARIABLE
%token INT

%type <expr> EXPR TERM UNARY FACTOR SECTION SEQ DECLARE ARGS TYPE FUNCT ASSIGN
%type <number> T_NUMBER
%type <string> T_VARIABLE INT

%start ROOT

%%

/* The TODO notes a are just a guide, and are non-exhaustive.
   The expectation is that you do each one, then compile and test.
   Testing should be done using patterns that target the specific
   feature; the testbench is there to make sure that you haven't
   broken anything while you added it.
*/

ROOT : SEQ { g_root = $1; }

/* TODO-3 : Add support for (x + 6) and (10 - y). You'll need to add production rules, and create an AddOperator or
            SubOperator. */


SEQ : SECTION    { $$ = $1; }
    | SEQ SECTION  { $$ = new Sequence($1, $2);}
    ;

FUNCT : DECLARE '(' ARGS ')' '{' SECTION '}' {$$ = new UserFunct($1, $3, $6);}
      ;

ARGS : DECLARE  {$$ = $1;}
     | ARGS ',' DECLARE {$$ = new Args($1,$3);}
     ;

SECTION : EXPR ';' {$$ = $1;}
        | FUNCT {$$ = $1;}
        | ASSIGN ';' { $$ = $1;}
        ;

EXPR : TERM           { $$ = $1; }
     | EXPR '+' TERM  { $$ = new AddOperator($1, $3); }
     | EXPR '-' TERM  { $$ = new SubOperator($1, $3); }
     ;

/* TODO-4 : Add support (x * 6) and (z / 11). */
TERM : UNARY          { $$ = $1; }
     | TERM '*' FACTOR  { $$ = new MulOperator($1, $3); }
     | TERM '/' FACTOR  { $$ = new DivOperator($1, $3); }
     ;

/*  TODO-5 : Add support for (- 5) and (- x). You'll need to add production rules for the unary minus operator and create a NegOperator. */
UNARY : FACTOR        { $$ = $1; }
      | '-' FACTOR  { $$ = new NegOperator($2); }
      ;

/* TODO-2 : Add a rule for variable, base on the pattern of number. */
FACTOR : T_NUMBER     { $$ = new Number( $1 ); }
       | T_VARIABLE   { $$ = new Variable( *$1 ); }
       | '(' EXPR ')' { $$ = $2; }
       ;

TYPE : INT  {$$ = new Type( *$1 );}
     ;

ASSIGN : FACTOR '=' EXPR { $$ = new Assign($1, $3); }
       ;

DECLARE : TYPE FACTOR { $$ = new Decleration($1, $2);}
        ;

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
