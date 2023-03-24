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

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_EXPONENT ADD_ASS SUB_ASS NOT
%token T_NUMBER T_VARIABLE
%token INT FLOAT
%token COMMA
%token IF ELSE BREAK CONTINUE SWITCH CASE DEFAULT WHILE FOR RETURN
%token LTE GTE EQUAL NOTEQUAL LOG_AND LOG_OR
%token INCREMENT DECREMENT

%type <expr> EXPR TERM UNARY FACTOR SECTION SEQ DECLARE ARGS TYPE FUNCT FUNCT_CALL ASSIGN CONTROL
%type <number> T_NUMBER
%type <string> T_VARIABLE INT FLOAT

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
      | DECLARE '(' ARGS ')' ';' {$$ = new Empty(); }
      | DECLARE '(' ')' ';' { $$ = new Empty(); }
      ;

FUNCT_CALL : FACTOR '(' ')' { $$ = new FunctCall($1); }
           | FACTOR '(' FACTOR ')' { $$ = new FunctCallwArgs($1, $3); }
           | FACTOR '(' ARGS ')' { $$ = new FunctCallwArgs($1, $3); }
           ;

CONTROL : IF '(' EXPR ')' '{' SEQ '}' ELSE '{' SEQ '}' { $$ = new IfElseControl($3, $6, $10); }
        | IF '(' EXPR ')' '{' SEQ '}' { $$ = new IfControl($3, $6); }
        | WHILE '(' EXPR ')' '{' SEQ '}' { $$ = new WhileControl($3, $6 ); }
        | WHILE '(' EXPR ')' '{''}' { $$ = new Empty(); }
        | FOR '(' SECTION SECTION ASSIGN ')' '{' SEQ '}' { $$ = new ForControl($3, $4, $5, $8); }
        | FOR '(' SECTION SECTION EXPR ')' '{' SEQ '}' { $$ = new ForControl($3, $4, $5, $8); }
        | FOR '(' SECTION SECTION ASSIGN ')' '{'  '}' { $$ = new ForControl($3, $4, $5, new Empty()); }
        | FOR '(' SECTION SECTION EXPR ')' '{'  '}' { $$ = new ForControl($3, $4, $5, new Empty()); }
        ;

SECTION : EXPR ';' {$$ = $1;}
        | FUNCT {$$ = $1;}
        | ASSIGN ';' { $$ = $1;}
        | RETURN EXPR ';' { $$ = new Return($2);}
        | DECLARE ';' { $$ = $1; }
        | CONTROL { $$ = $1; }
        ;

ARGS : DECLARE  {$$ = $1;}
     | ARGS COMMA DECLARE {$$ = new Args($1,$3);}
     | FACTOR COMMA FACTOR { $$ = new CallArgs($1, $3); }
     | ARGS COMMA FACTOR { $$ = new CallArgs($1, $3); }
     ;

EXPR : TERM           { $$ = $1; }
     | EXPR T_PLUS TERM  { $$ = new AddOperator($1, $3); }
     | EXPR T_MINUS TERM { $$ = new SubOperator($1, $3); }
     | EXPR '<' TERM     { $$ = new LessThanOperator($1, $3); }
     | EXPR '>' TERM     { $$ = new GreaterThanOperator($1, $3); }
     | EXPR LTE TERM     { $$ = new LessThanEqualOperator($1, $3); }
     | EXPR GTE TERM     { $$ = new GreaterThanEqualOperator($1, $3); }
     | EXPR EQUAL TERM   { $$ = new EqualOperator($1, $3); }
     | EXPR NOTEQUAL TERM   { $$ = new NotEqualOperator($1, $3); }
     | EXPR INCREMENT    { $$ = new Increment($1); }
     | EXPR DECREMENT    { $$ = new Decrement($1); }
     | EXPR LOG_AND TERM { $$ = new LogicalAnd($1, $3); }
     | EXPR LOG_OR TERM { $$ = new LogicalOr($1, $3); }
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
      | NOT FACTOR       { $$ = new NotOperator($2); }
      | FUNCT_CALL       { $$ = $1; }
      ;

FACTOR : T_NUMBER     { $$ = new Number( $1 ); }
       | T_VARIABLE   { $$ = new Variable( *$1 ); }
       | '(' EXPR ')' { $$ = $2; }
       ;

TYPE : INT  {$$ = new Type( *$1 );}
     | FLOAT  { $$ = new Type( *$1 ); }
     ;

ASSIGN : FACTOR '=' EXPR { $$ = new Assign($1, $3); }
       | DECLARE '=' EXPR { $$ = new Assign($1, $3); }
       | EXPR ADD_ASS TERM { $$ = new AddAssign($1, $3); }
       | EXPR SUB_ASS TERM { $$ = new SubAssign($1, $3); }
       ;

DECLARE : TYPE FACTOR { $$ = new Decleration($1, $2); }
        | DECLARE '[' ']' { $$ = new EmptyArrayDecleration($1); }
        | DECLARE '[' EXPR ']' { $$ = new ArrayDecleration($1, $3); }
        ;

%%

const Expression *g_root; //

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
