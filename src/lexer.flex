%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "parser.tab.hpp"
%}

Text [^)]
Letter [A-Za-z]
Num [0-9]

%%

int             {  yylval.string=new std::string(yytext); return INT; }
return          { return RETURN; }

[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }
[,]             { return COMMA; }
[=]             { return '='; }
[\^]            { return '^'; }
[|]            { return '|'; }
[&]            { return '&'; }

[(]             { return T_LBRACKET; }
[)]             { return T_RBRACKET; }
[{]             { return T_LCURLY; }
[}]             { return T_RCURLY; }
[;]             { return ';'; }


[-]?({Num}+)([.]{Num}+)? { yylval.number=strtod(yytext, 0); return T_NUMBER;}

{Letter}+       { yylval.string=new std::string(yytext); return T_VARIABLE; }

[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}
